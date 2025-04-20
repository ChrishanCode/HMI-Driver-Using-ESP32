#include <HardwareSerial.h>
#include <freertos/FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

extern HardwareSerial nextionSerial; // Create a one serial for nextionSerial communication
extern HardwareSerial simSerial;     // Create a second serial for SIM module communication

#define EEPROM_SIZE 512
#define nextionSerial_RX_PIN 14
#define nextionSerial_TX_PIN 13

#define SIM_RX_PIN 16
#define SIM_TX_PIN 17
#define SIM_ON 32 // Define the pin connected to SIM module's power-on pin

#define MAX_STRING_LENGTH 25
#define STRING1_ADDR 0
#define STRING9_ADDR 25
#define STRING3_ADDR 50
#define STRING4_ADDR 75
#define STRING5_ADDR 100
#define STRING6_ADDR 125
#define STRING7_ADDR 150
#define STRING8_ADDR 175
#define STRING2_ADDR 200
#define STRING10_ADDR 225
#define INT1_ADDR 250
#define INT2_ADDR 275
#define INT3_ADDR 300
#define INT4_ADDR 325

extern bool netCheck;
extern bool httpOk;
extern bool contentOk;
extern bool dataPacketOk;
extern bool dataSendtOk;
extern bool httpActionOk;
extern bool EPPROM_Active;
extern bool SEND_Active;
extern bool breakFlag;

extern char post_data[1500];
extern char httpDataCommand[50];
extern char hexValue[50];
extern const char delimiter[]; // ";"

extern uint8_t state;
extern uint8_t pageActive;
extern uint8_t epageActive;
extern uint16_t post_data_size;

extern int checkBreakDown;
extern int echeckBreakDown;

extern unsigned long currentTime, previusTime;

extern String str;
extern String username;
extern String password;
extern String startString;
extern String regiStatus;
extern String Breakstatus;
extern String breakdownFinish;
extern String breakdown;

extern String operatorName;
extern String operatorName1;
extern String operatorID;
extern String fabricBatchNo;
extern String fabricWidth;
extern String fabricBatchWeight;
extern String GSMValue;
extern String targetWeight;
extern String breakReason;
extern String errorCode;

extern uint32_t oneSecCount1;
extern uint32_t oneSecCount2;
extern uint32_t oneSecCount3;
extern uint32_t breakCount;
extern uint32_t ebreakCount;
extern uint32_t eoneSecCount1;

// Declare a pointer to hw_timer_t
extern hw_timer_t *OneSec_Timer;