#ifndef TEMPERATURE_FUNCTIONS
#define TEMPERATURE_FUNCTIONS

#define CONVERT_T_CONST 0x44

#include <stdint.h>

/**
* initiate a single temperature convertion
*/
int convert_T(uint8_t rom[8], float *output);

/*
* allows the master to read the contents of the scratchpad 
*/
int read_scratchpad(uint8_t scratchpad[9]);

#endif