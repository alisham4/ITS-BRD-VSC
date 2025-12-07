#include "printLine.h"
#include "LCD_general.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "readBitMap.h"
#include <stdint.h>
#include "minimizePicture.h"

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
extern RGBQUAD palette[256];

uint8_t linesArray[5][5*480];
uint16_t displayArray[480];

extern MinimizeState minState;
//extern int box_size;

//extern bool tooBig;
//extern int loopY;

void putPixel(int x, uint8_t farbIndex)
{
   if(!minState.tooBig) {
      displayArray[x] = farbeUmwandeln(palette[farbIndex]);
   }
   else {
      linesArray[minState.loopY][x] = farbIndex;
   }
}

void printLine(uint16_t displayArray[],Coordinate crd){
   if(!minState.tooBig) {
      int width;
      if(infoHeader.biWidth < displayWidth){
         width = infoHeader.biWidth;
      }else{
         width = displayWidth;
      }
      GUI_WriteLine(crd, width, displayArray);
   }
   else {
      minimizeLine();
   }
}