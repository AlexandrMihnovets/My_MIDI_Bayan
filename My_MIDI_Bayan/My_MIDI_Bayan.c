/*
 * My_MIDI_Bayan.c
 * Created: 24.01.2022 14:32:22
 * Author: MikhnovetsA
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>

#define Encoder1 PD6
#define Encoder2 PD7
#define Enc_but  PB2
#define Out6	 PB1
#define Out5	 PB0
#define Out4	 PC3 
#define Out3	 PC2
#define Out2	 PC1
#define Out1	 PC0
#define Address0 PD2
#define Address1 PD3
#define Address2 PD4
#define Address3 PD5
#define But1	 PB3 
#define But2	 PB4
#define But3	 PB5

#define note1Bb	22
#define note1B	23

#define note2C	24
#define note2Db	25
#define note2D	26
#define note2Eb	27
#define note2E	28
#define note2F	29
#define note2Gb	30
#define note2G	31
#define note2Ab	32
#define note2A	33
#define note2Bb	34
#define note2B	35

#define note3C	36
#define note3Db	37
#define note3D	38
#define note3Eb	39
#define note3E	40
#define note3F	41
#define note3Gb	42
#define note3G	43
#define note3Ab	44
#define note3A	45
#define note3Bb	46
#define note3B	47

#define note4C	48
#define note4Db	49
#define note4D	50
#define note4Eb	51
#define note4E	52
#define note4F	53
#define note4Gb	54
#define note4G	55
#define note4Ab	56
#define note4A	57
#define note4Bb	58
#define note4B	59

#define note5C	60
#define note5Db	61
#define note5D	62
#define note5Eb	63
#define note5E	64
#define note5F	65
#define note5Gb	66
#define note5G	67
#define note5Ab	68
#define note5A	69
#define note5Bb	70
#define note5B	71

#define note6C	72
#define note6Db	73
#define note6D	74
#define note6Eb	75
#define note6E	76

uint8_t count = 0;		//Для энкодера

void encoder();

void UART_ini(void);

void UART_send(unsigned char c);

int main(void)
{
	//Настройка портов
	DDRD &= (~(1 << Encoder2) | (1 << Encoder1));													//Входы для энкодера
	DDRD |= (1 << Address3) | (1 << Address2) | (1 << Address1) | (1 << Address0);					//Выходы для установки адреса мультиплексоров
	PORTD &= ~((1 << Address3) | (1 << Address2) | (1 << Address1) | (1 << Address0));				//Выходы для установки адреса мультиплексоров
	DDRB &= ~((1 <<But1) | (1 << But2) | (1 << But3) | (1 << Enc_but) | (1 << Out6) | (1 << Out5));	//Входы для кнопок и левой половины
	
	UART_ini();
	
    while(1)
    {
        for (uint8_t i = 0; i < 16; i++)		//Переключаем адреса входов с 0 по 15 на 6-ти мультиплексорах
        {
			PORTD &= ~((1 << Address3) | (1 << Address2) | (1 << Address1) | (1 << Address0));	//Сброс адреса
			
			switch(i)
			{
				case 0:		PORTD |= 0b00000000;	
							if(!(PINC & _BV(Out1))) UART_send('a');
							if(!(PINC & _BV(Out2))) UART_send('b') ;
							if(!(PINC & _BV(Out3))) UART_send('c') ;
							if(!(PINC & _BV(Out4))) UART_send('d') ;
							if(!(PINB & _BV(Out5))) UART_send('f') ;
							if(!(PINB & _BV(Out6))) UART_send('e') ;
					break;
					
				case 1:		PORTD |= 0b00000100;
							if(!(PINC & _BV(Out1))) UART_send('g') ;
							if(!(PINC & _BV(Out2))) UART_send('h') ;
							if(!(PINC & _BV(Out3))) UART_send('i') ;
							if(!(PINC & _BV(Out4))) UART_send('k') ;
							if(!(PINB & _BV(Out5))) UART_send('l') ;
							if(!(PINB & _BV(Out6))) UART_send('m') ;
					break;
					
				case 2:		PORTD |= 0b00001000;
							if(!(PINC & _BV(Out1))) UART_send('n') ;
							if(!(PINC & _BV(Out2))) UART_send('o') ;
							if(!(PINC & _BV(Out3))) UART_send('p') ;
							if(!(PINC & _BV(Out4))) UART_send('r') ;
							if(!(PINB & _BV(Out5))) UART_send('s') ;
							if(!(PINB & _BV(Out6))) UART_send('t') ;
					break;
					
				case 3:		PORTD |= 0b00001100;
							if(!(PINC & _BV(Out1))) UART_send('x') ;
							if(!(PINC & _BV(Out2))) UART_send('y') ;
							if(!(PINC & _BV(Out3))) UART_send('z') ;
							if(!(PINC & _BV(Out4))) UART_send('q') ;
							if(!(PINB & _BV(Out5))) UART_send('w') ;
							if(!(PINB & _BV(Out6))) UART_send('v') ;
					break;
					
				case 4:		PORTD |= 0b00010000;
							if(!(PINC & _BV(Out1))) UART_send('j') ;
							if(!(PINC & _BV(Out2))) UART_send('a') ;
							if(!(PINC & _BV(Out3))) UART_send('a') ;
							if(!(PINC & _BV(Out4))) UART_send('a') ;
							if(!(PINB & _BV(Out5))) UART_send('a') ;
							if(!(PINB & _BV(Out6))) UART_send('a') ;
					break;
					
				case 5:		PORTD |= 0b00010100;
							if(!(PINC & _BV(Out1))) UART_send('a') ;
							if(!(PINC & _BV(Out2))) UART_send('a') ;
							if(!(PINC & _BV(Out3))) UART_send('a') ;
							if(!(PINC & _BV(Out4))) UART_send('a') ;
							if(!(PINB & _BV(Out5))) UART_send('a') ;
							if(!(PINB & _BV(Out6))) UART_send('a') ;
					break;
					
				case 6:		PORTD |= 0b00011000;																
							if(!(PINC & _BV(Out1))) UART_send('a') ;
							if(!(PINC & _BV(Out2))) UART_send('a') ;
							if(!(PINC & _BV(Out3))) UART_send('a') ;
							if(!(PINC & _BV(Out4))) UART_send('a') ;
							if(!(PINB & _BV(Out5))) UART_send('a') ;
							if(!(PINB & _BV(Out6))) UART_send('a') ;
					break;
					
				case 7:		PORTD |= 0b00011100;
							if(!(PINC & _BV(Out1))) UART_send('a') ;
							if(!(PINC & _BV(Out2))) UART_send('a') ;
							if(!(PINC & _BV(Out3))) UART_send('a') ;
							if(!(PINC & _BV(Out4))) UART_send('a') ;
							if(!(PINB & _BV(Out5))) UART_send('a') ;
							if(!(PINB & _BV(Out6))) UART_send('a') ;
					break;
					
				case 8:		PORTD |= 0b00100000;
							if(!(PINC & _BV(Out1))) UART_send('a') ;
							if(!(PINC & _BV(Out2))) UART_send('a') ;
							if(!(PINC & _BV(Out3))) UART_send('a') ;
							if(!(PINC & _BV(Out4))) UART_send('a') ;
							if(!(PINB & _BV(Out5))) UART_send('a') ;
							if(!(PINB & _BV(Out6))) UART_send('a') ;
					break;
					
				case 9:		PORTD |= 0b00100100;
							if(!(PINC & _BV(Out1))) UART_send('a') ;
							if(!(PINC & _BV(Out2))) UART_send('a') ;
							if(!(PINC & _BV(Out3))) UART_send('a') ;
							if(!(PINC & _BV(Out4))) UART_send('a') ;
							if(!(PINB & _BV(Out5))) UART_send('a') ;
							if(!(PINB & _BV(Out6))) UART_send('a') ;
					break;
					
				case 10:	PORTD |= 0b00101000;
							if(!(PINC & _BV(Out1))) UART_send('a') ;
							if(!(PINC & _BV(Out2))) UART_send('a') ;
							if(!(PINC & _BV(Out3))) UART_send('b') ;
							if(!(PINC & _BV(Out4))) UART_send('b') ;
							if(!(PINB & _BV(Out5))) UART_send('b') ;
							if(!(PINB & _BV(Out6))) UART_send('b') ;
					break;
					
				case 11:	PORTD |= 0b0010110;
							if(!(PINC & _BV(Out1))) UART_send('b') ;
							if(!(PINC & _BV(Out2))) UART_send('b') ;
							if(!(PINC & _BV(Out3))) UART_send('b') ;
							if(!(PINC & _BV(Out4))) UART_send('b') ;
							if(!(PINB & _BV(Out5))) UART_send('b') ;
							if(!(PINB & _BV(Out6))) UART_send('b') ;
					break;
					
				case 12:	PORTD |= 0b00110000;
							if(!(PINC & _BV(Out1))) UART_send('b') ;
							if(!(PINC & _BV(Out2))) UART_send('b') ;
							if(!(PINC & _BV(Out3))) UART_send('c') ;
							if(!(PINC & _BV(Out4))) UART_send('c') ;
							if(!(PINB & _BV(Out5))) UART_send('c') ;
							if(!(PINB & _BV(Out6))) UART_send('c') ;
					break;
					
				case 13:	PORTD |= 0b00110100;
							if(!(PINC & _BV(Out1))) UART_send('d') ;
							if(!(PINC & _BV(Out2))) UART_send('h') ;
							if(!(PINC & _BV(Out3))) UART_send('d') ;
							if(!(PINC & _BV(Out4))) UART_send('k') ;
							if(!(PINB & _BV(Out5))) UART_send('r') ;
							if(!(PINB & _BV(Out6))) UART_send('e') ;
					break;
					
				case 14:	PORTD |= 0b00111000;
							if(!(PINC & _BV(Out1))) UART_send('s') ;
							if(!(PINC & _BV(Out2))) UART_send('g') ;
							if(!(PINC & _BV(Out3))) UART_send('c') ;
							if(!(PINC & _BV(Out4))) UART_send('b') ;
							if(!(PINB & _BV(Out5))) UART_send('r') ;
							if(!(PINB & _BV(Out6))) UART_send('y') ;
					break;
					
				case 15:	PORTD |= 0b00111100;
							if(!(PINC & _BV(Out1))) UART_send('j') ;
							if(!(PINC & _BV(Out2))) UART_send('v') ;
							if(!(PINC & _BV(Out3))) UART_send('d') ;
							if(!(PINC & _BV(Out4))) UART_send('e') ;
							if(!(PINB & _BV(Out5))) UART_send('s') ;
							if(!(PINB & _BV(Out6))) UART_send('q') ;
					break;
				
			}
			
			encoder();		//Опрашиваем энкодер
			
			UART_send(count);
        }
    }
}

void encoder()
{	
	static uint8_t new_state = 0;			//Новое состояние ножек энкодера
	static uint8_t old_state = 0;			//Старое состояние ножек энкодера
	
	new_state = (PIND & 0b11000000) >> 2;	//Читаем состояние битов энкодера, сдвигаем на два вправо и присваиваем переменной
	
	switch (old_state | new_state)			//Склеиваем две переменные. В рещультате получится число, по которому определяем направление вращения
	{
		case 0xd0:	count++;				//Энкодер вправо
			break;
		
		case 0xe0:	count--;				//Энкодер влево
			break;
	}
	
	if(count > 127) count = 127;			//В MIDI 127 - магическое число (127 инструментов, например)
	
	old_state = new_state << 2;
}

void UART_ini(void)
{
	// UBRR = F_CPU/(16*31250)-1=31 - это скорость работы UART
	UBRRH = 0;
	UBRRL = 31;
	
	UCSRB |= (1 << TXEN);					//Разрешаем передачу
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);	//8-bit, none, 1
}

void UART_send(unsigned char c)				//Отправка байта
{
	while(!(UCSRA & (1 << UDRE)))			//Устанавливается, когда регистр свободен
	{
		//UDRE = 0b00100000
	}
	
	UDR = c;
}