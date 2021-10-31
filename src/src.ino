#include <FastLED.h>
#include <TaskScheduler.h>

#define NUM_LEDS 64
#define LED_PIN D6
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
int BRIGHTNESS = 10; 
bool ledToggle = false;
CRGB leds[NUM_LEDS];

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
}
