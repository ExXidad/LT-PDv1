//
// Created by Ivan Kalesnikau on 29.12.2022.
//

#ifndef LT_PD_TIMER_HPP
#define LT_PD_TIMER_HPP

#include "tim.h"
#include <stdio.h>
#include <cmath>

struct Timer
{
    TIM_HandleTypeDef *timer_ = nullptr;
    uint32_t timerChannel_ = 0u;
    uint32_t timerFCLK_ = 0u, timerARR_ = 0u, timerCCR_ = 0u, timerPSC_ = 0u;
    uint16_t bitDepth_=0u;

    void updateTimerInfo(const bool &print = false);
    volatile uint32_t *timChannelToCCR(TIM_HandleTypeDef *tim, const uint32_t &timChannel);

    Timer() = default;
    Timer(TIM_HandleTypeDef *timer, uint32_t timerChannel, uint16_t bitDepth=16u);
    void start();
    void stop();
    void writePWM(const uint32_t &pwmFreq, const double &dutyCycle);
    int setPeriod(const double period);
};

bool operator==(const Timer& timerClass, const TIM_HandleTypeDef *timer);

#endif //LT_PD_TIMER_HPP
