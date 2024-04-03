#include "config.h"
#include "dspl_1602.h"
#include "iron_tips.h"

// Custom LCD Characters
// Special Characters
// Temperature Degree Character
byte degreeChar[8] = { 0b00100, 0b01010, 0b00100, 0b00000, 0b00000, 0b00000,
    0b00000, 0b00000 };

// Head Character
byte headChar[8] = { 0b00100, 0b01110, 0b11111, 0b00100, 0b00100, 0b00100,
    0b00100, 0b00100 };

// PWM Character
byte pwmChar[8] = { 0b10111, 0b10101, 0b10101, 0b10101, 0b10101, 0b10101,
    0b11101, 0b00000 };

// SET Char
byte setChar[8] = { 0b00100, 0b01010, 0b01010, 0b01010, 0b10001, 0b10001,
    0b01110, 0b00000 };

// TIP Char
byte tipChar[8] = { 0b01110, 0b01010, 0b01010, 0b01010, 0b11011, 0b01110,
    0b00100, 0b00000 };

#ifdef DISPLAY_1602

void DSPL::init(void) {
    LiquidCrystal::begin(16, 2);
    LiquidCrystal::clear();
	LiquidCrystal::createChar(PWM_CHAR, pwmChar);
    LiquidCrystal::createChar(DEGREE_CHAR, degreeChar);
    LiquidCrystal::createChar(SET_CHAR, setChar);
    LiquidCrystal::createChar(TIP_CHAR, tipChar);
    full_second_line = false;
}

void DSPL::tip(const char *tip_name, bool top) {
    uint8_t  y = 1; if (top) y = 0;
    LiquidCrystal::setCursor(8, 0);
    LiquidCrystal::print(tip_name);
    for (uint8_t i = strlen(tip_name); i < 8; ++i)
        LiquidCrystal::print(' ');
}

void DSPL::msgSelectTip(void) {
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("   TIP:"));
}

void DSPL::msgActivateTip(void) {
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("act. tip"));
}

void DSPL::tSet(uint16_t t, bool celsius) {
    char buff[10];
    char units = 'C';
    if (!celsius) units = 'F';
    LiquidCrystal::setCursor(0, 0);
    sprintf(buff, "%c%3d%c%c", ((uint8_t) SET_CHAR), t, ((uint8_t) DEGREE_CHAR), units);
    LiquidCrystal::print(buff);
}

void DSPL::tCurr(uint16_t t, bool celsius) {
  char buff[10];
  char units = 'C';		
  if (!celsius) units = 'F';  
  LiquidCrystal::setCursor(0, 1);
  if (t < 1000) {
    sprintf(buff, "%c%3d%c%c", ((uint8_t) TIP_CHAR), t, ((uint8_t) DEGREE_CHAR), units);									
  } else {
    LiquidCrystal::print(F("xxx"));
    return;
  }
  LiquidCrystal::print(buff);
  if (full_second_line) {
    LiquidCrystal::print(F("            "));
    full_second_line = false;
  }
}


void DSPL::tCurr(uint16_t t) {
    char buff[4];
    LiquidCrystal::setCursor(0, 1);
    if (t < 1000) {
        sprintf(buff, "%3d", t);
    } else {
        LiquidCrystal::print(F("xxx"));
        return;
    }
    LiquidCrystal::print(buff);
    if (full_second_line) {
        LiquidCrystal::print(F("    "));
        full_second_line = false;
    }
}

void DSPL::tCurrTune(uint16_t t, bool celsius) {
  char buff[10];
  char units = 'C';		
  if (!celsius) units = 'F';  
  LiquidCrystal::setCursor(10, 0);
  if (t < 1000) {
    sprintf(buff, "%c%3d%c%c", ((uint8_t) TIP_CHAR), t, ((uint8_t) DEGREE_CHAR), units);									
  } else {
    LiquidCrystal::print(F("xxx"));
    return;
  }
  LiquidCrystal::print(buff);
  if (full_second_line) {
    LiquidCrystal::print(F("            "));
    full_second_line = false;
  }
}

void DSPL::pSet(uint8_t  p) {
    char buff[6];
    sprintf(buff, "P:%3d", p);
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(buff);
}

void DSPL::tRef(uint8_t ref) {
    char buff[11];
    LiquidCrystal::setCursor(0, 0);
    sprintf(buff, "Ref.P. #%1d ", ref+1);
    LiquidCrystal::print(buff);
}

void DSPL::timeToOff(uint8_t  sec) {
    char buff[5];
    sprintf(buff, " %3d", sec);
    LiquidCrystal::setCursor(12, 0);
    LiquidCrystal::print(buff);
	  LiquidCrystal::setCursor(7, 0);
  LiquidCrystal::print(F("AutoOFF"));
}

void DSPL::msgReady(void) {
    LiquidCrystal::setCursor(12, 0);
    LiquidCrystal::print(F("RDY "));
}

void DSPL::msgWorking(void) {
    LiquidCrystal::setCursor(12, 0);
    LiquidCrystal::print(F("WORK"));
}

void DSPL::msgOn(void) {
    LiquidCrystal::setCursor(12, 0);
    LiquidCrystal::print(F("ON  "));
}

void DSPL::msgOff(void) {
    LiquidCrystal::setCursor(12, 0);
    LiquidCrystal::print(F("OFF "));
}

void DSPL::msgStandby(void) {
    LiquidCrystal::setCursor(12, 0);
    LiquidCrystal::print(F("STBY"));
}

void DSPL::msgCold(void) {
    LiquidCrystal::setCursor(2, 1);
    LiquidCrystal::print(F("COLD"));
    full_second_line = true;
}

void DSPL::msgFail(void) {
    LiquidCrystal::setCursor(0, 1);
    LiquidCrystal::print(F("   FAILED  "));
}

void DSPL::msgTune(void) {
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("TUNE"));
}

void DSPL::msgCelsius(void) {
    LiquidCrystal::setCursor(0, 1);
    LiquidCrystal::print(F("Celsius "));
}

void DSPL::msgFarneheit(void) {
    LiquidCrystal::setCursor(0, 1);
    LiquidCrystal::print(F("Fahrenheit      "));
}

void DSPL::msgDefault() {
    LiquidCrystal::setCursor(0, 1);
    LiquidCrystal::print(F(" DEFAULT        "));
}

void DSPL::setupMode(uint8_t mode, bool tune, uint16_t p) {
    char buff[5];
    LiquidCrystal::clear();
    if (!tune) {
        LiquidCrystal::print(F("SETUP"));
        LiquidCrystal::setCursor(1,1);
    }
    switch (mode) {
        case 0:                                 // C/F. In-line editing
            LiquidCrystal::print(F("UNITS"));
            LiquidCrystal::setCursor(7, 1);
            if (p)
                LiquidCrystal::print("C");
            else
                LiquidCrystal::print("F");
            break;
        case 1:                                 // Buzzer
            LiquidCrystal::print(F("BUZZER"));
            if (tune) {
                LiquidCrystal::setCursor(1,1);
                if (p)
                    LiquidCrystal::print(F("ON"));
                else
                    LiquidCrystal::print(F("OFF"));
            }
            break;
        case 2:                                 // Switch type
            LiquidCrystal::print(F("SWITCH TYPE"));
            if (tune) {
                LiquidCrystal::setCursor(1,1);
                if (p)
                    LiquidCrystal::print(F("REED"));
                else
                    LiquidCrystal::print(F("TILT"));
            }
            break;
        case 3:                                 // ambient temperature sensor
            LiquidCrystal::print(F("AMBIENT TEMP"));
            if (tune) {
                LiquidCrystal::setCursor(1,1);
                if (p)
                    LiquidCrystal::print(F("ON"));
                else
                    LiquidCrystal::print(F("OFF"));
            }
            break;
        case 4:                                 // standby temperature
            LiquidCrystal::print(F("ST-BY TEMP"));
            if (tune) {
                LiquidCrystal::setCursor(1,1);
                if (p > 0) {
                    sprintf(buff, "%3d", p);
                    LiquidCrystal::print(buff);
                } else {
                    LiquidCrystal::print(" NO");
                }   
            }
            break;
        case 5:                                 // Standby Time
            LiquidCrystal::print(F("ST-BY TIME"));
            if (tune) {
                LiquidCrystal::setCursor(1,1);
                sprintf(buff, "%3ds", p);
                LiquidCrystal::print(buff);
            }
            break;
        case 6:                                 // off-timeout
            LiquidCrystal::print(F("AutoOFF TIME"));
            if (tune) {
                LiquidCrystal::setCursor(1,1);
                if (p > 0) {
                    sprintf(buff, "%2dm", p);
                    LiquidCrystal::print(buff);
                } else {
                    LiquidCrystal::print(" NO");
                }   
            }
            break;
        case 7:                                 // Tip calibrage
            LiquidCrystal::print(F("TIP CALIBRATION"));
            break;
        case 8:                                 // Activate tip
            LiquidCrystal::print(F("ACTIVATE TIPS"));
            break;
        case 9:                                 // Tune controller
            LiquidCrystal::print(F("TUNE"));
            break;
        case 10:                                // save
            LiquidCrystal::print(F("APPLY"));
            break;
        case 11:                                // cancel
            LiquidCrystal::print(F("CANCEL"));
        default:
            break;
    }
}

void DSPL::percent(uint8_t  Power) {
    char buff[6];
    sprintf(buff, "%c%3d%c",((uint8_t) PWM_CHAR),Power,'%');
    LiquidCrystal::setCursor(11, 1);
    LiquidCrystal::print(buff);
}

void DSPL::markCalibrated(char sym, bool calibrated) {
    char buff[5];
    for (uint8_t  i = 0; i < 4; ++i) buff[i] = ' ';
    if (calibrated) buff[3] = sym;
    buff[4] = '\0';
	//LiquidCrystal::setCursor(0, 1);
	//LiquidCrystal::print (buff);
	LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("   TIP:"));
    LiquidCrystal::setCursor(0, 1);
	if (calibrated) {
    LiquidCrystal::print("  *Calibrated* ");
    }else{
    LiquidCrystal::print(" *Uncalibrated*");
	}
}

void DSPL::markActivated(char sym, bool on) {
    char buff[5];
    for (uint8_t  i = 0; i < 4; ++i) buff[i] = ' ';
    if (on) buff[3] = sym;
    buff[4] = '\0';
	//LiquidCrystal::setCursor(0, 1);
	//LiquidCrystal::print (buff);
	LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("   TIP:"));
    LiquidCrystal::setCursor(0, 1);
	if (on) {
    LiquidCrystal::print("  *Activated* ");
    }else{
    LiquidCrystal::print("  *Deactivated*");
	}
}
#endif
