#include "readBitMap.h"
#include "BMP_types.h"
#include "headers.h"
#include "input.h"

BITMAPINFOHEADER infoHeader;
BITMAPFILEHEADER fileHeader;

void readInput(){
     initInput();
     openNextFile();
     readHeaders();
     getFileHeader(&fileHeader);
     getInfoHeader(&infoHeader);
}

int get_number_Of_Colors(){
    
    if(infoHeader.biClrUsed == 0) {
			return 265;
		} else {
			return infoHeader.biClrUsed;
        }
}

void padding_Bytes(int paletteLength){

	int paddingBytes = fileHeader.bfOffBits - sizeof(infoHeader) - sizeof(fileHeader) - sizeof(RGBQUAD) * paletteLength;
	for(int i = 0; i < paddingBytes; i++){
		nextChar();
	}
}

void padding_Line(){

    int paddingLine = ((infoHeader.biWidth * 8 + 31) / 32) * 4 - infoHeader.biWidth;
    for (int i = 0; i < paddingLine; i++) {
					nextChar();
				}
}