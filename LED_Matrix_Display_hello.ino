
/*
Project: Seven Segment Scrolling Texts using COMMON ANODES LEDs
 
Written by: Anumbor Ogor (eocote2002@yahoo.com, +234-8036837259)

Company: Hercules Technology.
Address: OAU, New Central Mkt, Block 8, Office No. 11, Ile-Ife, Osun State, Nigeria 
Email:   eocote2002@yahoo.com

Date:    06-Jun-2016, Sunday, 11.40pm.

Version: 1;

The project uses:
*64 LEDs arranged in an 8x8 Matrix system
*Two 74HC574 octal latches controlled by pin 8 and 9 on portb 
*Arduino uno

Pins: 
PORTD = data pins (pins 0, 1, 2, 3, 4, 5, 6, 7) though only seven is needed for segments. Pin 7 is optional 
PORTB = control pins (pins 8, 9, 10, 11, 12, 13).


Project License:
This project is released under creative common license (http://creativecommons.org/licenses/) type
- Attribution CC BY - which allow others to distribute, remix,
tweak, and build upon the authors work, even commercially, as long
as they credit the author for the original creation. 

Please note further, that different projects published on this blog ()
would use different licensing type, so readers of the blog are encouraged to
read and understand the type of licenses projects published and released,
and to adhere strictly to the authors licensing specifications
for each projects.

*/


// variables
unsigned int frameRate = 0;
unsigned int frameDelay = 0;
unsigned int frameTemp = 0;
unsigned int frameCount = 0;
unsigned int multplxRate = 0;
unsigned int sDelayCount = 0;
unsigned int mulpxRate = 0;

// array to hold screen buffer area
byte columnSlicesBuffer[50]; // static/manual construction of buffer

int noOfColumns = 8;
//int columnSlices[8];
          
          
void setup() {
  // put your setup code here, to run once:
    
   // pin declarations
   // data for portd
   pinMode(0, OUTPUT);  
   pinMode(1, OUTPUT); 
   pinMode(2, OUTPUT); 
   pinMode(3, OUTPUT); 
   pinMode(4, OUTPUT); 
   pinMode(5, OUTPUT); 
   pinMode(6, OUTPUT); 
   pinMode(7, OUTPUT); 
   
   // control for portb
   pinMode(8, OUTPUT);  
   pinMode(9, OUTPUT);  
   pinMode(10, OUTPUT); 
   pinMode(11, OUTPUT);  
   pinMode(12, OUTPUT);  
   pinMode(13, OUTPUT);  
   
   // Local Declarations
   mulpxRate = 2;
   frameRate = 1;
 
   
   //Serial.begin(9600);
}

void loop() 
{   
   // manual/static filling of buffer for displaying "HELLO"
   
   // Initialize buffers with blanks
   columnSlicesBuffer[0] = 0xFF;
   columnSlicesBuffer[1] = 0xFF;
   columnSlicesBuffer[2] = 0xFF;
   columnSlicesBuffer[3] = 0xFF;
   columnSlicesBuffer[4] = 0xFF;
   columnSlicesBuffer[5] = 0xFF;
   columnSlicesBuffer[6] = 0xFF;
   columnSlicesBuffer[7] = 0xFF;
   
   //Initialize buffers with bytes to display H 
   columnSlicesBuffer[8] =  0x01;
   columnSlicesBuffer[9] =  0xEF;
   columnSlicesBuffer[10] = 0xEF;
   columnSlicesBuffer[11] = 0xEF;     
   columnSlicesBuffer[12] = 0x01;
   columnSlicesBuffer[13] = 0xFF;
   
   //Initialize buffers with bytes to display E
   columnSlicesBuffer[14] = 0x01;
   columnSlicesBuffer[15] = 0x6D;
   columnSlicesBuffer[16] = 0x6D;
   columnSlicesBuffer[17] = 0x6D;
   columnSlicesBuffer[18] = 0x7D;   
   columnSlicesBuffer[19] = 0xFF;
   
   //Initialize buffers with bytes to display L
   columnSlicesBuffer[20] = 0x01;
   columnSlicesBuffer[21] = 0xFD;
   columnSlicesBuffer[22] = 0xFD;
   columnSlicesBuffer[23] = 0xFD;
   columnSlicesBuffer[24] = 0xFD;
   columnSlicesBuffer[25] = 0xFF;
   
   //Initialize buffers with bytes to display L
   columnSlicesBuffer[26] = 0x01;
   columnSlicesBuffer[27] = 0xFD;
   columnSlicesBuffer[28] = 0xFD;
   columnSlicesBuffer[29] = 0xFD;
   columnSlicesBuffer[30] = 0xFD;
   columnSlicesBuffer[31] = 0xFF;
   
   //Initialize buffers with bytes to display O
   columnSlicesBuffer[32] = 0x83;
   columnSlicesBuffer[33] = 0x7D;
   columnSlicesBuffer[34] = 0x7D;
   columnSlicesBuffer[35] = 0x7D;
   columnSlicesBuffer[36] = 0x83;
   columnSlicesBuffer[37] = 0xFF;
   
   // Initialize buffers with bytes to display blanks
   columnSlicesBuffer[38] = 0xFF;
   columnSlicesBuffer[39] = 0xFF;
   columnSlicesBuffer[40] = 0xFF;
   columnSlicesBuffer[41] = 0xFF;
   columnSlicesBuffer[42] = 0xFF;
   columnSlicesBuffer[43] = 0xFF;
   columnSlicesBuffer[44] = 0xFF;
   columnSlicesBuffer[45] = 0xFF;
   columnSlicesBuffer[46] = 0xFF;
   columnSlicesBuffer[47] = 0xFF;
   columnSlicesBuffer[48] = 0xFF;
   columnSlicesBuffer[49] = 0xFF;
 
   // display logic for displaying on 8x8 LED Matrix
   leds_display();
   blank_screen();
} // end loop for main code

void blank_screen()
{ 
  // clear entire video screen content    
  for (int i = 0; i < sizeof(columnSlicesBuffer); i++)
  {
     columnSlicesBuffer[i] = 0xFF; // clear screen
  } // end for
} // end blank screen function

void leds_display()
{
  int temp = sizeof(columnSlicesBuffer);//screenBufferString.length();//sizeof(screenBufferString);
   while (temp != 0)
   {
      //printf("Inside display loop..\r\n");
      
      repeatFrame();
      
      rotateFrame();
      
      temp--;
   }
} // end display method

void repeatFrame()
{
   unsigned int temp = 60;
   
   displayScreenFrame();
   
   while(temp != 0) // wait until temp = 0
   {
      temp--;
   } // end while
} // end repeatFrames

void displayScreenFrame()
{
  frameDelay = 8; // hex number
   
   while (frameDelay != 0)
   {
      frameTemp = 0x01;
      
      ModuleScan();
      // moduleScan(); if using matrix LEDs
      
      // decrement by 1
      frameDelay--;
   } // end while
} // end display screen frame

void ModuleScan()
{
  // for 8 led columns
   //frameCount = noOfColumns; // use segmentCount
   
   
   // point to screen buffer location
   // portc is control signal byte***
   // portb is data    signal byte***   
   
   /// for handling video sequencing for no of columns
   for (frameCount = 0; frameCount < 8; frameCount++)//while (frameCount != 0)
   {
      PORTD = 0x00;
      digitalWrite(8, HIGH); // clock ON column latch to enable data
      digitalWrite(8, LOW); // clock OFF column latch to enable data
      
      // use for statement to load the entire array content
      
      PORTD = columnSlicesBuffer[frameCount];
      digitalWrite(9, HIGH); // clock ON row latch to enable data
      digitalWrite(9, LOW); // clock OFF row latch to enable data
      	  
      PORTD = frameTemp;
      digitalWrite(8, HIGH); // clock ON column latch to enable data
      digitalWrite(8, LOW); // clock OFF column latch to enable data
      
      // send control signal to portc
          
      // shift the bit to the left by 1
      frameTemp <<= 1; //frameTemp = frameTemp << 1;
          
      // clear last bit in frametemp
      bitClear(frameTemp, 0);
		  
      // call shortdelay
      shortDelay();
	      
      // clear portc control signal
      //PORTB = 0x00;
      PORTD = 0x00;
      digitalWrite(8, HIGH); // clock ON column latch to enable data
      digitalWrite(8, LOW); // clock OFF column latch to enable data
      
   } // end for   
      
} // end scan

void rotateFrame() //once
{
   int i; // character index pointer
   
   for (i = 0; i < sizeof(columnSlicesBuffer); i++)
   {
      // save current(old) data in present location 
      byte x = columnSlicesBuffer[i];
      
      // clear content of that present location
      columnSlicesBuffer[i] = 0xFF; // fill content with a white space
      
      // exchange data
      byte y = x;
      
      // point to new location and pass data to new location
      columnSlicesBuffer[i-1] = y;      
      
   } // end for
   
}// end function rotateFrame

void shortDelay()
{
   // Local Declarations
   int sDelayCount = 0;
   
   // Statements
   sDelayCount = mulpxRate;
   
   while(sDelayCount != 0)
   {
       delay(1);
      sDelayCount--;   
   } // end while
} // end funcion sdelay

