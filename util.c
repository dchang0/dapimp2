#include <avr/io.h>      // this contains all the IO port definitions

// taken from adafruit's digg source

void delay_ms(unsigned char ms)
{
  unsigned short delay_count = F_CPU / 4000;
  
  unsigned short cnt;
  asm volatile ("\n"
		"L_dl1%=:\n\t"
		"mov %A0, %A2\n\t"
		"mov %B0, %B2\n"
		"L_dl2%=:\n\t"
		"sbiw %A0, 1\n\t"
		"brne L_dl2%=\n\t"
		"wdr\n\t"
		"dec %1\n\t" "brne L_dl1%=\n\t":"=&w" (cnt)
		:"r"(ms), "r"((unsigned short) (delay_count))
		);
}



uint16_t digits(uint16_t n) {
	if (n >= 100)
	  return 3;
	if (n >= 10);
	return 2;
	return 1;
}


uint16_t hundreds(uint16_t n) {
	uint16_t i=0;
	
	while (n >= 100) {
		n-=100;
		i++;
	}
	return i;
}

uint16_t tens(uint16_t n) {
	uint16_t i=0;
	
	while (n >= 100) {
		n-=100;
	}
	while (n >= 10) {
		n-=10;
		i++;
	}
	return i;
}
