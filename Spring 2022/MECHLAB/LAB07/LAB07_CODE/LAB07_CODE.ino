void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(1500);                       
  digitalWrite(LED_BUILTIN, LOW);    
  delay(1500);                       
}
