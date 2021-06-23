
#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

void adc_init (void)
{
        // Setup ADC
        SET(ADCSRA,ADPS0);      // ADC pre-scalar0 set division by 8
        SET(ADCSRA,ADPS1);      // ADC pre-scalar1 set division by 8
        CLR(ADCSRA,ADPS2);      // ADC pre-scalar2 cleared division by 8
        SET(ADMUX, REFS0);      // REFS0 (bit 6) on for AREV <--> AVCC
        SET(ADCSRA,ADIE);       // ADC interrupt enable
        SET(ADCSRA,ADEN);       // ADC enable
        SET(ADCSRA, ADSC);              // start adc conversion
}


uint16_t adc_manual_read (void)
{
        SET(ADCSRA, ADSC);              // start adc conversion
        while(ADCSRA & (1<<ADSC));      // wait for conversion to complete:w
        return (ADCW);
}
