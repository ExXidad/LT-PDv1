//
// Created by Ivan Kalesnikau on 28.12.2022.
//

#ifndef LT_PD_MYMAIN_HPP
#define LT_PD_MYMAIN_HPP

#include "usart.h"
#include <cstring>
#include <stdio.h>
#include "Qpd.hpp"
#include "retarget.h"

//constexpr uint8_t MAXMESSAGELENGTH = 256;

[[noreturn]] int myMain();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#endif //LT_PD_MYMAIN_HPP
