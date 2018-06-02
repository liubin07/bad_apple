#ifndef __LCD1602_I2C_H
#define __LCD1602_I2C_H

void LCD1602_I2C_Config(void);
void LCD1602_I2C_Show_Str(char *str0, char *str1);
void LCD1602_I2C_Play(uint32_t frame, uint8_t mode);

#endif
