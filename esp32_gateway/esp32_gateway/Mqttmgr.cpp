#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "Config.h"
#include "MqttMgr.h"
#include "UartLink.h"

static WiFiClient espClient;
static PubSubClient mqtt(espClient);


static void onMqtt(char* topic, byte* payload, unsigned int len)
{
  if (len == 0) return;

  char c = (char)payload[0];   // first byte only
  UartLink::sendByte(c);

  Serial.print("MQTT->UART: ");
  Serial.println(c);
}

static void connectMqtt_()
{
  mqtt.setServer(MQTT_BROKER, MQTT_PORT);
  mqtt.setCallback(onMqtt);

  while (!mqtt.connected())
  {
    Serial.print("MQTT connecting to ");
    Serial.print(MQTT_BROKER);
    Serial.print(":");
    Serial.println(MQTT_PORT);

    if (mqtt.connect("esp32_gateway"))
    {
      Serial.println("MQTT connected.");
      mqtt.subscribe(TOPIC_CMD);
      mqtt.publish(TOPIC_TEL, "ESP32 GATEWAY CONNECTED");
    }
    else
    {
      Serial.print("MQTT connect failed, state=");
      Serial.println(mqtt.state());
      delay(1000);
    }
  }
}

void MqttMgr::init()
{
  connectMqtt_();
}

void MqttMgr::loop()
{
  if (!mqtt.connected())
  {
    connectMqtt_();
  }

  mqtt.loop();

  char line[256];
  if (UartLink::popLine(line, sizeof(line)))
  {
    mqtt.publish(TOPIC_TEL, line);
    Serial.print("UART->MQTT: ");
    Serial.println(line);
  }
}
