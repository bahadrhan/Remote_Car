#pragma once

#include <cstdint>
#include "stm32f0xx.h"

namespace BoardPins
{

    // Motor driver standby

    inline GPIO_TypeDef* const STBY_PORT = GPIOB;
    inline constexpr uint16_t  STBY_PIN  = (1u << 3);   // PB3


    // Motor direction pins


    // Front Left motor
    inline GPIO_TypeDef* const FL_IN1_PORT = GPIOB;
    inline constexpr uint16_t  FL_IN1_PIN  = (1u << 4); // PB4
    inline GPIO_TypeDef* const FL_IN2_PORT = GPIOB;
    inline constexpr uint16_t  FL_IN2_PIN  = (1u << 5); // PB5

    // Rear Left motor
    inline GPIO_TypeDef* const RL_IN1_PORT = GPIOB;
    inline constexpr uint16_t  RL_IN1_PIN  = (1u << 6); // PB6
    inline GPIO_TypeDef* const RL_IN2_PORT = GPIOB;
    inline constexpr uint16_t  RL_IN2_PIN  = (1u << 7); // PB7

    // Front Right motor
    inline GPIO_TypeDef* const FR_IN1_PORT = GPIOB;
    inline constexpr uint16_t  FR_IN1_PIN  = (1u << 8); // PB8
    inline GPIO_TypeDef* const FR_IN2_PORT = GPIOB;
    inline constexpr uint16_t  FR_IN2_PIN  = (1u << 9); // PB9

    // Rear Right motor
    inline GPIO_TypeDef* const RR_IN1_PORT = GPIOB;
    inline constexpr uint16_t  RR_IN1_PIN  = (1u << 10); // PB10
    inline GPIO_TypeDef* const RR_IN2_PORT = GPIOB;
    inline constexpr uint16_t  RR_IN2_PIN  = (1u << 11); // PB11

    // Convenience masks (all on GPIOB)
    inline constexpr uint16_t LEFT_IN1_MASK  = FL_IN1_PIN | RL_IN1_PIN;
    inline constexpr uint16_t LEFT_IN2_MASK  = FL_IN2_PIN | RL_IN2_PIN;
    inline constexpr uint16_t RIGHT_IN1_MASK = FR_IN1_PIN | RR_IN1_PIN;
    inline constexpr uint16_t RIGHT_IN2_MASK = FR_IN2_PIN | RR_IN2_PIN;


    // Ultrasonic sensors (HC-SR04)


    // Front ultrasonic
    inline GPIO_TypeDef* const US_ECHO_PORT = GPIOA;
    inline constexpr uint16_t  US_ECHO_PIN  = (1u << 0); // PA0
    inline GPIO_TypeDef* const US_TRIG_PORT = GPIOA;
    inline constexpr uint16_t  US_TRIG_PIN  = (1u << 1); // PA1

    // Rear ultrasonic
    inline GPIO_TypeDef* const US_REAR_TRIG_PORT = GPIOC;
    inline constexpr uint16_t  US_REAR_TRIG_PIN  = (1u << 0); // PC0
    inline GPIO_TypeDef* const US_REAR_ECHO_PORT = GPIOC;
    inline constexpr uint16_t  US_REAR_ECHO_PIN  = (1u << 1); // PC1

    // Lights


    // Headlight - PA5
    inline GPIO_TypeDef* const HEADLIGHT_PORT = GPIOA;
    inline constexpr uint16_t  HEADLIGHT_PIN  = (1u << 5); // PA5

    // Stop light - PA4
    inline GPIO_TypeDef* const STOPLIGHT_PORT = GPIOA;
    inline constexpr uint16_t  STOPLIGHT_PIN  = (1u << 4); // PA4


    // UART (USART1)
    inline GPIO_TypeDef* const UART_PORT  = GPIOA;
    inline constexpr uint16_t  UART_TX_PIN = (1u << 9);   // PA9
    inline constexpr uint16_t  UART_RX_PIN = (1u << 10);  // PA10
    inline USART_TypeDef* const UART = USART1;


    // Blue user button (active LOW)
    inline GPIO_TypeDef* const BTN_PORT = GPIOC;
    inline constexpr uint16_t  BTN_PIN  = (1u << 13); // PC13


    // PWM outputs (TIM3): CH1 PA6, CH2 PA7, CH3 PB0, CH4 PB1
    inline GPIO_TypeDef* const PWM_CH1_PORT = GPIOA;
    inline constexpr uint16_t  PWM_CH1_PIN  = (1u << 6); // PA6

    inline GPIO_TypeDef* const PWM_CH2_PORT = GPIOA;
    inline constexpr uint16_t  PWM_CH2_PIN  = (1u << 7); // PA7

    inline GPIO_TypeDef* const PWM_CH3_PORT = GPIOB;
    inline constexpr uint16_t  PWM_CH3_PIN  = (1u << 0); // PB0

    inline GPIO_TypeDef* const PWM_CH4_PORT = GPIOB;
    inline constexpr uint16_t  PWM_CH4_PIN  = (1u << 1); // PB1
}
