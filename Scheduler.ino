#include <avr/interrupt.h>
#include <util/atomic.h

typedef struct {
  uint16_t task_timer;
  uint16_t task_period;  
  void (*task)(void);
} task_t;

////////////////////////////////////////////////////////////////////////////////////
//                                                                                //
// define NUM_TASKS to be at least as big as the actual number of tasks defined!1 //
//                                                                                //
////////////////////////////////////////////////////////////////////////////////////

#define NUM_TASKS (4)
task_t tasks[NUM_TASKS] = {0};

void initializeScheduler(){
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                                                                                               //  
  // statically set up the tasks, e.g.:                                                                                //  
  // tasks[0].task_period = 500;   // execute once every 500ms (technically "no more frequantly than every 500ms") //
  // tasks[0].task = &exampleTask; // call the function exampleTask                                                //
  //                                                                                                               //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCCR3B = _BV(WGM32) | _BV(CS31) | _BV(CS30); // prescale clock by 64 and enable CTC mode
  OCR3A = 250;                                 // trigger compare match ever 250 ticks
  TIMSK3 = _BV(OCIE3A);                        // enable output OCR3A compare interrupt    
}

// initializeScheduler sets this ISR up to fire once per millisecond
ISR(TIMER3_COMPA_vect){  
  for(uint8_t ii = 0; ii < NUM_TASKS; ii++){
    if(tasks[ii].task_timer > 0) tasks[ii].task_timer--;
  }    
}

// call this from loop()
void executeTasks(){
  for(uint8_t ii = 0; ii < NUM_TASKS; ii++){
    if(tasks[ii].task != 0){
      if(tasks[ii].task_timer == 0){
        tasks[ii].task();
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
          tasks[ii].task_timer = tasks[ii].task_period;
        }
      }
    }
  }
}

// task functions must take no arguments, e.g. 
// void exampleTask(){
//  static uint8_t x = 0;
//  x ^= 1;
//  digitalWrite(A6, x);
// }
