#include <Wire.h>
#include <AD9850.h>

#include "config.h"
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x3F,16,2);  // lub 0x27

#include <LiquidCrystal.h>
              //  RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(20, 19, 18, 17, 16, 15);

void setup () 
{   
  lcd.begin(16,2);

  pinMode(buttonUp, INPUT);    digitalWrite(buttonUp, HIGH);
  pinMode(buttonDwn, INPUT);   digitalWrite(buttonDwn, HIGH);
  pinMode(buttonStep, INPUT);  digitalWrite(buttonStep, HIGH);
  pinMode(buttonBfo, INPUT);   digitalWrite(buttonBfo, HIGH);
  pinMode(buttonMenu, INPUT);  digitalWrite(buttonMenu, HIGH);
  
  pinMode(voltageInput, INPUT);
    
  pinMode(tuneUp, INPUT_PULLUP);
  pinMode(tuneDwn, INPUT_PULLUP);
  
  pinMode(int1, INPUT_PULLUP);

  pinMode(beeper, OUTPUT);
  
  pinMode(txPin, INPUT_PULLUP);
  
 // lcd.init();  
 // lcd.backlight(); 
 // lcd.clear();

  beep(10,30); beep(10,30); beep(10,0);

  VFO.begin(CLK1, FQ1, DATA1, RST1);
  VFO.calibrate(125000000+1200);
  
  BFO.begin(CLK2, FQ2, DATA2, RST2);
  BFO.calibrate(125000000+1200);
  
  setupSignalCharacters();
  interruptsSetup(); 
}

void loop () 
{ 
  BUTTONS_menu_control();
    
  if (menuRefresh == 1) {  
    menuRefresh = 0;
    lcd.clear();
    
    if (menu_id == 0) {
      freqRefresh = 1;
      bfoRefresh = 1;
      stepRefresh = 1;
    }
    
    if (menu_id == 1) {
      bfoRefresh = 1;
      lcd.setCursor(0,1); lcd.print("menu B");
    }
    
    if (menu_id == 2) {
      lcd.setCursor(0,1); lcd.print("menu C");
    }
  };

  if (menu_id == 0) {
    if (freqRefresh == 1) {
      freqRefresh = 0;
      VFO_control();
    }
    if (bfoRefresh == 1) {
      bfoRefresh = 0;
      BFO_control();
    }

    if (refreshSignal == 1) {
      // tutaj S-meter odswiezamy przerwaniem
      refreshSignal = 0;
      SIGNAL_meter();
    }

    BUTTONS_vfo_fast_tune_control();
    BUTTONS_step_control();
    BUTTONS_bfo_control();
    RX_TX_control();
  }

  if (menu_id == 1) {
    if (bfoRefresh == 1) {
      bfoRefresh = 0;
      BFO_control();
    }
  }
  
  if (menu_id == 2) {
    voltage();
  }
} // loop end

int BUTTONS_menu_control (void) 
{
  if (digitalRead(buttonMenu) == LOW) {
    if (buttonMenuLock < 300) buttonMenuLock++;
    if (buttonMenuLock == 300) { // debouncing
      buttonMenuLock = 301;
      menu_id++;
      if (menu_id > 2) {
        menu_id = 0;
      }
      menuRefresh = 1; 
      beep(5,0);
    }
  } else {
    buttonMenuLock = 0;
  }
}

void RX_TX_control()
{
  isTx = digitalRead(txPin) == LOW ? 1 : 0;
  
  if (isTxOld != isTx) {
    
    lcd.setCursor(11,1);
    lcd.print( isTx == 1 ? "T" : " ");
  
    beep(5, 0);
    freqRefresh = 1;
    bfoRefresh = 1;
  }
  
  isTxOld = isTx;  
}

void VFO_control(void)
{ 
  VFO.setfreq(isTx ? BFOfrq[bfo_id] : BFOfrq[bfo_id] - VFOfrq, 0);

  lcd.setCursor(0,0);
  lcd.print( LCD_format_frq( VFOfrq ));
}

void BFO_control(void)
{
  BFO.setfreq(isTx ? BFOfrq[bfo_id] - VFOfrq : BFOfrq[bfo_id], 0);
  VFO.setfreq(isTx ? BFOfrq[bfo_id] : BFOfrq[bfo_id] - VFOfrq, 0);
  
  
  lcd.setCursor(13,1);
  lcd.print(bfo_names[bfo_id]);
  
  if (menu_id == 1) {
    lcd.setCursor(0,0);
    lcd.print( LCD_format_frq( BFOfrq[bfo_id] ));
  }
}

void BUTTONS_vfo_fast_tune_control (void) 
{
  if (digitalRead(buttonUp) == LOW || digitalRead(buttonDwn) == LOW) {
    if (buttonUpLock == 300  /* debouncing */ || buttonUpLock == 3000) { /* press hold */
      VFOfrq = VFOfrq / steps[4] * steps[4];
      VFOfrq += digitalRead(buttonUp) ? steps[4] : (-1 * steps[4]);
      if (buttonUpLock == 3000) buttonUpLock = 2999;
      freqRefresh = 1;
      beep(5,0);
    }
    
    buttonUpLock++;
  } else {
    buttonUpLock = 0;
  }
}

void BUTTONS_step_control (void) 
{
  if (digitalRead(buttonStep) == LOW) {
    if (buttonStepLock < 300) buttonStepLock++;
    if (buttonStepLock == 300) { // debouncing
      buttonStepLock = 301;
      step_id++;
      if (step_id > 3) step_id = 0;
      stepRefresh = 1; 
      beep(5,0);
    }
  } else {
    buttonStepLock = 0;
  }

  if (stepRefresh == 1) {
    stepRefresh = 0;

    lcd.setCursor(11,0);
    lcd.print(step_names[step_id]); 
  }
}

void BUTTONS_bfo_control (void) 
{
  if (digitalRead(buttonBfo) == LOW) {
    if (buttonBfoLock < 300) buttonBfoLock++;
    if (buttonBfoLock == 300) { // debouncing
      buttonBfoLock = 301;
      bfo_id = bfo_id == 1 ? 0 : 1;
      bfoRefresh = 1; 
      beep(5,0);
    }
  } else {
    buttonBfoLock = 0;
  }

  if (bfoRefresh == 1) {
    bfoRefresh = 0;

    BFO_control();
  }
}


void voltage () {
  if (voltageTimer == 0) {
    lcd.setCursor(0,0);
    lcd.print( analogRead(voltageInput) * 5.0 / 1024.0 );
    lcd.setCursor(4,0);
    lcd.print('V');
  }
  voltageTimer++;
  if (voltageTimer == 10000) voltageTimer = 0;
}

void beep(int time, int space) 
{
  digitalWrite(beeper, HIGH);delay(time);
  digitalWrite(beeper, LOW);delay(space);
}


// DO CZEGO TO BYŁO??? JAKIEŚ PRZERWANIE???
 ISR (INT1_vect) //początek funkcji obsługi przerwania
 {
   if (digitalRead(int1) == LOW && int1flag == 0) {
     int1flag = 1;
   } else {
     int1flag = 0;
   }
 } 

/////////////////////////////////////
//  OBSŁUGA PRZERWANIA - ENKODER  ///
/////////////////////////////////////
ISR (INT0_vect) //początek funkcji obsługi przerwania
{  
  if (menu_id == 0) {
    VFOfrq = VFOfrq / steps[step_id] * steps[step_id];
    if (digitalRead(tuneDwn)) {
      VFOfrq -= steps[step_id] ;
    } else { 
      VFOfrq += steps[step_id];
    }
    freqRefresh = 1;
  }
  
 if (menu_id == 1) {
    if (digitalRead(tuneDwn)) {
      BFOfrq[bfo_id] -= 5 ;
    } else { 
      BFOfrq[bfo_id] += 5;
    }
    bfoRefresh = 1;
  }
}

/////////////////////////////////////
//  OBSŁUGA PRZERWANIA - TIMER  ///
/////////////////////////////////////
ISR (TIMER1_COMPA_vect)  // procedura obsługi przerwania od porównania
{   
  refreshSignal = 1;
}

void interruptsSetup()
{
  noInterrupts();        

  // TIMER1_COMPA_vect
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 1500;             // wygeneruj przerwanie gdy timer1 osiągnie...
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK  |= (1 << OCIE1A);  // włącz przerwanie od porównania

  // INT0_vect = przerwania dla impulsatora
  // w resejstrze MCUCR bity ICS01, ICS00 na H (Zbocze narastające na INT0 generuje przerwanie)

  MCUCR |= (1 << ISC01); 
  MCUCR |= (1 << ISC00);
  MCUCR |= (1 << ISC10); 
  MCUCR |= (1 << ISC11); 
  
  GICR  |= (1 << INT0); // włączamy INT0
  GICR  |= (1 << INT1); // włączamy INT1 // niewykorzystane
  interrupts();             
}

String LCD_format_frq(long freq)
{
  String OUT = String();

  int mhz = freq / 1000 / 1000;
  if (mhz < 10) OUT.concat(String(' '));
  OUT.concat(String(mhz, DEC));
  OUT.concat('.');

  int khz = (freq/1000) - (mhz * 1000);
  if (khz < 10) OUT.concat(String('0'));
  if (khz < 100) OUT.concat(String('0'));
  OUT.concat(String(khz, DEC));
  OUT.concat('.');

  int hz = freq - (mhz * 1000000) - (khz * 1000);
  if (hz < 10) OUT.concat(String('0'));
  if (hz < 100) OUT.concat(String('0'));
  OUT.concat(String(hz, DEC));

  return OUT;
}

void SIGNAL_meter () {
    
    int signal = analogRead(signalInput);

    lcd.setCursor(0, 1);  
    
    if (signal > 1000) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(1)); lcd.write(byte(2)); 
      lcd.write(byte(2)); lcd.write(byte(3)); lcd.write(byte(3)); lcd.write(byte(4)); lcd.write(byte(5));
      lcd.print(""); 
      
    } else if (signal > 900) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(1)); lcd.write(byte(2)); 
      lcd.write(byte(2)); lcd.write(byte(3)); lcd.write(byte(3)); lcd.write(byte(4));
      lcd.print(" "); 
      
    } else if (signal > 800) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(1)); lcd.write(byte(2));  
      lcd.write(byte(2)); lcd.write(byte(3)); lcd.write(byte(3));
      lcd.print("  "); 
      
    } else if (signal > 700) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(1)); lcd.write(byte(2)); 
      lcd.write(byte(2)); lcd.write(byte(3));
      lcd.print("   "); 
      
    } else if (signal > 600) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(1)); lcd.write(byte(2)); 
      lcd.write(byte(2));
      lcd.print("    "); 
      
    } else if (signal > 500) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(1)); lcd.write(byte(2)); 
      lcd.print("     "); 
      
    } else if (signal > 400) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); lcd.write(byte(1)); 
      lcd.print("      "); 
      
    } else if (signal > 300) { 
      lcd.write(byte(0)); lcd.write(byte(0)); lcd.write(byte(1)); 
      lcd.print("       "); 
      
    } else if (signal > 200) { 
      lcd.write(byte(0)); lcd.write(byte(0));
      lcd.print("        "); 
      
    } else if (signal > 100) { 
      lcd.write(byte(0)); 
      lcd.print("          "); 
      
    } else {
      lcd.print("           ");
    }              
}

void setupSignalCharacters()
{
  lcd.createChar(0, segmentA);
  lcd.createChar(1, segmentB);
  lcd.createChar(2, segmentC);
  lcd.createChar(3, segmentD);
  lcd.createChar(4, segmentE);
  lcd.createChar(5, segmentF);
}


