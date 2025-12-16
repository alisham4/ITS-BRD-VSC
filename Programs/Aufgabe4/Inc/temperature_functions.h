#ifndef TEMPERATURE_FUNCTIONS
#define TEMPERATURE_FUNCTIONS

#define CONVERT_T_CONST 0x44

static int scratchpad [64];

/**
* initiate a single temperature convertion
*/
void convert_T();

/*
* allows to write 3 bytes of data to a scratchpad memory
* 1. T_H register 
* 2. T_L register
* 3. configuration register
*/
void write_scratchpad();

/*
* allows the master to read the contents of the scratchpad 
*/
void read_scratchpad();

#endif