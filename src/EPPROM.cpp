#include <Arduino.h>
#include <lib.h>

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

void getEPPROM()
{
    operatorName = readOperatorName();
    operatorName1 = readOperatorName1();
    operatorID = readOperatorID();
    fabricBatchNo = readFabricBatchNo();
    fabricWidth = readFabricWidth();
    fabricBatchWeight = readFabricBatchWeight();
    GSMValue = readGSMValue();
    targetWeight = readTargetWeight();
    breakReason = readBreakReason();
    errorCode = readErrorCode();
    EEPROM.get(INT1_ADDR, eoneSecCount1);
    oneSecCount1 = eoneSecCount1;
    EEPROM.get(INT2_ADDR, epageActive);
    pageActive = epageActive;
    EEPROM.get(INT3_ADDR, ebreakCount);
    breakCount = ebreakCount;
    EEPROM.get(INT4_ADDR, echeckBreakDown);
    checkBreakDown = echeckBreakDown;

    Serial.println("****Read EPPROM Data****");
    Serial.println("Operator Name1:" + operatorName);
    Serial.println("Operator Name2:" + operatorName1);
    Serial.println("Operator ID:" + operatorID);
    Serial.println("Fabric Batch No:" + fabricBatchNo);
    Serial.println("Fabric Width:" + fabricWidth);
    Serial.println("Fabric Batch Weight:" + fabricBatchWeight);
    Serial.println("GSM Value:" + GSMValue);
    Serial.println("Target Weight:" + targetWeight);
    Serial.println("Breakdown Reason:" + breakReason);
    Serial.println("Error Code:" + errorCode);
    Serial.println("Breakdown Time:" + (String)oneSecCount1);
    Serial.println("pageActive:" + (String)pageActive);
    Serial.println("Breakdown Count:" + (String)breakCount);
    Serial.println("check BreakDown:" + (String)checkBreakDown);
    Serial.println("************************");
}

void saveOperatorName(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING1_ADDR + i, text[i]);
    }
    EEPROM.write(STRING1_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}

String readOperatorName()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING1_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}

void saveOperatorName1(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING2_ADDR + i, text[i]);
    }
    EEPROM.write(STRING2_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}

String readOperatorName1()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING2_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}

void saveOperatorID(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING3_ADDR + i, text[i]);
    }
    EEPROM.write(STRING3_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}
String readOperatorID()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING3_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}

void saveFabricBatchNo(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING4_ADDR + i, text[i]);
    }
    EEPROM.write(STRING4_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}
String readFabricBatchNo()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING4_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}

void saveFabricWidth(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING5_ADDR + i, text[i]);
    }
    EEPROM.write(STRING5_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}
String readFabricWidth()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING5_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}

void saveFabricBatchWeight(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING6_ADDR + i, text[i]);
    }
    EEPROM.write(STRING6_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}
String readFabricBatchWeight()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING6_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}
void saveGSMValue(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING7_ADDR + i, text[i]);
    }
    EEPROM.write(STRING7_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}
String readGSMValue()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING7_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}
void saveTargetWeight(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING8_ADDR + i, text[i]);
    }
    EEPROM.write(STRING8_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}
String readTargetWeight()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING8_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}
void saveBreakReason(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING9_ADDR + i, text[i]);
    }
    EEPROM.write(STRING9_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}

String readBreakReason()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING9_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}

void saveErrorCode(String text)
{
    int len1 = text.length();
    if (len1 > MAX_STRING_LENGTH)
        len1 = MAX_STRING_LENGTH;

    for (int i = 0; i < len1; i++)
    {
        EEPROM.write(STRING10_ADDR + i, text[i]);
    }
    EEPROM.write(STRING10_ADDR + len1, '\0'); // Null-terminate the string
    EEPROM.commit();
}
String readErrorCode()
{
    char text[MAX_STRING_LENGTH + 1]; // +1 for the null terminator
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        text[i] = EEPROM.read(STRING10_ADDR + i);
        if (text[i] == '\0')
            break; // Stop if null terminator is found
    }
    text[MAX_STRING_LENGTH] = '\0'; // Ensure null termination
    return String(text);
}