void initializeLight(){
  pinMode(A7, INPUT);
}

float getLight(){
  uint16_t sum = 0;
  uint16_t dummy = analogRead(A7);
  // oversample threading
  for(uint8_t ii = 0; ii < 32; ii++){
    sum += analogRead(A7);
  }
  
  return sum / 32.0;
}
