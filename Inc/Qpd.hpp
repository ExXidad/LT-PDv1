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
#include "adc.h"

class QPD
{
public:
    Timer timer_;
    uint32_t *pdMeasurements_;
public:
    QPD() = default;

    QPD(TIM_HandleTypeDef *timer, uint32_t timerChannel,
        uint32_t *pdMeasurements);

    void disableOpAmps();
    void enableOpAmps();

    // ADC section
public:
    ADC_HandleTypeDef *adcs[4]{&hadc1, &hadc2, &hadc3, &hadc4};

    [[noreturn]] void testADC();
};


#endif //LT_PD_QPD_HPP
