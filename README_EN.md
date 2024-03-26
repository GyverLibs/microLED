# microLED 
MicroLED - an ultra-lightweight library for working with addressable LED strips/matrices
- The main feature: color compression, the code occupies significantly less space in SRAM compared to alternatives (FastLED, NeoPixel, etc.)
- Supports color compression: 8, 16, and 24 bits
- Possibility to work without a buffer at all (with some restrictions)
- Working with color:
    - RGB
    - HSV
    - Hex (Web color)
    - "Color wheel" (1500 or 255 of the brightest shades)
    - 16 built-in colors
    - Colors by temperature
    - Gradients
- Ability to read compressed color in MHEX 0xRRGGBB format and RGB array
- Optimized ASM output
- Built-in support for working with addressable matrices
- Supported chips: 2811/2812/2813/2815/2818/WS6812/APA102
- Built-in TinyLED for working on ATtiny
- Compatibility with data types and tools from FastLED
- Expanded interrupt settings
- Native support for matrices
- Preservation of `millis()` functionality (only for AVR)
- Support for SPI strips (software and hardware)

## Compatibility
Only AVR: Atmega and Attiny

### Documentation
There is [expanded documentation](https://alexgyver.ru/microled/) to the library 

## Content
- [Installation](#install)
- [Initialization](#init)
- [Use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"> </a>
## Installation
- The library can be found by the name MicroLED and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/gyverlibs/microled/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unpack and put in `C:\Program Files (x86)\Arduino\Libraries` (Windows x64)
    - Unpack and put in `C:\Program Files\Arduino\Libraries` (Windows x32)
    - Unpack and put in `Documents\Arduino\libraries\`
    - (Arduino IDE) Automatic installation from .zip: Sketch\Include Library\Add .ZIP Library... and specify the downloaded archive
- Read more detailed instructions for installing libraries [here](https://alexgyver.ru/arduino-first)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- Through the IDE library manager: find the library how to install and click "update"
- Manually: **remove the folder with the old version**, and then put a new one in its place. "Replacement" cannot be done: sometimes, in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## Initialization
```cpp
microLED<amount, pin, clock, chip, order, cli, millis>
- amount – the number of LEDs on the strip. To work in stream mode, you can specify 0, as the length of the strip is effectively unlimited.
- pin – the pin to which the data input of the strip is connected (D, Din, DI).
- clock – the pin to which the clock input of the strip is connected (C, CLK). This pin is only connected for SPI strips, for example, APA102.
    - For working with WSxxxx series strips, you need to specify M_LED_NO_CLOCK or minus 1 instead of this pin, i.e., -1.
- chip – the model of the strip (LEDs), supported by the library are LEDWS2811, LEDWS2812, LEDWS2813, LEDWS2815, LEDWS2818, LEDWS6812, APA102, APA102SPI. The choice of the strip model sets the speed of the protocol (they vary) and settings for current consumption for limitation modes (read further on this).
- order – the order of colors on the strip. In an ideal world, the order of colors should depend on the chip model, and this setting should be built into the chip choice, but some Chinese strips, although matching one chip in protocol, may have a different color order. Thus, the library supports more types of strips than mentioned above, but you need to guess with the choice of "clone" and the order of colors.
    - Orders: ORDER_RGB, ORDER_RBG, ORDER_BRG, ORDER_BGR, ORDER_GRB, ORDER_GBR.

microLED<NUMLEDS, STRIP_PIN, -1, LED_WS2811, ORDER_GBR> strip;
microLED<NUMLEDS, STRIP_PIN, -1, LED_WS2812, ORDER_GRB> strip;
microLED<NUMLEDS, STRIP_PIN, -1, LED_WS2813, ORDER_GRB> strip;
microLED<NUMLEDS, STRIP_PIN, -1, LED_WS2815, ORDER_GRB> strip;
microLED<NUMLEDS, STRIP_PIN, -1, LED_WS2818, ORDER_RGB> strip;
microLED<NUMLEDS, STRIP_PIN, -1, LED_WS6812, ORDER_RGB> strip;
microLED<NUMLEDS, STRIP_PIN, CLOCK_PIN, LED_APA102, ORDER_BGR> strip;
microLED<NUMLEDS, -1, -1, LED_APA102_SPI, ORDER_BGR> strip;
```

<a id="usage"> </a>
## Usage
See [documentation] (https://alexgyver.ru/microled/)
```cpp
// template: <number, pin, chip, order, interrupts, millis>
// initialize STRIP: no arguments
microLED;

// initialize MATRIX: matrix width, matrix height, matrix type, connection angle, direction (see MATRIX CONNECTION)
microLED(uint8_t width, uint8_t height, M_type type, M_connection conn, M_dir dir);

// strip and matrix
void set(int n, mData color);   // set the color of the LED to mData (equivalent to leds[n] = color)
mData get(int num);             // get the color of the LED in mData (equivalent to leds[n])
void fill(mData color);         // fill with the color mData
void fill(int from, int to, mData color); // fill with the color mData
void fillGradient(int from, int to, mData color1, mData color2);  // fill with a gradient of two colors
void fade(int num, byte val);   // reduce brightness

// matrix
uint16_t getPixNumber(int x, int y);    // get the pixel number in the strip by coordinates
void set(int x, int y, mData color);    // set the color of pixel x y in mData
mData get(int x, int y);                // get the color of the pixel in mData
void fade(int x, int y, byte val);      // reduce brightness
void drawBitmap8(int X, int Y, const uint8_t *frame, int width, int height);    // output bitmap (1-dimensional bitmap PROGMEM)
void drawBitmap16(int X, int Y, const uint16_t *frame, int width, int height);  // output bitmap (1-dimensional bitmap PROGMEM)
void drawBitmap32(int X, int Y, const uint32_t *frame, int width, int height);  // output bitmap (1-dimensional bitmap PROGMEM)

// general
void setMaxCurrent(int ma);             // set the maximum current (auto brightness correction). 0 - turned off
void setBrightness(uint8_t newBright);  // brightness 0-255
void clear();                           // clear
void setCLI(type);                      // interrupt disable mode CLI_OFF, CLI_LOW, CLI_AVER, CLI_HIGH

// output buffer
void show();            // output the entire buffer

// stream output
void begin();           // start outputting in stream
void send(mData data);  // send a single LED
void end();             // end outputting in stream

// color
uint32_t getHEX(mData data);                        // repackage into 24-bit HEX
mData getFade(mData data, uint8_t val);             // decrease brightness by val
mData getBlend(int x, int amount, mData c0, mData c1);  // get intermediate color
mData mRGB(uint8_t r, uint8_t g, uint8_t b);        // RGB 255, 255, 255
mData mWheel(int color, uint8_t bright=255);        // colors 0-1530 + brightness
mData mWheel8(uint8_t color, uint8_t bright=255);   // colors 0-255 + brightness
mData mHEX(uint32_t color);                         // mHEX color
mData mHSV(uint8_t h, uint8_t s, uint8_t v);        // HSV 255, 255, 255
mData mHSVfast(uint8_t h, uint8_t s, uint8_t v);    // HSV 255, 255, 255
mData mKelvin(int kelvin);                          // temperature

// brightness reduction macros
fade8(x, b)
fade8R(x, b)
fade8G(x, b)
fade8B(x, b)

// packing-unpacking
getR(x)
getG(x)
getB(x)
mergeRGB(r,g,b)
mergeRGBraw(r,g,b)
getCRT(byte x) - get corrected brightness value x considering selected CRT gamma correction model
getCRT_PGM(byte x) - get CRT from PROGMEM (works only if PGM model is selected)
getCRT_SQUARE(byte x) - get CRT by square model
getCRT_QUBIC(byte x) - get CRT by cubic model
RGB24to16(x) - convert 24-bit color to 16-bit
RGB24to8(x) - convert 24-bit color to 8-bit
RGB16to24(x) - convert 16-bit color to 24-bit
RGB8to24(x) - convert 8-bit color to 24-bit
RGB24toR(x) - extract the R byte from 24-bit color
RGB24toG(x) - extract the G byte from 24-bit color
RGB24toB(x) - extract the B byte from 24-bit color
RGBto24(r,g,b) - merge into 24-bit color
RGBto16(r,g,b) - merge into 16-bit color
RGBto8(r,g,b) - merge into 8-bit color
```

<a id="example"> </a>
## Example
The rest of the examples look at ** Examples **!
```cpp
// basic example of working with a strip, main features
// microLED library version 3.0+
// for more detailed information, read the documentation

// constants for convenience
#define STRIP_PIN 2     // strip pin
#define NUMLEDS 20      // number of LEDs

// ===== COLOR DEPTH =====
// 1, 2, 3 (bytes per color)
// At lower color resolution, the sketch will take up significantly less space,
// but the number of shades and brightness levels will decrease!
// The define is made BEFORE THE LIBRARY IS INCLUDED
// Without it, 3 bytes will be the default
#define COLOR_DEBTH 3

// ===== FASTLED SUPPORT =====
// The define is made BEFORE THE LIBRARY IS INCLUDED
// Without it, it will be turned off by default
// #define FASTLED_SUPPORT

#include <microLED.h>   // include the library

// ======= INITIALIZATION =======
// <number-of-LEDs, pin, clock pin, chip, order>
// microLED<NUMLEDS, DATA_PIN, CLOCK_PIN, LED_WS2818, ORDER_GRB> strip;
// CLOCK pin is only needed for SPI strips (like APA102)
// for regular WS strips specify MLED_NO_CLOCK
// see a separate guide in the examples for APA102

// various Chinese knockoffs may be compatible
// with one chip, but have a different color order!
// Supported strip chips and their official color order:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2811, ORDER_GBR> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2813, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2815, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS6812, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, CLOCK_PIN, LED_APA102, ORDER_BGR> strip;
// microLED<NUMLEDS, MLED_NO_CLOCK, MLED_NO_CLOCK, LED_APA102_SPI, ORDER_BGR> strip;  // for hardware SPI


// ======= INTERRUPTS =======
// to increase the reliability of data transfer to the strip, interrupts can be disabled.
// The library has 4 modes:
// CLI_OFF - interrupts are not disabled (possible strip malfunctions)
// CLI_LOW - interrupts are disabled for the duration of one color transmission
// CLI_AVER - interrupts are disabled for the duration of one LED transmission (3 colors)
// CLI_HIGH - interrupts are disabled for the duration of data transmission to the entire strip

// By default, interrupt disabling is set to CLI_OFF (not disabled)
// The parameter is passed as the 5th during initialization:
// microLED<NUMLEDS, STRIP_PIN, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

// ======= SAVE THE MILLIS =======
// When disabling interrupts in mid and high priority mode (CLI_AVER and CLI_HIGH),
// the time functions millis() and micros() will inevitably lag slightly.
// The library includes support functions for time, to activate pass SAVE_MILLIS
// as the 6th argument during initialization:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER, SAVE_MILLIS> strip;
// this will SLOWLY slow down the output to the strip but will allow millis to count without lag!

// initializing the strip (guide above!)
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

void setup() {
  // ===================== BASIC STUFF =====================
  // brightness (0-255)
  strip.setBrightness(60);
  // brightness is applied via CRT gamma
  // applied during .show() output!

  // clearing the buffer (turn off LEDs, black color)
  strip.clear();
  // applied during .show() output!

  strip.show(); // output changes to the strip
  delay(1);     // there must be a pause of at least 40 µs between calls to show!!!!

  // ===================== SETTING COLOR =====================
  // The library supports two ways of working with the strip:
  // changing the color of an individual LED using the function set(led, color)
  // or working manually with the .leds[] array

  // writing strip.set(led, color); is equivalent to strip.leds[led] = color;

  // ------------- BASIC COLOR HANDLING FUNCTIONS ------------
  // The functions listed below return the mData type - a compressed representation of the color

  // mRGB(uint8_t r, uint8_t g, uint8_t b);   // RGB color, 0-255 each channel
  strip.set(0, mRGB(255, 0, 0));              // LED 0, RGB color (255 0 0) (red)

  // mHSV(uint8_t h, uint8_t s, uint8_t v);   // HSV color, 0-255 each channel
  strip.leds[1] = mHSV(30, 255, 255);         // LED 1, color 30, maximum brightness and saturation

  // mHSVfast(uint8_t h, uint8_t s, uint8_t v); // HSV color, 0-255 each channel
  // calculation is slightly faster, but colors are not as smooth
  strip.set(2, mHSVfast(90, 255, 255));       // LED 2, color 90, maximum brightness and saturation

  // mHEX(uint32_t color);        // WEB colors (0xRRGGBB)
  strip.set(3, mHEX(0x30B210));   // LED 3, HEX color 0x30B210

  // the library has 17 predefined colors (max brightness)
  strip.leds[4] = mAqua;          // LED 4, aqua color

  // mWheel(int color);                   // rainbow colors 0-1530
  // mWheel(int color, uint8_t bright);   // rainbow colors 0-1530 + brightness 0-255
  strip.set(5, mWheel(1200));             // LED 5, color 1200

  // mWheel8(int color);                  // rainbow colors 0-255
  // mWheel8(int color, uint8_t bright);  // rainbow colors 0-255 + brightness 0-255
  //strip.set(6, mWheel8(100));    // LED 6, color 100 (range 0-255 along the rainbow)
  strip.set(6, mWheel8(100, 50));   // brightness can be passed as the second parameter

  // mKelvin(int kelvin);           // color temperature 1'000-40'000 Kelvin
  strip.set(7, mKelvin(3500));      // LED 7, color temperature 3500K

  strip.show();                     // display all changes on the strip
  delay(2000);                      // display delay

  // ===================== FILLING =====================
  // There is a ready function to fill the entire strip with color - .fill()
  // accepts a converted color, for example from the color functions or the constants above
  strip.fill(mYellow);  // fill with yellow
  strip.show();         // display changes
  delay(2000);

  // start and end of fill can also be specified
  strip.fill(3, 7, mWheel8(100));   // fill with ~green from LED 3 to 6: count starts at 0, fills up to the specified -1
  strip.show();                     // display changes
  delay(2000);

  // ------------- MANUAL FILL IN A LOOP ------------
  // For example, let's paint half of the strip in one color, the other half in another
  for (int i = 0; i < NUMLEDS / 2; i++) strip.leds[i] = mHSV(0, 255, 255);      // red
  for (int i = NUMLEDS / 2; i < NUMLEDS; i++) strip.leds[i] = mHSV(80, 255, 255); // roughly green
  strip.show(); // display changes
  delay(2000);

  // ------------------------------------------
  // To speed up manual fills (speed up color calculation), you can create a variable of type mData
  mData value1, value2;
  value1 = mHSV(60, 100, 255);
  value2 = mHSV(190, 255, 190);
  for (int i = 0; i < NUMLEDS; i++) {
    if (i < NUMLEDS / 2) strip.leds[i] = value1;  // first half of the strip
    else strip.leds[i] = value2;                  // second half of the strip
  }
  strip.show(); // display changes
  delay(2000);

  // ------------------------------------------
  // in a loop, you can change color generation parameters. For instance, let's create a rainbow
  for (int i = 0; i < NUMLEDS; i++) strip.set(i, mWheel8(i * 255 / NUMLEDS)); // a full circle from 0 to 255
  strip.show(); // display changes
  delay(2000);

  // or a gradient from red to black (gradually changing brightness)
  for (int i = 0; i < NUMLEDS; i++) strip.set(i, mWheel8(0, i * 255 / NUMLEDS)); // a full circle from 0 to 255
  strip.show(); // display changes
}

void loop() {
}
```

<a id="versions"> </a>
## Versions
- v1.1
    - Fixed initialization
    - Added orange color
    
- v2.0
    - Rewritten and significantly optimized output algorithm
    - Added current limit
    
- v2.1
    - Fixed a matrix error
    
- v2.2
    - Color PINK replaced with MAGENTA
    
- v2.3
    - Added define setting MICROLEDALLOWINTERRUPTS
    - Fixed minor bugs, improved stability
    
- v2.4
    - Added ORDERBGR
    
- v2.5
    - Brightness by CRT gamma
    
- v3.0
    - Added functions and colors:
    - Color temperature .setKelvin() and data Kelvin
    - getBlend(position, total, color1, color2) and getBlend2(position, total, color1, color2)
    - .fill(from, to)
    - .fillGradient(from, to, color1, color2)
    - Added Perlin noise (extracted from FastLED)
    - Added gradients
    - Completely remade and optimized output
    - Ability to work without any buffer
    - Current limit setting for all types of strips
    - Configurable interrupt disable
    - Maintaining millis() operation during sending
    - Support for strips 2811, 2812, 2813, 2815, 2818
    - Support for 4-color strips: WS6812
    - Initialization remade into a template, see examples!
    - Many changes in names, everything is redone and simplified, read the documentation!
    
- v3.1
    - Fixed compilation errors for non-standard Arduino and Attiny cores
    - Added tinyLED.h class for streaming output with ATtiny and any AVR (see example)
    - Cut out FastLED tools (random, noise), will work directly with FastLED
    - Added support for joint work with the FastLED library and conversion from its types!
    - Added support for APA102 strip (and other SPI strips), software and hardware SPI
    
- v3.2
    - Some optimizations and fixes
    
- v3.3
    - Fixed a critical bug affecting other pins
    
- v3.4
    - Reworked ASM output, lighter, easier to adapt to other frequencies / timings
    - Added support for LGT8F328P with frequencies 32/16/8 MHz
    - Redone polling of millis()/micros() - direct call to TIMER0OVF interrupt, removed redundant code
    
- v3.5
    - Fixed a compilation error in some cases
    
- v3.6
    - Added setting for configuring interrupt disable mode on the fly
    
- v3.7
    - Fixed a compilation error when the FastLED.h library is missing (if FastLED data type support is not used)

<a id="feedback"> </a>
## Bugs and Feedback
Please create an **issue** if you find any bugs, and it's even better to directly email alex@alexgyver.ru. The library is open for improvements and your **pull requests** are welcome!

When reporting bugs or malfunctions of the library, it is necessary to specify:
- The version of the library
- The microcontroller (MCU) used
- SDK version (for ESP)
- Arduino IDE version
- Whether the built-in examples work correctly, especially those utilizing the functions and structures that lead to the bug in your code
- The code that was uploaded, what you expected it to do, and how it actually behaves
- Ideally, attach the minimum code that reproduces the bug. Not a thousand lines of code, but the minimal code necessary to observe the bug.
