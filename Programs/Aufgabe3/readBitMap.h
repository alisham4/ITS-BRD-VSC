#ifndef _READBITMAP_H
#define _READBITMAP_H

/*
* read input
*/
void readInput();

/**
* get number of colors in color palette
 */
int get_number_Of_Colors();

/*
* calculates padding bytes
*/
void padding_Bytes(int paletteLength);

/*
* calculates padding line
*/
void padding_Line();

#endif