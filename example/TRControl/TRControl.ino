

#include <TeensyROMControl.h>
#include <Bounce2.h>

#define CommandChannel   Serial  //Serial port connected to the TeensyROM

#define LED_PIN        13
#define Button1_PIN     3
#define Button2_PIN     4
#define Button3_PIN     5
#define Button4_PIN     6
#define Button5_PIN     7
#define Button6_PIN     8
#define Button7_PIN     9
#define Button8_PIN    10
#define Button9_PIN    11
#define Button10_PIN   12

#define Num_Buttons    10
const uint8_t ButtonPins[Num_Buttons] = 
{
   Button1_PIN, 
   Button2_PIN, 
   Button3_PIN, 
   Button4_PIN, 
   Button5_PIN,
   Button6_PIN,
   Button7_PIN,
   Button8_PIN,
   Button9_PIN,
   Button10_PIN,
};
   
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
               TRCont.LaunchFile(DriveTeensy, "/SID Cover Tunes/Tom Sawyer            Rush");
               break;
            case Button4_PIN:
               TRCont.LaunchFile(DriveTeensy, "/MIDI + ASID/Cynthcart 2.0.1       +Datel MIDI");
               break;
            case Button5_PIN:
               TRCont.LaunchFile(DriveTeensy, "/Games/Gorf!");
               //TRCont.LaunchFile(DriveUSB, "/multimedia/totaleclipse-fth.prg");
               break;
            case Button6_PIN:
               TRCont.PauseSIDToggle(); //toggle SID pause
               break;
            case Button7_PIN:
               TRCont.VoiceMuteToggle(1); //toggle voice 1 mute
               break;
            case Button8_PIN:
               TRCont.VoiceMuteToggle(2); //toggle voice 2 mute
               break;
            case Button9_PIN:
               TRCont.VoiceMuteToggle(3); //toggle voice 3 mute
               break;
            case Button10_PIN:
               TRCont.C64PauseToggle();  //toggle C64 pause
               break;
         }
         digitalWrite(LED_PIN, LOW);
      }
   }
}