#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define DISABLE()       cli()
#define ENABLE()        sei()

#define SET(x) (1 << x)

void initClk(void) {
    // CLKPCE: enable change of CLKPS.
    CLKPR = SET(CLKPCE);
    // CLKPS(3:0): division factor 1.
    // The other bits are unimportant.
    CLKPR = 0;
}

void initLcd(void) {
    // LCDEN: enables the driver.
    // LCDAB: low power waveform.
    LCDCRA = SET(LCDEN)   | SET(LCDAB);
    // LCDCS: asynchronous clock source.
    // LCDMUX(1:0): 1/4 duty.
    // LCDPM(2:0): 25 segments.
    LCDCRB = SET(LCDCS)
           | SET(LCDMUX1) | SET(LCDMUX0)
           | SET(LCDPM2)  | SET(LCDPM1)  | SET(LCDPM0);
    // LCDCD(2:0): 8 division ratio.
    LCDFRR = SET(LCDCD2)  | SET(LCDCD1)  | SET(LCDCD0);
    // LCDCC(3:0): 3.35 V contract control.
    LCDCCR = SET(LCDCC3)  | SET(LCDCC2)  | SET(LCDCC1)  | SET(LCDCC0);
}

void initTimer(void) {
    TCCR1B = SET(CS12);
}

void initButton(void) {
    PORTB = SET(PB7);
}

const uint16_t TICKS_PER_SECOND = 2;
static const uint16_t FREQ = 3906;

void setTimerInterrupt(void) {
    // COM1A(1:0): set OC1A on compare match.
    TCCR1A = SET(COM1A1) | SET(COM1A0);
    // WGM1(3:2): CTC mode.
    // CS1(2:0): 1024 prescaling factor.
    TCCR1B = SET(WGM12)  | SET(CS12) | SET(CS10);
    // OCIE1A: output comparison A enabled.
    TIMSK1 = SET(OCIE1A);

    // Interrupts must be disabled when accessing 16-bit registers.
    DISABLE();
    // OCR1A(:): counter comparison A value.
    OCR1A  = FREQ;
    // Reset timer.
    TCNT1  = 0;
    ENABLE();
}

void setButtonInterrupt(void) {
    // PCIE1: enable PCINT(15:8) interrupts.
    EIMSK  = SET(PCIE1);
    // PCIN15: enable PCINT15 interrupt.
    PCMSK1 = SET(PCINT15);
}

void clearChar(const int pos) {
    if (pos < 0 || pos > 5)
        return;

    div_t qr = div(pos, 2);

    volatile uint8_t *lcd = &LCDDR0 + qr.quot;
    uint8_t mask = qr.rem ? 0x0F : 0xF0;

    for (uint_fast8_t i = 0; i < 4; i++) {
        *lcd &= mask;
        lcd += 0x5;
    }
}

static const uint16_t sccTable[] = {
    0x1551, // 0
    0x0110, // 1
    0x1E11, // 2 
    0x1B11, // 3
    0x0B50, // 4
    0x1B41, // 5
    0x1F41, // 6
    0x0111, // 7
    0x1F51, // 8
    0x0B51  // 9
};

void writeChar(const char ch, const int pos) {
    if (pos < 0 || pos > 5)
        return;

    int_fast8_t num = ch - '0';
    if (num < 0 || num > 9) {
        clearChar(pos);
        return;
    }

    div_t qr = div(pos, 2);

    uint16_t scc = sccTable[num];
    volatile uint8_t *lcd = &LCDDR0 + qr.quot;
    uint8_t mask = qr.rem ? 0x0F : 0xF0;

    for (uint_fast8_t i = 0; i < 4; i++) {
        uint8_t nib = scc & 0xF;
        if (qr.rem)
            nib <<= 4;

        *lcd = (*lcd & mask) | nib;
        lcd += 0x5;

        scc >>= 4;
    }
}

void printAt(const long num, const int pos) {
    writeChar(num % 100 / 10 + '0', pos);
    writeChar(num % 10 + '0', pos + 1);
}

bool isPrime(const unsigned long n) {
    for (unsigned long i = 2; i * i <= n; i++)
         if (!(n % i))
            return false;

    return true;
}
