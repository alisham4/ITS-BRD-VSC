#include "phaseDetector.h"
#include "leds.h"
#include "input.h"
#include <stddef.h>
#include <stdio.h>

int stepCounter = 0; 
int phaseOld = -1;
int phaseAktuell = -1;

char phaseArray[4][4] = {
    {NO_CHANGE, FORWARD, ERROR_, BACKWARD},
    {BACKWARD, NO_CHANGE, FORWARD, ERROR_},
    {ERROR_, BACKWARD, NO_CHANGE, FORWARD},
    {FORWARD, ERROR_, BACKWARD, NO_CHANGE}
};

//GET SINGLE RESULT
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


    //GET FINAL RESUlT
    char get_result_transition(int phaseAktuell){
        
        if(phaseOld == -1 ) {
            phaseOld=phaseAktuell;

            return NO_CHANGE;
        } else {
            

            char phaseChange = phaseArray[phaseOld][phaseAktuell];
           //                                                                                           increase or decrease counter
            counter(phaseChange);
            phaseOld = phaseAktuell;


            return phaseChange;

        }
       
    }

    
    //COUNTER
    int counter(char phaseChange){
        
        if(phaseChange == FORWARD){
            stepCounter++;
        }
        if(phaseChange == BACKWARD){
            stepCounter--;
        }
        return stepCounter;
    }
