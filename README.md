# led_matrix_8x8_hello
This project is a low-cost Arduino-uno based 8x8 LED Matrix display system with all the LEDs arranged in a "common-anode" configuration. The Arduino drives the row and column of the 8x8 unit with two 74HC574 (octal) latches. One latch handles direct data byte flows from the Arduino, which is the row-latch, while the other latch, column-latch, handles the signal switching, i.e., turning the display LED columns on and off, a technique also known as hardware-multiplexing (or fast switching) or persistence-of-vision (POV) in some literatures. The project "statically" or hard-codes the characters to be written on the screen, which is a limitation at the moment. Future design would not hard-code messages but will use ASCII texts which can then be easily converted to segment display bytes. This repository was created to accompany my 11-part Youtube video series on the construction of an 8x8 LED matrix display system.