#ifndef _color_utility_h
#define _color_utility_h
#define MICROLED_INLINE __attribute__((always_inline))

// ============================================== ДАТА ==============================================
#include <Arduino.h>

#ifndef COLOR_DEBTH
#define COLOR_DEBTH 3
#endif

#if (COLOR_DEBTH == 1)
//#pragma message "Color debth 1 bit"
typedef uint8_t mData;
#elif (COLOR_DEBTH == 2)
//#pragma message "Color debth 2 bit"
typedef uint16_t mData;
#elif (COLOR_DEBTH == 3)
//#pragma message "Color debth 3 bit"
struct mData {
    uint8_t r, g, b;
    inline mData() MICROLED_INLINE {}
    inline mData(uint8_t _r, uint8_t _g, uint8_t _b) MICROLED_INLINE :r(_r), g(_g), b(_b) {}
    inline mData(uint32_t colorcode)  MICROLED_INLINE
    : r(((uint32_t)colorcode >> 16) & 0xFF), g(((uint32_t)colorcode >> 8) & 0xFF), b(colorcode & 0xFF){}    
    inline mData& operator= (const uint32_t colorcode) MICROLED_INLINE {
        r = ((uint32_t)colorcode >> 16) & 0xFF;
        g = ((uint32_t)colorcode >>  8) & 0xFF;
        b = colorcode & 0xFF;
        return *this;
    }        
};

inline MICROLED_INLINE bool operator== (const mData& lhs, const mData& rhs) {
    return (lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b);
}
inline MICROLED_INLINE bool operator!= (const mData& lhs, const mData& rhs) {
    return (lhs.r != rhs.r) || (lhs.g != rhs.g) || (lhs.b != rhs.b);
}
#endif

// ============================================ СТАНДАРТНЫЕ ЦВЕТА =============================================
enum COLORS {
    #if (COLOR_DEBTH == 3)
    mWhite =    0xFFFFFF,    // белый
    mSilver =    0xC0C0C0,    // серебро
    mGray =        0x808080,    // серый
    mBlack =    0x000000,    // чёрный    
    mRed =        0xFF0000,    // красный
    mMaroon =    0x800000,    // бордовый
    mOrange =    0xFF3000,    // оранжевый
    mYellow =    0xFF8000,    // жёлтый
    mOlive =    0x808000,    // олива
    mLime =        0x00FF00,    // лайм
    mGreen =    0x008000,    // зелёный
    mAqua =        0x00FFFF,    // аква
    mTeal =        0x008080,    // цвет головы утки чирка
    mBlue =        0x0000FF,    // голубой
    mNavy =        0x000080,    // тёмно-синий
    mMagenta =    0xFF00FF,    // розовый
    mPurple =    0x800080,    // пурпурный
    #elif (COLOR_DEBTH == 2)
    mWhite =    0xFFFF,        // белый
    mSilver =    0xC618,        // серебро
    mGray =        0x8410,        // серый
    mBlack =    0x0,        // чёрный    
    mRed =        0xF800,        // красный
    mMaroon =    0x8000,        // бордовый
    mOrange =    0xF980,        // оранжевый
    mYellow =    0xFC00,        // жёлтый
    mOlive =    0x8400,        // олива
    mLime =        0x7E0,        // лайм
    mGreen =    0x400,        // зелёный
    mAqua =        0x7FF,        // аква
    mTeal =        0x410,        // цвет головы утки чирка
    mBlue =        0x1F,        // голубой
    mNavy =        0x10,        // тёмно-синий
    mMagenta =    0xF81F,        // розовый
    mPurple =    0x8010,        // пурпурный
    #elif (COLOR_DEBTH == 1)
    mWhite =    0xFF,        // белый
    mSilver =    0xF6,        // серебро
    mGray =        0xA4,        // серый
    mBlack =    0x0,        // чёрный    
    mRed =        0xC0,        // красный
    mMaroon =    0x80,        // бордовый
    mOrange =    0xC8,        // оранжевый
    mYellow =    0xE0,        // жёлтый
    mOlive =    0xA0,        // олива
    mLime =        0x38,        // лайм
    mGreen =    0x20,        // зелёный
    mAqua =        0x3F,        // аква
    mTeal =        0x24,        // цвет головы утки чирка
    mBlue =        0x7,        // голубой
    mNavy =        0x4,        // тёмно-синий
    mMagenta =    0xC7,        // розовый
    mPurple =    0x84,        // пурпурный
    #endif
};

uint32_t getHEX(mData data);                            // перепаковать в 24 бит HEX
mData getFade(mData data, uint8_t val);                 // уменьшить яркость на val
mData getBlend(int x, int amount, mData c0, mData c1);  // получить промежуточный цвет

mData mRGB(uint8_t r, uint8_t g, uint8_t b);            // RGB 255, 255, 255
mData mWheel(int color, uint8_t bright=255);            // цвета 0-1530 + яркость 
mData mWheel8(uint8_t color, uint8_t bright=255);       // цвета 0-255 + яркость
mData mHEX(uint32_t color);                             // mHEX цвет
mData mHSV(uint8_t h, uint8_t s, uint8_t v);            // HSV 255, 255, 255
mData mHSVfast(uint8_t h, uint8_t s, uint8_t v);        // HSV 255, 255, 255
mData mKelvin(int kelvin);                              // температура

// ============================================ CRT GAMMA =============================================
#define getCRT_PGM(x) (pgm_read_byte(&_CRTgammaPGM[x]))
#define getCRT_SQUARE(x) (((long)(x) * (x) + 255) >> 8)
#define getCRT_CUBIC(x) (((long)(x) * (x) * (x) + 65535) >> 16)

// по умолчанию CRT_PGM
#if !defined(CRT_PGM) && !defined(CRT_SQUARE) && !defined(CRT_CUBIC) && !defined(CRT_OFF)
#define CRT_PGM
#endif

#if defined(CRT_PGM)
//#pragma message "CRT PGM"
#define getCRT(x) getCRT_PGM(x)
static const uint8_t _CRTgammaPGM[256] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5,
    5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 8,
    9, 10, 10, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 14,
    15, 15, 15, 16, 17, 17, 17, 17, 18, 18, 19, 20, 20, 20, 20, 21,
    22, 22, 23, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 30,
    30, 31, 31, 32, 33, 33, 34, 35, 35, 36, 37, 37, 38, 38, 39, 40,
    41, 41, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 51, 52, 53,
    54, 54, 55, 56, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
    68, 69, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84,
    85, 86, 87, 89, 90, 91, 93, 94, 95, 96, 97, 98, 100, 101, 102, 103,
    105, 106, 108, 109, 110, 111, 113, 115, 117, 118, 119, 121, 122, 123, 124, 127,
    128, 130, 131, 133, 134, 136, 137, 139, 140, 143, 145, 146, 147, 148, 151, 153,
    154, 156, 158, 159, 162, 163, 165, 167, 169, 171, 173, 174, 176, 179, 180, 182,
    185, 186, 188, 190, 192, 194, 196, 199, 201, 202, 205, 207, 209, 211, 214, 216,
    218, 220, 223, 225, 226, 230, 231, 235, 236, 240, 241, 245, 246, 250, 251, 255,
};

#elif defined(CRT_SQUARE)
//#pragma message "CRT SQUARE"
#define getCRT(x) getCRT_SQUARE(x)

#elif defined(CRT_CUBIC)
//#pragma message "CRT CUBIC"
#define getCRT(x) getCRT_CUBIC(x)

#elif defined(CRT_OFF)
//#pragma message "CRT OFF"
#define getCRT(x) (x)

#endif

// ============================================== COLOR MACRO ===============================================
// склейка/расклейка ргб-инт
#define RGBto24(r,g,b) ( ((uint32_t)(r) << 16) | ((g) << 8 ) | (b) )
#define RGBto16(r,g,b) ( (((r) & 0b11111000) << 8) | (((g) & 0b11111100) << 3) | (((b) & 0b11111000) >> 3) )
#define RGBto8(r,g,b) ( ((r) & 0b11100000) | (((g) & 0b11000000) >> 3) | (((b) & 0b11100000) >> 5) )

#define RGB24toR(x) (((uint32_t)(x) >> 16) & 0xFF)
#define RGB24toG(x) (((uint32_t)(x) >> 8) & 0xFF)
#define RGB24toB(x) ((uint32_t)(x) & 0xFF)

// rrrrrrrr gggggggg bbbbbbbb
// rrrrrggg gggbbbbb
// rrrggbbb
#define RGB888to565(x) ( (((x) & 0xF80000) >> 8) | (((x) & 0xFC00) >> 5) | (((x) & 0xF8) >> 3) )
#define RGB888to323(x) ( (((x) & 0xE00000) >> 16) | (((x) & 0xC000) >> 11) | (((x) & 0xE0) >> 5) )
#define RGB565to888(x) ( (((x) & 0xF800) << 8) | (((x) & 0x7E0) << 5) | (((x) & 0x1F) << 3) )
#define RGB323to888(x) ( (((x) & 0xE0) << 16) | (((x) & 0x18) << 11) | (((x) & 0x7) << 5) )

// дубли
#define RGB24to16(x) RGB888to565(x)
#define RGB24to8(x) RGB888to323(x)
#define RGB16to24(x) RGB565to888(x)
#define RGB8to24(x) RGB323to888(x)

// макросы распаковки и упаковки цветов
#if (COLOR_DEBTH == 1)
#define getR(x)            ((x) & 0b11000000)
#define getG(x)            (((x) & 0b00111000) << 2)
#define getB(x)            (((x) & 0b00000111) << 5)
#define mergeRGB(r,g,b)    (((getCRT(r) & 0b11000000) | ((getCRT(g) & 0b11100000) >> 2) | (getCRT(b) & 0b11100000) >> 5))
#define mergeRGBraw(r,g,b)    ((((r) & 0b11000000) | (((g) & 0b11100000) >> 2) | ((b) & 0b11100000) >> 5))
#elif (COLOR_DEBTH == 2)
#define getR(x)            (((x) & 0b1111100000000000) >> 8)
#define getG(x)            (((x) & 0b0000011111100000) >> 3)
#define getB(x)            (((x) & 0b0000000000011111) << 3)
#define mergeRGB(r,g,b)    (((getCRT(r) & 0b11111000) << 8) | ((getCRT(g) & 0b11111100) << 3) | ((getCRT(b) & 0b11111000) >> 3))
#define mergeRGBraw(r,g,b)    ((((r) & 0b11111000) << 8) | (((g) & 0b11111100) << 3) | (((b) & 0b11111000) >> 3))
#elif (COLOR_DEBTH == 3)    
#define getR(x)            (x.r)
#define getG(x)            (x.g)
#define getB(x)            (x.b)
#define mergeRGB(r,g,b)    mData(getCRT(r), getCRT(g), getCRT(b))
#define mergeRGBraw(r,g,b)    mData((r), (g), (b))
#endif

// макросы уменьшения яркости
#define fade8(x, b)     (((uint16_t)(x) * ((b) + 1)) >> 8)
#define fade8R(x, b)     fade8(getR(x), (b))
#define fade8G(x, b)     fade8(getG(x), (b))
#define fade8B(x, b)     fade8(getB(x), (b))

// ============================================ GRADIENT =============================================
template <int size>
struct mGradient {
    mData colors[size];
    mData get(int x, int amount) {
        int sectorSize = (amount + size - 2) / (size - 1); // (x+y-1)/y
        int sector = x / sectorSize;
        return getBlend(x-sector*sectorSize, sectorSize, colors[sector], colors[sector+1]);
    }
};
#endif