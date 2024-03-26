#ifdef FASTLED_SUPPORT

    #ifndef _FastLEDsupport_h
    #define _FastLEDsupport_h

    // поддержка типа данных FastLED для microLED
    #include <FastLED.h>
    #include "microLED.h"

    mData CRGBtoData(CRGB col);

    #endif // _FastLEDsupport_h

#endif // FASTLED_SUPPORT
