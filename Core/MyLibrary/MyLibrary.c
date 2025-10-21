#include "MyLibrary.h"

static void MyLib_EnableGPIOClock(GPIO_TypeDef *GPIOx) {
  if (GPIOx == GPIOA)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  else if (GPIOx == GPIOB)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  else if (GPIOx == GPIOC)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  else if (GPIOx == GPIOD)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  else if (GPIOx == GPIOE)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
}

void MyLib_SystemClockInit(void) {
  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY))
    ;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR |= PWR_CR_VOS;
  RCC->PLLCFGR = (8 << RCC_PLLCFGR_PLLM_Pos) | (360 << RCC_PLLCFGR_PLLN_Pos) |
                 (0 << RCC_PLLCFGR_PLLP_Pos) | (RCC_PLLCFGR_PLLSRC_HSE) |
                 (7 << RCC_PLLCFGR_PLLQ_Pos);
  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY))
    ;
  FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN |
               FLASH_ACR_LATENCY_5WS;
  RCC->CFGR = RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
    ;
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
  SystemCoreClock = 180000000;
}

void MyLib_PinInit(GPIO_TypeDef *GPIOx, uint8_t pin) {
  MyLib_EnableGPIOClock(GPIOx);
  GPIOx->MODER &= ~(0x3 << (pin * 2));
  GPIOx->MODER |= (0x1 << (pin * 2));
  GPIOx->OTYPER &= ~(1 << pin);
  GPIOx->OSPEEDR &= ~(0x3 << (pin * 2));
  GPIOx->PUPDR &= ~(0x3 << (pin * 2));
}

void MyLib_TogglePin(GPIO_TypeDef *GPIOx, uint8_t pin) {
  GPIOx->ODR ^= (1 << pin);
}

void MyLib_SetPin(GPIO_TypeDef *GPIOx, uint8_t pin) {
  GPIOx->BSRR = (1 << pin);
}

void MyLib_ResetPin(GPIO_TypeDef *GPIOx, uint8_t pin) {
  GPIOx->BSRR = (1 << (pin + 16));
}

uint8_t MyLib_ReadPin(GPIO_TypeDef *GPIOx, uint8_t pin) {
  return (GPIOx->IDR & (1 << pin)) ? 1 : 0;
}

void MyLib_SwitchPin(GPIO_TypeDef *GPIOx, uint8_t pin) {
  if (MyLib_ReadPin(GPIOx, pin))
    MyLib_ResetPin(GPIOx, pin);
  else
    MyLib_SetPin(GPIOx, pin);
}

void MyLib_Delay_ms(uint32_t ms) {
  volatile uint32_t count;
  uint32_t ticks = (SystemCoreClock / 1000) / 5;

  while (ms--) {
    count = ticks;
    while (count--) {
    }
  }
}

volatile uint32_t MyLib_tick_ms = 0;

void MyLib_TimerInit(void) {
  SysTick->LOAD = (SystemCoreClock / 1000) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |
                  SysTick_CTRL_ENABLE_Msk;
}

uint32_t MyLib_GetTime_ms(void) { return MyLib_tick_ms; }

void SysTick_Handler(void) { MyLib_tick_ms++; }

void MyLib_BlinkMorse(GPIO_TypeDef *GPIOx, uint8_t pin, const char *message) {
  const uint32_t unit = 200;
  while (*message) {
    char c = *message++;
    if (c >= 'a' && c <= 'z')
      c -= 32;

    const char *morse = NULL;
    switch (c) {
    case 'A':
      morse = ".-";
      break;
    case 'B':
      morse = "-...";
      break;
    case 'C':
      morse = "-.-.";
      break;
    case 'D':
      morse = "-..";
      break;
    case 'E':
      morse = ".";
      break;
    case 'F':
      morse = "..-.";
      break;
    case 'G':
      morse = "--.";
      break;
    case 'H':
      morse = "....";
      break;
    case 'I':
      morse = "..";
      break;
    case 'J':
      morse = ".---";
      break;
    case 'K':
      morse = "-.-";
      break;
    case 'L':
      morse = ".-..";
      break;
    case 'M':
      morse = "--";
      break;
    case 'N':
      morse = "-.";
      break;
    case 'O':
      morse = "---";
      break;
    case 'P':
      morse = ".--.";
      break;
    case 'Q':
      morse = "--.-";
      break;
    case 'R':
      morse = ".-.";
      break;
    case 'S':
      morse = "...";
      break;
    case 'T':
      morse = "-";
      break;
    case 'U':
      morse = "..-";
      break;
    case 'V':
      morse = "...-";
      break;
    case 'W':
      morse = ".--";
      break;
    case 'X':
      morse = "-..-";
      break;
    case 'Y':
      morse = "-.--";
      break;
    case 'Z':
      morse = "--..";
      break;
    case '1':
      morse = ".----";
      break;
    case '2':
      morse = "..---";
      break;
    case '3':
      morse = "...--";
      break;
    case '4':
      morse = "....-";
      break;
    case '5':
      morse = ".....";
      break;
    case '6':
      morse = "-....";
      break;
    case '7':
      morse = "--...";
      break;
    case '8':
      morse = "---..";
      break;
    case '9':
      morse = "----.";
      break;
    case '0':
      morse = "-----";
      break;
    case ' ':
      MyLib_Delay_ms(unit * 7);
      continue;
    default:
      continue;
    }

    while (*morse) {
      if (*morse == '.') {
        MyLib_SetPin(GPIOx, pin);
        MyLib_Delay_ms(unit);
        MyLib_ResetPin(GPIOx, pin);
      } else if (*morse == '-') {
        MyLib_SetPin(GPIOx, pin);
        MyLib_Delay_ms(unit * 3);
        MyLib_ResetPin(GPIOx, pin);
      }
    }
  }
}
