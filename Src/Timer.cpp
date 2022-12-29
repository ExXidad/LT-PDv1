//
// Created by Ivan Kalesnikau on 29.12.2022.
//

#include "Timer.hpp"

void Timer::updateTimerInfo(const bool &print)
{
    timerARR_ = timer_->Instance->ARR;
    timerCCR_ = *timChannelToCCR(timer_, timerChannel_);
    timerPSC_ = timer_->Instance->PSC;
    timerFCLK_ = HAL_RCC_GetPCLK2Freq();

    if (print)
    {
        printf("PCLK 2 freq: %lu\n", timerFCLK_);
        printf("PWM timer ARR: %lu\n", timerARR_);
        printf("PWM timer CCR: %lu\n", timerCCR_);
        printf("PWM timer PSC: %lu\n", timerPSC_);
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
        timerChannel_(timerChannel),
        bitDepth_(bitDepth)
{
    updateTimerInfo(false);
}

void Timer::writePWM(const uint32_t &pwmFreq, const double &dutyCycle)
{
    timer_->Instance->ARR = 1. * timerFCLK_ / pwmFreq / (1 + timerPSC_) - 1.;
    *timChannelToCCR(timer_, timerChannel_) = dutyCycle * (1. * timerFCLK_ / pwmFreq / (1 + timerPSC_) - 1.);
    updateTimerInfo(false);
}

int Timer::setPeriod(const double period)
{
    const uint64_t cntMax = std::pow(2, 2 * bitDepth_);
    const uint64_t cnt = period * timerFCLK_;
//    if (cnt > cntMax)
//        return 1; // if period is too large
//    if (cnt < 1)
//        return 2; // if period is too small

    // It can be smarter

    timer_->Instance->PSC = std::pow(2., bitDepth_) * 0.5 - 1;
//    timer_->Instance->PSC = 10;
    timer_->Instance->ARR = 1.*cnt / timer_->Instance->PSC - 1;

    updateTimerInfo(true);

    printf("Asked Period: %d (cnt) \t",cnt);
    printf("Actual period: %d (cnt)\n", 1. * (timerARR_ + 1) * (timerPSC_ + 1));
    return 0;
}

bool operator==(const Timer &timerClass, const TIM_HandleTypeDef *timer)
{
    return timerClass.timer_ == timer;
}