int pirSen = 2;
int calibTime = 30;
unsigned long lowIn;
unsigned int pause = 5000;
bool lockLow = true;
bool takeLowTime;
int pirValue = 0;
int a = 0;
void setup() 
{
  Serial.begin(9600);
  pinMode(pirSen, INPUT);
}

void loop() 
{
  motionDetection();
}

void motionDetection()
{
  a = analogRead(3);
  Serial.println(a);
  if (digitalRead(pirSen == HIGH))
  {
    if (lockLow)
    {
      pirValue = 1;
      lockLow = false;
      Serial.println("Motion Detected");
      delay(50);
    }
    takeLowTime = true;
  }
  if (digitalRead(pirSen) == LOW)
  {
    if (takeLowTime)
    {
      lowIn = millis();
      takeLowTime = false;
    }
    if(!lockLow && millis() - lowIn > pause)
    {
      pirValue = 0;
      lockLow = true;
      Serial.println("Motion ended");
      delay(50);
    }
  }
}
