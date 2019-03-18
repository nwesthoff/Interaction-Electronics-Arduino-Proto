int ledPin1 = 5;
int ledPin2 = 4;
int ledPin3 = 0;
int ledPin4 = 2;
int interruptPin = 14;
int state = 0;
int mode = 0;
long startTime, endTime;

void setup() {
  attachInterrupt(interruptPin, interruptHigh, RISING);
  attachInterrupt(interruptPin, interruptLow, FALLING);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  Serial.println('SETUP DONE');
}

void loop() {
  Serial.println('LOOP START');
  if(state == 0) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    delay(1000);
               
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW); 
    delay(1000);
  } else {    
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW); 
    delay(100); 
  }                     
}

void interruptHigh() {
    startTime = millis();
    Serial.println('Interrupt HIGH');
}

void interruptLow() {
  endTime = millis();
  Serial.println('Interrupt LOW');
  if (endTime - startTime < 3000) {
    if (state == 0) {
      state++;
    }
    else {
      state = 0;
    }
  }
  Serial.print('State is ');
  Serial.println(state);
}