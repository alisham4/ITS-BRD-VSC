#include "phaseDetector.h"
#include <stddef.h>
#include <stdio.h>

//initialize variables
int stepCounter = 0; 
int phaseOld = -1;
int phaseCurrent = -1;

//phase detector array
char phaseArray[4][4] = {
    {NO_CHANGE, FORWARD, ERROR_, BACKWARD},
    {BACKWARD, NO_CHANGE, FORWARD, ERROR_},
    {ERROR_, BACKWARD, NO_CHANGE, FORWARD},
    {FORWARD, ERROR_, BACKWARD, NO_CHANGE}
};

//get single result
int get_single_phase(){

    int res_PinA = 0;
    int res_PinB = 0;
    int phase;

    res_PinA = readPinA();
    res_PinB = readPinB();  

    if(res_PinA == 0 && res_PinB == 0){
       phase = PHASE_A;
    }else if (res_PinA == 1 && res_PinB == 0){
        phase = PHASE_B;
       }else if (res_PinA == 1 && res_PinB == 1){
        phase = PHASE_C;
       }else{
        phase = PHASE_D;
       }
       return phase;
    }


    //get final result
    char get_result_transition(int phaseCurrent){
        
        if(phaseOld == -1 ) {
            phaseOld=phaseCurrent;
            return NO_CHANGE;
        } else {
            char phaseChange = phaseArray[phaseOld][phaseCurrent];                                                                                      
            counter(phaseChange);
            phaseOld = phaseCurrent;
            return phaseChange;
        }  
    }

    
    //update counter
    int counter(char phaseChange){
        
        if(phaseChange == FORWARD){
            stepCounter++;
        }
        if(phaseChange == BACKWARD){
            stepCounter--;
        }
        return stepCounter;
    }
