/*********************************************
  Helper Functions for gathering the Lamp ID
**********************************************/

int getLampValue(const byte _row, const byte _column){
  selectColumn(MSensorCol[_column]);
  // now read the sensor
  return analogRead (MSensorRow[_row]);
}

int selectColumn (const byte _column){
  // select correct MUX channel
//  digitalWrite (MAddressPinA,bitRead(_column, 0));
//  digitalWrite (MAddressPinB,bitRead(_column, 1));
//  digitalWrite (MAddressPinC,bitRead(_column, 2));
  digitalWrite (MAddressPinA, (_column & 1) ? HIGH : LOW);
  digitalWrite (MAddressPinB, (_column & 2) ? HIGH : LOW);
  digitalWrite (MAddressPinC, (_column & 4) ? HIGH : LOW);
}

