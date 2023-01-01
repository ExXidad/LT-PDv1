//
// Created by Ivan Kalesnikau on 28.12.2022.
//
#include "myMain.hpp"

uint8_t rxBuffer[MAXMESSAGELENGTH];
uint32_t pdMeasurements[4];
uint32_t pdVal1, pdVal2, pdVal3, pdVal4;
constexpr uint16_t bufSize = 128;
uint16_t buffers[4][bufSize];
uint32_t *pdVals[4]{&pdVal1, &pdVal2, &pdVal3, &pdVal4};
QPD qpd;
ADC_HandleTypeDef *adcs[4]{&hadc1, &hadc2, &hadc3, &hadc4};
char readyToRead = 0;// 8 bit 0000 1111

[[noreturn]] int myMain()
{
    RetargetInit(&huart1);

    qpd = QPD(&htim4, TIM_CHANNEL_1, pdMeasurements);
//    qpd.enableOpAmps();
//    qpd.calibrate();

    for (int i = 0; i < 4; ++i)
    {
        HAL_ADC_Start_IT(adcs[i]);
    }

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    qpd.enableOpAmps();
//    HAL_ADC_Start(&hadc1);
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
//    for (int i = 0; i < 4; ++i)
//        if (adcs[i] == hadc){
//            printf("ADC%d %ld \n",i, HAL_ADC_GetValue(adcs[i]));
//        }
    // Set flag for each adc available to read
    for (int i = 0; i < 4; ++i)
        if (hadc == adcs[i])
            readyToRead |= (1 << i);
    if (readyToRead == 0xF)
    {
        for (int i = 0; i < 4; ++i)
            printf("%lu\t", HAL_ADC_GetValue(adcs[i]));
        printf("\n");
        readyToRead = 0;
    }
//    if (hadc == &hadc1)
//        printf("%lu\n", HAL_ADC_GetValue(&hadc1));
}
