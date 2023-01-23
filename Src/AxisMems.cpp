//
// Created by Ivan Kalesnikau on 22.01.2023.
//

#include "AxisMems.hpp"

AxisMEMS::AxisMEMS(TIM_HandleTypeDef *timer, uint32_t timerChannel,
                         const double zeroPoint, const double slope,
                         const double const__, const double maxVoltageDifference,
                         RegularMeshLinearInterpolator &voltageDifferenceToAngleInterpolator) :
        timer_(Timer(timer, timerChannel)),
        zeroPoint_(zeroPoint),
        slope_(slope),
        const_(const__),
        inversedSlope_(1. / slope),
        maxVoltageDifference_(maxVoltageDifference),
        voltageDifferenceToAngleInterpolator_(&voltageDifferenceToAngleInterpolator)
{
    zero();
}

void AxisMEMS::start()
{
    timer_.startPWM();
}

void AxisMEMS::stop()
{
    timer_.stopPWM();
}

AxisMEMS::~AxisMEMS()
{
    stop();
}

void AxisMEMS::zero()
{
    timer_.setDuty(zeroPoint_);
}

bool AxisMEMS::setVoltageDifference(const double voltageDifference)
{
    bool flag = true;
    double duty;
    if (std::fabs(voltageDifference) <= maxVoltageDifference_)
        duty = inversedSlope_ * (voltageDifference - const_);
    else
    {
        duty = inversedSlope_ * (maxVoltageDifference_ * (voltageDifference > 0 ? 1. : -1.) - const_);
        flag = false;
    }

    timer_.setDuty(duty);
    return flag;
}

bool AxisMEMS::setAngle(const double angle, const bool rad)
{
    // TODO: добавить проверку за вылезание из диапазона углов
    double voltageDifference = voltageDifferenceToAngleInterpolator_->interpolate(angle * (rad ? RAD2DEG : 1.));
    return setVoltageDifference(voltageDifference);
}
