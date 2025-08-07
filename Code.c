#include <avr/io.h>
#include <util/delay.h>  // Для _delay_ms()

int main(void)
{
	DDRB = 0xFF;       // PORTB – вихід
	PORTB = 0xFF;      // Усі лінії PBx = лог. 1

	DDRD &= ~(1 << PD4);   // PD4 – вхід
	PORTD |= (1 << PD4);   // Підтягуючий резистор на PD4

	TCCR0B = 0x07; // Таймер0: лічильник на спадаючому фронті на PD4 (T0)

	while (1)
	{
		if (TCNT0 == 0x14) {
			PORTB = 0xFF;
			TCNT0 = 0;
			_delay_ms(1);  // Затримка після спрацювання (антидребезг)
		}

		if (TCNT0 == 0x0A) {
			PORTB = 0x00;
			_delay_ms(1);  // Затримка після спрацювання (антидребезг)
		}
	}
}

