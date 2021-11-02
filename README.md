# TeensyDelay
Stereo delay using Teensy 4.1 + AudioShield + 10pots :

Pots usages :
- Pot 1 = Delay 1 Level
- Pot 2 = Delay 2 Level
- Pot 3 = Delay 3 Level
- Pot 4 = Feedback Level
- Pot 5 = Intput Level
  
- Pot 6 = AudioShield DSP EQ Low frequency output
- Pot 7 = AudioShield DSP EQ Bass frequency output
- Pot 8 = AudioShield DSP EQ Mid frequency output
- Pot 9 = AudioShield DSP EQ High frequency output
- Pot 10 = AudioShield DSP EQ Top frequency output

Can also be configured as intput frequency EQ.
  
  Use a lot of memory, sometime sound a bit weird, may switch to mono instead ?
  Changing the delay time seem not be possible with a pot, it produce weird artefact...
    Instead, I use a switch to change the settings of all delay.
  
   ![Audio Tool Graph](https://raw.githubusercontent.com/DmaEvilCorp/TeensyDelay/main/AudioToolGraph.PNG) 
   
 
Future modifications:
Adding a lfo to modulate the level of feedback or the levels of delays
Endless...
