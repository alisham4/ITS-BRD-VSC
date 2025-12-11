#ifndef ONE_WIRE_BUS_FUNCTIONS_
#define ONE_WIRE_BUS_FUNCTIONS_
#include <stdbool.h>

static int byte_read[8];

//Masken für PD0 und PD1
#define MASK_PD0 0x01
#define MASK_PD1 0x02

//Offset
#define OFFSET_16 16

/**
* wird am Anfang des Programs aufgerufen. Stellt sichr, ob Sensoren angeschlossen sind oder nicht.
 */
bool reset();

/**
* liest ein Bit und schreibt das gelesenes Bit ins byte array für die Weiterverarbeitung
 */
int readBit();

/**
* verschickt ein Bit über dem Bus an den Sensor
 */
void writeBit(int bit);

/*
* ruft intern readBit 8 mal auf und speichert die gelesenen Bits in einem Array
*/
void readByte();


#endif