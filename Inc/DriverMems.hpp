//
// Created by Ivan Kalesnikau on 22.01.2023.
//

#ifndef LT_PD_DRIVERMEMS_HPP
#define LT_PD_DRIVERMEMS_HPP

#include "AxisMems.hpp"
#include "Timer.hpp"
#include "GPIO.hpp"

class DriverMEMS
{
private:

public:
    AxisMEMS *xAxis_, *yAxis_;
    Timer clkTimer_;
    GPIO enblGPIO_;

public:
    ~DriverMEMS();
    DriverMEMS(TIM_HandleTypeDef *clkHtim, const uint32_t clkHtimChannel,
               GPIO_TypeDef *enblPort, const uint16_t enblPin,
               AxisMEMS &xAxis, AxisMEMS &yAxis);

    void start();

    void stop();
};


#endif //LT_PD_DRIVERMEMS_HPP
