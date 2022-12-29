//
// Created by Ivan Kalesnikau on 28.12.2022.
//
#include "myMain.hpp"

uint8_t rxBuffer[MAXMESSAGELENGTH];
QPD qpd;

[[noreturn]] int myMain()
{

//    laserController = LaserController(&huart3, rxBuffer, &htim2, TIM_CHANNEL_4);
    qpd = QPD(&huart1, rxBuffer, &htim4, TIM_CHANNEL_1);

    while (1)
    {
//        laserController.pasteThisToMainLoop();
//        HAL_Delay();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//    laserController.pasteThisToRxCpltCallback();
}

uint counter = 0u;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (qpd.timer_ == htim)
    {
    printf("%u", ++counter);
    printf("\n");
    }
}
