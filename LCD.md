# Liquid Crystal Display

I am using a 16x2 LCD. In order to save pins, I will be using the display in 4-bit mode. As such, I am only using data pins 4 - 7. This is the pinout:

![alt text](https://github.com/max-mejia-13/Skynet_Security/blob/main/images/16x2-LCD-Pinout.png)

## Wiring

Power:
VSS = GND
VDD = +5v
VE = Potentiometer (Contrast Control)

Registers & Enable:
RS = P2.2
RW = GND
E = P2.3

Data:
D4 = P2.4
D5 = P2.5
D6 = P2.6
D7 = P2.7

Backlight:
A = +5v
K = GND

## Code

These are the variable definitions used in the code. I am using pins on port 2 to handle LCD functions:

![alt text](https://github.com/max-mejia-13/Skynet_Security/blob/main/images/lcd_setup.png)


These are the function prototypes:

![alt text](https://github.com/max-mejia-13/Skynet_Security/blob/main/images/lcd_prototypes.png)


These are the complete LCD functions:

![alt text](https://github.com/max-mejia-13/Skynet_Security/blob/main/images/lcd_fn_1.png)
![alt text](https://github.com/max-mejia-13/Skynet_Security/blob/main/images/lcd_fn_2.png)
![alt text](https://github.com/max-mejia-13/Skynet_Security/blob/main/images/lcd_fn_3.png)
![alt text](https://github.com/max-mejia-13/Skynet_Security/blob/main/images/lcd_fn_4.png)
