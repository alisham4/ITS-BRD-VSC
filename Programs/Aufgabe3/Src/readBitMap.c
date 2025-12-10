#include "readBitMap.h"
#include "BMP_types.h"
#include "headers.h"
#include "input.h"

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;

void readInput(){
	// Öffnet das nächste Bild
     openNextFile();
	 //Header vom Bild einlesen 
     readHeaders();
     getFileHeader(&fileHeader);
     getInfoHeader(&infoHeader);
}

int get_number_Of_Colors(){
    // Wenn biClrUsed = 0 → BMP verwendet *volle* Palette (256 Farben)
    if(infoHeader.biClrUsed == 0) {
			return MAX_PALETTE_LENGTH;
		} else {
			// Sonst → nur die tatsächlich im Bild gespeicherten Farben
			return infoHeader.biClrUsed;
        }
}

void padding_Bytes(int paletteLength){

	// Berechnet, wie viele Bytes zwischen Palette und Bitmapdaten übersprungen werden müssen.
	int paddingBytes = fileHeader.bfOffBits - sizeof(infoHeader) - sizeof(fileHeader) - sizeof(RGBQUAD) * paletteLength;
	// Diese "Padding-Bytes" müssen einfach gelesen und verworfen werden.
	for(int i = 0; i < paddingBytes; i++){
		// liest ein Byte und ignoriert es
		nextChar();
	}
}

// Überspringt die Padding-Bytes am Ende einer BMP-Zeile
void padding_Line(){

	// BMP-Zeilen sind auf 4-Byte-Grenzen aufgefüllt.
    // Formel: Anzahl der Gesamtbytes pro Zeile (inkl. Padding) minus tatsächliche Pixelbreite.
    int paddingLine = ((infoHeader.biWidth * 8 + 31) / 32) * 4 - infoHeader.biWidth;
	// Überspringt jedes der Padding-Bytes durch Aufruf von nextChar()
    for (int i = 0; i < paddingLine; i++) {
					nextChar();
	}
}

// Wandelt eine 24-Bit-RGB-Farbe in 16-Bit-Format um
uint16_t farbeUmwandeln(RGBQUAD farbe)
{
	return (farbe.rgbRed >> 3) << 11 | (farbe.rgbGreen >> 2) << 5 | (farbe.rgbBlue>> 3);
}
