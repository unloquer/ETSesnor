#include <FastLED.h>
#define LED_PIN D3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define amarillo CRGB::Yellow 
#define negro CRGB::Black 
#define rojo CRGB::Red
#define azul CRGB::Blue
 
const uint8_t matrixWidth  = 8;
const uint8_t matrixHeight = 8;
#define NUM_LEDS (matrixWidth * matrixHeight)
 
int BRIGHTNESS = 60;
CRGB leds[matrixWidth * matrixHeight];
 
int loop_cnt = 0;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() {
  Serial.begin(115200);
  LEDS.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}
 
#define ESCENAS 1
CRGB matrix[ESCENAS][8][8] = {
  {
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
  },
};
 
void loop() {
  for(int i = 0; i< matrixHeight; i++) {
    for(int j = 0; j< matrixWidth; j++) {
      leds[i*matrixWidth + j] = matrix[loop_cnt%ESCENAS][i][j];
    }
  }
  unsigned long startMillis = millis();  // Start of sample window
  unsigned int peakToPeak = 0;
 
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
 
  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024) {
        if (sample > signalMax)
        {
          signalMax = sample;
        }
        else if (sample < signalMin)
        {
          signalMin = sample;
        }
      }
 
   }
   peakToPeak = signalMax - signalMin;
   int changeBrightness = map(peakToPeak, 20, 500, 0, 100);
   FastLED.setBrightness(changeBrightness);
   FastLED.show();
   Serial.println(peakToPeak);
   loop_cnt++;
   FastLED.clear();
}