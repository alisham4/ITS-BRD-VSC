#include "uncompressed.h"
#include "BMP_types.h"
#include "readBitMap.h"
#include "input.h"
#include <stdint.h>
#include "printLine.h"

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
extern uint16_t displayArray[480];

void print_uncmp_picture(){
    
    int x;
    int y;
    
    // BMP speichert die erste Zeile am Dateiende.
    // Daher von der unteren Zeile (biHeight-1) nach oben (0).
    for(y=infoHeader.biHeight-1; y>=0; y--) {
        // DisplayKoordinate für die Zeile
        Coordinate crd = { 0, y };
        // Alle Pixel der Zeile einlesen
        for (x = 0; x < infoHeader.biWidth; x++) {
            uint8_t farbIndex = nextChar();
            putPixel(x, farbIndex);
        }

        // Die fertig verarbeitete Zeile ausgeben
        printLine(displayArray, crd);
        // Eventuelle Padding-Bytes am Zeilenende überspringen
        padding_Line();
    }
}

