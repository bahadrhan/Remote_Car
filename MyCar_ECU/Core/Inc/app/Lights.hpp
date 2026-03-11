#pragma once
#include <cstdint>

enum class LightMode : uint8_t
{
    Auto = 0,
    ForceOn,
    ForceOff
};

struct LightsConfig
{
    LightMode headlight = LightMode::Auto;
    LightMode stoplight = LightMode::Auto;
};

class Lights
{
public:
    void init();

    void enable();
    void disable();
    bool isEnabled() const;

    void setConfig(const LightsConfig& cfg);

    void apply(bool moving);

    void setHeadlight(bool on);
    void setStoplight(bool on);

    void allOff();

private:
    void applyOne_(LightMode mode, bool autoValue, bool isHeadlight);
    void write_(bool isHeadlight, bool on);

private:
    LightsConfig cfg_{};
    bool enabled_ = true;
};
