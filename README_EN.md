This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/microLED.svg?color=brightgreen)](https://github.com/GyverLibs/microLED/releases/latest/download/microLED.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/microLED.svg)](https://registry.platformio.org/libraries/gyverlibs/microLED)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/microLED?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# microLED
microLED - an ultra-lightweight library for working with address tape / matrix
- The main feature: color compression, the code takes up several times less space in SRAM compared to analogues (FastLED, NeoPixel, etc.)
- Color compression support: 8, 16 and 24 bits
- Ability to work without a buffer at all (with some limitations)
- Working with color:
- RGB
- HSV
- HEX (WEB colors)
- Color wheel (1500 or 255 brightest shades)
- 16 built-in colors
- Color by heat
- Gradients
- Ability to read compressed color in mHEX 0xRRGGBB and RGB array
- Optimized Asm output
- Built-in support for working with address matrices
- Chip support: 2811/2812/2813/2815/2818/WS6812/APA102
- Built-in tinyLED to work on ATtiny
- Compatibility of data types and tools from FastLED
- Advanced Interruption Setup
- Native Matrix Support
- Millis() (AVR only)
- Support for SPI tapes (software and hardware)

### Compatibility
Only AVR, ATmega and ATtiny

### Documentation.
There's a library[extended documentation](https://alexgyver.ru/microLED/)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **microLED** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/microLED/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
```cpp
microLED< amount, pin, clock, chip, order, cli, millis>
- amount – количество светодиодов в ленте. Для работы в режиме потока можно указать 0, так как длина ленты фактически ничем не ограничена.
- pin –  пин, к которому подключен дата-вход ленты (D, Din, DI).
- clock – пин, к которому подключен тактовый-вход ленты (C, CLK). Этот пин подключается только для SPI лент, например APA102.
    - Для работы с лентами серии WSxxxx нужно указать вместо этого пина параметр MLED_NO_CLOCK или минус 1 , т.е. -1
- chip – модель ленты (светодиодов), в библиотеке поддерживаются LED_WS2811, LED_WS2812, LED_WS2813, LED_WS2815, LED_WS2818, LED_WS6812, APA102, APA102_SPI. Выбор модели ленты задаёт скорость протокола (она у них разная) и настройки тока потребления для режимов ограничения (о них читай дальше).
- order – порядок цветов в ленте. В идеальном мире порядок цветов должен зависеть от модели чипа и эта настройка должна быть встроена в выбор чипа, но китайцы торгуют лентами, которые по протоколу совпадают с одним чипом, но имеют другой порядок цветов. Таким образом библиотека поддерживает больше типов лент, чем написано выше, но нужно угадать с выбором “клона” и порядок цветов. 
    - Порядок: ORDER_RGB, ORDER_RBG, ORDER_BRG, ORDER_BGR, ORDER_GRB, ORDER_GBR.

microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2811, ORDER_GBR> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2812, ORDER_GRB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2813, ORDER_GRB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2815, ORDER_GRB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS2818, ORDER_RGB> strip;
microLED< NUMLEDS, STRIP_PIN, -1, LED_WS6812, ORDER_RGB> strip;
microLED< NUMLEDS, STRIP_PIN, CLOCK_PIN, LED_APA102, ORDER_BGR> strip;
microLED< NUMLEDS, -1, -1, LED_APA102_SPI, ORDER_BGR> strip;
```

<a id="usage"></a>
## Use of use
See.[documentation](https://alexgyver.ru/microLED/)
```cpp
// template: <number, pin, chip, order, interrupts, millis >>
// Initialization of the tape: no arguments
microLED;

// Matrix initialization: matrix width, matrix height, matrix type, connection angle, direction (see MAtrix CONCLUSION)
microLED(uint8_t width, uint8_t height, M_type type, M_connection conn, M_dir dir);

// ribbon
void set(int n, mData color);   // Put the color of the LED mData (equivalent to leds[n] = color)
mData get(int num);             // Get the diode color in mData (equal to leds[n])
void fill(mData color);         // mData
void fill(int from, int to, mData color);// mData
void fillGradient(int from, int to, mData color1, mData color2);  // gradient
void fade(int num, byte val);   // brighten

// matrix
uint16_t getPixNumber(int x, int y);    // get the pixel number in the tape by coordinate n
void set(int x, int y, mData color);    // Put the pixel color x y in mData
mData get(int x, int y);                // get pixel color in mData
void fade(int x, int y, byte val);      // brighten
void drawBitmap8(int X, int Y, const uint8_t *frame, int width, int height);    // Bitmap output (bitmap 1D PROGMEM)
void drawBitmap16(int X, int Y, const uint16_t *frame, int width, int height);  // Bitmap output (bitmap 1D PROGMEM)
void drawBitmap32(int X, int Y, const uint32_t *frame, int width, int height);  // Bitmap output (bitmap 1D PROGMEM)

// general
void setMaxCurrent(int ma);             // set the maximum current (autocorrection of brightness). 0 - off
void setBrightness(uint8_t newBright);  // brightness 0-255
void clear();                           // cleaning
void setCLI(type);                      // CLI OFF, CLI LOW, CLI AVER, CLI HIGH

// buffering
void show();            // buffer

// flow
void begin();           // flow out
void send(mData data);  // send out
void end();             // flow out

// colour
uint32_t getHEX(mData data);                        // repackage
mData getFade(mData data, uint8_t val);             // reduce brightness to val
mData getBlend(int x, int amount, mData c0, mData c1);  // intermediate
mData mRGB(uint8_t r, uint8_t g, uint8_t b);        // RGB 255, 255, 255
mData mWheel(int color, uint8_t bright=255);        // color 0-1530 + brightness
mData mWheel8(uint8_t color, uint8_t bright=255);   // color 0-255 + brightness
mData mHEX(uint32_t color);                         // mHEX
mData mHSV(uint8_t h, uint8_t s, uint8_t v);        // HSV 255, 255, 255
mData mHSVfast(uint8_t h, uint8_t s, uint8_t v);    // HSV 255, 255, 255
mData mKelvin(int kelvin);                          // temperature

// macros
fade8(x, b)
fade8R(x, b)
fade8G(x, b)
fade8B(x, b) 

// packaging
getR(x)
getG(x)
getB(x)
mergeRGB(r,g,b)
mergeRGBraw(r,g,b)
getCRT(byte x) - получить скорректированное значение яркости x с учётом выбранной модели CRT гамма-коррекции
getCRT_PGM(byte x) - получить CRT из прогмем (работает только если выбрана PGM модель)
getCRT_SQUARE(byte x) - получить CRT по квадратной модели
getCRT_QUBIC(byte x) - получить CRT по кубической модели
RGB24to16(x) - конвертация 24-бит цвета в 16-бит
RGB24to8(x) - конвертация 24-бит цвета в 8-бит
RGB16to24(x) - конвертация 16-бит цвета в 24-бит
RGB8to24(x) - конвертация 8-бит цвета в 24-бит
RGB24toR(x) - вытащить байт R из 24-бит цвета
RGB24toG(x) - вытащить байт G из 24-бит цвета
RGB24toB(x) - вытащить байт B из 24-бит цвета
RGBto24(r,g,b) - склеить 24-бит цвет
RGBto16(r,g,b) - склеить 16-бит цвет
RGBto8(r,g,b) - склеить 8-бит цвет
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
// basic example of work with tape, the main opportunities
// MicroLED library version 3. 0 +
// For more information, read the documentation

// constants
#define STRIP_PIN 2     // pin
#define NUMLEDS 20      // LED count

// ===== Color depth ====
// 1, 2, 3 (bytes per color)
// at a lower color resolution, the sketch will take up several times less space,
// But the number of shades and brightness levels will also decrease!
// Define is made before the library is signed
// Without it, there will be 3 bytes by default.
#define COLOR_DEBTH 3

#include <microLED.h>   // plug in the bible

// ======== Initialization =====
// <kolvo-ice, pin, clok pin, chip, order >>
// microLED<NUMLEDS, DATA_PIN, CLOCK_PIN, LED_WS2818, ORDER_GRB> strip;
// CLOCK PIN is only required for SPI tapes (e.g. APA102)
// For regular WS tapes we specify MLED NO CLOCK
// for APA102 see a separate guide in examples

// Different Chinese counterfeits may be compatible
// with one chip, but another order of colors!
// Supported ribbon chips and their official color order:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2811, ORDER_GBR> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2813, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2815, ORDER_GRB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS6812, ORDER_RGB> strip;
// microLED<NUMLEDS, STRIP_PIN, CLOCK_PIN, LED_APA102, ORDER_BGR> strip;
// microLED<NUMLEDS, MLED NO CLOCK, MLED NO CLOCK, LED APA102 SPI, ORDER BGR> strip; // for hardware SPI


// ======== = ======
// To improve the reliability of data transmission to the tape, you can turn off interrupts.
// The library has 4 modes:
// CLI OFF - interrupts are not turned off (may malfunction in the tape)
// CLI LOW - interrupts are turned off during the transfer of one color
// CLI AVER - interrupts are turned off during the transfer of one LED (3 colors)
// CLI HIGH - interrupts are turned off during the transfer of data to the entire tape

// By default, disabling interrupts is on CLI OFF (not disabled)
// The parameter is transmitted by the 5th at initialization:
// microLED<NUMLEDS, STRIP_PIN, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

// ========= Save Millis ====
// When disabling interrupts in medium and high prority mode (CLI AVER and CLI HIGH)
// The time functions of millis() and micros() will inevitably lag behind.
// The library has built-in service of time functions, for activation pass SAVE MILLIS
// The 6th argument for initialization:
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER, SAVE_MILLIS> strip;
// This will NEVER slow the output to the tape, but will allow Millis to count without lagging!

// I'm going to initialize the tape (higher was the guide!)
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

void setup() {
  // ========================================================================
  // brightness (0-255)
  strip.setBrightness(60);
  // brightness applied to the CRT gamma
  // It is used in .show()!

  // buffer cleaning (turn off diodes, black)
  strip.clear();
  // It is used in .show()!

  strip.show(); // ribboning
  delay(1);     // There should be a minimum of 40 μs between show calls!!!

  // ===========================================================================
  // The library supports two options for working with tape:
  // Changing the color of a particular diode using the set function (diode, color)
  // Or work with an array of .leds[] manually

  // strip.set (diode, color); equivalent to strip.leds[diode] = color;

  // Main functions of working with color
  // The following functions rotate the mData data type - a compressed color representation

  // mRGB(uint8 t r, uint8 t g, uint8 t b) RGB color, 0-255 each channel
  strip.set(0, mRGB(255, 0, 0));              // diode 0, color RGB (255 0) (red)

  // mHSV(uint8 t h, uint8 t s, uint8 t v); // HSV color, 0-255 each channel
  strip.leds[1] = mHSV(30, 255, 255);         // diode 1, (color 30, brightness and saturation maximum)

  // mHSVfast(uint8 t h, uint8 t s, uint8 t v); // HSV color, 0-255 each channel
  // Calculation is done a little faster, but the colors are not so smooth.
  strip.set(2, mHSVfast(90, 255, 255));         // diode 2, color 90, brightness and saturation maximum

  // mHEX(uint32 t color); // WEB colors (0xRRGGBB)
  strip.set(3, mHEX(0x30B210));   // diode 3, color HEX 0x30B210

  // The library has 17 preset colors (max. brightness)
  strip.leds[4] = mAqua;          // diode 4, color aqua

  // mWheel(int color); // rainbow colours 0-1530
  // mWheel (int color, uint8 t bright) // rainbow colors 0-1530 + brightness 0-255
  strip.set(5, mWheel(1200));             // diode 5, color 1200

  // mWheel8 (int color) // rainbow colours 0-255
  // mWheel8 (int color, uint8 t bright) // rainbow colours 0-255 + brightness 0-255
  //strip.set(6, mWheel8(100)) // diode 6, color 100 (range 0-255 along the rainbow)
  strip.set(6, mWheel8(100, 50));   // The second parameter can transmit brightness.

  // mKelvin(int kelvin); Color temperature 1000-40,000 Kelvin
  strip.set(7, mKelvin(3500));      // diode 7, color temperature 3500K

  strip.show();                     // Put all the changes on the tape
  delay(2000);                      // delay

  // ==========================================================================================
  // There is a ready-made function for pouring the entire tape with color - .fill()
  // receives a converted color, for example from functions of color or constants above
  strip.fill(mYellow);  // pour yellow n
  strip.show();         // modify
  delay(2000);

  // You can also specify the beginning and end of the filling.
  strip.fill(3, 7, mWheel8(100));   // pour ~green from 3 to 6: the count goes from 0, poured to the specified -1
  strip.show();                     // modify
  delay(2000);

  // Manual pouring in the cycle
  // For example, paint half the tape in one, half in the other.
  for (int i = 0; i < NUMLEDS / 2; i++) strip.leds[i] = mHSV(0, 255, 255);  	  // red
  for (int i = NUMLEDS / 2; i < NUMLEDS; i++) strip.leds[i] = mHSV(80, 255, 255); // roughly green
  strip.show(); // modify
  delay(2000);

  // ------------------------------------------
  // To accelerate manual fills (accelerate color calculation), you can create a variable type mData.
  mData value1, value2;
  value1 = mHSV(60, 100, 255);
  value2 = mHSV(190, 255, 190);
  for (int i = 0; i < NUMLEDS; i++) {
    if (i < NUMLEDS / 2) strip.leds[i] = value1;  // first-half
    else strip.leds[i] = value2;                  // second-half
  }
  strip.show(); // modify
  delay(2000);

  // ------------------------------------------
  // In the cycle, you can change the parameters of color generation. For example, make a rainbow.
  for (int i = 0; i < NUMLEDS; i++) strip.set(i, mWheel8(i * 255 / NUMLEDS)); // full circle
  strip.show(); // modify
  delay(2000);

  // gradient from red to black (consistently changing brightness)
  for (int i = 0; i < NUMLEDS; i++) strip.set(i, mWheel8(0, i * 255 / NUMLEDS)); // full circle
  strip.show(); // modify
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.1
    - Updated initialization
    - Added orange
    
- v2.0
    - Rewritten and greatly accelerated output algorithm
    - Added current restriction
    
- v2.1
    - Corrected matrix error
    
- v2.2
    - Pink colour replaced by Magenta
    
- v2.3
    - Added defiant setting MICROLED ALLOW INTERRUPTS
    - Fixed minor errors, improved stability
    
- v2.4
    - Added ORDER BGR
    
- v2.5
    - Brightness on the CRT scale
    
- v3.0
    - Features and colors added:
    - Color temperature .setKelvin() and date Kelvin
    - getBlend (position, total color1, color2) and getBlend2 (position, total color1, color2)
    - .fill.
    - .fillGradient (from, to, color 1, color 2)
    - Added Perlin noise (pulled from FastLED)
    - Gradients added
    - Completely redesigned and optimized output
    - Ability to work without a buffer at all
    - Configure current restriction for all types of tapes
    - Configurable Interrupt Ban
    - Preserving Millis for the duration of shipment
    - Support for tapes 2811, 2812, 2813, 2815, 2818
    - Support for 4 colored ribbons: WS6812
    - The initialization is redesigned to the template, see examples!
    - Lots of changes in the titles, everything is reworked and simplified, read the documentation!
    
- v3.1
    - Fixed compilation errors for non-standard cores Arduino and Attini
    - TinyLED.h is added to stream ATtiny and any AVR (see example)
    - FastLED tools are cut out (random, noise), we will work directly with the fastled
    - Added support for collaboration with the library FastLED and conversion from its types!
    - Added support for APA102 tape (and other SPIs), software and hardware SPI
    
- v3.2
    - A little optimization and corrections
    
- v3.3
    - Fixed a critical bug with an impact on other pins
    
- v3.4
    - Reworked ASM output, less weight, easier to adapt to other frequencies / timings
    - Added support for LGT8F328P 32/16/8 MHz
    - Reworked Polling millis()/micros() - direct interrupt call TIMER0 OVF, removed extra code
    
- v3.5
    - Fixed compilation error in some cases
    
- v3.6
    - Added setting the mode of prohibition of interruptions on the fly

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
