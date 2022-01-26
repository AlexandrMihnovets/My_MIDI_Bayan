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

uint8_t count = 0;		//Для энкодера

void encoder();

int main(void)
{
	//Настройка портов
	DDRD &= (~(1 << Encoder2) | (1 << Encoder1));													//Входы для энкодера
	DDRD |= (1 << Address3) | (1 << Address2) | (1 << Address1) | (1 << Address0);					//Выходы для установки адреса мультиплексоров
	PORTD &= ~((1 << Address3) | (1 << Address2) | (1 << Address1) | (1 << Address0));				//Выходы для установки адреса мультиплексоров
	DDRB &= ~((1 <<But1) | (1 << But2) | (1 << But3) | (1 << Enc_but) | (1 << Out6) | (1 << Out5));	//Входы для кнопок и левой половины
	
	
    while(1)
    {
        for (uint8_t i = 0; i < 16; i++)		//Переключаем адреса входов с 0 по 15 на 6-ти мультиплексорах
        {
			PORTD &= ~((1 << Address3) | (1 << Address2) | (1 << Address1) | (1 << Address0));	//Сброс адреса
			
			switch(i)
			{
				case 0:		PORTD |= 0b00000000;	
							//if(PINC & Out1) send_note(_C);
					break;
					
				case 1:		PORTD |= 0b00000100;
							
					break;
					
				case 2:		PORTD |= 0b00001000;
				
					break;
					
				case 3:		PORTD |= 0b00001100;
				
					break;
					
				case 4:		PORTD |= 0b00010000;
				
					break;
					
				case 5:		PORTD |= 0b00010100;
				
					break;
					
				case 6:		PORTD |= 0b00011000;																
				
					break;
					
				case 7:		PORTD |= 0b00011100;
					
					break;
					
				case 8:		PORTD |= 0b00100000;
					
					break;
					
				case 9:		PORTD |= 0b00100100;
					
					break;
					
				case 10:	PORTD |= 0b00101000;
					
					break;
					
				case 11:	PORTD |= 0b0010110;
					
					break;
					
				case 12:	PORTD |= 0b00110000;
					
					break;
					
				case 13:	PORTD |= 0b00110100;
					
					break;
					
				case 14:	PORTD |= 0b00111000;
					
					break;
					
				case 15:	PORTD |= 0b00111100;
					
					break;
				
			}
			
			encoder();		//Опрашиваем энкодер
        }
    }
}

void encoder(){
	static uint8_t new_state = 0;			//Новое состояние ножек энкодера
	static uint8_t old_state = 0;			//Старое состояние ножек энкодера
	
	new_state = (PIND & 0b11000000) >> 2;	//Читаем состояние битов энкодера, сдвигаем на два вправо и присваиваем переменной
	
	switch (old_state | new_state)			//Склеиваем две переменные. В рещультате получится число, по которому определяем направление вращения
	{
		case 0xd0:  
		case 0x40: 
		case 0x20:
		case 0xb0:	count++;				//Энкодер вправо
			break;
		
		case 0xe0:  
		case 0x70: 
		case 0x10:
		case 0x80:	count--;				//Энкодер влево
			break;
	}
	
	if(count > 127) count = 0;				//В MIDI 127 - магическое число (127 инструментов, например)
	
	old_state = new_state << 2;
}