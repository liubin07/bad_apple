#include "stm32f10x.h"
#include "led.h"
#include "systick.h"

//=============================================================================
// LED -> PC13
//=============================================================================
#define LED_CLK     RCC_APB2Periph_GPIOC
#define LED_PIN     GPIO_Pin_13
#define LED_PORT    GPIOC

void LED_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

  /* Configure PC13 in output push pull mode */
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void LED_Off(void)
{
  GPIO_SetBits(LED_PORT, LED_PIN);
}

void LED_On(void)
{
  GPIO_ResetBits(LED_PORT, LED_PIN);
}

void LED_Blink(uint8_t count)
{
  uint8_t bit = GPIO_ReadOutputDataBit(LED_PORT, LED_PIN);
  for (uint8_t i = 0; i < (count + count); i++) {
    bit = (bit == 0 ? 1 : 0);
    GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction)bit);
    delay_ms(500);
  }
}

