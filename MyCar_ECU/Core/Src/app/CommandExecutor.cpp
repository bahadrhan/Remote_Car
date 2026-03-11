/*
 * CommandExecutor.cpp
 *
 *  Created on: Feb 2, 2026
 *      Author: bahad
 */

#include "app/CommandExecutor.hpp"

#include "app/MotorDriver.hpp"
#include "app/Lights.hpp"

static inline uint8_t clamp0_100(uint8_t v)
{
    return (v > 100) ? 100 : v;
}

void CommandExecutor::init(MotorDriver& motor, Lights& lights, Parameters& params)
{
    motor_  = &motor;
    lights_ = &lights;
    params_ = &params;

    motor_->setSpeedPercent(clamp0_100(params_->defaultSpeedPercent));
    stop();
}

void CommandExecutor::apply(const Command& cmd)
{
    if (!motor_ || !params_) return;

    switch (cmd.type)
    {
        case CommandType::SetSpeed:
            params_->defaultSpeedPercent = cmd.value;
            motor_->setSpeedPercent(cmd.value);
            break;

        case CommandType::Forward:
            moving_ = true;
            motor_->forward();
            break;

        case CommandType::Backward:
            moving_ = true;
            motor_->back();
            break;

        case CommandType::TurnLeft:
            moving_ = true;
            motor_->spinLeft();
            break;

        case CommandType::TurnRight:
            moving_ = true;
            motor_->spinRight();
            break;

        case CommandType::Stop:
            moving_ = false;
            motor_->stop();
            break;

        case CommandType::EnableLights:
            params_->lightsEnabled = (cmd.value != 0);
            break;

        case CommandType::SetHeadlight:
            params_->headlightOn = (cmd.value != 0);
            break;

        case CommandType::SetBrakelight:
            params_->brakelightOn = (cmd.value != 0);
            break;

        case CommandType::EnableSensors:
            params_->sensorsEnabled = (cmd.value != 0);
            break;

        case CommandType::EnableAutoMode:
            params_->autoModeEnabled = (cmd.value != 0);
            break;

        default:
            break;
    }


    updateLights_();
}


void CommandExecutor::stop()
{
    if (!motor_ || !lights_ || !params_)
        return;

    motor_->stop();
    moving_ = false;
    updateLights_();
}

void CommandExecutor::applyMotion_(CommandType t)
{
    if (!motor_ || !params_)
        return;


    motor_->setSpeedPercent(clamp0_100(params_->defaultSpeedPercent));

    switch (t)
    {
        case CommandType::Forward:
            motor_->forward();
            moving_ = true;
            break;

        case CommandType::Backward:
            motor_->back();
            moving_ = true;
            break;

        case CommandType::TurnLeft:
            motor_->spinLeft();
            moving_ = true;
            break;

        case CommandType::TurnRight:
            motor_->spinRight();
            moving_ = true;
            break;

        case CommandType::Stop:
        default:
            motor_->stop();
            moving_ = false;
            break;
    }
}

void CommandExecutor::applySpeed_(uint8_t percent)
{
    if (!motor_ || !params_)
        return;

    params_->defaultSpeedPercent = clamp0_100(percent);
    motor_->setSpeedPercent(params_->defaultSpeedPercent);
}

void CommandExecutor::applyFeatureToggle_(CommandType t, uint8_t value)
{
    if (!params_)
        return;

    const bool en = (value != 0);

    switch (t)
    {
        case CommandType::EnableLights:
            params_->lightsEnabled = en;
            break;

        case CommandType::EnableSensors:
            params_->sensorsEnabled = en;
            break;

        case CommandType::EnableAutoMode:
            params_->autoModeEnabled = en;
            break;

        default:
            break;
    }
}

void CommandExecutor::updateLights_()
{
    if (!lights_ || !params_) return;

    if (!params_->lightsEnabled)
    {

        lights_->setHeadlight(false);
        lights_->setStoplight(false);
        return;
    }


    lights_->setHeadlight(params_->headlightOn);

    bool brake = params_->brakelightOn || (!moving_);
    lights_->setStoplight(brake);
}




