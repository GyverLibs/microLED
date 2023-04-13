#include "microLED.h"

// Ручное обслуживание функций времени на период запрета прерываний
void systemUptimePoll(void) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168p__) \
        || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) \
        || defined(__AVR_ATmega32u4__)
    if (TIFR0 & (1 << TOV0)) {    // Если Timer0 досчитал до переполнения
        asm volatile                
        (
        "IN __tmp_reg__,__SREG__  \n\t"    // Сохраняем настройки прерываний    
        "CLI                         \n\t" // Запрещаем прерывания
        "ICALL                       \n\t" // Прыгаем в прерывание TIMER0 OVERFLOW, где обслуживается millis() / micros()
        "OUT __SREG__,__tmp_reg__ \n\t" // Возвращаем настройки прерываний
        ::"z"(TIMER0_OVF_vect_num * 2)  // Адрес прерывания
        );
    }
#endif
}