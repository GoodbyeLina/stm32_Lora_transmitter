/* lora.c */
#include "main.h"
#include "lora.h"
#include "usart.h"
#include <string.h>

void LoRa_SetMode(LoRa_Mode_t mode) {
    // 切换前建议等待 AUX 引脚变高（如果连接了的话），或者简单 Delay
    HAL_Delay(10); 
    
    switch(mode) {
        case LORA_MODE_NORMAL:
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
            break;
        case LORA_MODE_CFG:
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
            break;
        // 其他模式按需添加
    }
    
    HAL_Delay(50); // 模式切换后必须留出稳定时间
}
	

/**
  * @brief LoRa 发送字符串并闪烁蓝灯
  */
void LoRa_SendString(char *str) {
    if (str == NULL) return;

    // 1. 发送提示：蓝灯亮 (PF8)
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
    
    // 2. 串口传输：增加对返回值的处理
    if (HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000) != HAL_OK) {
        // 如果发送失败，可以点亮红灯提示错误
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
    }
    
    // 3. 延时并熄灭蓝灯
    HAL_Delay(100); 
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
}
