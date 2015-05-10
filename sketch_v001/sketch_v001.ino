/* How many shift register chips are daisy-chained.
*/
#define NUMBER_OF_SHIFT_CHIPS   2

/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5

/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   1

/* Def for LampID */
// defines how many measurements for one cycle are needed
#define MSTORE_SIZE 30
// defines the maximum measurmement cycles 
#define MSTORE_MAX_CYCLES 30
// defines the delay between each measurement
#define MSTORE_POLL_DELAY_MSEC 30

typedef struct
 {
     boolean pluggedIn;
     boolean pressed;
     boolean light;
     byte lampDir;
     int lampId;
 }  plug_type;

/**********************************
  PLUG ARRAY, where the formula is
        plugs[row * 8 + col];
***********************************/
plug_type plugs[64];

/**********************************
  LAMP ID - Analog Input Multiplex
***********************************

  The circuit
  * Address Port MAddressA = D5
  * Address Port MAddressB = D6
  * Address Port MAddressC = D7

  * Analog Port MSensorRow0 = A0 -> Row 0
  * Analog Port MSensorRow1 = A1 -> Row 1
  * Analog Port MSensorRow2 = A2 -> Row 2
  * Analog Port MSensorRow3 = A3 -> Row 3
  * Analog Port MSensorRow4 = A4 -> Row 4
  * Analog Port MSensorRow5 = A5 -> Row 5
  * Analog Port MSensorRow6 = A6 -> Row 6
  * Analog Port MSensorRow7 = A7 -> Row 7

http://www.gammon.com.au/forum/?id=11976
*/

//Array with the Analog Pin Numbers for each Lamp Row.
const byte MSensorRow[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
//Array with the MUX - PinID for a Lamp colum.
const byte MSensorCol[8] = {3, 0, 1, 2, 4, 6, 7, 5};

//Pin address for setting the Multiplexer
const byte MAddressPinA = 5;
const byte MAddressPinB = 6;
const byte MAddressPinC = 7;
 
// storage of the measurement cycle
int lampID_MCyc_Store[MSTORE_SIZE];
// measurement cycle index
int lampID_MCyc_index = 0;
// counter of completed measurement cycles
int lampID_FirstMCyc_complete = 0;
// measurement active flag
boolean lampID_MCyc_active = false;
// lamp row to poll
byte lampID_row;
// lamp column to poll
byte lampID_column;
// last polling time
unsigned long lampID_lastPollMSec;


/**********************************
  Socket - Digital Shift Input 
***********************************/

const byte IN1_clockPin = 18;
const byte IN1_dataPin  = 19;
const byte IN1_loadPin  = 17;

//Mapping Array with the MUX - PinID for a Lamp colum.
const byte IN1_RegisterBitRow[16] = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7};

//Mapping Array to geth the BitId 
const byte socket_pressedBit[8] = {0, 2, 4, 6, 8, 10, 12, 14};
const byte socket_puggedInBit[8] = {1, 3, 5, 7, 9, 11, 13, 15};

// storage for the scanned shift-ins
unsigned int socketRow[8];


/**********************************
  LAMP DIR - Digital Shift Input 
***********************************/

const byte IN2_clockPin = 15;
const byte IN2_dataPin  = 16;
const byte IN2_loadPin  = 14;

//Mapping Array with the MUX - PinID for a Lamp colum.
const byte IN2_RegisterBitRow[16] = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7};

//Mapping Array to swap the two direction bits
// and set values corresponding direction 
// {down, up, right, left}
//const byte direction_BitCorrection[4] = {0, 2, 1, 3};
const byte direction_BitMapping[4] = {6, 12, 3, 9};

// storage for the scanned shift-ins
unsigned int directionRow[8];


/**********************************
  LAMP LIGHT - Digital output 
***********************************/

const byte OUT_ser  = 4;
const byte OUT_sclk = 3;
const byte OUT_rclk = 2;

/*************************
  LiquidCrystal Library
**************************

  The circuit:
 * LCD RS pin to digital pin 39
 * LCD Enable pin to digital pin 41
 * LCD D4 pin to digital pin 43
 * LCD D5 pin to digital pin 45
 * LCD D6 pin to digital pin 47
 * LCD D7 pin to digital pin 49
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(39, 41, 43, 45, 47, 49);


