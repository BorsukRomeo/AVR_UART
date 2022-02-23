#define F_CPU 16000000UL

//USART init parameters ---------------
#define FOSC 16000000 // clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
//-------------------------------------

//asynchronous, interrupt driven with cyclic buffer-------
#define UART_RX_BUF_SIZE 32 //RX buffer size
#define UART_RX_BUF_MASK (UART_RX_BUF_SIZE-1)


// Libraries ------------------
#include<avr/io.h>
#include<avr/delay.h>
#include"HD44780.h"
#include<avr/interrupt.h>

volatile char UART_RxBuf[UART_RX_BUF_SIZE];
volatile uint8_t UART_RxHead;
volatile uint8_t UART_RxTail;


ISR(USART_RXC_vect){

    //UART_RxBuf[UART_RxHead]=UDR;
    //UART_RxHead++;

   char* charon;
   *charon = UDR;

    if((*charon>31)&(*charon)<127){
        LCD_WriteText(charon);
    }
}
//---------------------------------------------------------


//USART init function ---------------------------
void USART_init(unsigned int ubrr){

    //normal asynchronous mode
    UCSRA&=~(1<<U2X);

    //set baud rate
    UBRRH=(unsigned char)(ubrr>>8);
    UBRRL=(unsigned char)(ubrr);

    //enable Rx Tx and Rx interrupts
    UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);

    //set frame format ( 8 data, 1 stop )
    UCSRC=(1<<URSEL)|(3<<UCSZ0);
}
//-----------------------------------------------

// Frankfurt
//~~~~~~~~~~~~~~~~~~~~~~~~~
int main(void){

    
    //LCD init
    LCD_Initalize();   
    LCD_Home();
    LCD_WriteText("AVR UART");
    _delay_ms(2000);
    LCD_Clear();

    //Initialize UART and interrupts
    USART_init(MYUBRR);
    sei();

    DDRB = (1<<PB1);// < ------------  Jakakolwiek zmiana rozwala mi uarta... chyba trzeba ustabilizować clock albo ogarnąć oscylator
    PORTB = (1<<PB1);

    //main program loop
    while(1){

        //LCD_Clear();
        //LCD_Home();
    _delay_ms(1000);
    PORTB ^= (1<<PB1);    
 
         
    }
}

/*

#define LCD_RS_DIR		DDRC
#define LCD_RS_PORT 	PORTC
#define LCD_RS			(1 << PC5)

#define LCD_E_DIR		DDRC
#define LCD_E_PORT		PORTC
#define LCD_E			(1 << PC4)

#define LCD_DB4_DIR		DDRB
#define LCD_DB4_PORT	PORTB
#define LCD_DB4			(1 << PB0)

#define LCD_DB5_DIR		DDRD
#define LCD_DB5_PORT	PORTD
#define LCD_DB5			(1 << PD7)

#define LCD_DB6_DIR		DDRD
#define LCD_DB6_PORT	PORTD
#define LCD_DB6			(1 << PD6)

#define LCD_DB7_DIR		DDRD
#define LCD_DB7_PORT	PORTD
#define LCD_DB7			(1 << PD5)

*/