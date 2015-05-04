
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
const byte MSensorCol[8] = {3, 0, 1, 2, 4, 6, 7, 5};

//Pin address for setting the Multiplexer
const byte MAddressPinA = 5;
const byte MAddressPinB = 6;
const byte MAddressPinC = 7;

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


