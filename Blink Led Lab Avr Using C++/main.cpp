#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

class LED
{
    public:
       LED();            // Constructor
       void LED_Toggle(); // Method to toggle LED
};

LED::LED()
{
    DDRA = 0xff;   // Set all pins on PORTA as output
    PORTA = 0x00;  // Initialize PORTA to low
}

void LED::LED_Toggle()
{
    PORTA = ~PORTA;  // Toggle PORTA (inverts the state)
}

int main()
{
    LED led_blink;  // Create an object of the LED class
    
    while(1)
    {
        led_blink.LED_Toggle();  // Toggle LED
        _delay_ms(500);          // Add a delay to make the toggle visible (500ms)
    }
    
    return 0;
}
