//DMA EVIL CORP - TEENSY DELAY BOX
//14.01.2021
//COPYLEFT

#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=128,103
AudioEffectDelay         delay1;         //xy=385,199
AudioEffectDelay         delay2;         //xy=387,408
AudioMixer4              mixerLeft;      //xy=563,89
AudioMixer4              mixerRight;     //xy=567,298
AudioMixer4              mixerdelay1;    //xy=571,173
AudioMixer4              mixerdelay2;    //xy=573,382
AudioMixer4              OutLeft; //xy=753,109
AudioMixer4              OutRight; //xy=754,315
AudioOutputI2S           i2s2;           //xy=985,115
AudioConnection          patchCord1(i2s1, 0, mixerLeft, 0);
AudioConnection          patchCord2(i2s1, 1, mixerRight, 0);
AudioConnection          patchCord3(delay1, 0, mixerdelay1, 0);
AudioConnection          patchCord4(delay1, 1, mixerdelay1, 1);
AudioConnection          patchCord5(delay1, 2, mixerdelay1, 2);
AudioConnection          patchCord6(delay1, 3, mixerdelay1, 3);
AudioConnection          patchCord7(delay2, 0, mixerdelay2, 0);
AudioConnection          patchCord8(delay2, 1, mixerdelay2, 1);
AudioConnection          patchCord9(delay2, 2, mixerdelay2, 2);
AudioConnection          patchCord10(delay2, 3, mixerdelay2, 3);
AudioConnection          patchCord11(mixerLeft, delay1);
AudioConnection          patchCord12(mixerLeft, 0, OutLeft, 0);
AudioConnection          patchCord13(mixerRight, delay2);
AudioConnection          patchCord14(mixerRight, 0, OutRight, 0);
AudioConnection          patchCord15(mixerdelay1, 0, mixerLeft, 1);
AudioConnection          patchCord16(mixerdelay1, 0, OutLeft, 1);
AudioConnection          patchCord17(mixerdelay2, 0, mixerRight, 1);
AudioConnection          patchCord18(mixerdelay2, 0, OutRight, 1);
AudioConnection          patchCord19(OutLeft, 0, i2s2, 0);
AudioConnection          patchCord20(OutRight, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=119,149
// GUItool: end automatically generated code

Bounce button33 = Bounce(33, 100);
int loopmode = 0;
int delay1time = 100;
int delay2time = 250;
int delay3time = 500;
int delay1time2x = 200;
int delay2time2x = 500;
int delay3time2x = 1000;


void setup() {
  // Initial setup:
  Serial.begin(9600);
  Serial.print("Ready ?");
  pinMode(33, INPUT_PULLUP);
  AudioMemory(850); //Lot of memory
  sgtl5000_1.enable(); //Enable Codec
  //sgtl5000_1.volume(1); //Headset output level
  sgtl5000_1.muteHeadphone();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN); //Enable line input
  //sgtl5000_1.dacVolume(1); //Left+Right output level
  sgtl5000_1.lineInLevel(5);
  sgtl5000_1.lineOutLevel(29);
  //sgtl5000_1.autoVolumeControl(0, 0, 1, 0, 0, 0);
  //sgtl5000_1.autoVolumeEnable();
  sgtl5000_1.autoVolumeDisable();
  sgtl5000_1.surroundSoundDisable();
  //sgtl5000_1.lineOutLevel(29); //By default 1.29v p-p
  sgtl5000_1.audioPostProcessorEnable(); //Enable effects on the output (Eq)
  //sgtl5000_1.surroundSoundEnable(); // Enable virtual surround processing
  sgtl5000_1.eqSelect(3); //Enable graphic Eq
  sgtl5000_1.eqBands(0, 0, 0, 0, 0); //Output 5 bands Eq

  mixerLeft.gain(0, 1); //Left channel input
  mixerLeft.gain(1, 1); //Left channel feedback input
  mixerLeft.gain(2, 0); //Not used
  mixerLeft.gain(3, 0); //Not used

  OutLeft.gain(0, 1); //Left channel output
  OutLeft.gain(1, 1); //Left channel output delay
  OutLeft.gain(2, 0); //Not used
  OutLeft.gain(3, 0); //Not used

  mixerdelay1.gain(0, 0); //Left channel feedback 1
  mixerdelay1.gain(1, 0); //Left channel feedback 2
  mixerdelay1.gain(2, 0); //Left channel feedback 3
  mixerdelay1.gain(3, 0); //Not used

  delay1.delay(0, 100); //Left channel delay 1
  delay1.delay(1, 250); //Left channel delay 2
  delay1.delay(2, 1000); //Left channel delay 3
  delay1.disable(3); //Not used
  delay1.disable(4); //Not used
  delay1.disable(5); //Not used
  delay1.disable(6); //Not used
  delay1.disable(7); //Not used

  mixerRight.gain(0, 1); //Right channel input
  mixerRight.gain(1, 1); //Right channel feedback input
  mixerRight.gain(2, 0); //Not used
  mixerRight.gain(3, 0);

  OutRight.gain(0, 1); //Right channel output
  OutRight.gain(1, 1); //Right channel output delay
  OutRight.gain(2, 0); //Not used
  OutRight.gain(3, 0); //Not used

  mixerdelay2.gain(0, 0); //Right channel feedback 1
  mixerdelay2.gain(1, 0); //Right channel feedback 2
  mixerdelay2.gain(2, 0); //Right channel feedback 3
  mixerdelay2.gain(3, 0); //Not Used

  delay2.delay(0, 100); //Right channel delay 1
  delay2.delay(1, 250); //Right channel delay 2
  delay2.delay(2, 500); //Right channel delay 3
  delay2.disable(3); //Not used
  delay2.disable(4); //Not used
  delay2.disable(5); //Not used
  delay2.disable(6); //Not used
  delay2.disable(7); //Not used

  delay(1000);
//  Serial.println("Start");
}

void loop() {

  //LOOP LOOP LOOP
  int knob1 = analogRead(A13);  // knob = 0 to 1023 Input level L+R
  int knob2 = analogRead(A15);  // knob = 0 to 1023 Delay 1 level L+R
  int knob3 = analogRead(A14);  // knob = 0 to 1023 Delay 2 level L+R
  int knob4 = analogRead(A16);  // knob = 0 to 1023 Delay 3 level L+R
  int knob5 = analogRead(A17);  // knob = 0 to 1023 Feedback level L+R
  int knob6 = analogRead(A12); // knob = 0 to 1023 EQ Band 1
  int knob7 = analogRead(A11); // knob = 0 to 1023 EQ Band 2
  int knob8 = analogRead(A10); // knob = 0 to 1023 EQ Band 3
  int knob9 = analogRead(A0); // knob = 0 to 1023 EQ Band 4
  int knob10 = analogRead(A2); // knob = 0 to 1023 EQ Band 5
  //  Debug print knobs values
  //  Serial.println(knob1);
  //  Serial.println(knob2);
  //  Serial.println(knob3);
  //  Serial.println(knob4);
  //  Serial.println(knob5);
  //  Serial.println(knob6);
  //  Serial.println(knob7);
  //  Serial.println(knob8);
  //  Serial.println(knob9);
  //  Serial.println(knob10);
  float InputLevel = (float)knob1 / 1023.0;
  float Delay1Level = (float)knob2 / 1023.0;
  float Delay2Level = (float)knob3 / 1023.0;
  float Delay3Level = (float)knob4 / 1023.0;
  float FeedbackLevel = (float)knob5 / 1023.0;

  //Setup levels of the 5 bands Eq
  //Range from 1.00 (+12dB) to -1.00 (-11.75dB)
  float BassLevel  = map((float)knob6, 0, 1023, -0.5, 0.5);
  float MidBassLevel  = map((float)knob7, 0, 1023, -0.5, 0.5);
  float MidLevel  = map((float)knob8, 0, 1023, -0.5, 0.5);
  float MidHighLevel  = map((float)knob9, 0, 1023, -0.5, 0.5);
  float HighLevel  = map((float)knob10, 0, 1023, -0.5, 0.5);
  //  Debug print EQ values
  //  Serial.println(BassLevel);
  //  Serial.println(MidBassLevel);
  //  Serial.println(MidLevel);
  //  Serial.println(MidHighLevel);
  //  Serial.println(HighLevel);
  sgtl5000_1.eqBands(BassLevel, MidBassLevel, MidLevel, MidHighLevel, HighLevel); //Output 5 bands Eq

  mixerLeft.gain(0, InputLevel); //Left channel input
  mixerRight.gain(0, InputLevel); //Right channel input

  mixerdelay1.gain(0, Delay1Level); //Left channel delay level 1
  mixerdelay1.gain(1, Delay2Level); //Left channel delay level 2
  mixerdelay1.gain(2, Delay3Level); //Left channel delay level 3

  mixerdelay2.gain(0, Delay1Level); //Left channel delay level 1
  mixerdelay2.gain(1, Delay2Level); //Left channel delay level 2
  mixerdelay2.gain(2, Delay3Level); //Left channel delay level 3

  mixerLeft.gain(1, FeedbackLevel); //Left feedback level
  mixerRight.gain(1, FeedbackLevel); //Right feedback level

  // Change delay times (2x)
  button33.update();
  if (button33.read() == LOW) {
    delay1.delay(0, delay1time); //Left channel delay 1
    delay1.delay(1, delay2time); //Left channel delay 2
    delay1.delay(2, delay3time); //Left channel delay 3
    delay2.delay(0, delay1time); //Right channel delay 1
    delay2.delay(1, delay2time); //Right channel delay 2
    delay2.delay(2, delay3time); //Right channel delay 3
  }
  else {
    delay1.delay(0, delay1time2x); //Left channel delay 1
    delay1.delay(1, delay2time2x); //Left channel delay 2
    delay1.delay(2, delay3time2x); //Left channel delay 3
    delay2.delay(0, delay1time2x); //Right channel delay 1
    delay2.delay(1, delay2time2x); //Right channel delay 2
    delay2.delay(2, delay3time2x); //Right channel delay 3
  }

//  Serial.println(button33.read());
//  Serial.println("Loop done");
//  Serial.println(AudioMemoryUsage());

}
