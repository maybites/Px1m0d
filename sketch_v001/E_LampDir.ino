/****************************************************
  Helper Functions for gathering the Lamp Direction
*****************************************************/

//get the condition of the specified socket. 
// returns 1 if a socket is pressed (no matter if a lamp is plugged in)
byte getDirection(const byte _row, const byte _column){
  unsigned int mask = 3 << (_column * 2);
  unsigned int added = directionRow[_row] & mask;
  return direction_BitMapping[added >> (_column * 2)];
}

// this method scans the whole board for the pluggedin / pressed - PlugData
void updateScanDirectionRow(){
  _latch_direction();
  for(int i = 0; i < 8; i++){
    directionRow[i] = _read_directionRow();
  }
}

// This code is intended to trigger the shift register to grab values 
void _latch_direction(){
  // Trigger loading the state of the A-H data lines into the shift register
  digitalWrite(IN2_loadPin, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC); // Requires a delay here according to the datasheet timing diagram
  digitalWrite(IN2_loadPin, HIGH);
  delayMicroseconds(PULSE_WIDTH_USEC);
}

// This code is intended to grab values row by row
unsigned int _read_directionRow(){
  unsigned int the_shifted = 0;  // An 16 bit number to carry each bit value of A-H
  int bitVal;

  for(int i = 0; i < DATA_WIDTH; i++){
    // inverting the read digital value because the shift register is pulled up
    bitVal = 1 - digitalRead(IN2_dataPin);
 
    /* Set the corresponding bit in the_shifted. */     
    the_shifted |= (bitVal << IN2_RegisterBitRow[i]);

    /* Pulse the Clock (rising edge shifts the next bit).*/
    digitalWrite(IN2_clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(IN2_clockPin, LOW);
  }
  
  return the_shifted;
}

