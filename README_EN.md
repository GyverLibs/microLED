This is an automatic translation, may be incorrect in some places. See sources and examples!

# Microled
Microled - Ultra -Luga Library for working with targeted tape/matrix
- The main feature: compression of the color, the code takes many times less space in SRAM compared to analogues (Fastled, Neopixel, etc.)
- Support for color compression: 8, 16 and 24 bits
- the ability to work at all without a buffer (with some restrictions)
- Work with color:
- RGB
- HSV
- Hex (Web color)
- "Color wheel" (1500 or 255 of the brightest shades)
- 16 built -in colors
- Color according to warmth
- gradients
- the ability to read compressed color in MHEX 0XRRGGBB and RGB array
- optimized ASM conclusion
- Built -in support for working with targeted matrices
- Support of chips: 2811/2812/2813/2815/2818/WS6812/APA102
- Built -in Tinyled to work on Attiny
- compatibility of data and tools from Fastled
- Expanded interruption setting
- Native support for matrices
- Preservation of the work Millis () (only for AVR)
- Support for SPI ribbons (software and hardware)

## compatibility
Only AVR, Atmega and Attiny

### Documentation
There is [expanded documentation] to the library (https://alexgyver.ru/microled/)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** Microled ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/microled/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Microled <Amount, Pin, Clock, Chip, Order, Cli, Millis>
- Amount - the number of LEDs in the tape.To work in the flow mode, you can specify 0, since the length of the tape is actually unlimited.
- PIN- PIN, to which the date-entry of the tape is connected (D, DIN, DI).
- Clock- PIN, to which the clock-input of the tape (C, CLK) is connected.This pin is connected only for SPI ribbons, such as APA102.
    - To work with the ribbons of the WSXXXX series, you need to specify instead of Pin the parameter MLED_NO_CLOCK or minus 1, i.e.-1
- Chip - a model of tape (LEDs), in the library supportLED_WS2811, LED_WS2812, LED_WS2813, LED_WS2815, LED_WS2818, LED_WS6812, APA102, APA102_SPI.The choice of the tape model sets the speed of the protocol (they have different ones) and the consumption current settings for restriction modes (read more about them).
- Order - the order of flowers in the tape.In the ideal world, the color order should depend on the chip model and this setting should be built into the choice of the chip, but the Chinese sell ribbons that coincide with one chip in the protocol, but have a different color order.Thus, the library supports more types of tapes than written above, but you need to guess with the choice of “clone” and the order of flowers.
    - Order: Order_RGB, Order_RBG, Order_BRG, Order_BGR, Order_GRB, Order_GBR.

Microleds <numleds, strip_pin, -1, led_ws2811, order_gbr> strip;
Microleds <numleds, strip_pin, -1, led_ws2812, oorder_grb> strip;
Microleds <numleds, strip_pin, -1, led_ws2813, oorder_grb> strip;
Microleds <numleds, strip_pin, -1, led_ws2815, oorder_grb> strip;
Microleds <numleds, strip_pin, -1, led_ws2818, oorder_rgb> strip;
Microleds <numleds, strip_pin, -1, led_ws6812, oorder_rgb> strip;
Microleds <numleds, strip_pin, claock_pin, led_apa102, order_bgr> strip;
Microleds <numleds, -1, -1, led_apa102_spi, order_bgr> strip;
`` `

<a id="usage"> </a>
## Usage
See [documentation] (https://alexgyver.ru/microled/)
`` `CPP
// template: <quantity, pin, chip, order, interruption, millis>
// initialization of the tape: no arguments
Microled;

// Initialization Matrix: matrix width, matrix height, matrix type, connection angle, direction (see the connection of the matrix)
Microled (Uint8_t Width, Uint8_t Height, M_type Type, M_connection Conn, M_dir Dir);

// Tape and Matrix
VOID set (int n, mdata color);// put the color of the LED MDATA (equivalent to leds [n] = color)
Mdata Get (int num);// Get the color of the diode in mdata (equivalent to leds [n])
Void Fill (Mdata Color);// pouring with color mdata
VOID Fill (Int FROM, Int to, MDATA Color); // Pouring MDATA color
VOID Fillgradient (Int frim, int to, mdata color1, mdata color2);// Pour a gradient of two colors
VOID FADE (int num, byte val);// Reduce brightness

// matrix
uint16_t getpixnumber (int x, int y);// Get a pixel number in the tape according to the coordinates
VOID SET (int X, int y, mdata color);// put the color of the pixel x y in mdata
mdata get (int x, int y);// get the color of the pixel in mdata
VOID FADE (Int X, Int Y, Byte Val);// Reduce brightness
VOID DRAWBITMAP8 (Int X, Int Y, COST UINT8_T *FRAME, Int Width, Intt Height);// Bitmap output (Bitmap 1mater Progmem)
VOID DRAWBITMAP16 (Int X, Int Y, COST UINT16_T *FRAME, IntHIDTH, IntHTHT);// Bitmap output (Bitmap 1mater Progmem)
VOID DRAWBITMAP32 (Int X, Int Y, COST UINT32_T *FRAME, IntHIDTH, IntHTHT);// Bitmap output (Bitmap 1mater Progmem)

// General
VOID setmaxcurrent (int ma);// Set the maximum current (auto -correction of brightness).0 - off
VOID Setbrightness (Uint8_T Newbright);// brightness 0-255
Void Clear ();// Cleaning
VOID setcli (Type);// Prohibition of interruptions of pli_off, cli_low, cli_aver, cli_high

// Boofer conclusion
VOID show ();// Determine the entire buffer

// Stream output
VOID Begin ();// Start the conclusion with a stream
VOID SEND (MDATA DATA);// Send one LED
VOID end ();// End the output with a stream

// color
uint32_t gethex (mdata data);// reproduce in 24 bits hex
Mdata Getfade (Mdata Data, Uint8_t Val);// Reduce brightness by val
MDATA Getblend (Int X, Intsount, MDATA C0, MDATA C1);// get an interim color
mdata mrgb (uint8_t r, uint8_t g, uint8_t b);// RGB 255, 255, 255
Mdata mwheel (int color, uint8_t bright = 255);// Colors 0-1530 + brightness
mdata mwheel8 (Uint8_t Color, Uint8_t Bright = 255);// Colors 0-255 + brightness
mdata mhex (uint32_t color);// mhex color
mdata mhsv (uint8_t h, uint8_t s, uint8_t v);// hsv 255, 255, 255
Mdata mhsvfast (uint8_th, uint8_t s, uint8_t v);// hsv 255, 255, 255
Mdata Mkelvin (Int Kelvin);// temperature

// Macros of brightness reduction
fade8 (x, b)
Fade8r (x, b)
Fade8g (x, b)
Fade8b (x, b)

// packaging-packing
Getr (x)
Getg (x)
Getb (x)
Mergergb (r, g, b)
Mergergbraw (r, g, b)
Getcrt (byte X) - get the adjusted value of brightness X taking into account the selected CRT model of gamma correction
Getcrt_pgm (Byte X) - get CRT from the progress (it only works if the PGM model is selected)
Getcrt_SQUARE (Byte X) - Get CRT by square model
Getcrt_Qubic (Byte X) - Get CRT by cubic model
RGB24TO16 (X)-Convertation 24-bit color in 16-bit
RGB24TO8 (x)-Convertation 24-bit colors in 8-bit
RGB16TO24 (X)-Convertation 16-bit color in 24-bit
RGB8TO24 (x)-8-bit color conversion in 24-bit
RGB24TOR (x) - pull out byt R of 24 -bit color
RGB24TOG (x) - pull out byt G of 24 -bit color
RGB24TOB (x) - pull out byte B of 24 -bit color
Rgbto24 (r, g, b) - glue 24 -bit color
Rgbto16 (r, g, b) - glue 16 -bit color
Rgbto8 (r, g, b) - glue 8 -bit color
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
// Basic example of working with the tape, basic possibilities
// Library Microled version 3.0+
// For more information, read the documentation

// Constants for convenience
#define strip_pin 2 // Pin tape
#define numleds 20 // Sum of LEDs

// ===== Color depth ========
// 1, 2, 3 (byte for color)
// on a smaller color resolution, the sketch will occupy many times less space,
// But the number of shades and brightness levels will decrease!
// Define is made before connecting the library
// Without it there will be 3 bytes by default
#define color_debth 3

#include <microled.h> // Connect the bibla

// ====== Entialization ============
// <Kolvo-training, pin, Klok Pin, chip, order>
// microleds <numleds, data_pin, claock_pin, led_ws2818, oner_grb> strip;
// Clock Pin is needed only for SPI tapes (for example, APA102)
// For ordinary WS tapes, indicate mled_no_clock
// by APA102 see a separate guide in the examples

// Various Chinese fakes can have compatibility
// with one chip, but another order of flowers!
// Supported tapes and their official color order:
// Microleds <numleds, strip_pin, mled_no_clock, led_ws2811, order_gbr> strip;
// Microleds <numleds, strip_pin, mled_no_clock, led_ws2812, order_grb> strip;
// microleds <numleds, strip_pin, mled_no_clock, LED_WS2813, Order_GRB> Strip;
// Microleds <numleds, strip_pin, mled_no_clock, led_ws2815, order_grb> strip;
// Microleds <numleds, strip_pin, mled_no_clock, led_ws2818, order_rgb> strip;
// Microleds <numleds, strip_pin, mled_no_clock, led_ws6812, order_rgb> strip;
// microleds <numleds, strip_pin, claock_pin, led_apa102, oorder_bgr> strip;
// Microleds <numleds, mled_no_clock, mled_no_clock, led_apa102_spi, order_bgr> strip;// for hardware SPI


// ======= Interruption ============
// To increase the reliability of data transfer to the tape, you can turn off the interruption.
// The library has 4 modes:
// cli_Off - interruptions are not disconnected (tape failures are possible)
// cli_low - interruptions are disconnected during the transmission of one color
// cli_aver - interruptions are disconnected during the transfer of one LED (3 colors)
// cli_high - interruptions are disconnected during the transfer of the given to the entire tape

// by default, the disabling of interruptions stands on Cli_off (do not turn off)
// The parameter is transmitted to the 5th during initialization:
// Microleds <numleds, strip_pin, led_ws2818, iter_grb, cli_aver> strip;

// ======= Save millis =============
// when disconnecting interruptions in medium and high proportion mode (Cli_aver and Cli_high)
// Inevitably, the functions of the time millis () and micros () will be slightly lagging behind
// The library is built into the maintenance of the functions of the time, for activation, we transfer Save_Millis
// 6th argument in initialization:
// Microleds <numleds, strip_pin, mled_no_clock, led_ws2818, order_grb, clai_aver, save_millis> strip;
// This will slowly slow down on the tape, but will allow Millis to count without a lag!

// I initialize the tape (it was aboveHyde!)
Microleds <numleds, strip_pin, mled_no_clock, led_ws2818, oorder_grb, cli_aver> strip;

VOID setup () {
  // ===================== Basic things ============================================
  // brightness (0-255)
  strip.setbrightness (60);
  // brightness is used in CRT gamut
  // applies in the withdrawal of .show ()!

  // Cleaning the buffer (turn off the diodes, black)
  strip.clear ();
  // applies in the withdrawal of .show ()!

  strip.show ();// Conclusion of changes to the tape
  DELAY (1);// Between the show challenges there should be a pause of at least 40 μs !!!!

  // ====ward
  // The library supports two options for working with the tape:
  // Changing the color of a particular diode using the SET function (diode, color)
  // or work with the .LEDS [] "Manual" array

  // recording Strip.set (diode, color);equivalent to strip.leds [diode] = color;

  // ------------ The main functions of working with color -----------
  // The following functions of the BRZENT are the type of data MDATA - compressed color view

  // mrgb (uint8_t r, uint8_t g, uint8_t b);// Color RGB, 0-255 Each channel
  strip.set (0, mrgb (255, 0, 0));// diode 0, color RGB (255 0 0) (red)

  // mhsv (uint8_t h, uint8_t s, uint8_t v);// color hsv, 0-255 each channel
  strip.leds [1] = mhsv (30, 255, 255);// diode 1, (color 30, brightness and saturation maximum)

  // mhsvfast (uint8_t h, uint8_t s, uint8_t v);// color hsv, 0-255 each channel
  // The calculation is performed a little faster, but the colors are not so smooth
  Strip.set (2, mhsvfast (90, 255, 255));// diode 2, color 90, brightness and saturation maximum

  // mhex (uint32_t color);// Web Colors (0xrrggb)
  strip.set (3, mhex (0x30b210));// diode 3, color hex 0x30b210

  // The library has 17 pre -installed colors (max. Brightness)
  strip.leds [4] = maqua;// diode 4, color aqua

  // mwheel (int color);// Rainbow colors 0-1530
  // mwheel (int color, uint8_t bright);// rainbow colors 0-1530 + brightness 0-255
  strip.set (5, mwheel (1200));// diode 5, color 1200

  // mwheel8 (int color);// Rainbow colors 0-255
  // mwheel8 (int color, uint8_t Bright);// rainbow colors 0-255 + brightness 0-255
  //strip.set(6, mwheel8 (100));// diode 6, color 100 (range 0-255 along the rainbow)
  strip.set (6, mwheel8 (100, 50));// The second parameter can be conveyed brightness

  // mkelvin (int Kelvin);// Color temperature 1'000-40'000 Kelvin
  strip.set (7, mkelvin (3500));// diode 7, color temperature 3500k

  strip.show ();// We display all changes to the tape
  DELAY (2000);// delay in the show

  // =========================================ward
  // there is a ready -made function for filling the entire tape with color - .Fill ()
  // accepts the converted color, for example, from color functions or constants above
  strip.fill (Myillow);// Pour yellow
  strip.show ();// We display changes
  DELAY (2000);

  // You can also specify the beginning and end of the filling
  strip.fill (3, 7, mwheel8 (100));// Pour ~ green from 3 to 6: the account goes from 0, poured to the specified -1
  strip.show ();// We display changes
  DELAY (2000);

  // ------------- Manual filling in the cycle -----------
  // For example, paint half the tape into one, half in the other
  for (int i = 0; i <numleds / 2; i ++) strip.Leds [i] = mhsv (0, 255, 255);// red
  for (int i = numleds / 2; i <numleds; i ++) strip.leds [i] = mhsv (80, 255, 255);// approximately green
  strip.show ();// We display changes
  DELAY (2000);

  // ------------------------------------
  // To accelerate manual fills (acceleration of color calculation), you can create a variable type MDATA
  Mdata Value1, Value2;
  Value1 = mhsv (60, 100, 255);
  Value2 = mhsv (190, 255, 190);
  for (int i = 0; i <numleds; i ++) {
    if (i <numleds / 2) strip.leds [i] = value1;// First half of the tape
    else strip.leds [i] = value2;// second half of the tape
  }
  strip.show ();// We display changes
  DLAY (2000);

  // ------------------------------------
  // In the cycle, you can change the color generation parameters.For example, make a rainbow
  for (int i = 0; i <numleds; i ++) strip.set (i, mwheel8 (I * 255 / numleds));// Full circle from 0 to 255
  strip.show ();// We display changes
  DELAY (2000);

  // or gradient from red to black (sequentially changing brightness)
  for (int i = 0; i <numleds; i ++) strip.set (I, mwheel8 (0, I * 255 / numleds));// Full circle from 0 to 255
  strip.show ();// We display changes
}

VOID loop () {
}
`` `

<a id="versions"> </a>
## versions
- V1.1
    - The initialization is corrected
    - added orange color
    
- V2.0
    - rewritten and greatly accelerated the output algorithm
    - Added current restriction
    
- V2.1
    - corrected error with the matrix
    
- V2.2
    - Pink color is replaced by Magenta
    
- V2.3
    - Added define setting Microled_allow_interrupts
    - Fixed small errors, improved stability
    
- V2.4
    - Added Order_BGR
    
- V2.5
    - CRT Gamma brightness
    
- V3.0
    - Added functions and colors:
    - color temperature .Setkelvin () and Kelvin date
    - Getblend (position, total color1, color2) and getblend2 (position, all, color1, color2)
    - .Fill (from, to)
    - .Fillgradient (from, to, color1, color2)
    - added the noise of Perlin (pulled out of Fastled)
    - Added gradients
    - the conclusion is completely redone and optimized
    - the ability to work at all without a buffer
    - Setting up current restrictions for all types of tapes
    - Networking ban on interruptions
    - Preservation of the work of Millis for the duration of sending
    - Support for tapes 2811, 2812, 2813, 2815, 2818
    - Support for 4 color tapes: WS6812
    - Initialization was converted to the template, see examples!
    - Many changes in the names, everything is redone and simplified, read the documentation!
    
- V3.1
    - Correction errors for non -standard nuclei Arduino and Attini are adjusted
    - added Tinyled.h class for output with a stream from Attiny and in general any avr (see example)
    - Fastled tools are cut out (random, noise), we will work directly from the fastric
    - Added support for joint work with the Fastled library and converting from its types!
    - Added support for the APA102 tape (as well as other SPIs), software and hardware SPI
    
- V3.2
    - slightly optimization and corrections
    
- V3.3
    - Fixed a critical bug with influence on other pins
    
- V3.4
    - ASM recycled, less weighs, adapts easier to other frequencies / timings
    - Added Support LGT8F328P with a frequency of 32/16/8 MHZ
    - redesigned Polling Millis ()/Micros () - direct call call to interrupt Timer0_OVF, removed the extra code
    
- V3.5
    - Fixed compilation error in some cases
    
- V3.6
    - Added adjustment of the interruption ban regime on the fly

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code