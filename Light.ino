void initializeLight(){
  pinMode(A7, INPUT);
}

float getLight(){
  return analogRead(A7);
}
