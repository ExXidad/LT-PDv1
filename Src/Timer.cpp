//
// Created by Ivan Kalesnikau on 29.12.2022.
//

#include "Timer.hpp"

void Timer::updateTimerInfo(const bool &print)
{
    ARR_ = timer_->Instance->ARR;
    CCR_ = *timChannelToCCR(timer_, channel_);
    PSC_ = timer_->Instance->PSC;
    FCLK_ = HAL_RCC_GetPCLK2Freq();

    if (print)
    {
        printf("PCLK 2 freq: %lu\n", FCLK_);
        printf("PWM timer ARR: %lu\n", ARR_);
        printf("PWM timer CCR: %lu\n", CCR_);
        printf("PWM timer PSC: %lu\n", PSC_);
    }
}

volatile uint32_t *Timer::timChannelToCCR(TIM_HandleTypeDef *tim, const uint32_t &timChannel)
{
    switch (timChannel)
    {
        case TIM_CHANNEL_1:
            return &(tim->Instance->CCR1);
        case TIM_CHANNEL_2:
            return &(tim->Instance->CCR2);
        case TIM_CHANNEL_3:
            return &(tim->Instance->CCR3);
        case TIM_CHANNEL_4:
            return &(tim->Instance->CCR4);
        default:
            return nullptr;
    }
}

void Timer::start()
{
    HAL_TIM_Base_Start_IT(timer_);
    HAL_TIM_Base_Start(timer_);
}

void Timer::stop()
{
    HAL_TIM_Base_Stop(timer_);
    HAL_TIM_Base_Stop_IT(timer_);
}

Timer::Timer(TIM_HandleTypeDef *timer, uint32_t timerChannel, uint16_t bitDepth) :
        timer_(timer),
        channel_(timerChannel),
        bitDepth_(bitDepth)
{
    updateTimerInfo(false);
}


void Timer::setPWM(const uint32_t &pwmFreq, const double dutyCycle)
{
    timer_->Instance->ARR = 1. * FCLK_ / pwmFreq / (1 + PSC_) - 1.;
    *timChannelToCCR(timer_, channel_) = dutyCycle * (1. * FCLK_ / pwmFreq / (1 + PSC_) - 1.);
    updateTimerInfo();
}

void Timer::setPeriod(const uint32_t &arr, const uint32_t &psc)
{
    timer_->Instance->ARR = arr;
    timer_->Instance->PSC = psc;
    updateTimerInfo();
}

void Timer::startPWM()
{
    HAL_TIM_PWM_Start(timer_, channel_);
}

void Timer::stopPWM()
{
    HAL_TIM_PWM_Stop(timer_, channel_);
}

void Timer::setDuty(const double dutyCycle)
{
    *timChannelToCCR(timer_, channel_) = (dutyCycle > 1. ? 1. : (dutyCycle < 0 ? 0. : dutyCycle)) * ARR_;
    updateTimerInfo();
}


bool operator==(const Timer &timerClass, const TIM_HandleTypeDef *timer)
{
    return timerClass.timer_ == timer;
}