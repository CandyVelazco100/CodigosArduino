int option;
int led = 2;
 
void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
 
void loop(){
  //si existe datos disponibles los leemos
  if (Serial.available() > 0){
    //leemos la opcion enviada
    option = Serial.read();

    if(option=='a') {
      digitalWrite(led, LOW);
      Serial.println("ON");
    }

    if(option=='b') {
      digitalWrite(led, HIGH);
      Serial.println("OFF");
    }
  }
}