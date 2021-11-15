#include <FastLED.h>

#define LED_PIN D3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define amarillo CRGB::Yellow 
#define negro CRGB::Black 
#define rojo CRGB::Red
#define azul CRGB::Blue

int loop_cnt = 0;
const uint8_t matrixWidth =8;
const uint8_t matrixHeight=8;
#define NUM_LEDS (matrixWidth * matrixHeight)
#define ESCENAS 1


int BRIGHTNESS = 60;
CRGB leds[matrixWidth * matrixHeight]; 

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
int ruidoMedio=800/2;
//dibujo 1
CRGB matrixBajo[matrixHeight][matrixWidth] = {
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
};
//dibujo 2
CRGB matrixAlto [matrixHeight][matrixWidth] = {
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
    {azul, azul, azul,azul, azul, azul, azul,azul},
};


/*funcion para solo 2 estados*/
void stateHighLow(bool operation,CRGB m1[matrixHeight][matrixWidth],CRGB m2[matrixHeight][matrixWidth]){
  if(operation){
    changeLed(m1);
  }else{
    changeLed(m2);
  }
}
void changeLed(CRGB matrix[matrixHeight][matrixWidth]){
  for(int i = 0; i< matrixHeight; i++) {
    for(int j = 0; j< matrixWidth; j++) {
      leds[i*matrixWidth + j] = matrix[loop_cnt%ESCENAS][i][j];
    }
  }
}
void setup() {
  Serial.begin(115200);
  LEDS.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}
 

void loop() {
  
  unsigned long startMillis = millis();  // Start of sample window
  unsigned short int peakToPeak = 0;
 
  unsigned short int signalMax = 0;
  unsigned short int signalMin = 1024;
 
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
   stateHighLow(peakToPeak<ruidoMedio,matrixBajo,matrixAlto);
   FastLED.show();
   Serial.println(peakToPeak);
   FastLED.clear();
}
