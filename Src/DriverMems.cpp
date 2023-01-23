//
// Created by Ivan Kalesnikau on 22.01.2023.
//

#include "DriverMems.hpp"

DriverMEMS::DriverMEMS(TIM_HandleTypeDef *clkHtim, const uint32_t clkHtimChannel,
                       GPIO_TypeDef *enblPort, const uint16_t enblPin,
                       AxisMEMS &xAxis, AxisMEMS &yAxis) :
        clkTimer_(clkHtim, clkHtimChannel),
        enblGPIO_(enblPort, enblPin),
        xAxis_(&xAxis), yAxis_(&yAxis)
{

}

void DriverMEMS::start()
{
    HAL_Delay(100); // Startup delay
    clkTimer_.startPWM(); // Start CLK
    xAxis_->start(); // Enable axes PWM
    yAxis_->start();
    xAxis_->zero(); // Go to origin position
    yAxis_->zero();
    HAL_Delay(100); // Stabilization delay
    enblGPIO_.set(); // Enable HV
}

void DriverMEMS::stop()
{
    xAxis_->zero(); // Go to origin position
    yAxis_->zero();
    HAL_Delay(100); // Stabilization delay
    enblGPIO_.reset(); // Disable HV
    xAxis_->stop(); // Disable axes PWM
    yAxis_->stop();
    clkTimer_.stopPWM(); // Stop CLK
}

DriverMEMS::~DriverMEMS()
{
    stop();
}
