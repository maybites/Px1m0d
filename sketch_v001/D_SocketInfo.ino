/****************************************************
  Helper Functions for gathering the Socket Infos
*****************************************************/

/* returns the plugid of a socket if a socket has been pressed. 
*/
int hasSocketBeenPressed(){
  for(byte row = 0; row < 8; row++){
    for(byte col = 0; col < 8; col++){
      if(isSocketPressed(row, col) != plugs[row * 8 + col].pressed){
        return row * 8 + col;
      }
    }
  }
  return -1;
}

/* returns the plugid of a socket if a lamp has been unplugged from the socket. 
*/
int hasSocketBeenUnPlugged(){
  for(byte row = 0; row < 8; row++){
    for(byte col = 0; col < 8; col++){
      if(isSocketPlugged(row, col) == false && plugs[row * 8 + col].pluggedIn == true){
        return row * 8 + col;
      }
    }
  }
  return -1;
}

//get the condition of the specified socket. returns 1 if a lamped is plugged in
boolean isSocketPlugged(const byte _row, const byte _column){
  unsigned int mask = 1 << socket_puggedInBit[_column];
  unsigned int added = socketRow[_row] & mask;
  return (added >> socket_puggedInBit[_column] == 1)? true: false;
}

//get the condition of the specified socket. 
// returns 1 if a socket is pressed (no matter if a lamp is plugged in)
boolean isSocketPressed(const byte _row, const byte _column){
  unsigned int mask = 1 << socket_pressedBit[_column];
  unsigned int added = socketRow[_row] & mask;
  return (added >> socket_pressedBit[_column] == 1)? true: false;
}

// this method scans the whole board for the pluggedin / pressed - PlugData
void updateScanSocketInfoRow(){
  _latch_socket();
  for(int i = 0; i < 8; i++){
    socketRow[i] = _read_SocketRow();
  }
}

// This code is intended to trigger the shift register to grab values 
void _latch_socket(){
  // Trigger loading the state of the A-H data lines into the shift register
  digitalWrite(IN1_loadPin, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC); // Requires a delay here according to the datasheet timing diagram
  digitalWrite(IN1_loadPin, HIGH);
  delayMicroseconds(PULSE_WIDTH_USEC);
}

// This code is intended to grab values row by row
unsigned int _read_SocketRow(){
  unsigned int the_shifted = 0;  // An 16 bit number to carry each bit value of A-H
  int bitVal;

  for(int i = 0; i < DATA_WIDTH; i++){
    // inverting the read digital value because the shift register is pulled up
    bitVal = 1 - digitalRead(IN1_dataPin);
 
    /* Set the corresponding bit in the_shifted. */     
    the_shifted |= (bitVal << IN1_RegisterBitRow[i]);

    /* Pulse the Clock (rising edge shifts the next bit).*/
    digitalWrite(IN1_clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(IN1_clockPin, LOW);
  }
  
  return the_shifted;
}

// buffer must have length >= sizeof(int) + 1
// Write to the buffer backwards so that the binary representation
// is in the correct order i.e.  the LSB is on the far right
// instead of the far left of the printed string
char *int2bin(int a, char *buffer, int buf_size) {
    buffer += (buf_size - 1);

    for (int i = 31; i >= 0; i--) {
        *buffer-- = (a & 1) + '0';

        a >>= 1;
    }

    return buffer;
}

