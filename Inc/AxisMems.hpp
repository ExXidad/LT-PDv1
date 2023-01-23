//
// Created by Ivan Kalesnikau on 22.01.2023.
//

#ifndef LT_PD_AXISMEMS_HPP
#define LT_PD_AXISMEMS_HPP

#include "gpio.h"
#include "tim.h"
#include "Timer.hpp"
#include "adc.h"
#include "spi.h"

#include <array>
#include "RegularMeshInterpolator.hpp"

#define DEG2RAD 0.0174533
#define RAD2DEG 57.2958

class AxisMEMS
{
private:

public:
    Timer timer_;
    double zeroPoint_;
    double slope_, const_, inversedSlope_;
    double maxVoltageDifference_;
    RegularMeshLinearInterpolator *voltageDifferenceToAngleInterpolator_;

public:
    AxisMEMS(
            TIM_HandleTypeDef *timer, uint32_t timerChannel,
            const double zeroPoint, const double slope, const double const__,
            const double maxVoltageDifference,
            RegularMeshLinearInterpolator &voltageDifferenceToAngleInterpolator
    );

    ~AxisMEMS();

    void start();

    void stop();

    void zero();

    bool setVoltageDifference(const double voltageDifference); // Returns false if out of limits

    bool setAngle(const double angle, const bool rad = false);
};


#endif //LT_PD_AXISMEMS_HPP
