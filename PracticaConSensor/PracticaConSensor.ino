#define ledPin1 D0 
#define ledPin2 D1 
#define ledPin3 D2 
#define analogPin A0 
int valorLDR = 0;  

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  delay(100);
  
  valorLDR= analogRead(analogPin);
  Serial.println("--------------------------");
  Serial.print(valorLDR);

  if (valorLDR > 681) {
    digitalWrite(ledPin1, HIGH); 
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  } else if (valorLDR >= 511 && valorLDR <= 681 ) {
    digitalWrite(ledPin1, LOW); 
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
  } else if (valorLDR >= 341 && valorLDR <=510) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH); 
  } else if (valorLDR >= 171 && valorLDR <=340) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH); 
  } else if (valorLDR >= 0 && valorLDR <=170) {
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
  } 
  delay(2000);
}

