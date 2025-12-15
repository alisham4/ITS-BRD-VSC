#include "one_wire_bus_functions.h"
#include "Errors.h"
#include "stm32f429xx.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>

void delayUs(int us)
{
    int ticks = us * TICKS_PER_US;
    uint32_t start = getTimeStamp();
    while((getTimeStamp() - start) < ticks) {}
}

void setPinLow(int mask){
    GPIOD->BSRR = mask << OFFSET_16; 
}

void setPinHigh(int mask){
    GPIOD->BSRR = mask;
}

void write1(void)
{
    setPinLow(MASK_PD0);
    delayUs(6);
    setPinHigh(MASK_PD0);
    delayUs(64);
}

void write0(void)
{
    setPinLow(MASK_PD0);
    delayUs(60);
    setPinHigh(MASK_PD0);
    delayUs(10);
}

int readBit(){
    //set low
    setPinLow(MASK_PD0);
    //dealy 6
    delayUs(6);
    //set high
    setPinHigh(MASK_PD0);
    //delay 9
    delayUs(9);
    //Bit einlesen
    return (GPIOD->IDR & 0x01);
}

void readByte(){

    for(int i = 0; i < EIN_BYTE; i++){
        byte_read[i] = readBit();
    }
}

void writeByte(int startIndex){
    readByte();
    for(int i = startIndex; i<ACHT_BYTE;i++){
        reg_ROM_number[i] = byte_read[i];
    }
}

void readROMCommand() {
 
    for(int i = 0; i < EIN_BYTE; i++){
        if(read_ROM_command[i] == 1){
            write1();
        }else{
            write0();
        }
    }
}

void readROMNumber(){
    for (int i = 0; i < ACHT_BYTE; i= i+8) {
        writeByte(i);
    }
}




bool reset(){

    //set low
    setPinLow(MASK_PD0);
    //delay 480
    delayUs(480);
    //set high
    setPinHigh(MASK_PD0);
    //delay 70
    delayUs(70);
    //Bit einlesen vom Sensor
    if(readBit()!= 0){
       return SENSOR_NOT_CONNECTED;
    }else{
        return SENSOR_CONNECTED;
    }
}