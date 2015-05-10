
void loop() {
  // scan again the complete board and store the found info in its temporary memory
  update(); 
  
  int changed_plugID = -1;
  
  changed_plugID = hasSocketBeenPressed();
  //either a naked socket has been pressed or a lamp has been plugged in and pressed
  if(changed_plugID >= 0){
    byte row = changed_plugID / 8;
    byte col = changed_plugID % 8;
    // if a lamp has been plugged in but is not yet registered
    if(isSocketPlugged(row, col) && !plugs[row * 8 + col].pluggedIn && !isSocketPressed(row, col)){
      // setup lamp
      plugs[row * 8 + col].pluggedIn = true;
      plugs[row * 8 + col].lampDir = getDirection(row, col);
      // measure lamp id
      plugID_start_MCyc(row, col);
    } else if(isSocketPlugged(row, col) && !plugs[row * 8 + col].pluggedIn && isSocketPressed(row, col)){
      plugs[row * 8 + col].pressed = isSocketPressed(row, col);
      //do nothing else
    } else if(plugs[row * 8 + col].pluggedIn){
      // update lamp (it got pressed)
      plugs[row * 8 + col].pressed = isSocketPressed(row, col);
      // send data
    } else {
      // a nacked socked has been pressed
      plugs[row * 8 + col].pressed = isSocketPressed(row, col);
      // send data
    }
  }

  changed_plugID = hasSocketBeenUnPlugged();
  if(changed_plugID >= 0){
    byte row = changed_plugID / 8;
    byte col = changed_plugID % 8;
    // if a lamp has been plugged in but is not yet registered
    if(plugs[row * 8 + col].pluggedIn){
      // remove lamp
      plugs[row * 8 + col].pluggedIn = false;
      // send data
      LCD_delLamp(row, col);
    }
  }
  
  // Measurement Cycle Loop
  if(plugID_isMCyc_active()){
    if(plugID_poll_MCyc()){
      if(plugID_isWithin_MeanDiff(5)){
        // the measurement was successfull
        plugID_MCycle_done(true);
        Serial.println("ID found");
        switchLamp(plugID_row, plugID_column, 1);
        delay(300);
        switchLamp(plugID_row, plugID_column, 0);
        
        LCD_addLamp(plugID_row, plugID_column);
        // send data of new plug
      }
    } else {
       // no conclusive ID has been found.
       plugID_MCycle_done(false);
       switchLamp(plugID_row, plugID_column, 1);
       delay(200);
       switchLamp(plugID_row, plugID_column, 0);
       delay(200);
       switchLamp(plugID_row, plugID_column, 1);
       delay(200);
       switchLamp(plugID_row, plugID_column, 0);
       
       Serial.println("no ID found");
    }
  }
}

void LCD_addLamp(const byte _row, const byte _column){
  lcd.setCursor(0, 1);
  lcd.print("new");
  lcd.setCursor(4, 1);
  lcd.print(_row);
  lcd.setCursor(6, 1);
  lcd.print(_column);
  lcd.setCursor(8, 1);
  if(plugs[_row * 8 + _column].lampDir > 9){
    lcd.print(plugs[_row * 8 + _column].lampDir); 
  } else {
    lcd.print('0');
    lcd.print(plugs[_row * 8 + _column].lampDir); 
  }   
  lcd.setCursor(11, 1);
  lcd.print(plugs[_row * 8 + _column].plugId);
 }
 
 void LCD_delLamp(const byte _row, const byte _column){
  lcd.setCursor(0, 1);
  lcd.print("del");
  lcd.setCursor(4, 1);
  lcd.print(_row);
  lcd.setCursor(6, 1);
  lcd.print(_column);
  lcd.setCursor(8, 1);
  if(plugs[_row * 8 + _column].lampDir > 9){
    lcd.print(plugs[_row * 8 + _column].lampDir); 
  } else {
    lcd.print('0');
    lcd.print(plugs[_row * 8 + _column].lampDir); 
  }   
  lcd.setCursor(11, 1);
  lcd.print(plugs[_row * 8 + _column].plugId);
 }
