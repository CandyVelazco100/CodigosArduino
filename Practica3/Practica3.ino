int option;
#define LED D1

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT); 
}

void loop() {
    if (Serial.available() > 0) {
      option = Serial.parseInt();
      Serial.print("Numero de veces: ");
      Serial.println(option);
      
      if (option >= 1 && option <= 9){
        for(int i=0; i < option; i++){
          digitalWrite(LED, HIGH);
          delay(1000);
          digitalWrite(LED, LOW);
          delay(1000);
        }
      }else if(option >= 10){
        Serial.println("Solo un numero del 1 al 9");
      }
    }  
}