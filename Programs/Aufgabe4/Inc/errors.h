#ifndef ERRORS_H_
#define ERRORS_H_

#define STATUS_SUCCESS       0
#define ERROR_NOT_CONNECTED  1
#define ERROR_CRC_CHECK      2
#define ERROR_SEARCH_ALGORYTHM_FAILED 3

void printError(int error);

#endif