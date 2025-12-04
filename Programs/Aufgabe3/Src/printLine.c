#include "printLine.h"
#include "LCD_general.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include <stdint.h>

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;

void printLine(uint16_t displayArray[],Coordinate crd){
   int width;
   if(infoHeader.biWidth < displayWidth){
      width = infoHeader.biWidth;
   }else{
      width = displayWidth;
   }
   GUI_WriteLine(crd, width, displayArray);
}