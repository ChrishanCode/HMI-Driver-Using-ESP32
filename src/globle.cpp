#include <Arduino.h>
#include <lib.h>

HardwareSerial nextionSerial(1);
HardwareSerial simSerial(2);

bool netCheck = 0;
bool httpOk = 0;
bool contentOk = 0;
bool dataPacketOk = 0;
bool dataSendtOk = 0;
bool httpActionOk = 0;
bool EPPROM_Active = 0;
bool SEND_Active = 0;
bool breakFlag = 0;

char post_data[1500];
char httpDataCommand[50];
char hexValue[50];
const char delimiter[] = "3B"; // ";"

uint8_t state = 0;
uint8_t pageActive = 0;
uint8_t epageActive = 0;
uint16_t post_data_size = 0;

int checkBreakDown = 0;
int echeckBreakDown = 0;

unsigned long currentTime = 0, previusTime = 0;

String str = "";
String username = "";
String password = "";
String startString = "";
String regiStatus = "";
String Breakstatus = "NO";
String breakdownFinish = "";
String breakdown = "";
String operatorName = "";
String operatorName1 = "";
String operatorID = "";
String fabricBatchNo = "";
String fabricWidth = "";
String fabricBatchWeight = "";
String GSMValue = "";
String targetWeight = "";
String breakReason = "";
String errorCode = "";

uint32_t oneSecCount1 = 0;
uint32_t oneSecCount2 = 0;
uint32_t oneSecCount3 = 0;
uint32_t breakCount = 0;
uint32_t ebreakCount = 0;
uint32_t eoneSecCount1 = 0;

hw_timer_t *OneSec_Timer = NULL;