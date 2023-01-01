//
// Created by Ivan Kalesnikau on 29.12.2022.
//

#include "Qpd.hpp"

QPD::QPD(TIM_HandleTypeDef *timer, uint32_t timerChannel,
         uint32_t *pdMeasurements) :
        timer_(Timer(timer, timerChannel, 0)),
        pdMeasurements_(pdMeasurements)
{
    printf("Started QPD.\n");
}

void QPD::disableOpAmps()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}

void QPD::enableOpAmps()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
}

void QPD::calibrate()
{
    printf("Calibrating adc's\n");
    for (int i = 0; i < 4; ++i) // Stop adcs
        HAL_ADC_Stop(adcs[i]);
    for (int i = 0; i < 4; ++i) // Calibration
        HAL_ADCEx_Calibration_Start(adcs[i], ADC_SINGLE_ENDED);
    printf("Calibration values: ");
    for (int i = 0; i < 4; ++i)
        printf("%lu\t",HAL_ADCEx_Calibration_GetValue(adcs[i], ADC_SINGLE_ENDED));
    printf("\n");
//
//
//    uint measNumber = 0;
//    while (true)
//    {
//        for (int i = 0; i < 4; ++i) // Start adcs
//            HAL_ADC_Start_DMA(adcs[i], &pdMeasurements_[i], 1);
//        printf("i was here");
//
//        printf("Measurement %d: ", ++measNumber); // Print
//        for (int i = 0; i < 4; ++i)
//            printf("%lX ", pdMeasurements_[i]);
//        printf("\n");
//        HAL_Delay(100);
//    }
}


