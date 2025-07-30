
#include <TeensyROMControl.h>
#include <Bounce2.h>

#define Button1_PIN    10
#define Button2_PIN    11
#define Button3_PIN    12
#define Num_Buttons     3
uint8_t ButtonPins[] = {Button1_PIN, Button2_PIN, Button3_PIN};
   
#define DebounceIntMs  25  
#define LED_PIN        13

#define CmdChannel   Serial1  //port connected to the TeensyROM

Bounce Buttons[Num_Buttons];
TeensyROMControl TRCont;

void setup() 
{
   CmdChannel.begin(115200);

   for (uint8_t ButNum = 0; ButNum < Num_Buttons; ButNum++) 
   {
      Buttons[ButNum].attach(ButtonPins[ButNum], INPUT_PULLUP);
      Buttons[ButNum].interval(DebounceIntMs);
   }
   
   pinMode(LED_PIN, OUTPUT);   
   digitalWrite(LED_PIN, LOW);
   
   TRCont.begin(CmdChannel);
}

void loop()
{
   for (uint8_t ButNum = 0; ButNum < Num_Buttons; ButNum++) 
   {
      Buttons[ButNum].update();
      if(Buttons[ButNum].fell())
      {
         DbgPrintf("Button #%d pressed\n", ButNum);
         digitalWrite(LED_PIN, HIGH);
         switch(ButtonPins[ButNum])
         {
            case Button1_PIN:
               TRCont.MenuReset();
               break;
            case Button2_PIN:
               TRCont.LaunchFile(DriveSD, "/Paranoid.sid");
               break;
            case Button3_PIN:
               TRCont.LaunchFile(DriveUSB, "/games/sound check.prg");
               break;
         }
         digitalWrite(LED_PIN, LOW);
      }
   }
}