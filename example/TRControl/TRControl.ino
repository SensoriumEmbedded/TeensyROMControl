

#define CmdChannel   Serial1  //Serial port connected to the TeensyROM

#include <TeensyROMControl.h>
#include <Bounce2.h>

#define LED_PIN        13
#define Button1_PIN     8
#define Button2_PIN     9
#define Button3_PIN    10
#define Button4_PIN    11
#define Button5_PIN    12
#define Num_Buttons     5
const uint8_t ButtonPins[] = {Button1_PIN, Button2_PIN, Button3_PIN, Button4_PIN, Button5_PIN};
   
#define DebounceIntMs  25  

Bounce Buttons[Num_Buttons];
TeensyROMControl TRCont;
uint8_t VoiceMuteBits = 0; //default to all unmuted

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
         DbgPrintf("Button #%d pressed\n", ButNum+1);
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
               TRCont.PauseSIDToggle();
               break;
            case Button4_PIN:
               VoiceMuteBits ^= 0b001;  //toggle voice 1 mute
               TRCont.SIDVoiceMute(VoiceMuteBits);
               break;
            case Button5_PIN:
               VoiceMuteBits ^= 0b010;  //toggle voice 1 mute
               TRCont.SIDVoiceMute(VoiceMuteBits);
               break;
         }
         digitalWrite(LED_PIN, LOW);
      }
   }
}