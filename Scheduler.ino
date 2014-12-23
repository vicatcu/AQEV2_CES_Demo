#include <avr/interrupt.h>
#include <util/atomic.h>
 
typedef struct {
  uint16_t task_timer;
  uint16_t task_period;
  void (*task)(void);
} task_t;
 
////////////////////////////////////////////////////////////////////
//                                                                //
// define NUM_TASKS to be >= the actual number of tasks defined!  //
//                                                                //
////////////////////////////////////////////////////////////////////
 
#define NUM_TASKS (4)
task_t tasks[NUM_TASKS] = {0};
 
void initializeScheduler(){
  /////////////////////////////////////////////////////////////////////////////
  //                                                                         //
  // statically set up the tasks here, e.g.:                                 //
  // tasks[0].task_period = 500;   // execute once every 500ms (technically  //
  //                               // "no more frequantly than every 500ms") //
  // tasks[0].task = &exampleTask; // call the function exampleTask          //
  //                                                                         //
  /////////////////////////////////////////////////////////////////////////////
  tasks[0].task_period = 250;
  tasks[0].task = &sampleSensorsTask; // collect into the moving average window 
 
  tasks[1].task_period = 2000;   // every 2 seconds...
  tasks[1].task = &lcdUpdateTask;
 
  TCCR3B = _BV(WGM32) | _BV(CS31) | _BV(CS30); // prescaler=64, enable CTC mode
  OCR3A = 250;                                 // compare match every 250 ticks
  TIMSK3 = _BV(OCIE3A);                        // enable compare match ISR
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
