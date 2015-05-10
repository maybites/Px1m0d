/*********************************************
  Helper Functions for gathering the Lamp ID
**********************************************/

// checks if a measurement cycle is currently active
boolean lampID_isMCyc_active(){
  return lampID_MCyc_active;
}

/* stops the Measurement cycle. when _store is set to true the current mean value is stored
*/
void lampID_MCycle_done(boolean _store){
  if(_store){
    plugs[lampID_row * 8 + lampID_column].lampId = lampID_get_Mean();
  }
  lampID_MCyc_active = false;
}

/* starts a measurement cycle for the lampID
*/
void lampID_start_MCyc(const byte _row, const byte _column){
  lampID_FirstMCyc_complete = 0;
  lampID_MCyc_active = true;
  lampID_MCyc_index = 0;
  lampID_row = _row;
  lampID_column = _column;
  lampID_lastPollMSec = millis();
}

/* polls for another value during the measurment cycle
    it polls once the specified milliseconds in MSTORE_POLL_DELAY_MSEC have passed.
    This way this method can be called even in higher frequency without to worry.
    
    returns true if it keeps polling, 
            false if the maxiumum measurment cycles have been reached
*/
boolean lampID_poll_MCyc(){
  if(lampID_lastPollMSec + MSTORE_POLL_DELAY_MSEC < millis()){
    lampID_lastPollMSec = millis();
    lampID_MCyc_Store[lampID_MCyc_index] = getLampValue(lampID_row, lampID_column);
    lampID_MCyc_index++;
    if(lampID_MCyc_index ==  MSTORE_SIZE){
      lampID_MCyc_index = 0;
      lampID_FirstMCyc_complete++;
      if(lampID_FirstMCyc_complete >= MSTORE_MAX_CYCLES)
        return false;
    }
  }
  return true;
}

/* returns true once all the collected values are within the specified mean difference
     before this method tests the collected values, it makes first sure it has the
     number of measuremens specified by MSTORE_SIZE.
*/
boolean lampID_isWithin_MeanDiff(int meanDiff){
  boolean returnVal = true;
  
  if(lampID_FirstMCyc_complete > 0){
    long sum = 0;
    for(int i = 0; i < MSTORE_SIZE; i++){
      sum += lampID_MCyc_Store[i];
    }
    int mean = sum / MSTORE_SIZE;
    for(int i = 0; i < MSTORE_SIZE; i++){
      if(returnVal &&
          (lampID_MCyc_Store[i] < mean - meanDiff ||
          lampID_MCyc_Store[i] > mean + meanDiff)){
         returnVal = false;
      }
    }
  } else {
      returnVal = false;
  }
  return returnVal;
}

// returns the mean average of the measurment cycle
int lampID_get_Mean(){
  long sum = 0;
  for(int i = 0; i < MSTORE_SIZE; i++){
    sum += lampID_MCyc_Store[i];
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

