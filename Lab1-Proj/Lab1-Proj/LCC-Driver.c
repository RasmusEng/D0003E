#define short charCodes[5] = {0x01050501};
/* LCD Control and Status Register B */
#define LCDCRB	_SFR_MEM8(0xE5)
#define LCDCS	7
#define LCD2B	6
#define LCDMUX1	5
#define LCDMUX0	4
#define LCDPM2	2
#define LCDPM1	1
#define LCDPM0	0

/* LCD Frame Rate Register */
#define LCDFRR	_SFR_MEM8(0xE6)
#define LCDPS2	6
#define LCDPS1	5
#define LCDPS0	4
#define LCDCD2	2
#define LCDCD1	1
#define LCDCD0	0

/* LCD Contrast Control Register */
#define LCDCCR	_SFR_MEM8(0xE7)
#define LCDDC2	7
#define LCDDC1	6
#define LCDDC0	5
#define LCDMDT	4
#define LCDCC3	3
#define LCDCC2	2
#define LCDCC1	1
#define LCDCC0	0

/* LCD Control and Status Register A */
#define LCDCRA	_SFR_MEM8(0xE4)
#define LCDEN	7
#define LCDAB	6
#define LCDIF	4
#define LCDIE	3
#define LCDBD	2
#define LCDCCD	1
#define LCDBL	0

void LCD_Init(void){
	//Use 32 kHz crystal oscillator
	//1/3 Bias and 1/4 duty, SEG0:SEG24 is used as port pins
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX0)| (1<<LCDMUX1)|(1<<LCDPM0) |(1<<LCDPM1) |(1<<LCDPM2);
	/* Using 16 as prescaler selection and 8 as LCD Clock Divide */
	/* gives a frame rate of 32 Hz */
	LCDFRR = (1<<LCDCD0) | (1<<LCDCD1) | (1<<LCDCD2);
	/* Set segment drive time to 125 μs and output voltage to 3.35 V*/
	LCDCCR = (1<<LCDDC0) | (1<<LCDCC1) | (1<<LCDCC2) | (1<<LCDCC3);
	/* Enable LCD, default waveform and no interrupt enabled */
	LCDCRA = (1<<LCDEN);
}

void LCD_update(unsigned char data1, unsigned char data2){
	/* LCD Blanking and Low power waveform are unchanged. */
	/* Update Display memory. */
	LCDDR0 = data1;
	LCDDR6 = data2;
}

void writeChar(int ch, int pos){
	if(pos < 0 && pos > 5){
		return;
	}
	if(ch < 48 || ch > 57){
		return;
	}
	LCDDR19:0 = 0x01;
	LCDDR19:5 = 0x05;
	LCDDR19:10 = 0x05;
	LCDDR19:15 = 0x01;
	
	
	
}