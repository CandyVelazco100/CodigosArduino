#define ledPin1 D0 
#define ledPin2 D1 
#define ledPin3 D2 
#define switchPin D3 

int count = 0;
boolean lastButton;
boolean currentButton = false;
boolean ledOn = false;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  count = 0;
}

boolean debounce(boolean last) {
  boolean current = digitalRead(switchPin);
  if (last != current) {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;  
}

void loop() {
  lastButton = currentButton;
  currentButton = debounce(lastButton);

  if (lastButton == false && currentButton == true) {

    while(count == 0){
      count++;
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW); 
    }

    if (count == 1) {  
      count++;
      digitalWrite(ledPin1, HIGH); 
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
    }

    else if (count == 2) { 
      count++;
      digitalWrite(ledPin1, LOW); 
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
    }

    else if (count == 3) { 
      count++;
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH); 
    }

    else if (count == 4) { 
      count++;
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH); 
    }

    else if (count == 5) { 
      for(int i = 0; i < 5; i++) {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH); 
        delay(50); 
        digitalWrite(ledPin1, LOW);   
        digitalWrite(ledPin2, LOW);   
        digitalWrite(ledPin3, LOW);   
        delay(50); 
      }
      count = 0;
    }
  } 
}