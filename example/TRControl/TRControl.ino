

#include <TeensyROMControl.h>
#include <Bounce2.h>

#define CommandChannel   Serial  //Serial port connected to the TeensyROM

#define LED_PIN        13
#define Button1_PIN     8
#define Button2_PIN     9
#define Button3_PIN    10
#define Button4_PIN    11
#define Button5_PIN    12

#define Num_Buttons     5
const uint8_t ButtonPins[Num_Buttons] = {Button1_PIN, Button2_PIN, Button3_PIN, Button4_PIN, Button5_PIN};
   
#define DebounceIntMs  25  

Bounce Buttons[Num_Buttons];
TeensyROMControl TRCont;

void setup() 
{
   for (uint8_t ButNum = 0; ButNum < Num_Buttons; ButNum++) 
   {
      Buttons[ButNum].attach(ButtonPins[ButNum], INPUT_PULLUP);
      Buttons[ButNum].interval(DebounceIntMs);
   }
   
   pinMode(LED_PIN, OUTPUT);   
   digitalWrite(LED_PIN, LOW);
   
   CommandChannel.begin(115200);
   TRCont.begin(CommandChannel);
}

void loop()
{
   for (uint8_t ButNum = 0; ButNum < Num_Buttons; ButNum++) 
   {
      Buttons[ButNum].update();
      if(Buttons[ButNum].fell())
      {
         DbgPrintf("Button #%d pressed\n", ButNum+1);
         digitalWrite(LED_PIN, HIGH);
         switch(ButtonPins[ButNum])
         {
            case Button1_PIN:
               TRCont.MenuReset();  //Return to main TR Menu
               break;
            case Button2_PIN:
               TRCont.LaunchFile(DriveSD, "/Paranoid.sid");
               break;
            case Button3_PIN:
               TRCont.PauseSIDToggle(); //toggle SID pause
               break;
            case Button4_PIN:
               TRCont.VoiceMuteToggle(3); //toggle voice 1 mute
               break;
            case Button5_PIN:
               TRCont.C64PauseToggle();  //toggle C64 pause
               break;
         }
         digitalWrite(LED_PIN, LOW);
      }
   }
}