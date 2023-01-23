//
// Created by Ivan Kalesnikau on 22.01.2023.
//

#ifndef LT_PD_REGULARMESHINTERPOLATOR_HPP
#define LT_PD_REGULARMESHINTERPOLATOR_HPP

struct RegularMeshLinearInterpolator
{
    double step_;
    double invStep_;
    double start_;
    double stop_;
    uint32_t size_;
    const double *data_;

    RegularMeshLinearInterpolator(const double start, const double step, const uint32_t size, const double *data) :
            start_(start),
            step_(step),
            invStep_(1. / step),
            data_(data),
            size_(size)
    {
        stop_ = start + size * step_;
    }

    double interpolate(const double x)
    {
        if ((x - start_) <= 0)
            return data_[0];
        else if ((x - stop_) >= 0)
            return data_[size_ - 1];

        uint32_t i = (x - start_) * invStep_;
        double xLeft = start_ + i * step_;
        double dx = x - xLeft;
        double left = data_[i];
        double right = data_[i + 1];
        return left + dx * (right - left) * invStep_;
    }
};

#endif //LT_PD_REGULARMESHINTERPOLATOR_HPP
