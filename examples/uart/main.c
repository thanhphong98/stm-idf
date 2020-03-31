#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"
#include "uart.h"

#define TASK_SIZE   1024
#define TASK_PRIOR  5

static const char *TAG = "APP_MAIN";

static void system_clock_init(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

static void uart_example_task(void* arg)
{
    uart_config_t uart_config;
    uart_config.uart_num = UART_NUM_4;
    uart_config.uart_pins_pack = UART_PINS_PACK_1;
    uart_config.baudrate = 115200;
    uart_config.frame_format = UART_FRAME_8N1;
    uart_config.mode = UART_TRANSFER_MODE_TX_RX;
    uart_config.hw_flw_ctrl = UART_HW_FLW_CTRL_NONE;
    uart_init(&uart_config);
    STM_LOGI(TAG, "UART init complete");

    while(1)
    {
        uart_write_bytes(UART_NUM_4, (uint8_t *)"Welcome to STM-IDF \r\n", 21,100);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    HAL_Init();
    system_clock_init();
    stm_log_init();

    stm_log_level_set("*", STM_LOG_NONE);
    stm_log_level_set("APP_MAIN", STM_LOG_INFO);

    xTaskCreate(uart_example_task, "uart_example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);
    vTaskStartScheduler();
}