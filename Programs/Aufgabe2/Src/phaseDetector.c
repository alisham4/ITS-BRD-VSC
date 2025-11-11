#include "phaseDetector.h"
#include "leds.h"
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

    //PHASE OUTOUT 
    void phase_Output(){
        char currentState = get_result_Phase();

        //???methods for each state 
        switch (currentState) {
            // case BACKWARD -> LED22 on 
            case BACKWARD : LED_ON(BSRR_LED22_MASK);
            break;
            //case FORWARD -> LED23 on
            case FORWARD : LED_ON(BSRR_LED23_MASK);
            break;
            //case ERROR -> LED21 on 
            case ERROR_ : LED_ON(BSRR_LED21_MASK);
            break; 
            //case NO_CHANGE ??
            case NO_CHANGE : 
            break;
        }
    }


