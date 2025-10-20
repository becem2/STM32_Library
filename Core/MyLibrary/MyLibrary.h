#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include "main.h" // For HAL, GPIO definitions

/*==============================================================================
 * Function Prototypes
 *============================================================================*/

/**
 * @brief  Initialize a GPIO pin for output
 * @param  GPIOx: GPIO port (e.g., GPIOC)
 * @param  GPIO_Pin: GPIO pin (e.g., GPIO_PIN_13)
 * @retval None
 */
void MyLib_PinInit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief  Toggle the state of a GPIO pin
 * @param  GPIOx: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval None
 */
void MyLib_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief  Set a GPIO pin HIGH
 * @param  GPIOx: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval None
 */
void MyLib_SetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief  Set a GPIO pin LOW
 * @param  GPIOx: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval None
 */
void MyLib_ResetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief  Read the state of a GPIO pin
 * @param  GPIOx: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval GPIO_PIN_SET or GPIO_PIN_RESET
 */
GPIO_PinState MyLib_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief  Switch pin state (HIGH -> LOW, LOW -> HIGH)
 * @param  GPIOx: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval None
 */
void MyLib_SwitchPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* MY_LIBRARY_H */
