int data = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    data = Serial.read();

    // say what you got:
    Serial.print("Recibi: ");
    Serial.println(data, DEC);
  }
}
