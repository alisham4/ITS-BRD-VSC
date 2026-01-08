#include "phaseDetector.h"
#include <stddef.h>
#include <stdio.h>
#include "input.h"
#include "leds.h"
#include "stm32f429xx.h"
#include "timer.h"

//initialize variables
volatile int stepCounter = 0;
volatile uint32_t startTime = 0;
volatile char currentState = NO_CHANGE;

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
      
            char phaseChange = phaseArray[phaseOld][phaseCurrent];                                                                                      
            counter(phaseChange);
            phaseOld = phaseCurrent;
            return phaseChange;
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



    void EXTI0_IRQHandler (void) {
        EXTI->PR = (1 << 0);
        readInputInterrupt();
    }

    void EXTI1_IRQHandler (void) {
        EXTI->PR = (1 << 1);
        readInputInterrupt();
    }


    void initISR(){
        //step 1 : Routing des Interrupts
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; //Clock for GPIO Port G    
        RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // System conf. Clock enable
        
        // Routing Pin 0, 1 of Port G -> EXTI0, EXTI1
        SYSCFG->EXTICR[0] &= ~((0x0f << (4*0)) | (0x0f << (4*1))); //Remove old selection
        SYSCFG->EXTICR[0] |=   (0x06 << (4*0)) | (0x06 << (4*1));  //0x00 : Select Port G

        //step 2 : Definiere Events für INT2 und unmask IRQ2
        EXTI->RTSR |= (1 << 0) | (1 << 1); //select rising trigger for INT0, INT1 
        EXTI->FTSR |= (1 << 0) | (1 << 1); //select falling trigger for INT0, INT1
        EXTI->IMR  |= (1 << 0) | (1 << 1); // Unmask INT0, INT1

        //step 3 : Einstellung des Interrupts Controllers 
        NVIC_SetPriority(EXTI0_IRQn, 0); // Setup EXTI0 auf höchste Prio.
        NVIC_EnableIRQ(EXTI0_IRQn);      // Enable EXTI0

        NVIC_SetPriority(EXTI1_IRQn, 0); // Setup EXTI0 auf höchste Prio.
        NVIC_EnableIRQ(EXTI1_IRQn);      // Enable EXTI0

        phaseOld = get_single_phase();
    }

    void static inline readInputInterrupt(){
        //read input 
        startTime = getTimeStamp();
        phaseCurrent = get_single_phase();

        //update phase 
        if(currentState != ERROR_)
        {
            currentState = get_result_transition(phaseCurrent);
        }
    }
