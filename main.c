#include <msp430.h>
#include <inttypes.h>
#include <msp430g2553.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//LCD pins
#define CMD         0
#define DATA        1
#define LCD_OUT     P2OUT
#define LCD_DIR     P2DIR
#define RS          BIT2
#define EN          BIT3
#define D4          BIT4
#define D5          BIT5
#define D6          BIT6
#define D7          BIT7

// LCD Functions prototypes
void delay(uint8_t t);
void pulseEN(void);
void lcd_init();
void lcd_start();
void lcd_layout();
void lcd_clear();
void lcd_update();
void lcd_write(uint8_t value, uint8_t mode);
void lcd_print(char *s);
void lcd_setCursor(uint8_t row, uint8_t col);

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	 P1OUT = 0;              // set default values to all zeros for port 1
	 P1DIR = 0;              // set port direction to all inputs for port 1
	 P1REN = 0;              // disable pull up/down resistors for port 1

	 lcd_init();
	 lcd_start();

	 __delay_cycles(100000);
	return 0;
}

// Function to pulse EN pin after data is written
// Pulsing the enable pin (EN) refreshed the screen to display
//  the data written to the screen
void pulseEN(void)
{
    LCD_OUT |= EN;
    delay(1);
    LCD_OUT &= ~EN;
    delay(1);
}

// Initialize LCD
void lcd_init()
{
    P2SEL &= ~(BIT6+BIT7); // Set P2.6 and P2.7 for General Purpose I/O
    LCD_DIR |= (RS+EN+D4+D5+D6+D7); // Set the designated P2 bits as output
    LCD_OUT &= ~(RS+EN+D4+D5+D6+D7); // Set the P2 outputs as low

    delay(150);            // Wait for power up ( 15ms )
    lcd_write(0x33, CMD);  // Initialization Sequence 1
    delay(50);
    lcd_write(0x32, CMD); // Initialization Sequence 2
    delay(1);
    // All subsequent commands take 40 us to execute, except clear & cursor return (1.64 ms)
    lcd_write(0x28, CMD); delay(1);          // 4 bit mode, 2 line
    lcd_write(0x0F, CMD); delay(1);          // Display ON, Cursor ON, Blink ON
    lcd_write(0x01, CMD); delay(20);         // Clear screen
    lcd_write(0x06, CMD);  delay(1);        // Auto Increment Cursor
    lcd_setCursor(0,0);               // Goto Row 1 Column 1
}

void lcd_start()
{
    lcd_setCursor(0,4);
    lcd_print("Skynet");
    lcd_setCursor(1,3);
    lcd_print("Security");
    __delay_cycles(3000000);
}

//Configuring the LCD to display voltage read
void lcd_layout()
{
    lcd_setCursor(0, 0);
    lcd_print("                ");
    lcd_setCursor(0, 4);
    lcd_print("Disarmed");
    lcd_setCursor(1, 0);
    lcd_print("                ");
    lcd_setCursor(1, 0);
    lcd_print("Pass:");
}

void lcd_clear()
{
    lcd_setCursor(0,0);
    lcd_print("                ");
    lcd_setCursor(1,0);
    lcd_print("                ");
}

//Update the LCD with the read voltage
void lcd_update()
{
   lcd_setCursor(1,0);
   lcd_print("Pass:");
   lcd_setCursor(1,5);
   lcd_print("         "); //Clearing the screen to display the key
   lcd_setCursor(1,5);
   lcd_print(password);
}

//Function to write data/command to LCD
void lcd_write(uint8_t value, uint8_t mode)
{
    if(mode == CMD)  // Set RS -> LOW for Command mode
    {
        LCD_OUT &= ~RS;
    }
    else    // Set RS -> HIGH for Data mode
    {
        LCD_OUT |= RS;
    }

    LCD_OUT = ((LCD_OUT & 0x0F) | (value & 0xF0));
    pulseEN();
    delay(1);      // Write high nibble first
    LCD_OUT = ((LCD_OUT & 0x0F) | ((value << 4) & 0xF0));
    pulseEN();
    delay(1);      // Write low nibble next
 }

// Function to print a string on LCD
void lcd_print(char *s)
{
    while (*s)
    {
        lcd_write(*s, DATA);
        s++;
    }
}

// Function to move cursor to desired position on LCD
void lcd_setCursor(uint8_t row, uint8_t col)
{
    const uint8_t row_offsets[] = { 0x00, 0x40};
    lcd_write(0x80 | (col + row_offsets[row]), CMD);
    delay(1);
}
