// TX
const int txPin = 8;//-- guzik TX
int isTx = 0;
int isTxOld = 0;

// BEEPER
const int beeper = 12;//-- wyjście na głośniczeok
int beeperTimer  = 0;

  // VOLTAGE
int voltageInput = A4; 
int voltageTimer = 0;

// SIGNAL
int signalInput = A5; 
int refreshSignal = 0;

// BUTTONS
const int buttonDwn  = 21;
const int buttonUp   = 22;
const int buttonStep = 23;
const int buttonBfo  = 31;
const int buttonMenu = 30;

int buttonUpLock     = 0;
int buttonStepLock   = 0;
int buttonBfoLock    = 0;
int buttonMenuLock   = 0;

// PINY DDS VFO
const int CLK1  = 1;
const int FQ1   = 0;
const int DATA1 = 2;
const int RST1  = 3; // wygląda ma to ze jest niepodłączony

// PINY DDS BFO
const int CLK2  = 26;
const int FQ2   = 25;
const int DATA2 = 24;
const int RST2  = 27;

int menu_id           = 0;
int menuRefresh       = 1;

// ENCODER
const int tuneUp   = 10;//--
const int tuneDwn  = 9;//--

//INT1 // do czego te zmienne??????
const int int1     = 11;//--
int int1flag = 0;

// VFO STEPS
char step_0[]         = " 10Hz";
char step_1[]         = " 25Hz";
char step_2[]         = " 50Hz";
char step_3[]         = "100Hz";
char step_4[]         = "10kHz"; // FAST
char *step_names[5]   = {step_0, step_1, step_2, step_3, step_4};
int steps[]           = {10, 25, 50, 100, 10000};
int step_id           = 0; // default step
int stepRefresh = 1;

// VFO
long VFOfrq = 3700000;
int freqRefresh = 1;

// BFO
char usb[]         = "USB";
char lsb[]         = "LSB";
char *bfo_names[6] = {usb, lsb};
//long BFOfrq[]        = {9000100, 8999700};
long BFOfrq[]        = {0000000, 0000000};
int bfo_id         = 1;
int bfoRefresh     = 1;


// wygląda ma to ze jest niepodłączony

// CUSTOM CHARACTERS
byte segmentA[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b11111};
byte segmentB[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111};
byte segmentC[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b11111};
byte segmentD[8] = {0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b11111,0b11111};
byte segmentE[8] = {0b00000,0b00000,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
byte segmentF[8] = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};


