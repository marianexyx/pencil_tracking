#include <Servo.h>

Servo servo_down;
Servo servo_up;

bool bCoreFullDataBlock = false; //czy są jakieś dane do wysłania
String strDataReceived;
char buffer;
void skladajPrzychodzaceDane()
{
  while (Serial.available() > 0)
  {
    buffer = Serial.read();
    if (buffer == '$') 
    {
      bCoreFullDataBlock = true;
      break;
    }
    strDataReceived += buffer;
  }
}

String answer;

void sprawdzajPrzychodzaceDane()
{
  if (bCoreFullDataBlock == true) //odczytywanie danych po serialu z core'a
  {
    if (strDataReceived.substring(0,1) == "(" && strDataReceived.substring(4,5) == "," && 
        strDataReceived.substring(8,9) == ")")
      {
        String str_servo_down_angle = strDataReceived.substring(1,4);
        int n_servo_down_angle = str_servo_down_angle.toInt();
        String str_servo_up_angle = strDataReceived.substring(5,8);
        int n_servo_up_angle = str_servo_up_angle.toInt();
        servo_down.write(n_servo_down_angle);
        servo_up.write(n_servo_up_angle);
        delay(20);
        answer = "ok " + strDataReceived;
        Serial.write(answer.c_str());
        answer = "";
      }
     else
     {
       answer = "error " + strDataReceived;
       Serial.write(answer.c_str());
       answer = "";
     }

    bCoreFullDataBlock = false; //wiadomość otrzymana. wyczyść flagę
    strDataReceived = "";
  }
}

void setup()
{
  servo_down.attach(9);
  servo_up.attach(10);
  Serial.begin(9600);
  servo_down.write(90);
  servo_up.write(90);
}

void loop() 
{
  skladajPrzychodzaceDane();
  sprawdzajPrzychodzaceDane();
}



