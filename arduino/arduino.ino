const int CHANNELS = 4;
const int LED_PINS[CHANNELS] = {5, 4, 0, 2};
const byte interruptPin = 14;
const byte interruptPin2 = 12;
byte state = 0;
byte mode = 0;
long startTime, endTime;
int count = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleActionInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), handleModeInterrupt, RISING);
  for (int i = 0; i < CHANNELS; i++)
  {
    pinMode(LED_PINS[i], OUTPUT);
  }
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
    for (int i = 0; i < CHANNELS; i++)
    {
      digitalWrite(LED_PINS[i], LOW);
    }
    delay(500);
  }
  else
  {
    fadeUp();
    delay(3000);
    state = 0;
    logModeState();
    fadeDown();
  }
}

void sessionLoop()
{
  if (state == 0)
  {
    upCycleSlow();
  }
  else
  {
    bool isReleased = digitalRead(interruptPin);
    if (isReleased == true)
    {
      upCycleFast();
      state = 0;
    }
  }
}

void fadeUp()
{
  for (int i = 0; i < 1023; i++)
  {
    for (int c = 0; c < CHANNELS; c++)
    {
      analogWrite(LED_PINS[c], i);
    }
    delay(1);
  }
}

void fadeDown()
{
  for (int i = 1023; i > 0; i = i - 1)
  {
    for (int c = 0; c < CHANNELS; c++)
    {
      analogWrite(LED_PINS[c], i);
    }
    delay(1);
  }
}

void upCycleSlow()
{
  int offset = 255;

  for (int i = 1023; i > 0; i = i - 1)
  {
    for (int c = 0; c < CHANNELS; c++)
    {
      int brightness = (i + c * offset) % 1023;
      analogWrite(LED_PINS[c], brightness);
    }
    delay(5);
  }
}

void upCycleFast()
{
  int offset = 255;

  for (int i = 1023; i > 0; i = i - 1)
  {
    for (int c = 0; c < CHANNELS; c++)
    {
      int brightness = (i + c * offset) % 1023;
      analogWrite(LED_PINS[c], brightness);
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