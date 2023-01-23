//
// Created by Ivan Kalesnikau on 28.12.2022.
//
#include "myMain.hpp"

uint8_t rxBuffer[MAXMESSAGELENGTH];
uint32_t pdMeasurements[4];
constexpr uint16_t bufferSize = 8;
uint16_t buffer[4][bufferSize]{};
QPD qpd;
ADC_HandleTypeDef *adcs[4]{&hadc1, &hadc2, &hadc3, &hadc4};
char readyToRead = 0; // 8 bit 0000 1111
constexpr uint16_t spiBufferSize = 8;
uint8_t spiTxBuffer[spiBufferSize];
uint8_t spiRxBuffer[spiBufferSize];

[[noreturn]] int myMain()
{
    RetargetInit(&huart1);

    qpd = QPD(&htim4, TIM_CHANNEL_1, pdMeasurements);
//    qpd.enableOpAmps();
//    qpd.calibrate();
    Timer clk(&MEMS_CLK_TIM, MEMS_CLK_TIM_CH);
    Timer timX(&MEMS_X_TIM, MEMS_X_TIM_CH);
    Timer timY(&MEMS_Y_TIM, MEMS_Y_TIM_CH);

    HAL_GPIO_WritePin(MEMS_ENBL_PORT, MEMS_ENBL_PIN, GPIO_PIN_RESET);

    // Start ADC's in DMA mode
    for (int i = 0; i < 4; ++i)
        HAL_ADC_Start_DMA(adcs[i], (uint32_t *) buffer[i], bufferSize);

    // Start regular ADC's
//    for (int i = 0; i < 4; ++i)
//    {
//        HAL_ADC_Start_IT(adcs[i]);
//    }

    // Start ADC timer
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    qpd.enableOpAmps();

    ///////////////////////////////// Start Driver initialization /////////////////////////////////
    RegularMeshLinearInterpolator
            xAxisAngleToVoltageDifferenceInterpolator(-5., 3.44787, MEMS_X_AVD_SIZE, xAxisAngleToVoltageDifference);
    AxisMEMS xAxisMEMS(&MEMS_X_TIM, MEMS_X_TIM_CH,
                       0.523998, 335.029, -175.554, 150.,
                       xAxisAngleToVoltageDifferenceInterpolator);

    RegularMeshLinearInterpolator
            yAxisAngleToVoltageDifferenceInterpolator(-5., 3.44787, MEMS_Y_AVD_SIZE, yAxisAngleToVoltageDifference);
    AxisMEMS yAxisMEMS(&MEMS_Y_TIM, MEMS_Y_TIM_CH,
                       0.512069, -341.271, 174.754, 150.,
                       yAxisAngleToVoltageDifferenceInterpolator);

    DriverMEMS driverMEMS(&MEMS_CLK_TIM, MEMS_CLK_TIM_CH,
                          MEMS_ENBL_PORT, MEMS_ENBL_PIN,
                          xAxisMEMS, yAxisMEMS);

    driverMEMS.start();
    HAL_Delay(3000);
    driverMEMS.stop();

    ///////////////////////////////// Stop Driver initialization /////////////////////////////////

    while (1)
    {
        printf("rx buffer:\n");
        for (int i = 0; i < spiBufferSize; ++i)
            printf("%u ", spiRxBuffer[i]);
        printf("\n");
        printf("tx buffer:\n");
        for (int i = 0; i < spiBufferSize; ++i)
            printf("%u ", spiTxBuffer[i]);
        printf("\n");
        // Test SPI
        HAL_SPI_TransmitReceive_DMA(&hspi1, spiTxBuffer, spiRxBuffer, spiBufferSize);
//        laserController.pasteThisToMainLoop();
        HAL_Delay(1000);
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

    // If all ADC's completed conversions
    if (readyToRead == 0xF)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < bufferSize; ++j)
                printf("%hu ", buffer[i][j]);
        printf("\t");
        printf("\n");

        for (int i = 0; i < spiBufferSize; ++i)
        {
            spiTxBuffer[i] = i + 1;
        }

        readyToRead = 0;
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == &hspi1)
    {
        printf("SPI tx cplt.\n");
    }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == &hspi1)
    {
        printf("PD SPI rx cplt.\n");
    }
    for (int i = 0; i < spiBufferSize; ++i)
    {
        printf("%ld ", spiRxBuffer[i]);
    }
    printf("\n");
}