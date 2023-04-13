#include "color_utility.h"

// ============================================== COLOR FUNC ===============================================
mData getFade(mData data, uint8_t val) {
    if (data == 0) return 0;
    val = 255 - val;
    return mergeRGBraw(fade8R(data, val), fade8G(data, val), fade8B(data, val));
}

uint32_t getHEX(mData data) {
    return RGBto24(getR(data), getG(data), getB(data));
}

mData getBlend(int x, int amount, mData c0, mData c1) {
    while (x >= amount) x -= amount;
    amount -= 1;
    return mergeRGBraw(
    getR(c0) + (getR(c1) - getR(c0)) * x / amount,
    getG(c0) + (getG(c1) - getG(c0)) * x / amount,
    getB(c0) + (getB(c1) - getB(c0)) * x / amount
    );
}

mData mRGB(uint8_t r, uint8_t g, uint8_t b) {
    return mergeRGB(r, g, b);
}

mData mHSVfast(uint8_t h, uint8_t s, uint8_t v) {    
    // быстрый HSV
    uint8_t r, g, b;
    uint8_t value = ((24 * h / 17) / 60) % 6;
    uint8_t vmin = (long)v - v * s / 255;
    uint8_t a = (long)v * s / 255 * (h * 24 / 17 % 60) / 60;
    uint8_t vinc = vmin + a;
    uint8_t vdec = v - a;
    switch (value) {
    case 0: r = v; g = vinc; b = vmin; break;
    case 1: r = vdec; g = v; b = vmin; break;
    case 2: r = vmin; g = v; b = vinc; break;
    case 3: r = vmin; g = vdec; b = v; break;
    case 4: r = vinc; g = vmin; b = v; break;
    case 5: r = v; g = vmin; b = vdec; break;
    }
    return mRGB(r, g, b);
}

mData mHSV(uint8_t h, uint8_t s, uint8_t v) {    
    // обычный HSV
    float r, g, b;
    
    float H = h / 255.0;
    float S = s / 255.0;
    float V = v / 255.0;
    
    int i = int(H * 6);
    float f = H * 6 - i;
    float p = V * (1 - S);
    float q = V * (1 - f * S);
    float t = V * (1 - (1 - f) * S);
    
    switch (i % 6) {
    case 0: r = V, g = t, b = p; break;
    case 1: r = q, g = V, b = p; break;
    case 2: r = p, g = V, b = t; break;
    case 3: r = p, g = q, b = V; break;
    case 4: r = t, g = p, b = V; break;
    case 5: r = V, g = p, b = q; break;    
    }
    r *= 255.0;
    g *= 255.0;
    b *= 255.0;
    return mRGB((byte)r, (byte)g, (byte)b);
}

mData mHEX(uint32_t color) {
    return mRGB(RGB24toR(color), RGB24toG(color), RGB24toB(color));
}

mData mWheel(int color, uint8_t bright) {
    uint8_t r, g, b;
    if (color <= 255) {                         // красный макс, зелёный растёт
        r = 255;
        g = color;
        b = 0;
    }
    else if (color > 255 && color <= 510) {   // зелёный макс, падает красный
        r = 510 - color;
        g = 255;
        b = 0;
    }
    else if (color > 510 && color <= 765) {   // зелёный макс, растёт синий
        r = 0;
        g = 255;
        b = color - 510;
    }
    else if (color > 765 && color <= 1020) {  // синий макс, падает зелёный
        r = 0;
        g = 1020 - color;
        b = 255;
    }
    else if (color > 1020 && color <= 1275) { // синий макс, растёт красный
        r = color - 1020;
        g = 0;
        b = 255;
    }
    else if (color > 1275 && color <= 1530) { // красный макс, падает синий
        r = 255;
        g = 0;
        b = 1530 - color;
    }
    if (bright != 255) {
        r = fade8(r, bright);
        g = fade8(g, bright);
        b = fade8(b, bright);
    }
    return mRGB(r, g, b);
}

mData mWheel8(uint8_t color, uint8_t bright) {
    uint8_t r, g, b;
    byte shift;
    if (color > 170) {
        shift = (color - 170) * 3;
        r = shift;
        g = 0;
        b = 255 - shift;
    } else if (color > 85) {
        shift = (color - 85) * 3;
        r = 0;
        g = 255 - shift;
        b = shift;
    } else {
        shift = color * 3;
        r = 255 - shift;
        g = shift;
        b = 0;
    }
    if (bright != 255) {
        r = fade8(r, bright);
        g = fade8(g, bright);
        b = fade8(b, bright);
    }
    return mRGB(r, g, b);
}

mData mKelvin(int kelvin) {
    float tmpKelvin, tmpCalc;
    uint8_t _r, _g, _b;
    
    kelvin = constrain(kelvin, 1000, 30000);
    tmpKelvin = kelvin / 100;
    
    // red
    if (tmpKelvin <= 66) _r = 255;
    else {
        tmpCalc = tmpKelvin - 60;
        tmpCalc = (float)pow(tmpCalc, -0.1332047592);
        tmpCalc *= (float)329.698727446;
        tmpCalc = constrain(tmpCalc, 0, 255);
        _r = tmpCalc;
    }
    
    // green
    if (tmpKelvin <= 66) {
        tmpCalc = tmpKelvin;
        tmpCalc = (float)99.4708025861 * log(tmpCalc) - 161.1195681661;
        tmpCalc = constrain(tmpCalc, 0, 255);
        _g = tmpCalc;
    } else {
        tmpCalc = tmpKelvin - 60;
        tmpCalc = (float)pow(tmpCalc, -0.0755148492);
        tmpCalc *= (float)288.1221695283;
        tmpCalc = constrain(tmpCalc, 0, 255);
        _g = tmpCalc;
    }
    
    // blue
    if (tmpKelvin >= 66) _b = 255;
    else if (tmpKelvin <= 19) _b = 0;
    else {
        tmpCalc = tmpKelvin - 10;
        tmpCalc = (float)138.5177312231 * log(tmpCalc) - 305.0447927307;
        tmpCalc = constrain(tmpCalc, 0, 255);
        _b = tmpCalc;
    }
    return mRGB(_r, _g, _b);
}