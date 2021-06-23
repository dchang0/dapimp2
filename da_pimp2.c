#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "util.c"	
#include "adc.h"		

#define MUX_OFFSET 0x40         // MUX value for REFS0 to be enabled for AREV <---> VCC tie
#define ADC_SAVE 64             // average ADC values for sensors 
#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))
#define CC_D1 PB0
#define CC_D2 PB1
#define CC_D3 PB2
#define ADC0 PC0
#define ADC_DEBUG 0		// show ADC values on 7 segement display


// globals 
uint16_t	volt_out = 0;		// range 0 - 5120, used to convert adc to voltage - adc multiplier
uint16_t	volt = 0;		// battery voltage, could be mains power {120V,220VAC} if battery is not connected
uint8_t		adc_count = 0;		// counts sensor averaging
uint16_t	avg_adc[ADC_SAVE];	// store adc values for each sensor for average calc
uint8_t		volt_dig1,		// voltage reading broken broken out for 7-segment
		volt_dig2, 
		volt_dig3 = 0;
uint8_t 	hexcode;
uint16_t 	adc_volt;
uint16_t 	adc_read;
uint16_t 	adc_avg_total;
uint8_t 	disp_pos=1;


int main (void);
ISR(ADC_vect);
void port_init (void);
void adc2avg (void);
void adc2volt (void);
void digit_breakup (void);
void display_digits (void);
void write_sev_seg (uint8_t alphanum, uint8_t digit);
uint8_t digit_2_hex (uint8_t display_digit);


int main (void)
{

	port_init();
	adc_init();
	sei();

	while (1) 
	{
		SET(ADCSRA, ADSC);      // start adc conversion

		if ( adc_count == ADC_SAVE ) 	// accumulate ADC readings 
		{

			adc_count = 0;
			adc2avg();		// average analog voltage sensor values
			adc2volt();		// convert analog readings into voltage fahrenheit
			digit_breakup();	// break voltage into hundreds, tens and ones places

		}

		display_digits(); 			// update 7-segement display w/voltage
//		delay_ms(1);

	}

	return(0);
}


void port_init (void) {

	DDRD=0xFF;		// display port all outputs
	PORTD=0x00;		// disable all pull-ups

	SET(DDRB, CC_D1);	// output for display, start high, pull low to use
	SET(DDRB, CC_D2);	// output for display, start high, pull low to use
	SET(DDRB, CC_D3);	// output for display, start high, pull low to use
	SET(PORTB, CC_D1);	// output for display, start high, pull low to use
	SET(PORTB, CC_D2);	// output for display, start high, pull low to use
	SET(PORTB, CC_D3);	// output for display, start high, pull low to use

}


// collect analog values for averaging
ISR(ADC_vect)
{

	// ADC sensors:
	// adc0 - temp
	avg_adc[adc_count] = ADCW;
	adc_count++;
}


// average sensor data
void adc2avg (void)
{
	uint8_t i;

        // reset global vars to zero
        adc_count = 0;
        adc_volt = 0;
	adc_read = 0;
        adc_avg_total = 0;

        // slow down and average ADC readings to reduce noise
        // reduce ADC_SAVE to speed up response
        for(i=0;i<=ADC_SAVE;i++)
        {
                adc_avg_total += avg_adc[adc_count];
        }

        adc_read += adc_avg_total / ADC_SAVE;
	adc_volt = adc_read;

}


// convert adc values into voltage 
// just diving adc by 4 gives approximate voltage
void adc2volt (void) 
{
	// external spreadsheet used for calculating adc_divider
	float adc_divider = 3.50;

        adc_volt = 10 * ( adc_volt / adc_divider );

	// 5% boost on readings below 15v
	if ( adc_volt >=  150 )
		adc_volt = adc_volt * .985;

}


// reformat voltage and pot values for 7 seg
void digit_breakup (void) 
{

	if ( ADC_DEBUG )
		adc_volt = adc_read;

	volt_dig1 = adc_volt / 100;                                             // hundreds place
	volt_dig2 = ( adc_volt - ( volt_dig1 * 100 ) ) / 10;                    // tens place
	volt_dig3 = adc_volt - ( ( volt_dig1 * 100 ) + ( volt_dig2 * 10 ) );    // ones place

}

uint8_t digit_2_hex ( uint8_t display_digit )
{                                                                                                                      
        uint8_t hex;                                                                                                   

        switch ( display_digit )
	{
			case (0): { hex = 0x77; break; }
			case (1): { hex = 0x12; break; }
			case (2): { hex = 0x3D; break; }
			case (3): { hex = 0x3E; break; }
			case (4): { hex = 0x5A; break; }
			case (5): { hex = 0x6E; break; }
			case (6): { hex = 0x6F; break; }
			case (7): { hex = 0x32; break; }
			case (8): { hex = 0x7F; break; }
			case (9): { hex = 0x7A; break; }
	}

        return(hex);

}



// send voltage to 7-segment
// one digit at a time
void display_digits (void)
{
        
        // run the 7-segememt display
        for ( disp_pos=1;disp_pos<=3;disp_pos++)
        {
                if ( disp_pos == 1 )
                        hexcode = digit_2_hex(volt_dig1);	// hexcode for 7-segement first digit
                else if ( disp_pos == 2 ) {
			if (ADC_DEBUG)
				hexcode = digit_2_hex(volt_dig2); // hexcode for 7-segement second digit with decimal (0x80)
			else 
				hexcode = digit_2_hex(volt_dig2) | 0x80; // hexcode for 7-segement second digit with decimal (0x80)
                } else if ( disp_pos == 3 )
                        hexcode = digit_2_hex(volt_dig3);	// hexcode for 7-segement third digit                         

                write_sev_seg(hexcode,disp_pos);		// pull the cathodes low to populate display
	}
	
}


void write_sev_seg (uint8_t hexcode, uint8_t digit) 
{

	if ( digit == 1 ) {

		// shutdown display - reverse logic for common cathode
		// enable digit-1
		SET(PORTB, CC_D1);
		SET(PORTB, CC_D2);
		SET(PORTB, CC_D3);
		CLR(PORTB, CC_D1);

	} else if ( digit == 2 ) {

		SET(PORTB, CC_D1);
		SET(PORTB, CC_D2);
		SET(PORTB, CC_D3);
		CLR(PORTB, CC_D2);

	} else if ( digit == 3 ) {

		SET(PORTB, CC_D1);
		SET(PORTB, CC_D2);
		SET(PORTB, CC_D3);
		CLR(PORTB, CC_D3);

	}

	PORTD = hexcode;

	delay_ms(1);		// controls display speed

	SET(PORTB, CC_D1);      // output for display, start high, pull low to use
	SET(PORTB, CC_D2);      // output for display, start high, pull low to use
	SET(PORTB, CC_D3);      // output for display, start high, pull low to use

}
