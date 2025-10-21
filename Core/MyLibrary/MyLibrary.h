#ifndef MY_SUPER_LIB_H
#define MY_SUPER_LIB_H

#include "stm32f4xx.h"
#include <stdint.h>

void MyLib_SystemClockInit(void);
void MyLib_PinInit(GPIO_TypeDef *GPIOx, uint8_t pin);
void MyLib_TogglePin(GPIO_TypeDef *GPIOx, uint8_t pin);
void MyLib_SetPin(GPIO_TypeDef *GPIOx, uint8_t pin);
void MyLib_ResetPin(GPIO_TypeDef *GPIOx, uint8_t pin);
uint8_t MyLib_ReadPin(GPIO_TypeDef *GPIOx, uint8_t pin);
void MyLib_SwitchPin(GPIO_TypeDef *GPIOx, uint8_t pin);
void MyLib_Delay_ms(uint32_t ms);
void MyLib_TimerInit(void);
uint32_t MyLib_GetTime_ms(void);
void MyLib_BlinkMorse(GPIO_TypeDef *GPIOx, uint8_t pin, const char *message);

#endif
