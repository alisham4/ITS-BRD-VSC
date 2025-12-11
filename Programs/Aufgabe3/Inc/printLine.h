#ifndef _PRINTLINE_H
#define _PRINTLINE_H
#include "stdint.h"
#include "LCD_GUI.h"

#define displayWidth 480
#define displayHeight 320

#define MAX_BUFF_SIZE 5
static uint8_t linesArray[MAX_BUFF_SIZE][MAX_BUFF_SIZE*480];
/**
* print line by line on display
 */
void printLine(uint16_t  displayArray[],Coordinate crd);

void putPixel(int x, uint8_t farbe);

#endif