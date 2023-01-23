//
// Created by Ivan Kalesnikau on 23.01.2023.
//

#ifndef LT_PD_GPIO_HPP
#define LT_PD_GPIO_HPP

#include "gpio.h"

struct GPIO
{
    GPIO_TypeDef *port_;
    const uint16_t pin_;

    GPIO() = default;

    GPIO(GPIO_TypeDef *port, const uint16_t pin) : port_(port), pin_(pin) {};

    void set()
    {
        HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_SET);
    }

    void reset()
    {
        HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_RESET);
    }

    void toggle()
    {
        HAL_GPIO_TogglePin(port_, pin_);
    }
};

#endif //LT_PD_GPIO_HPP
