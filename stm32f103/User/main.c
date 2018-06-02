#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"

#include "systick.h"
#include "led.h"
#include "lcd1602_i2c.h"

//=============================================================================
// Mode switch -> PC14
//=============================================================================
#define SWITCH_CLK     RCC_APB2Periph_GPIOC
#define SWITCH_PIN     GPIO_Pin_14
#define SWITCH_PORT    GPIOC

void Switch_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(SWITCH_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = SWITCH_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(SWITCH_PORT, &GPIO_InitStructure);
}

uint8_t Switch_State(void)
{
  if (GPIO_ReadInputDataBit(SWITCH_PORT, SWITCH_PIN) == Bit_SET) {
    return 1;
  }
  return 0;
}

int main(void)
{
  uint8_t mode = 0;
  uint32_t prev_tick = 0;
  /* fps = 5, interval = 200ms */ 
  uint32_t interval = 200;
  /* total 1095 frames, 00:03:39 */
  uint32_t frame = 0;

  SysTick_Init_Config();
  LED_Config();
  Switch_Config();
  LCD1602_I2C_Config();

  LED_Off();
  mode = Switch_State();

  delay_ms(1000);
  LCD1602_I2C_Show_Str("", "");
  delay_ms(1000);

  prev_tick = HAL_GetTick();
  while(1) {
    LCD1602_I2C_Play(frame, mode);

    frame++;
    delay_until_ms(&prev_tick, interval);

    if (frame >= 1095) {
      frame = 0;
      delay_ms(1000);
      LCD1602_I2C_Show_Str("", "");
      delay_ms(1000);
      prev_tick = HAL_GetTick();
    }
  }
}
