#include "stm32f10x.h"
#include "systick.h"

#define HAL_MAX_DELAY      0xFFFFFFFFU
__IO uint32_t uwTick = 0;

/*
 * 1. SystemCoreClock / 1000       1ms
 * 2. SystemCoreClock / 100000     10us
 * 3. SystemCoreClock / 1000000    1us
 */
void SysTick_Init_Config(void)
{
  while (SysTick_Config(SystemCoreClock / 100000));
}

void HAL_IncTick(void)
{
  uwTick++;
}

uint32_t HAL_GetTick(void)
{
  return uwTick;
}

void HAL_SuspendTick(void)
{
  /* Disable SysTick Interrupt */
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

void HAL_ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

void delay_10us(__IO uint32_t delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = delay;
  
  /* Add a period to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY) {
     wait++;
  }
  
  while ((HAL_GetTick() - tickstart) < wait);
}

void delay_ms(__IO uint32_t delay)
{
  delay_10us(delay * 100);
}

void delay_s(__IO uint32_t delay)
{
  delay_10us(delay * 100000);
}

void delay_until_ms(uint32_t *prev_wake_tick, uint32_t delay)
{
  uint32_t cur_tick;
  uint32_t wait = delay * 100;
  if (wait < HAL_MAX_DELAY) {
     wait++;
  }
  while (1) {
    cur_tick = HAL_GetTick();
    if ((cur_tick - *prev_wake_tick) >= wait) {
      break;
    }
  }
  *prev_wake_tick = cur_tick;
}

