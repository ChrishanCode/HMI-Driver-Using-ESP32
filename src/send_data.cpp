#include <Arduino.h>
#include <lib.h>

void initializeGPRS();
void sendCommand(String cmd);
void setVisibility(String code);
void changePage(int pageNumber);
void updateTextBox(String component, String value);
void fristTimeSetup();
void datapacket();
bool sendATCommandWithResponse(String command, String expectedResponse, int timeout);

void sendTelemetryData()
{
    uint8_t postStatus = 0, count = 0;
    bool postDone = 0;
    datapacket();
    while (1)
    {
        if (count >= 5)
        {
            count = 0;
            simSerial.flush();
            initializeGPRS();
        }
        // datapacket();
        switch (postStatus)
        {
        case 0:
            Serial.println("URL");
            httpOk = sendATCommandWithResponse("AT+HTTPPARA=\"URL\",\"https://industry-app.utech-iiot.lk/api/v1/OljXO1VJ0wbGYXSQpJs/telemetry\"", "OK", 10000);
            if (httpOk)
            {
                postStatus = 1;
                Serial.println("-URL ok-");
            }
            else
            {
                Serial.println("-URL fail-");
                count++;
            }
            break;
        case 1:
            Serial.println("CONTENT");
            contentOk = sendATCommandWithResponse("AT+HTTPPARA=\"CONTENT\",\"application/json\"", "OK", 10000);
            if (contentOk)
            {
                postStatus = 2;
                Serial.println("-CONTENT ok-");
            }
            else
            {
                Serial.println("-CONTENT fail-");
                count++;
            }
            break;
        case 2:
            Serial.println("Data Packet");
            dataPacketOk = sendATCommandWithResponse(httpDataCommand, "DOWNLOAD", 10000);
            if (dataPacketOk)
            {
                postStatus = 3;
                Serial.println("-Data Packet ok-");
            }
            else
            {
                Serial.println("-Data Packet fail-");
                count++;
            }
            break;
        case 3:
            Serial.println("Data Packet Sending");
            dataSendtOk = sendATCommandWithResponse(post_data, "OK", 10000);
            if (dataSendtOk)
            {
                postStatus = 4;
                Serial.println("-Packet Sending ok-");
            }
            else
            {
                Serial.println("-Packet Sending fail-");
                count++;
            }
            break;
        case 4:
            Serial.println("HTTP Action");
            httpActionOk = sendATCommandWithResponse("AT+HTTPACTION=1", "OK", 10000);
            if (httpActionOk)
            {
                Serial.println("-HTTP Action ok-");
                postStatus = 5;
            }
            else
            {
                Serial.println("-HTTP Action fail-");
                count++;
            }
        case 5:
            if (simSerial.available())
            {
                String response = simSerial.readString();
                Serial.println("Response: " + response);
                simSerial.flush();
                postDone = 1; // Successful transmission
            }
            break;
        default:
            postStatus = 0; // Reset the process if needed
            break;
        }
        if (postDone)
        {
            SEND_Active = 0;
            Serial.println("Telemetry data sent successfully!");
            break;
        }
    }
}

void datapacket()
{
    uint16_t len = 0;
    Serial.println("breakReason: " + breakReason);

    len = sprintf((char *)post_data + len, "{\"operatorName\": \"%s\", ", operatorName);
    len += sprintf((char *)post_data + len, "\"operatorName1\": \"%s\", ", operatorName1);
    len += sprintf((char *)post_data + len, "\"operatorID\": \"%s\", ", operatorID);
    len += sprintf((char *)post_data + len, "\"fabricBatchNo\": \"%s\", ", fabricBatchNo);
    len += sprintf((char *)post_data + len, "\"fabricWidth\": \"%s\", ", fabricWidth);
    len += sprintf((char *)post_data + len, "\"fabricBatchWeight\": \"%s\", ", fabricBatchWeight);
    len += sprintf((char *)post_data + len, "\"GSMValue\": \"%s\", ", GSMValue);
    len += sprintf((char *)post_data + len, "\"targetWeight\": \"%s\", ", targetWeight);
    len += sprintf((char *)post_data + len, "\"breakReason\": \"%s\", ", (String)breakReason);
    len += sprintf((char *)post_data + len, "\"errorCode\": \"%s\", ", errorCode);
    len += sprintf((char *)post_data + len, "\"checkBreakDown\": \"%d\", ", checkBreakDown);
    len += sprintf((char *)post_data + len, "\"breakCount\": \"%u\", ", breakCount);
    len += sprintf((char *)post_data + len, "\"oneSecCount1\": \"%u\"", oneSecCount1);
    len += sprintf((char *)post_data + len, "}");

    // len = sprintf((char *)post_data, "{\"operatorName\": \"%s\", \"operatorID\": \"%s\",\"breakReason\": \"%s\",\"oneSecCount1\": \"%u\"}", operatorName, operatorID, breakReason, oneSecCount1);
    // len = sprintf((char *)post_data, "{\"temperature\": \"%d\", \"humidity\": \"%d\", \"pressure\": \"%d\", \"altitude\": \"%d\"}",temperature, humidity, pressure, altitude);
    Serial.println(post_data);
    Serial.print("length:");
    Serial.println(len);
    post_data_size = len;
    sprintf(httpDataCommand, "AT+HTTPDATA=%d,5000", post_data_size);
}