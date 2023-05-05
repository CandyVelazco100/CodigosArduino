#define LED D1 
#define BUTTON D2 

void setup() { 
  pinMode(LED, OUTPUT); // Set the LED Pin as an output
  pinMode(BUTTON, INPUT_PULLUP); // Set the Tilt Switch as an input
}

void loop() {
  int digitalVal = digitalRead(BUTTON); // Take a reading
  
  if(HIGH == digitalVal) {
    digitalWrite(LED, LOW); //Turn the LED off
  } else {
    digitalWrite(LED, HIGH);//Turn the LED on
  }
}