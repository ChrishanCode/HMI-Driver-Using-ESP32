#include <Arduino.h>
#include <lib.h>

void initializeGPRS();
void sendCommand(String cmd);
void setVisibility(String code);
void changePage(int pageNumber);
void updateTextBox(String component, String value);
void fristTimeSetup();
void nextionSerialToEsp();
void pageController();
void sendTelemetryData();
void datapacket();
void getEPPROM();
void dataSaveEPPROM(void *parameter);
void simConect(void *parameter);
void hendlenextionSerial(void *parameter);
void saveOperatorName(String text);
void saveOperatorName1(String text);
void saveOperatorID(String text);
void saveFabricBatchNo(String text);
void saveFabricWidth(String text);
void saveFabricBatchWeight(String text);
void saveGSMValue(String text);
void saveTargetWeight(String text);
void saveBreakReason(String text);
void saveErrorCode(String text);

bool sendATCommandWithResponse(String command, String expectedResponse, int timeout);

String readOperatorName();
String readOperatorName1();
String readOperatorID();
String readFabricBatchNo();
String readFabricWidth();
String readFabricBatchWeight();
String readGSMValue();
String readTargetWeight();
String readBreakReason();
String readErrorCode();

void IRAM_ATTR onTimer()
{
  if (breakFlag == 1)
  {
    oneSecCount1++; // breakdown time
    oneSecCount2++; // epprom open time
    oneSecCount3++; // post data time
  }
}

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  nextionSerial.begin(9600, SERIAL_8N1, nextionSerial_RX_PIN, nextionSerial_TX_PIN);
  simSerial.begin(115200, SERIAL_8N1, SIM_RX_PIN, SIM_TX_PIN);

  pinMode(SIM_ON, OUTPUT); // Set SIM_ON as output for powering on the SIM module
  OneSec_Timer = timerBegin(0, 80, true);
  timerAttachInterrupt(OneSec_Timer, &onTimer, true);
  timerAlarmWrite(OneSec_Timer, 1000000, true);
  timerAlarmEnable(OneSec_Timer);
  delay(1000);

  // for (int i = 0; i < 512; i++)
  // {
  //   EEPROM.write(i, 0);
  //   Serial.println("eeprom cleaning");
  // }
  // EEPROM.commit();

  getEPPROM();
  Serial.println("Initializing SIM module...");
  initializeGPRS();

  xTaskCreate(dataSaveEPPROM, "dataSaveEPPROM", 1024 * 12, NULL, 1, NULL);
  xTaskCreate(simConect, "simConect", 1024 * 12, NULL, 2, NULL);
  xTaskCreate(hendlenextionSerial, "nextionSerial1", 1024 * 12, NULL, 3, NULL);

  fristTimeSetup();
  simSerial.flush();
  nextionSerial.flush();
}

void loop()
{
}

void simConect(void *parameter)
{
  while (1)
  {
    if (SEND_Active)
    {
      Serial.println("****POST Data****");
      sendTelemetryData();
    }
    if (oneSecCount3 > 40)
    {
      oneSecCount3 = 0;
      sendTelemetryData();
    }
    Serial.println("Total Break Down Time:" + String(oneSecCount1));
    Serial.println("EPPROM Open Time(100s):" + String(oneSecCount2));
    Serial.println("Posting Time(40s):" + String(oneSecCount3));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void hendlenextionSerial(void *parameter)
{
  while (1)
  {
    // Serial.println("****waitong to user data****");
    nextionSerialToEsp();
    vTaskDelay(800 / portTICK_PERIOD_MS);
  }
}

void dataSaveEPPROM(void *parameter)
{
  while (1)
  {
    if (breakFlag == 1 && oneSecCount2 > 100)
    {
      Serial.println("****Write EPPROM Breakdown Time****");
      oneSecCount2 = 0;
      EEPROM.put(INT1_ADDR, oneSecCount1);
      EEPROM.commit();
      Serial.println("****Write EPPROM data successfully!****");
    }
    if (EPPROM_Active)
    {
      EPPROM_Active = 0;
      Serial.println("****Write EPPROM data****");
      saveOperatorName(operatorName);
      saveOperatorName1(operatorName1);
      saveOperatorID(operatorID);
      saveFabricBatchNo(fabricBatchNo);
      saveFabricWidth(fabricWidth);
      saveFabricBatchWeight(fabricBatchWeight);
      saveGSMValue(GSMValue);
      saveTargetWeight(targetWeight);
      saveBreakReason(breakReason);
      saveErrorCode(errorCode);
      EEPROM.put(INT2_ADDR, pageActive);
      EEPROM.put(INT3_ADDR, breakCount);
      EEPROM.put(INT4_ADDR, checkBreakDown);
      EEPROM.commit();
      Serial.println("****Write EPPROM data successfully!****");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}