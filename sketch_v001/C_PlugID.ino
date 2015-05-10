/*********************************************
  Helper Functions for gathering the Lamp ID
**********************************************/

// checks if a measurement cycle is currently active
boolean plugID_isMCyc_active(){
  return plugID_MCyc_active;
}

/* stops the Measurement cycle. when _store is set to true the current mean value is stored
*/
void plugID_MCycle_done(boolean _store){
  if(_store){
    plugs[plugID_row * 8 + plugID_column].plugId = plugID_get_Mean();
  }
  plugID_MCyc_active = false;
  // switches on all the lamps of the row
  switchOnRow(plugID_row);
}

/* starts a measurement cycle for the plugId
*/
void plugID_start_MCyc(const byte _row, const byte _column){
  // switches off all the lamps of the row
  switchOffRow(_row);
  plugID_FirstMCyc_complete = 0;
  plugID_MCyc_active = true;
  plugID_MCyc_index = 0;
  plugID_row = _row;
  plugID_column = _column;
  plugID_lastPollMSec = millis();
}

/* polls for another value during the measurment cycle
    it polls once the specified milliseconds in MSTORE_POLL_DELAY_MSEC have passed.
    This way this method can be called even in higher frequency without to worry.
    
    returns true if it keeps polling, 
            false if the maxiumum measurment cycles have been reached
*/
boolean plugID_poll_MCyc(){
  if(plugID_lastPollMSec + MSTORE_POLL_DELAY_MSEC < millis()){
    plugID_lastPollMSec = millis();
    plugID_MCyc_Store[plugID_MCyc_index] = getLampValue(plugID_row, plugID_column);
    plugID_MCyc_index++;
    if(plugID_MCyc_index ==  MSTORE_SIZE){
      plugID_MCyc_index = 0;
      plugID_FirstMCyc_complete++;
      if(plugID_FirstMCyc_complete >= MSTORE_MAX_CYCLES)
        return false;
    }
  }
  return true;
}

/* returns true once all the collected values are within the specified mean difference
     before this method tests the collected values, it makes first sure it has the
     number of measuremens specified by MSTORE_SIZE.
*/
boolean plugID_isWithin_MeanDiff(int meanDiff){
  boolean returnVal = true;
  
  if(plugID_FirstMCyc_complete > 0){
    long sum = 0;
    for(int i = 0; i < MSTORE_SIZE; i++){
      sum += plugID_MCyc_Store[i];
    }
    int mean = sum / MSTORE_SIZE;
    for(int i = 0; i < MSTORE_SIZE; i++){
      if(returnVal &&
          (plugID_MCyc_Store[i] < mean - meanDiff ||
          plugID_MCyc_Store[i] > mean + meanDiff)){
         returnVal = false;
      }
    }
  } else {
      returnVal = false;
  }
  return returnVal;
}

// returns the mean average of the measurment cycle
int plugID_get_Mean(){
  long sum = 0;
  for(int i = 0; i < MSTORE_SIZE; i++){
    sum += plugID_MCyc_Store[i];
  }
  return sum / MSTORE_SIZE;
}

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

