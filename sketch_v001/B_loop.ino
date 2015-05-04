void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // lcd.print(millis()/1000);
  
  // measuring all 
  
  for(byte row = 0; row < 8; row++){
    for(byte col = 0; col < 8; col++){
      Serial.print("row : ");
      Serial.print(row);
      Serial.print(" | col : ");
      Serial.print(col);
      Serial.print(" | val : ");
      Serial.println(getLampValue(row, col));
      if(getLampValue(row, col) > 0){
        lcd.setCursor(0, 1);
        lcd.print(row);
        lcd.setCursor(2, 1);
        lcd.print(col);
        lcd.setCursor(4, 1);
        lcd.print(getLampValue(row, col));
      }
    }
  }
}
