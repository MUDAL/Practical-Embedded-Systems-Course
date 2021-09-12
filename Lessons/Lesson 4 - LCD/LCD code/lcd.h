#ifndef LCD_H
#define LCD_H

extern void LCD_Init(void);
extern void LCD_WriteChar(char data);
extern void LCD_WriteString(char* pData);
extern void LCD_Clear(void);
extern void LCD_SetCursor(uint8_t row,uint8_t column);

#endif //LCD_H
