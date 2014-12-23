void initializeLight(){
  pinMode(A7, INPUT);
}

float getLight(){
  const float volts_per_tick = 5.0f/1024.0f;
  uint16_t sum = 0;
  uint16_t dummy = analogRead(A7);
  // oversample threading
  for(uint8_t ii = 0; ii < 32; ii++){
    sum += analogRead(A7);
  }
  
  return (sum / 32.0) * volts_per_tick;
}
