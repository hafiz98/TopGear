//                Information

//                Developers
//----------------------------------------
//  Hafiz Elkilic     |   74005   |   Helk
//  Nassim Tijani     |   76654   |   Ntij
//  Emirhan Demirci   |   76716   |   Edem
//----------------------------------------

//Date: 24-05-2018




bool enableLog;


void setup()
{
  Serial.begin(115200);
  Serial.println("init...");
  initGlobals();
}

void loop()
{

}

void initGlobals()
{
  Serial.println("init globals...");
  enableLog = true;
  Serial.println("finished...");
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

