#include <Adafruit_NeoPixel.h>

#define LEDS_PIN    6    // What output pin is the LED strip data line?
#define NUM_LEDS    100  // How many LEDs are there in the strip?
#define FRAME_DELAY 75   // Time between frames in ms (smaller is faster)
#define SCAN_FRAMES 500  // How many frames to stay on a single mode
#define MAX_MODE    20   // Number of the last mode

#define COLOR_RED   strip.Color(255, 0, 0)
#define COLOR_GREEN strip.Color(0, 255, 0)
#define COLOR_BLUE strip.Color(0, 0, 255)
#define COLOR_WHITE strip.Color(255, 255, 255)
#define COLOR_BLACK strip.Color(0, 0, 0)

uint8_t  mode;  // What display are we doing?
uint16_t frame; // How long have we been doing it?

uint32_t buffer[50];
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LEDS_PIN,
                                            NEO_RGB + NEO_KHZ800);

void setup()
{
  uint8_t i;

  randomSeed(analogRead(0));

  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(64);
//  strip.show();

  mode = 0;
  frame = 0;
}

void loop()
{
//    Serial.println(mode);
  switch(mode) {
  case 0:    
    strip.setPixelColor(frame, COLOR_GREEN);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 1:
    strip.setPixelColor(frame, COLOR_RED);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 2:
    strip.setPixelColor(frame, COLOR_BLUE);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 3:
    strip.setPixelColor(frame, COLOR_WHITE);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 4:
    strip.setPixelColor(NUM_LEDS - frame, COLOR_GREEN);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 5:
    strip.setPixelColor(NUM_LEDS - frame, COLOR_RED);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 6:
    strip.setPixelColor(NUM_LEDS - frame, COLOR_BLUE);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 7:
    strip.setPixelColor(NUM_LEDS - frame, COLOR_WHITE);
    if (frame > NUM_LEDS)
    {
      frame = SCAN_FRAMES;
    }
    break;
  case 8:    
    rainbow(25);
    frame = SCAN_FRAMES;
    break;
  case 9: // Candy stripes (white-red)
    if(frame == 0) {
      fillBufferSolid(0, 10, COLOR_WHITE);
      fillBufferSolid(10, 10, COLOR_RED);
      fillBufferSolid(20, 10, COLOR_BLACK);
    }
    drawMarquee(30);
    break;
  case 10: // Candy stripes (red-green)
    if(frame == 0) {
      fillBufferSolid(0, 10, COLOR_RED);
      fillBufferSolid(10, 10, COLOR_GREEN);
      fillBufferSolid(20, 10, COLOR_BLACK);
    }
    drawMarquee(30);
    break;
  case 11: // Candy stripes (green-blue)
    if(frame == 0) {
      fillBufferSolid(0, 10, COLOR_GREEN);
      fillBufferSolid(10, 10, COLOR_BLUE);
      fillBufferSolid(20, 10, COLOR_BLACK);
    }
    drawMarquee(30);
    break;
  case 12: // Thin green stripes
    if(frame == 0) {
      fillBufferSolid(0, 3, COLOR_GREEN);
      fillBufferSolid(3, 7, COLOR_BLACK);
    }
    drawMarquee(10);
    break;
  case 13: // Thin red stripes
    if(frame == 0) {
      fillBufferSolid(0, 3, COLOR_RED);
      fillBufferSolid(3, 7, COLOR_BLACK);
    }
    drawMarquee(10);
    break;
  case 14: // Thin blue stripes
    if(frame == 0) {
      fillBufferSolid(0, 3, COLOR_BLUE);
      fillBufferSolid(3, 7, COLOR_BLACK);
    }
    drawMarquee(10);
    break;
  case 15: // Red/black gradient stripes
    if(frame == 0) {
      fillBufferGradient(0,  10, 0,   0, 0, 255, 0, 0);
      fillBufferGradient(10, 10, 255, 0, 0, 0,   0, 0);
    }
    drawMarquee(20);
    break;
  case 16: // Green/black gradient stripes
    if(frame == 0) {
      fillBufferGradient(0,  10, 0,   0, 0, 0, 255, 0);
      fillBufferGradient(10, 10, 0, 255, 0, 0, 0,   0);
    }
    drawMarquee(20);
    break;
  case 17: // Blue/black gradient stripes
    if(frame == 0) {
      fillBufferGradient(0,  10, 0,   0, 0, 0, 0, 255);
      fillBufferGradient(10, 10, 0, 0, 255, 0, 0,   0);
    }
    drawMarquee(20);
    break;
  case 18: // White/black gradient stripes
    if(frame == 0) {
      fillBufferGradient(0,  10, 0, 0, 0, 255, 255, 255);
      fillBufferGradient(10, 10, 255, 255, 255, 0, 0, 0);
    }
    drawMarquee(20);
    break;
  case 19:
    strip.setPixelColor(frame, COLOR_BLACK);
    if (frame > NUM_LEDS)
    {
      colorSnake(1+random(4), Wheel(25 + random(230)), FRAME_DELAY + 10*random(7), false);
      colorSnake(1+random(4), Wheel(25 + random(230)), FRAME_DELAY + 10*random(7), true);
      frame = SCAN_FRAMES;
    }
  case 20:
    if (frame > NUM_LEDS)
    {
      uint16_t frame2 = ((frame - NUM_LEDS) * 10 ) % 511;
      if (frame2 > 255)
      {      
        frame2 = 511 - frame2;
      }
      drawSolid(strip.Color(frame2, frame2, frame2));
    }
    else
    {
      strip.setPixelColor(frame, COLOR_BLACK);
    }
  }

  strip.show();
  frame++;
  delay(FRAME_DELAY);
  if(frame > SCAN_FRAMES) {
//    mode = random(MAX_MODE + 1);
    if (mode < MAX_MODE)
    {      
      mode++;
    }
    else
    {
      mode = 0;    
    }
    frame = 0;
  }
}

void colorSnake(uint8_t l, uint32_t c, uint8_t wait, boolean reverse) {
//  Serial.println("===================");
  uint32_t no = strip.Color(0, 0, 0);
  uint16_t s = strip.numPixels();

  int16_t from = reverse ? s+l+1 : l;
  int16_t to = reverse ? 1 : s+2*l;
  int16_t diff = reverse ? -1: 1;
  
  for(int16_t i=from; (from<=i && i<=to) || (from>=i && i>=to); i+=diff){
        int16_t jon = i-l-1;
        int16_t joff = reverse ? i-1 : i-2*l-1;
//        Serial.print(i);
//        Serial.print("->");
//        Serial.print(jon);
//        Serial.print(",");
//        Serial.println(joff);
        if (jon>=0 && jon<s) {
          strip.setPixelColor(jon, c);
        }        
        if (joff>=0 && joff<s) {
          strip.setPixelColor(joff, no);  
        }
        strip.show();
        delay(wait);    
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<NUM_LEDS; i++) {
//    Serial.print("i=");
//    Serial.print(i);
//    Serial.print(",j=");
//    Serial.println(j);
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void fillBufferSolid(uint8_t start, uint8_t size, uint32_t color)
{
  uint8_t i;
  for(i = start; i != (start + size); i++) {
    buffer[i] = color;
  }
}

void fillBufferGradient(uint8_t start, uint8_t size,
                        uint8_t r0, uint8_t g0, uint8_t b0,
                        uint8_t r1, uint8_t g1, uint8_t b1)
{
  uint8_t i;
  float sizeF = size;
  for(i = 0; i != size; i++) {
    buffer[i + start] = strip.Color((r0 * ((size - i) / sizeF)) + (r1 * (i / sizeF)),
                                    (g0 * ((size - i) / sizeF)) + (g1 * (i / sizeF)),
                                    (b0 * ((size - i) / sizeF)) + (b1 * (i / sizeF)));
  }
}

void drawMarquee(uint8_t size)
{
  uint8_t i;
  for(i = 0; i != NUM_LEDS; i++) {
    strip.setPixelColor(i, buffer[(i + frame) % size]);
  }
}

void drawSolid(uint32_t color)
{
  uint8_t i;
  for(i = 0; i != NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
