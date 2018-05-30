//                Information

//                Developers
//----------------------------------------
//  Hafiz Elkilic     |   74005   |   Helk
//  Nassim Tijani     |   76654   |   Ntij
//  Emirhan Demirci   |   76716   |   Edem
//----------------------------------------

//Date: 24-05-2018

//NEH: Nassim Emirhan Hafiz 

  #include "SevSeg.h"
  SevSeg sevseg; 


  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
  bool resistorsOnSegments = true;

  bool enableLog;

  int aoNeg      =  2; // wiele
  int aoPos      =  3; // wiele

  int doStepPin0 =  8; // motor sensor
  int doDirPin0  =  9; // motor sensor

  #define echoPin   11 //Orange Cable
  #define trigPin   12 //Yellow Cable
  
  int outputValueNeg;
  int outputValuePos;
  int valueCount = 0;
  
  bool moveUp = true;
  int c_MaxValueInMeterRange = 255;
  bool stopWheels = false;

  int stepDelayInUs = 1500; //delay too short will stall motor sensor
  int maxToeslag = 500;

void initPins()
{
  Serial.println("init pins...");
  Serial.println("finished...");
}

void initGlobals()
{
  Serial.println("init globals...");
  Serial.println("finished...");
}

void setup()
{
  
  Serial.begin(9600);
  Serial.println("init...");
  initPins();
  initGlobals();

  pinMode(doDirPin0, OUTPUT);
  pinMode(doStepPin0, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  enableLog = true;

  
}

void loop()
{
  checkWall();
}

void ControlMotors() // sensor ultrasonic
{
  //SensorMotorLinksNEH();
  //SensorMotorRechtsNEH();
}

void SensorMotorLinksNEH()
{
  digitalWrite(doDirPin0, HIGH);
  for (int i = 0; i <= maxToeslag; i++)
  {
    digitalWrite(doStepPin0, LOW);
    digitalWrite(doStepPin0, HIGH);
    delayMicroseconds(stepDelayInUs);
    if (i == maxToeslag)
    {
      digitalWrite(doDirPin0, LOW);
      for (int i = 0; i <= maxToeslag; i++)
      {
        digitalWrite(doStepPin0, LOW);
        digitalWrite(doStepPin0, HIGH);
        delayMicroseconds(stepDelayInUs);
      }
    }
  }
}

void SensorMotorRechtsNEH()
{
  digitalWrite(doDirPin0, LOW);
  for (int i = 0; i <= maxToeslag; i++)
  {
    digitalWrite(doStepPin0, LOW);
    digitalWrite(doStepPin0, HIGH);
    delayMicroseconds(stepDelayInUs);
    if (i == maxToeslag)
    {
//      if (distance > 8)
//      {
//         Serial.println("Wiel moet Rechts gaan");
//      }
      digitalWrite(doDirPin0, HIGH);
      for (int i = 0; i <= maxToeslag; i++)
      {
        digitalWrite(doStepPin0, LOW);
        digitalWrite(doStepPin0, HIGH);
        delayMicroseconds(stepDelayInUs);
      }
    }
  }
  
}

void debugLogging(String a_text, int a_infoType)
{
  if (enableLog == true)
  {
    switch (a_infoType)
    {
      case 0:
        Serial.println("ERROR: " + a_text);
        break;
      case 1:
        Serial.println("WARNING: " + a_text);
        break;
      case 2:
        Serial.println("INFO: " + a_text);
        break;
      default:
        Serial.println(a_text);
        break;
    }
  }
}
 

void checkWall()
{
  
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  delay(250);

  if (distance < 8)
  {
    Serial.println("Wiel moet stoppen");
    outputValueNeg = 0;
    valueCount = 0;

    //SensorMotorLinksNEH();
      digitalWrite(doDirPin0, LOW);
  for (int i = 0; i <= maxToeslag; i++)
  {
    digitalWrite(doStepPin0, LOW);
    digitalWrite(doStepPin0, HIGH);
    delayMicroseconds(stepDelayInUs);
    if (i == maxToeslag)
    {
      if (distance > 10)
      {
         Serial.println("Wiel moet Rechts gaan");
      }
      digitalWrite(doDirPin0, HIGH);
      for (int i = 0; i <= maxToeslag; i++)
      {
        digitalWrite(doStepPin0, LOW);
        digitalWrite(doStepPin0, HIGH);
        delayMicroseconds(stepDelayInUs);
      }
    }
  }
  }
  else
  {
    outputValueNeg = 127;
    valueCount = 50;
    ControlMotors();
  }
  
  analogWrite(aoNeg, valueCount);
  analogWrite(aoPos, outputValueNeg);
  
 
}

