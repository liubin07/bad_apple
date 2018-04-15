#ifndef __SYSTICK_H
#define __SYSTICK_H

void SysTick_Init_Config(void);
uint32_t HAL_GetTick(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
void delay_10us(__IO uint32_t delay);
void delay_ms(__IO uint32_t delay);
void delay_s(__IO uint32_t delay);
void delay_until_ms(uint32_t *prev_tick, uint32_t delay);

#endif
