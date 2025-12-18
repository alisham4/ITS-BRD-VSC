#include "temperature_functions.h"
#include "crc.h"
#include "errors.h"
#include "one_wire_bus_functions.h"
#include "stm32f4xx.h"
#include <stdint.h>

int convert_T(uint8_t rom[8], float *output) {
    int status = match_rom(rom);
    if(status != SUCCESS)
    {
        return status;
    }

    //write 0x44 for iniate a single temperature convertion
    writeByte(CONVERT_T_CONST);

    setPinPushPull(0);
    delayUs(750000);
    setPinOpenDrain(0);

    status = match_rom(rom);
    if(status != STATUS_SUCCESS)
    {
        return status;
    }

    uint8_t scratchpad [9] = {0};
    status = read_scratchpad(scratchpad);
    if(status != STATUS_SUCCESS)
    {
        return status;
    }

    int16_t raw = scratchpad[0] | (scratchpad[1] << 8);
    float temp = raw / 16.0;
    *output = temp;
    return STATUS_SUCCESS;
}

int read_scratchpad(uint8_t scratchpad[9])
{
    writeByte(0xBE);
    for(int i = 0; i < 9; i++)
    {
        scratchpad[i] = readByte();
    }

    if(!checkCRC(9, scratchpad))
    {
        return ERROR_CRC_CHECK;
    }

    return STATUS_SUCCESS;
}
