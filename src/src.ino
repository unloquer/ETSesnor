#include <FastLED.h>
#include <TaskScheduler.h>
const uint8_t kMatrixWidth  = 8;
const uint8_t kMatrixHeight = 8;
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
#define LED_PIN D6
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define analogpin = 0;//mic pin
int BRIGHTNESS = 10; 
bool ledToggle = false;
CRGB leds[NUM_LEDS];

 
int loop_cnt = 0;
 
const int sampleWindow = 50;
unsigned int sample;
 
uint8_t noise[kMatrixWidth][kMatrixHeight];

#define ESCENAS 1 
#define amarillo CRGB::Yellow 
#define black CRGB::Black 
#define rojo CRGB::Red
#define blue CRGB::Blue
 
CRGB matrix[ESCENAS][8][8] = {
  {
    {blue, blue, blue,blue, blue, blue, blue,blue},
    {blue, blue, blue,blue, blue, blue, blue,blue},
    {blue, blue, blue,blue, blue, blue, blue,blue},
    {blue, blue, blue,blue, blue, blue, blue,blue},
    {blue, blue, blue,blue, blue, blue, blue,blue},
    {blue, blue, blue,blue, blue, blue, blue,blue},
    {blue, blue, blue,blue, blue, blue, blue,blue},
    {blue, blue, blue,blue, blue, blue, blue,blue},
  },
};

CRGB setColor(){
  CRGB color = CRGB::Gold;
  return color ;

}
void setLed(){
  ledToggle = !ledToggle;
    for(int i=0; i < NUM_LEDS; i++) leds[i] = ledToggle ? setColor() : CRGB::Black;
      FastLED.show();
}

Scheduler runner;
Task ledBlink(1000, TASK_FOREVER, &setLed);

void setup() {
    runner.init();
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("1");
    FastLED.setBrightness(BRIGHTNESS);
    LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    runner.addTask(ledBlink);
    ledBlink.enable();
}
void loop() {  
    runner.execute();
 
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
 
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
 
 while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(analogpin);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
 
  int cambiarBrillo = map(volts, 0, 5, 0, 100);

    loop_cnt++;
}
