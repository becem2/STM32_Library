#include "MyLibrary.h"

/*==============================================================================
 * Initialize a GPIO pin as output
 *============================================================================*/

/*==============================================================================
 * Toggle the state of a GPIO pin
 *============================================================================*/
void MyLib_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}

/*==============================================================================
 * Set a GPIO pin HIGH
 *============================================================================*/
void MyLib_SetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

/*==============================================================================
 * Set a GPIO pin LOW
 *============================================================================*/
void MyLib_ResetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

/*==============================================================================
 * Read the state of a GPIO pin
 *============================================================================*/
GPIO_PinState MyLib_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/*==============================================================================
 * Switch pin state (HIGH -> LOW, LOW -> HIGH)
 *============================================================================*/
void MyLib_SwitchPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  GPIO_PinState state = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
  if (state == GPIO_PIN_SET)
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
  else
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}
