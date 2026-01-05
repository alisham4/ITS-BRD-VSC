#include "one_wire_bus_functions.h"
#include "Errors.h"
#include "crc.h"
#include "errors.h"
#include "stm32f429xx.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void delayUs(int us)
{
    int ticks = us * TICKS_PER_US;
    uint32_t start = getTimeStamp();
    while((getTimeStamp() - start) < ticks) {}
}

void setPinLow(int pin){
    GPIOD->BSRR = 1 << (pin + OFFSET_16); 
}

void setPinHigh(int pin){
    GPIOD->BSRR = (1 << pin);
}

void setPinInput(int pin) {
    GPIOD->MODER &= ~(0x3 << (2 * pin));
}

void setPinOutput(int pin) {
    GPIOD->MODER &= ~(0x3 << (2 * pin));
    GPIOD->MODER |= (0x1 << (2 * pin));
}

void setPinOpenDrain(int pin) {
    GPIOD->OTYPER |= (1 << pin);
}

void setPinPushPull(int pin) {
    GPIOD->OTYPER &= ~(1 << pin);
}

void initOnewire() {
    setPinHigh(1);
    setPinOpenDrain(0);
    setPinHigh(0);
}

int readPin(int pin) {
    return (GPIOD->IDR >> pin) & 1;
}

void write1(void)
{
    setPinLow(0);
    delayUs(6);
    setPinHigh(0);
    delayUs(64);
}

void write0(void)
{
    setPinLow(0);
    delayUs(60);
    setPinHigh(0);
    delayUs(10);
}

int readBit(){
    //set low
    setPinLow(0);
    //dealy 6
    delayUs(6);
    //set high
    setPinHigh(0);
    //delay 9
    setPinInput(0);
    delayUs(9);
    //Bit einlesen
    int bit = readPin(0);

    delayUs(55);
    setPinOutput(0);
    return bit;
}

void writeBit(int bit)
{
    if(bit) {
        write1();
    }
    else {
        write0();
    }
}

uint8_t readByte() {
    uint8_t byte = 0;
    for(int i = 0; i < EIN_BYTE; i++) {
        byte |= (readBit() << i);
    }

    return byte;
}

void writeByte(uint8_t byte){
    for(int i = 0; i < EIN_BYTE; i++){
        writeBit((byte >> i) & 1);
    }
}

void readROMCommand() {
    writeByte(READ_ROM_CMD);
}

void readROMNumber(uint8_t rom[8]) {
    for (int i = 0; i < 8; i++) {
        rom[i] = readByte();
    }
}

bool reset(){

    //set low
    setPinLow(0);
    //delay 480
    delayUs(480);
    //set high
    setPinHigh(0);
    //delay 70
    setPinInput(0);
    delayUs(70);
    //Bit einlesen vom Sensor
    int bit = readBit();

    setPinOutput(0);
    delayUs(410);

    if(bit != 0){
       return ERROR_NOT_CONNECTED;
    }else{
        return STATUS_SUCCESS;
    }
}

int skip_rom()
{
    int status = reset();
    if(status != STATUS_SUCCESS)
    {
        return status;
    }

    writeByte(0xCC);
    return status;
}

int match_rom(uint8_t rom[8])
{
    int status = reset();
    if(status != STATUS_SUCCESS)
    {
        return status;
    }

    writeByte(0x55);
    for(int i = 0; i < 8; i++) {
        writeByte(rom[i]);
    }

    return status;
}

uint8_t searchROM(uint8_t *rom, uint8_t last_device_flag){
    uint8_t id_bit, inverse_id_bit;
    uint8_t last_discrepancy = 0; 
    uint8_t last_zero = 0;

    if (last_device_flag)
        return 0;

    if (reset())
        return ERROR_NOT_CONNECTED;

    writeByte(0xF0); // SEARCH_ROM

    for (uint8_t id_bit_number = 1; id_bit_number <= 64; id_bit_number++)
    {
        id_bit = readBit();
        inverse_id_bit = readBit();

        if ((id_bit==1) && (inverse_id_bit==1))
            return ERROR_SEARCH_ALGORYTHM_FAILED;

        uint8_t search_direction;

        if ((id_bit==0) && (inverse_id_bit==1)||(id_bit==1) && (inverse_id_bit==0))
        {
            search_direction = id_bit;
        }
        else //both equals 0
        {
          if(id_bit_number==last_discrepancy) {
            search_direction = 1;
          } else if (id_bit_number>last_discrepancy) {
            search_direction = 0;
          } else {
            search_direction = id_bit_number;
          }


          if (search_direction==0) {
            last_zero=id_bit_number;
          }

          if (last_zero < 9) {
            
          }

        }

        //write found ROM-bit into array 
        rom[id_bit_number] = search_direction;

        writeBit(search_direction);
    }

    last_discrepancy = last_zero;
    if (last_discrepancy == 0)
        last_device_flag = 1;

    return 1;
}

void detect_sensors(uint8_t roms[][8], uint8_t found_sensor_count)
{
    uint8_t rom[8];
   
    uint8_t last_device_flag = 0;// if it is 1, then all sensors are found

    found_sensor_count = 0;

    while (!last_device_flag && found_sensor_count < 4)
    {
        if (!searchROM(rom, last_device_flag))
            break;

        // CRC prüfen
        if (checkCRC(7,rom) != rom[7])
            continue;

        memcpy(roms[found_sensor_count], rom, 8);
        found_sensor_count++;
    }
}

