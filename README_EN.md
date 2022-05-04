This is an automatic translation, may be incorrect in some places. See sources and examples!

#microLED
microLED - ultra-lightweight address strip/matrix library
- The main feature: color compression, the code takes up much less space in SRAM compared to analogues (FastLED, NeoPixel, etc.)
- Color compression support: 8, 16 and 24 bits
- Ability to work without a buffer at all (with some restrictions)
- Working with color:
- RGB
- HSV
- HEX (WEB colors)
- "Color wheel" (1500 or 255 brightest shades)
- 16 built-in colors
- Color by warmth
- Gradients
- Ability to read compressed color in mHEX 0xRRGGBB and RGB array
- Optimized asm output
- Built-in support for working with address matrices
- Chip support: 2811/2812/2813/2815/2818/WS6812/APA102
- Built-in tinyLED to work on ATtiny
- Compatibility of data types and tools from FastLED
- Advanced interrupt settings
- Native matrix support
- Saving millis() (AVR only)
- Support for SPI tapes (software and hardware)

### Compatibility
Only AVR, ATmega and ATtiny

### Documentation
The library has [extended documentation] (https://alexgyver.ru/microLED/)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **microLED** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2- PlatformIO
- [Download Library](https://github.com/GyverLibs/microLED/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
microLED< amount, pin, clock, chip, order, cli, millis>
- amount – number of LEDs in the strip. You can specify 0 for streaming mode, as there is virtually no limit to the length of the tape.
- pin – pin to which the data input of the tape is connected (D, Din, DI).
- clock - pin to which the clock-input of the tape is connected (C, CLK). This pin is connected only for SPI tapes, for example APA102.
    - To work with tapes of the WSxxxx series, you need to specify the parameter MLED_NO_CLOCK or minus 1 instead of this pin, i.e. -one
- chip – strip model (LEDs), LED_WS2811, LED_WS2812, LED_WS2813, LED_WS2815, LED_WS2818, LED_WS6812, APA102, APA102_SPI are supported in the library. Selecting a tape model sets the protocol speed (they have different ones) and current consumption settings for limiting modes (read about them later).
- order - the order of the colors in the ribbon. In an ideal world, the color order should depend on the chip model and this setting should be built into the chip selection, but the Chinese sell ribbons that are protocol-matched to one chip, but have a different color order. Thus, the library supports more types of ribbons than written above, but you need to guess with the choice of “clone” and the order of colors.
    - Order: ORDER_RGB, ORDER_RBG, ORDER_BRG, ORDER_BGR, ORDER_GRB, ORDER_GBR.

microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2811, ORDER_GBR> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2812, ORDER_GRB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2813, ORDER_GRB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2815, ORDER_GRB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2818, ORDER_RGB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS6812, ORDER_RGB> strip;
microLED< NUMLEDS, STRIP_PIN, CLOCK_PIN, LED_APA102, ORDER_BGR> strip;
microLED< NUMLEDS, MLED_NO_CLOCK, MLED_NO_CLOCK, LED_APA102_SPI, ORDER_BGR> strip;
```

<a id="usage"></a>
## Usage
See [documentation](https://alexgyver.ru/microLED/)
```cpp
// pattern: <number, pin, chip, order, interrupts, millis>
// initialization TAPE: no arguments
microLED;
// initialization MATRIX: matrix width, matrix height, matrix type, connection angle, direction (see CONNECTING THE MATRIX)
microLED(uint8_t width, uint8_t height, M_type type, M_connection conn, M_dir dir);
// tape and matrix
void set(int n, mData color); // set the color of the mData LED (equivalent to leds[n] = color)
mData get(int num);// get the color of the diode in mData (equivalent to leds[n])
void fill(mData color); // fill color mData
void fill(int from, int to, mData color);// fill mData with color
void fillGradient(int from, int to, mData color1, mData color2); // fill with a gradient of two colors
void fade(int num, byte val); // decrease brightness
// matrix
uint16_t getPixNumber(int x, int y); // get the pixel number in the feed by coordinates
void set(int x, int y, mData color); // set the color of pixel x y to mData
mData get(int x, int y);// get pixel color in mData
void fade(int x, int y, byte val);// decrease brightness
void drawBitmap8(int X, int Y, const uint8_t *frame, int width, int height); // bitmap output (bitmap 1 dimensional PROGMEM)
void drawBitmap16(int X, int Y, const uint16_t *frame, int width, int height); // bitmap output (bitmap 1 dimensional PROGMEM)
void drawBitmap32(int X, int Y,cranberry const uint32_t *frame, int width, int height); // bitmap output (bitmap 1 dimensional PROGMEM)
// general
void setMaxCurrent(int ma);// set the maximum current (brightness auto-correction). 0 - disabled
void setBrightness(uint8_t newBright); // brightness 0-255
void clear(); // cleanup
// buffer output
void show(); // output the entire buffer
// stream output
voidbegin(); // start stream output
void send(mData data); // send one LED
void end();// end the output with a stream
// Colour
uint32_t getHEX(mData data); // repack to 24 bit HEX
mData getFade(mData data, uint8_t val); // decrease brightness by val
mData getBlend(int x, int amount, mData c0, mData c1); // get intermediate color
mData mRGB(uint8_t r, uint8_t g, uint8_t b); // RGB 255, 255, 255
mData mWheel(int color, uint8_t bright=255); // colors 0-1530 + brightness
mData mWheel8(uint8_t color, uint8_t bright=255); // colors 0-255 + brightness
mData mHEX(uint32_t color); // mHEX color
mData mHSV(uint8_t h, uint8_t s, uint8_t v); // HSV 255, 255, 255
mData mHSVfast(uint8_t h, uint8_t s, uint8_t v); // HSV 255, 255, 255
mData mKelvin(int kelvin); // temperature
// macros for dimming
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
getCRT(byte x) - get the corrected brightness value x, taking into account the selected CRT model of gamma correction
getCRT_PGM(byte x) - get CRT from programs (works only if PGM model is selected)
getCRT_SQUARE(byte x) - get CRT by square model
getCRT_QUBIC(byte x) - get CRT by cubic model
RGB24to16(x) - convert 24-bit color to 16-bit
RGB24to8(x) - convert 24-bit color to 8-bit
RGB16to24(x) - convert 16-bit color to 24-bit
RGB8to24(x) - convert 8-bit color to 24-bit
RGB24toR(x) - pull byte R from 24-bit color
RGB24toG(x) - pull byte G from 24-bit color
RGB24toB(x) - pull byte B from 24-bit color
RGBto24(r,g,b) - glue 24-bit color
RGBto16(r,g,b) - merge 16-bit color
RGBto8(r,g,b) - merge 8-bit color
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
// basic example of working with the ribbon, main features
// microLED library version 3.0+
// read the documentation for more details

// constants for convenience
#define STRIP_PIN 2 // strip pin
#define NUMLEDS 20 // number of LEDs

// ===== COLOR DEPTH =====
// 1, 2, 3 (byte per color)
// at a lower color resolution, the sketch will take up much less space,
// but the number of shades and brightness levels will also decrease!
// define is done BEFORE INCLUDING THE LIBRARY
// without it will be 3 bytes by default
#define COLOR_DEBTH 3

#include <microLED.h> // include the bible

// ======= INITIALIZATION =======
// <number of ices, pin, clock pin, chip, order>
// microLED<NUMLEDS, DATA_PIN, CLOCK_PIN, LED_WS2818, ORDER_GRB> strip;
// CLOCK pin is only needed for SPI tapes (for example APA102)
// for regular WS tapes, specify MLED_NO_CLOCK
// for APA102, see separate guide in examples

// various Chinese knockoffs may have compatibility
// with same chip but different color order!
// supported ribbon chips and their official color order:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2811, ORDER_GBR> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2813, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2815, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS6812, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, CLOCK_PIN, LED_APA102, ORDER_BGR> strip;
// microLED<NUMLEDS, MLED_NO_CLOCK, MLED_NO_CLOCK, LED_APA102_SPI, ORDER_BGR> strip; // for hardware SPI


// ======= INTERRUPTS =======
// to increase the reliability of data transfer to the tape, interrupts can be disabled.
// The library has 4 modes:
// CLI_OFF - interrupts are not disabled (tape crashes are possible)
// CLI_LOW - interrupts are disabled for the duration of the transfer of one color
// CLI_AVER - interrupts are disabled for the duration of the transmission of one LED (3 colors)
// CLI_HIGH - interrupts are disabled while transferring data to the entire tape

// Disable interrupts by default set to CLI_OFF (not disabled)
// Parameter is passed 5th during initialization:
// microLED<NUMLEDS, STRIP_PIN, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

// ======= SAVE MILLIS =======
// When interrupts are disabled in medium and high priority mode (CLI_AVER and CLI_HIGH)
// the time functions millis() and micros() will inevitably lag behind a bit
// The library has a built-in service of time functions, for activation we pass SAVE_MILLIS
// 6th argument during initialization:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER, SAVE_MILLIS> strip;
// this will SLIGHTLY slow down the output to the tape, but will allow the millis to keep up!

// initialize the feed (there was a guide above!)
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

void setup() {
  // ===================== BASIC ITEMS ======================
  // brightness (0-255)
  strip.setBrightness(60);
  // brightness applied by CRT gamma
  // applied when outputting .show() !

  // clear buffer (turn off diodes, black color)
  strip.clear();
  // applied when outputting .show() !

  strip.show(); // output changes to the tape
  delay(1); // there must be a pause of at least 40 µs between show calls !!!!

  // ===================== SET COLOR ======================
  // The library supports two options for working with the ribbon:
  // change the color of a specific diode using the set(diode, color) function
  // or work with the .leds[] array "manually"

  // record strip.set(diode, color); is equivalent to strip.leds[diode] = color;

  // ------------- BASIC COLOR FUNCTIONS ------------
  // the following functions inCranberries corrupt the mData data type - a compressed color representation

  // mRGB(uint8_t r, uint8_t g, uint8_t b); // RGB color, 0-255 each channel
  strip.set(0, mRGB(255, 0, 0)); // diode 0, RGB color (255 0 0) (red)

  // mHSV(uint8_t h, uint8_t s, uint8_t v); // HSV color, 0-255 each channel
  strip.leds[1] = mHSV(30, 255, 255); // diode 1, (color 30, brightness and saturation maximum)

  // mHSVfast(uint8_t h, uint8_t s, uint8_t v); // HSV color, 0-255 each channel
  // calculation is slightly faster, but the colors are not as smooth
  strip.set(2, mHSVfast(90, 255, 255)); // diode 2, color 90, brightness and saturation maximum

  // mHEX(uint32_t color); // WEB colors (0xRRGGBB)
  strip.set(3, mHEX(0x30B210)); // diode 3, color HEX 0x30B210

  // there are 17 preset colors in the library (max brightness)
  strip.leds[4] = mAqua; // diode 4, color aqua

  // mWheel(int color); // rainbow colors 0-1530
  // mWheel(int color, uint8_t bright); // rainbow colors 0-1530 + brightness 0-255
  strip set(5, mWheel(1200)); // diode 5, color 1200

  // mWheel8(int color); // rainbow colors 0-255
  // mWheel8(int color, uint8_t bright); // rainbow colors 0-255 + brightness 0-255
  //strip.set(6, mWheel8(100)); // diode 6, color 100 (range 0-255 along the rainbow)
  strip.set(6, mWheel8(100, 50)); // brightness can be passed as the second parameter

  // mKelvin(int kelvin); // color temperature 1'000-40'000 Kelvin
  strip.set(7, mKelvin(3500)); // diode 7, color temperature 3500K

  strip.show(); // output all changes to the tape
  delay(2000); // display delay

  // ===================== FILL =====================
  // There is a ready-made function for filling the entire ribbon with color - .fill()
  // accepts a converted color, such as from the color functions or constants above
  strip fill(mYellow); // fill with yellow
  strip.show(); // output changes
  delay(2000);

  // you can also specify the start and end of the fill
  strip.fill(3, 7, mWheel8(100)); // fill ~green from 3 to 6: count starts from 0, fills up to the specified -1
  strip.show(); // output changes
  delay(2000);

  // ------------- MANUAL FILL IN A LOOP ------------
  // For example, paint half of the ribbon in one, half in the other
  for (int i = 0; i < NUMLEDS / 2; i++) strip.leds[i] = mHSV(0, 255, 255); // red
  for (int i = NUMLEDS / 2; i < NUMLEDS; i++) strip.leds[i] = mHSV(80, 255, 255); // roughly green
  strip.show(); // output changes
  delay(2000);

  // ------------------------------------------------
  // To speed up manual fills (speed up color calculation), you can create a variable of type mData
  mData value1, value2;
  value1 = mHSV(60, 100, 255);
  value2 = mHSV(190, 255, 190);
  for (int i = 0; i < NUMLEDS; i++) {
    if (i < NUMLEDS / 2) strip.leds[i] = value1; // first half of tape
    else strip.leds[i] = value2; // second half of tape
  }
  strip.show(); // output changes
  delay(2000);

  // ------------------------------------------------
  // in the loop, you can change the color generation parameters. For example, let's make a rainbow
  for (int i = 0; i < NUMLEDS; i++) strip.set(i, mWheel8(i * 255 / NUMLEDS)); // full circle from 0 to 255
  strip.show(); // output changes
  delay(2000);

  // or gradient from red to black (sequentially changing the brightness)
  for (int i = 0; i < NUMLEDS; i++) strip.set(i, mWheel8(0, i * 255 / NUMLEDS)); // full circle from 0 to 255
  strip.show(); // output changes
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.1
    - Fixed initialization
    - Added orange color
    
- v2.0
    - Rewritten and greatly accelerated output algorithm
    - Added current limit
    
- v2.1
    - Fixed a bug with the matrix
    
- v2.2
    - PINK color changed to MAGENTA
    
- v2.3
    - Added define setting MICROLED_ALLOW_INTERRUPTS
    - Fixed minor bugs, improved withcranberry stability
    
- v2.4
    - Added ORDER_BGR
    
- v2.5
    - Brightness by CRT gamma
    
- v3.0
    - Added features and colors:
    - .setKelvin() color temperature and Kelvin date
    - getBlend(position, total, color1, color2) and getBlend2(position, total, color1, color2)
    - .fill(from, to)
    - .fillGradient(from, to, color1, color2)
    - Added Perlin noise (pulled from FastLED)
    - Added gradients
    - Completely redesigned and optimized output
    - Ability to work without a buffer at all
    - Current limit setting for all types of tapes
    - Configurable interrupt disable
    - Saving the work of the millis for the time of sending
    - Support for tapes 2811, 2812, 2813, 2815, 2818
    - Support for 4 color ribbons: WS6812
    - Initialization redesigned for the template, see examples!
    - A lot of changes in the names, everything is redone and simplified, read the documentation!
    
- v3.1
    - Fixed compilation errors for non-standard cores of Arduino and Attini
    - Added class tinyLED.h for streaming with ATtiny and any AVR in general (see example)
    - Cut out FastLED tools (random, noise), we will work directly with fastled
    - Added support for working with the FastLED library and converting from its types!
    - Added support for APA102 tape (as well as other SPI), software and hardware SPI
    
- v3.2
    - Some optimizations and fixes
    
- v3.3
    - Fixed a critical bug with influence on other pins
    
- v3.4
    - Redesigned ASM output, weighs less, adapts more easily to other frequencies / timings
    - Added support for LGT8F328P with a frequency of 32/16/8 MHz
    - Redesigned millis()/micros() polling - direct TIMER0_OVF interrupt call, removed extra code
    
- v3.5
    - Fixed compilation error in some cases pleasing to the compiler

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!