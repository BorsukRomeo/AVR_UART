#include<avr/io.h>
#include<avr/delay.h>



/*----
PLAN:
/-----

VARIANT 1
USART...




VARIANT 2
(Receiving)------------------------------------------------------------------
First impulse triggers the interrupt
the interrupt triggers counter in order to get the impulse length
Pin interrupt disabled, timer interrupt enabled
Then after moving the phase a little, we are reading incoming bits in a loop 
End of trensmission, deactivate timer interrupt, activate pin interrupt
-----------------------------------------------------------------------------*/





/*--------
PINS 
---------*/

#define TX (1 << PD1)
#define TX_up PORTD|=TX
#define TX_down PORTD&=~TX

#define RX (1 << PD0)
#define RX_up (PIND & (1 << PIND0))
#define RX_down !(PIND & (1 << PIND0))


void UART_init(){

    DDRD|=TX;
    DDRD&=~RX;
}

int main(void){

    UART_init();


    while(1){

       if(RX_up){
           TX_up;
       }
       else{TX_down;}

    }


}