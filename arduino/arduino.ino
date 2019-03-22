

const byte ledPin1 = 5;
const byte ledPin2 = 4;
const byte ledPin3 = 0;
const byte ledPin4 = 2;
const byte interruptPin = 14;
const byte interruptPin2 = 12;
byte state = 0;
byte mode = 0;
long startTime, endTime;
int count = 0;

void setup()
{
  Serial.begin(74880);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleActionInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), handleModeInterrupt, RISING);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  Serial.println("SETUP DONE");
}

void loop()
{
  if (mode == 0)
  {
    dayLoop();
  }
  else
  {
    sessionLoop();
  }
}

void dayLoop()
{
  if (state == 0)
  {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    delay(500);
  }
  else
  {
    fadeUp();
    delay(3000);
    state = 0;
    logModeState();
  }
}

void sessionLoop()
{
  if (state == 0)
  {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    delay(100);

    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    delay(10);
  }
}

void fadeUp()
{
  for (int i = 0; i < 1023; i++)
  {
    for (int currentLedPin = 0; currentLedPin <= 4; currentLedPin = currentLedPin++)
    {
      analogWrite(currentLedPin, i);
    }
    delay(1);
  }
}

void fadeDown()
{
  for (int i = 1023; i > 0; i++)
  {
    for (int currentLedPin = 0; currentLedPin <= 4; currentLedPin = currentLedPin++)
    {
      analogWrite(currentLedPin, i);
    }
    delay(1);
  }
}

void handleActionInterrupt()
{
  endTime = millis();
  if (endTime - startTime > 50)
  {
    if (state == 0)
    {
      state++;
    }
    else
    {
      state = 0;
    }

    logModeState();
  }
  startTime = millis();
}

void handleModeInterrupt()
{
  endTime = millis();
  if (endTime - startTime > 50)
  {
    if (mode == 0)
    {
      mode++;
    }
    else
    {
      mode = 0;
    }

    logModeState();
  }
  startTime = millis();
}

void logModeState()
{
  Serial.print("Watch is in ");
  if (mode == 0)
  {
    Serial.print("day");
  }
  else
  {
    Serial.print("session");
  }

  Serial.print(" mode, state is ");
  if (state == 0)
  {
    Serial.println("inactive");
  }
  else
  {
    Serial.println("active");
  }
}