//
// Created by Ivan Kalesnikau on 29.12.2022.
//

#ifndef LT_PD_QPD_HPP
#define LT_PD_QPD_HPP

#include "Parser.hpp"
#include "Serial.hpp"
#include "retarget.h"
#include "gpio.h"
#include "tim.h"
#include "Timer.hpp"


class QPD
{
public:
    Serial serial_;
    Timer timer_;

public:
    QPD() = default;

    QPD(UART_HandleTypeDef *huart, uint8_t *rxBuffer, TIM_HandleTypeDef *timer,
        uint32_t timerChannel);

    void disableOpAmps();
    void enableOpAmps();

};


#endif //LT_PD_QPD_HPP
