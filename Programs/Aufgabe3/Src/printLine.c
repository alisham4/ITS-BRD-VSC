#include "LCD_general.h"
#include "uncompressed.h"
#include "BMP_types.h"
#include "readBitMap.h"
#include "LCD_GUI.h"
#include "headers.h"
#include "input.h"
#include <stdint.h>


extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;

int width;

void printLine(uint16_t displayArray[],Coordinate crd){

       if(infoHeader.biWidth < displayWidth){
               width = infoHeader.biWidth;
            }else{
               width = displayWidth;
            }
            GUI_WriteLine(crd, width, displayArray);
}