from flask import Flask, render_template, jsonify, Response
import paho.mqtt.client as mqtt
import re
import threading
import time

MQTT_BROKER = "localhost"
MQTT_PORT = 1883
TOPIC_CMD = "car/cmd"
TOPIC_TEL = "car/telemetry"

app = Flask(__name__)

_last_front = None
_last_rear = None
_last_ts = None
_lock = threading.Lock()

_dist_re = re.compile(r"\bD\s+F=(-?\d+)\s+R=(-?\d+)\b")

mqtt_client = mqtt.Client()

def on_connect(client, userdata, flags, rc):
    print("MQTT connected, rc =", rc)
    client.subscribe(TOPIC_TEL)

def on_message(client, userdata, msg):
    global _last_front, _last_rear, _last_ts
    try:
        text = msg.payload.decode("utf-8", errors="ignore").strip()
        m = _dist_re.search(text)
        if m:
            f = int(m.group(1))
            r = int(m.group(2))
            with _lock:
                _last_front = f
                _last_rear = r
                _last_ts = time.time()
    except Exception as e:
        print("MQTT parse error:", e)

mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message
mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)
mqtt_client.loop_start()

def send_cmd(cmd: str):
    if not cmd:
        return
    mqtt_client.publish(TOPIC_CMD, cmd)
    print(f"CMD -> {cmd}")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/cmd/<c>")
def cmd(c):
    send_cmd(c)
    return Response(status=204)

@app.route("/sensors.json")
def sensors_json():
    with _lock:
        f = _last_front
        r = _last_rear
        ts = _last_ts
    age_ms = None
    if ts is not None:
        age_ms = int((time.time() - ts) * 1000.0)
    return jsonify({"front_mm": f, "rear_mm": r, "age_ms": age_ms})

@app.route("/telemetry.json")
def telemetry_json():
    return sensors_json()

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
