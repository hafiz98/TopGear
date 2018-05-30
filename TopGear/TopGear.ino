//                Information

//                Developers
//----------------------------------------
//  Hafiz Elkilic     |   74005   |   Helk
//  Nassim Tijani     |   76654   |   Ntij
//  Emirhan Demirci   |   76716   |   Edem
//----------------------------------------

//Date: 24-05-2018

//NEH: Nassim Emirhan Hafiz 



  bool enableLog;

  //Wielen H-Brug
  int aoNeg = 9;
  int aoPos = 10;
  
  int outputValueNeg;
  int outputValuePos;
  int valueCount = 0;
  bool moveUp = true;
  int c_MaxValueInMeterRange = 255;
  bool stopWheels = false;
  
void initPins()
{
  Serial.println("init pins...");

  //Ultrasonic Sensor
  #define echoPin 11 //Orange Cable
  #define trigPin 12 //Yellow Cable

  Serial.println("finished...");
}

void initGlobals()
{
  Serial.println("init globals...");
  
  enableLog = true;

  //Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.println("finished...");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("init...");
  initPins();
  initGlobals();
}

void loop()
{
  handleMovingCoilMeter();
  //ultrasonicSensorNEH();
  checkWall();
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

void ultrasonicSensorNEH() 
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
  delay(500);
}

void loopMotor()
{
  if (valueCount < c_MaxValueInMeterRange && moveUp == true && stopWheels == false)
  {
    valueCount++;
  }
  else
  {
    moveUp = false;
  }

  if (valueCount > 0 && moveUp == false && stopWheels == false)
  {
    valueCount--;
  }
  else
  {
    moveUp = true;
  }
  
  Serial.println("valueCount.." + (String)valueCount);
  delay(100);
  handleMovingCoilMeter();
}

void handleMovingCoilMeter()
{

}

void checkWall()
{

  //outputValuePos = valueCount;
  //outputValueNeg = 127; //c_MaxValueInMeterRange - valueCount;

  
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);

  if (distance < 8)
  {
    Serial.println("Wiel moet stoppen");
    outputValueNeg = 0;
    valueCount = 0;
  }
  else
  {
    outputValueNeg = 127;
    valueCount = 50;
  }

  analogWrite(aoNeg, outputValuePos);
  analogWrite(aoPos, outputValueNeg);
 
  
}

