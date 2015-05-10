/****************************************************
  Helper Functions for switching the Lights
*****************************************************/

void switchOff(){
  for(int i = 0; i < 8; i++){
    lightRow[i] = 0;
  }
  _write_Light();
}

void switchOffRow(const byte _row){
  lightRow[_row] = 0;
  _write_Light();
}

void switchOn(){
  switchOff();
  for(byte row = 0; row < 8; row++){
    for(byte col = 0; col < 8; col++){
      if(plugs[row * 8 + col].pluggedIn && plugs[row * 8 + col].light){
        _setLamp(row, col, 1);
      }
    }
  }
  _write_Light();
}

void switchOnRow(const byte _row){
  switchOff();
  for(byte col = 0; col < 8; col++){
    if(plugs[_row * 8 + col].pluggedIn && plugs[_row * 8 + col].light){
      _setLamp(_row, col, 1);
    }
  }
  _write_Light();
}

void switchLamp(const byte _row, const byte _column, const byte _switch){
  _setLamp(_row, _column, _switch);
  _write_Light();
}

void _setLamp(const byte _row, const byte _column, const byte _switch){
  unsigned int lamp = 1 << _column;
  if(_switch == 1){
    lightRow[_row] = lightRow[_row] | lamp;
  } else {
    lightRow[_row] = lightRow[_row] & ~lamp;
  }
}

void _write_Light(){
  digitalWrite(OUT_latchPin, LOW);
  
  for(byte row = 0; row < 8; row++){
    shiftOut(OUT_dataPin, OUT_clockPin, MSBFIRST, lightRow[7 - row]);
  }
  
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(OUT_latchPin, HIGH);  
}
