#include "printLine.h"
#include "LCD_general.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "readBitMap.h"
#include <stdint.h>
#include "minimizePicture.h"

// Globale Header-Informationen des BMP-Bildes
extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
extern RGBQUAD palette[256];

// Array für die verkleinerten Zeilen (für große Bilder)
// 5 Zeilen-Puffer, jede Zeile bis zu 5*480 Bytes
uint8_t linesArray[5][5*480];
// Array zum speichern der Pixel, die eine Displayzeile bilden
uint16_t displayArray[480];

extern MinimizeState minState;

// Flag zur Steuerung der Zeilenverarbeitung
extern uint8_t flag;

/**
 * Zeichnet ein einzelnes Pixel an Position x.
 * Wenn das Bild klein genug ist, wird die Farbe in 16-Bit RGB565 gewandelt.
 * Wenn das BMP zu groß ist, wird nur der Farbindextyp gespeichert,
 * damit später die Verkleinerungsfunktion darauf zugreifen kann.
 */
void putPixel(int x, uint8_t farbIndex)
{
   if(!minState.tooBig) {
      displayArray[x] = farbeUmwandeln(palette[farbIndex]);
   }
   else {
      linesArray[minState.loopY][x] = farbIndex;
   }
}


/**
 * Schreibt eine komplette Zeile auf das Display oder,
 * falls das Bild zu groß ist, startet die Verkleinerungslogik.
 */
void printLine(uint16_t displayArray[], Coordinate crd){
    if(!minState.tooBig) {
        int width;
        if(infoHeader.biWidth < displayWidth){
            width = infoHeader.biWidth;
        } else {
            width = displayWidth;
        }
        // Zeile auf dem Display ausgeben
        GUI_WriteLine(crd, width, displayArray);
    } else {
        if (flag == 1){ 
            minimizeLine();
            flag = minState.box_size;
            minState.loopY = 0;
        } else {
            flag--;
            minState.loopY = minState.loopY + 1;
        }
    }
}
