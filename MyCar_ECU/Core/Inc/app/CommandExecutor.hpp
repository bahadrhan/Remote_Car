#pragma once

#include <cstdint>

#include "app/Command.hpp"
#include "app/Parameters.hpp"

class MotorDriver;
class Lights;

class CommandExecutor
{
public:
    void init(MotorDriver& motor, Lights& lights, Parameters& params);

    void apply(const Command& cmd);


    void stop();


    bool isMoving() const { return moving_; }

private:
    void applyMotion_(CommandType t);
    void applySpeed_(uint8_t percent);
    void applyFeatureToggle_(CommandType t, uint8_t value);

    void updateLights_();

private:
    MotorDriver* motor_ = nullptr;
    Lights*      lights_ = nullptr;
    Parameters*  params_ = nullptr;

    bool moving_ = false;
};
