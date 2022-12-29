//
// Created by Ivan Kalesnikau on 29.12.2022.
//

#include "Qpd.hpp"

QPD::QPD(UART_HandleTypeDef *huart, uint8_t *rxBuffer, TIM_HandleTypeDef *timer, uint32_t timerChannel) :
        serial_(Serial(huart, rxBuffer, ';', ',')),
        timer_(Timer(timer, timerChannel, 0))
{
    RetargetInit(huart);
    printf("Started!\n");
    timer_.updateTimerInfo(true);
    if (timer_.setPeriod(1.)) printf("Something went wrong!\n");
    timer_.start();
    disableOpAmps();
}

void QPD::disableOpAmps()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}

void QPD::enableOpAmps()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
}
