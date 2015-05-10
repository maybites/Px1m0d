void setup() {
  // Setup Multiplex Analog IN for plugId
  pinMode (MAddressPinA, OUTPUT); 
  pinMode (MAddressPinB, OUTPUT); 
  pinMode (MAddressPinC, OUTPUT); 

  // Setup Shift IN1
  pinMode(IN1_loadPin, OUTPUT);
  pinMode(IN1_clockPin, OUTPUT);
  pinMode(IN1_dataPin, INPUT);

  // Setup Shift IN2
  pinMode(IN2_loadPin, OUTPUT);
  pinMode(IN2_clockPin, OUTPUT);
  pinMode(IN2_dataPin, INPUT);

  // Setup Shift OUT
  pinMode(OUT_latchPin, OUTPUT);
  pinMode(OUT_clockPin, OUTPUT);
  pinMode(OUT_dataPin, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Sketch V001");

  Serial.begin(9600);
  
  scan();
}

void scan() {
  update();
  for(byte row = 0; row < 8; row++){
    for(byte col = 0; col < 8; col++){
      if(isSocketPlugged(row, col)){
        plugs[row * 8 + col].plugId = getLampValue(row, col);
        plugs[row * 8 + col].pluggedIn = true;
        plugs[row * 8 + col].lampDir = getDirection(row, col);

        Serial.print("gotit row: ");
        Serial.print(row);
        Serial.print(" col: ");
        Serial.print(col);
        Serial.print(" dir: ");
        Serial.print(plugs[row * 8 + col].lampDir);
        Serial.print(" val: ");
        Serial.println(plugs[row * 8 + col].plugId);

      }
    }
  }  


/*
          lcd.setCursor(0, 1);
        lcd.print(row);
        lcd.setCursor(2, 1);
        lcd.print(col);
        lcd.setCursor(4, 1);
        lcd.print(getLampValue(row, col));
*/
}

void update(){
  updateScanSocketInfoRow();
  updateScanDirectionRow();
}
