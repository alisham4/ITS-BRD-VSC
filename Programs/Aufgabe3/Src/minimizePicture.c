#include "minimizePicture.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include "printLine.h"
#include "math.h"
#include "readBitMap.h"
#include <stdbool.h>

extern RGBQUAD palette[256];
extern uint8_t linesArray[5][5*480];
extern BITMAPFILEHEADER fileHeader;
extern BITMAPINFOHEADER infoHeader;
extern uint16_t displayArray[480];

#define MAX_BUFF_SIZE 5

uint8_t flag;

MinimizeState minState;
int yCor=320;

//Hilfsmethoden
int min(int a, int b){
    return a < b ? a : b;
}


/**
 Berechnet den effektiven Zeilenindex im Ringpuffer.
 i  = gewünschte Bildzeile relativ zur aktuellen Verarbeitung
 loopY = wie oft der Puffer bereits rotiert wurde
 MAX_BUFF_SIZE = Anzahl der gepufferten Zeilen
Durch das Modulo wird dafür gesorgt, dass wir immer im Bereich 0..MAX_BUFF_SIZE-1 bleiben.
 */

int indexLine(int i) {
    return (i + minState.loopY) % MAX_BUFF_SIZE;
}

/**  Liefert die RGB-Farbe eines Pixels an Position (x, y).
/linesArray enthält Indexwerte in die Palette (8-Bit Farbindex).
 palette[index] liefert den tatsächlichen RGBQUAD-Farbwert.
 */
RGBQUAD getPixel(int x, int y) {
	int index = linesArray[y][x];
    return palette[index];
}


/*
Berechnet die Durchschnittsfarbe eines quadratischen Bereichs ("Box").
Die Box wird von (x_start, y_start) bis (x_end, y_end) durchlaufen.
 minState.startY bestimmt die aktuelle Bildzeile, die geladen wurde.
 Durch die Schleifen werden alle Pixel aus diesem Bereich summiert.
 Anschließend wird der Mittelwert berechnet und in ein 16-Bit Farbformat umgewandelt.
*/ 
uint16_t averageColor(int x_start, int y_start, int x_end, int y_end) {
    int r = 0, g = 0, b = 0;

    for(int y = y_start; y >= y_end; y--) {
        for(int x = x_start; x <= x_end; x++) {
            int lineIndex = y - minState.startY-1;
            RGBQUAD color = getPixel(x, lineIndex);
            r += color.rgbRed;
            g += color.rgbGreen;
            b += color.rgbBlue;
        }
    }

    int count = minState.box_size * minState.box_size;
    if(count == 0) count = 1;

    RGBQUAD avg = { b/count, g/count, r/count, 0 };
    return farbeUmwandeln(avg);
}

void initMinimize() {
    // Prüfen, ob das Bild größer ist als das Display
    if(infoHeader.biHeight > displayHeight || infoHeader.biWidth > displayWidth) { 
        // Verhältnis zwischen Bild und Display berechnen
        float scaleX = (float)displayWidth/ infoHeader.biWidth;                    
        float scaleY = (float)displayHeight / infoHeader.biHeight;

        // Kleineren Skalierungsfaktor nehmen, damit das Bild nicht verzerrt wird
        minState.scale = fmin(scaleX, scaleY);      
        // Größe der "Pixelbox" bestimmen,
        // box_size = wie viele Originalpixel zu einem Displaypixel zusammengefasst werden                                 
        minState.box_size = ceil(1 / minState.scale);       
        // Berechnung der neuen Bildgröße nach Skalierung                      
        minState.scaled_width = infoHeader.biWidth * minState.scale;
        minState.scaled_height = infoHeader.biHeight * minState.scale;
        // Bild ist zu groß
        minState.tooBig = true;
    } else {
        // Keine Skalierung nötig → Bild passt auf das Display
        minState.scale = 1.0;
        minState.box_size = 1;
        minState.scaled_width = infoHeader.biWidth;
        minState.scaled_height = infoHeader.biHeight; 
        minState.tooBig = false;
    }

    // Start bei der untersten Bildzeile (Bitmap wird von unten nach oben gespeichert)
    minState.startY = infoHeader.biHeight;
    // Startwert für Ringpuffer-Zyklus
    minState.loopY = 0;
	flag = minState.box_size;
}

void minimizeLine() { 
    // y_orig = aktuelle oberste Zeile der Box im Originalbild
    int y_orig = minState.startY;
    // y_end = untere Zeile der Box 
    int y_end = y_orig - minState.box_size + 1;
    // Für nächste Iteration: y_orig auf nächste Bildzeile verschieben
    minState.startY = y_end - 1;
	
    // Über die Displaybreite laufen
    for(int x = 0; x < minState.scaled_width; x++) {
        // x_orig = linke Kante der Box im Originalbild
        int x_orig = (minState.box_size * x);
        // x_end = rechte Kante der Box
		int x_end = x_orig + minState.box_size - 1;

        // Durchschnittsfarbe für diese Box berechnen
        displayArray[x] = averageColor(x_orig, y_orig, x_end, y_end);
    }

    // Eine Zeile auf das Display schreiben
    Coordinate crd = {0, yCor };
    GUI_WriteLine(crd, minState.scaled_width, displayArray);
    // Nächste Displayzeile (nach oben rücken)
    yCor--;
    minState.loopY = (minState.loopY + 1) % MAX_BUFF_SIZE;
		
}

