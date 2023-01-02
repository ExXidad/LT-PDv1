//
// Created by Ivan Kalesnikau on 28.12.2022.
//
#include "myMain.hpp"

uint8_t rxBuffer[MAXMESSAGELENGTH];
uint32_t pdMeasurements[4];
constexpr uint16_t bufSize = 16;
uint16_t buffer[4][bufSize]{};
QPD qpd;
ADC_HandleTypeDef *adcs[4]{&hadc1, &hadc2, &hadc3, &hadc4};
char readyToRead = 0;// 8 bit 0000 1111

void startADC()
{
    for (int i = 0; i < 4; ++i)
        HAL_ADC_Start_DMA(adcs[i], (uint32_t *) buffer[i], bufSize);
}


[[noreturn]] int myMain()
{
    RetargetInit(&huart1);

    qpd = QPD(&htim4, TIM_CHANNEL_1, pdMeasurements);
//    qpd.enableOpAmps();
//    qpd.calibrate();

    startADC();
//    for (int i = 0; i < 4; ++i)
//    {
//        HAL_ADC_Start_IT(adcs[i]);
//    }

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    qpd.enableOpAmps();


    while (1)
    {
//        printf("%X\n",readyToRead);
//        HAL_Delay(100);
//        printf("asked\n");
//        HAL_ADC_Start_DMA(&hadc1,(uint32_t *)pdbuf,4);
//        for (int i = 0; i < 4; ++i) // Start adcs
//            HAL_ADC_Start_DMA(adcs[i], pdVals[i], 1);
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
//    printf("%u", ++counter);
//    printf("\n");
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    // Set flag for each adc available to read
    for (int i = 0; i < 4; ++i)
        if (hadc == adcs[i])
            readyToRead |= (1 << i);
    if (readyToRead == 0xF)
    {
//        startADC();
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < bufSize; ++j)
                printf("%hu ", buffer[i][j]);
        printf("\t");
//            printf("%lu\t", HAL_ADC_GetValue(adcs[i]));
        printf("\n");
        readyToRead = 0;
    }
}