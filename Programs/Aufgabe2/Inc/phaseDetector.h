#ifndef PHASEDETECTOR_H
#define PHASEDETECTOR_H

#define FORWARD   'F'
#define BACKWARD  'B'
#define NO_CHANGE 'X'
#define ERROR_    'E'

#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2
#define PHASE_D 3

char phaseArray[4][4] = {
    {NO_CHANGE, BACKWARD, ERROR_, FORWARD},
    {FORWARD, NO_CHANGE, BACKWARD, ERROR_},
    {ERROR_, FORWARD, NO_CHANGE, BACKWARD},
    {BACKWARD, ERROR_, FORWARD, NO_CHANGE}
};

/**
 * @brief determines single phase
 * @return int
 */
int get_single_phase();


/**
 * @brief determines resulting phase after reading input A and B
 * @return char
 */
char get_result_Phase();

#endif