#ifndef ONE_WIRE_BUS_FUNCTIONS_
#define ONE_WIRE_BUS_FUNCTIONS_
#include <stdbool.h>
#include <stdint.h>


#define READ_ROM_CMD 0x33

#define EIN_BYTE 8
#define ACHT_BYTE 64



//Masken für PD0 und PD1
#define MASK_PD0 0x01
#define MASK_PD1 0x02

//Offset für Bus low setzen
#define OFFSET_16 16

void delayUs(int us);
void setPinLow(int pin);
void setPinHigh(int pin);
void setPinInput(int pin);
void setPinOutput(int pin);
void setPinOpenDrain(int pin);
void setPinPushPull(int pin);

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
uint8_t readByte();

void writeByte(uint8_t startIndex);

void setPinHigh(int mask);

void setPinLow(int mask);

void write0();

void write1();

void readROMCommand();

void readROMNumber(uint8_t rom[8]);

/**
* identifies the ROM codes of all slave devices on the bus, 
* which allows the master to determine the number of 
* slaves and their device types
*/
int searchROM(uint8_t *rom);

void initOnewire();


int skip_rom();
int match_rom(uint8_t rom[8]);

int detect_sensors();

#endif