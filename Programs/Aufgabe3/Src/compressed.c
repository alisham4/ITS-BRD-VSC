#include "compressed.h"
#include "BMP_types.h"
#include "readBitMap.h"
#include "input.h"
#include "printLine.h"

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
extern uint16_t displayArray[480];

void print_cmp_picture(){

	int x = 0;
	int y = infoHeader.biHeight;
	while(true) {
		uint8_t a = nextChar();
		uint8_t b = nextChar();

		if(a == 0) {
			if(b == 0) {
				// end of line (a==0 && b==0)
				Coordinate crd = {0,y};
				printLine(displayArray, crd);
				x = 0;
				y--;
			}
			else if(b == 1) {
				// end of file (a==0 && b==1)
				Coordinate crd = {0,y};
				printLine(displayArray, crd);
				break;
			}
			else if(b == 2) {
				// delta (a==0 && b==2)
				x += nextChar();
				y -= nextChar();
			}
			else {
				// absolute mode (a==0 && b==n)
				for (int i = 0; i < b; i++) {
					uint8_t farbIndex = nextChar();
					putPixel(x, farbIndex);
					x++;
				}

				if(b % 2 != 0)
				{
					// padding byte
					nextChar();
				}
			}
		} else {
			// encoded mode (a==n && b==m)
			for (int i = 0; i < a; i++) {
				putPixel(x, b);
				x++;      
			}
		}
	}
}
                