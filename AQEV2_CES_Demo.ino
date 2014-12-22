#include "WildFire.h"
WildFire wf;

void setup(){
  wf.begin();
  Serial.begin(115200);
  initializeLCD();
  
  initializeGasSensors();
  initializeTempHumidity();  
  initializeLight();
  
  initializeScheduler();
  
}

void loop(){
  executeTasks();
}
