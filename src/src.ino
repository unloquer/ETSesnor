#include <FastLED.h>
#define LED_PIN D3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define amarillo CRGB::Yellow 
#define negro CRGB::Black 
#define rojo CRGB::Red
#define azul CRGB::Blue


#define ESCENAS 1


const uint8_t matrixSize  = 8;
#define NUM_LEDS (matrixSize * matrixSize)

int BRIGHTNESS = 60;
CRGB leds[matrixSize* matrixSize];
 
int loop_cnt = 0;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

CRGB matrixBajo[ESCENAS][matrixSize][matrixSize] = {
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
CRGB matrixAlto[ESCENAS][matrixSize][matrixSize] = {
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



void stateHighLow(bool operation,CRGB m1,CRGB m2){
  if(operation){
    
  }
}
void changeLed(){
  for(int i = 0; i< matrixSize; i++) {
    for(int j = 0; j< matrixSize; j++) {
      leds[i*matrixSize + j] = matrix[loop_cnt%ESCENAS][i][j];
    }
  }
  LEDS.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS);
}
void setup() {
  Serial.begin(115200);
  LEDS.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}
 

void loop() {
  changeLed()
  unsigned long startMillis = millis();  // Start of sample window
  unsigned int peakToPeak = 0;
 
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
 
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
   stateHighLow(,matrixBajo,matrixAlto);
   FastLED.show();
   Serial.println(peakToPeak);
   loop_cnt++;
   FastLED.clear();
}
