void setup() {
  // Setup Multiplex Analog IN for LampID
  pinMode (MAddressPinA, OUTPUT); 
  pinMode (MAddressPinB, OUTPUT); 
  pinMode (MAddressPinC, OUTPUT); 

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Sketch V001");

  Serial.begin(9600);
}

