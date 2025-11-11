#include "phaseDetector.h"
#include "pins.h"


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
        phase = PHASE_B;
       }else{
        phase = PHASE_D;
       }

       return phase;
    }


    //GET FINAL RESUlT
    char get_result_Phase(){

        int phase1;
        int phase2;
        
        phase1 = get_single_phase();
        phase2 = get_single_phase();

        return phaseArray[phase1][phase2];

    }


