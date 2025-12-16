#ifndef ONE_WIRE_BUS_FUNCTIONS_
#define ONE_WIRE_BUS_FUNCTIONS_
#include <stdbool.h>
#include <stdint.h>

static int byte_read[8];
static int reg_ROM_number[64];
static int read_ROM_command[] = {0,0,1,1,0,0,1,1};

#define EIN_BYTE 8
#define ACHT_BYTE 64



//Masken für PD0 und PD1
#define MASK_PD0 0x01
#define MASK_PD1 0x02

//Offset für Bus low setzen
#define OFFSET_16 16

/**
* wird am Anfang des Programs aufgerufen. Stellt sichr, ob Sensoren angeschlossen sind oder nicht.
 */
bool reset();

/**
* liest ein Bit und schreibt das gelesenes Bit ins byte array für die Weiterverarbeitung
 */
int readBit();

/*
* ruft intern readBit 8 mal auf und speichert die gelesenen Bits in einem Array
*/
void readByte();

void writeByte(uint8_t startIndex);

void setPinHigh(int mask);

void setPinLow(int mask);

void write0();

void write1();

void readROMCommand();

void readROMNumber();

/**
* identifies the ROM codes of all slave devices on the bus, 
* which allows the master to determine the number of 
* slaves and their device types
*/
void searchROM();


#endif