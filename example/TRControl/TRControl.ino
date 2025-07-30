
#include <TeensyROMControl.h>

#define Button1_PIN    10
#define Button2_PIN    11
#define Button3_PIN    12
#define LED_PIN        13

#define CmdChannel   Serial1  //port connected to the TeensyROM

TeensyROMControl TRCont;

void setup() 
{
   CmdChannel.begin(115200);
  
   pinMode(Button1_PIN, INPUT_PULLUP);
   pinMode(Button2_PIN, INPUT_PULLUP);
   pinMode(Button3_PIN, INPUT_PULLUP);
   pinMode(LED_PIN, OUTPUT);
   
   digitalWrite(LED_PIN, LOW);
   
   TRCont.begin(CmdChannel);
   
}

void loop()
{
   if (digitalRead(Button1_PIN) == 0)
   {
      digitalWrite(LED_PIN, HIGH);
      TRCont.MenuReset();
      while(digitalRead(Button1_PIN) == 0);
      digitalWrite(LED_PIN, LOW);
   }
   
   if (digitalRead(Button2_PIN) == 0)
   {
      digitalWrite(LED_PIN, HIGH);
      TRCont.LaunchFile(DriveUSB, "/games/sound check.prg");
      //TRCont.LaunchFile(DriveSD, "Paranoid.sid");
      while(digitalRead(Button2_PIN) == 0);
      digitalWrite(LED_PIN, LOW);
   }
   
}