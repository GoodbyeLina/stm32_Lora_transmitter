#ifndef __LORA_H
#define __LORA_H

#include "main.h"

/* 硬件引脚宏定义：方便修改硬件连接 */
#define LORA_M0_PORT    GPIOE
#define LORA_M0_PIN     GPIO_PIN_2
#define LORA_M1_PORT    GPIOE
#define LORA_M1_PIN     GPIO_PIN_3

// 1. 先定义枚举
typedef enum {
    LORA_MODE_NORMAL = 0,
    LORA_MODE_WAKEUP = 1,
    LORA_MODE_POWER  = 2,
    LORA_MODE_CFG    = 3
} LoRa_Mode_t;

// 2. 再声明函数
void LoRa_SetMode(LoRa_Mode_t mode);
void LoRa_SendString(char *str);


#endif
