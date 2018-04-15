#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"

#include "systick.h"
#include "led.h"
#include "lcd1602_i2c.h"

int main(void)
{
  uint32_t prev_tick = 0;
  /* fps = 5, interval = 200ms */ 
  uint32_t interval = 200;
  /* total 1095 frames, 00:03:39 */
  uint32_t frame = 0;

  SysTick_Init_Config();
  LED_Config();
  LCD1602_I2C_Config();

  LED_Off();
  delay_ms(1000);
  LCD1602_I2C_Show_Str("", "");
  delay_ms(1000);

  prev_tick = HAL_GetTick();
  while(1) {
    LCD1602_I2C_Play(frame);

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
