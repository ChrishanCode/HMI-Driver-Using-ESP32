#include <Arduino.h>
#include <lib.h>

void setVisibility(String code);
void changePage(int pageNumber);
void updateTextBox(String component, String value);
void pageController();

bool isReadable(const char *data)
{
    for (int i = 0; data[i] != '\0'; i++)
    {
        if (!isPrintable(data[i]))
        {
            return false;
        }
    }
    return true;
}

void nextionSerialToEsp()
{
    if (nextionSerial.available() > 0)
    {
        Serial.println("***************data coming***********************");

        size_t length = nextionSerial.readBytesUntil('\n', hexValue, sizeof(hexValue) - 1);
        hexValue[length] = '\0';

        Serial.print("Received Hex Value: ");
        Serial.println(hexValue);

        str = String(hexValue);

        // Check if data is clean
        if (!isReadable(hexValue))
        {
            Serial.println("❌ Invalid (non-readable) data received");
            memset(hexValue, 0, sizeof(hexValue));
            str = "";
            state = 0;
            return;
        }

        // Now safe to parse
        if (strstr(hexValue, "login") != NULL)
        {
            state = 1;
            Serial.println("login is done");
        }
        else if (strstr(hexValue, "register1") != NULL)
        {
            state = 2;
            Serial.println("register1 is done");
        }
        else if (strstr(hexValue, "register2") != NULL)
        {
            state = 3;
            Serial.println("register2 is done");
        }
        else if (strstr(hexValue, "Pvalue") != NULL)
        {
            state = 4;
            pageActive = 1;
            Serial.println("New Registration is done");
        }
        else if (strstr(hexValue, "callBreak") != NULL)
        {
            state = 5;
            Serial.println("Breakdown is done");
        }
        else if (strstr(hexValue, "BreakReset") != NULL)
        {
            state = 6;
            Serial.println("Break Reset is done");
        }
        else if (strstr(hexValue, "cancelAll") != NULL)
        {
            state = 7;
            Serial.println("Cancel All is done");
        }
        else if (strstr(hexValue, "register3") != NULL)
        {
            state = 8;
            Serial.println("register3 is done");
        }
        else if (strstr(hexValue, "breakReason") != NULL)
        {
            state = 9;
            Serial.println("break Reason is done");
        }
        else if (strstr(hexValue, "register4") != NULL)
        {
            state = 10;
            Serial.println("register4 is done");
        }

        nextionSerial.flush();
        pageController();
    }
}

void pageController()
{
    int delim1, delim2, delim3;
    switch (state)
    {
    case 1: // login
        Serial.println("state 1");
        delim1 = str.indexOf(";");
        delim2 = str.indexOf(";", delim1 + 1);
        startString = str.substring(0, delim1);
        username = str.substring(delim1 + 1, delim2);
        password = str.substring(delim2 + 1);
        Serial.println("startString: " + startString);
        Serial.println("Username: " + username);
        Serial.println("Password: " + password);
        if (username == "gg" && password == "gg")
        {
            changePage(2);

            state = 0;
        }
        break;
    case 2: // regis 1
        Serial.println("state 2");
        delim1 = str.indexOf(";");
        delim2 = str.indexOf(";", delim1 + 1);
        startString = str.substring(0, delim1);
        operatorName = str.substring(delim1 + 1, delim2);
        operatorID = str.substring(delim2 + 1);
        Serial.println("startString: " + startString);
        Serial.println("operator Name: " + operatorName);
        Serial.println("operator ID: " + operatorID);
        if (operatorName != "" && operatorID != "")
        {
            changePage(3);
            state = 0;
        }
        break;

    case 3: // regis 2
        Serial.println("state 3");
        delim1 = str.indexOf(";");
        delim2 = str.indexOf(";", delim1 + 1);
        startString = str.substring(0, delim1);
        fabricBatchNo = str.substring(delim1 + 1, delim2);
        delim1 = delim2;
        delim2 = str.indexOf(";", delim1 + 1);
        fabricBatchWeight = str.substring(delim1 + 1, delim2);
        delim1 = delim2;
        delim2 = str.indexOf(";", delim1 + 1);
        fabricWidth = str.substring(delim1 + 1, delim2);
        delim1 = delim2;
        delim2 = str.indexOf(";", delim1 + 1);
        GSMValue = str.substring(delim1 + 1, delim2);
        targetWeight = str.substring(delim2 + 1);
        Serial.println("Start String: " + startString);
        Serial.println("Fabric Batch No: " + fabricBatchNo);
        Serial.println("Fabric Batch Weight: " + fabricBatchWeight);
        Serial.println("Fabric Width: " + fabricWidth);
        Serial.println("GSM Value: " + GSMValue);
        Serial.println("Target Weight: " + targetWeight);
        if ((fabricBatchNo != "" && fabricBatchWeight != "") && (targetWeight != "" && fabricWidth != ""))
        {
            changePage(6);
            updateTextBox("t2", operatorName);
            updateTextBox("t3", operatorID);
            updateTextBox("t4", fabricBatchWeight);
            updateTextBox("t5", fabricWidth);
            updateTextBox("t6", fabricBatchNo);
            updateTextBox("t7", GSMValue);
            updateTextBox("t8", targetWeight);
            state = 0;
        }
        break;

    case 4: // save data and send server activation
        Serial.println("state 4");
        delim1 = str.indexOf(";");
        startString = str.substring(0, delim1);
        regiStatus = str.substring(delim1 + 1);
        Serial.println("Start String: " + startString);
        Serial.println("regi Status: " + regiStatus);
        if (startString == "Pvalue" && regiStatus == "OK")
        {
            changePage(5);
            updateTextBox("t2", operatorName);
            updateTextBox("t3", operatorID);
            updateTextBox("t4", fabricBatchWeight);
            updateTextBox("t5", fabricWidth);
            updateTextBox("t6", fabricBatchNo);
            updateTextBox("t7", GSMValue);
            updateTextBox("t8", targetWeight);
            updateTextBox("t9", Breakstatus);
            setVisibility("vis b2,0");
            setVisibility("vis p21,1");
            state = 0;
            pageActive = 1;
            SEND_Active = 1;
            EPPROM_Active = 1;
            Serial.print("EPPROM_Active:");
            Serial.println(EPPROM_Active);
        }
        break;

    case 5: // call the breakdown
        Serial.println("state 5");
        delim1 = str.indexOf(";");
        startString = str.substring(0, delim1);
        breakdown = str.substring(delim1 + 1);
        Serial.println("Start String: " + startString);
        Serial.println("Break down: " + breakdown);
        if (startString == "callBreak" && breakdown == "OK")
        {
            changePage(4);
            //        updateTextBox("t0", operatorName);
            //        updateTextBox("t1", "Enter The Reason");
            setVisibility("vis p21,0"); // red
            setVisibility("vis b2,1");
            state = 0;
        }
        break;

    case 6: // finished the breakdown
        Serial.println("state 6");
        delim1 = str.indexOf(";");
        startString = str.substring(0, delim1);
        breakdownFinish = str.substring(delim1 + 1);
        Serial.println("Start String: " + startString);
        if (startString == "BreakReset" && breakdownFinish == "OK")
        {
            breakCount++;
            changePage(5);
            setVisibility("vis b2,0");
            setVisibility("vis p21,1");
            Breakstatus = "NO";
            updateTextBox("t2", operatorName);
            updateTextBox("t3", operatorID);
            updateTextBox("t9", Breakstatus);
            state = 0;
            breakFlag = 0;
            oneSecCount2 = 0;
            oneSecCount3 = 0;
            SEND_Active = 1;
            EPPROM_Active = 1;
            checkBreakDown = 0;
        }
        break;

    case 7: // cancel any
        Serial.println("state 7");
        delim1 = str.indexOf(";");
        startString = str.substring(0, delim1);
        Serial.println("Start String: " + startString);
        if (startString == "cancelAll")
        {
            changePage(5);
            updateTextBox("t2", operatorName);
            updateTextBox("t3", operatorID);
            //        updateTextBox("t4", fabricBatchWeight);
            //        updateTextBox("t5", fabricWidth);
            //        updateTextBox("t6", fabricBatchNo);
            //        updateTextBox("t7", GSMValue);
            //        updateTextBox("t8", targetWeight);
            //        updateTextBox("t9", Breakstatus);
            setVisibility("vis b2,0");
            setVisibility("vis p21,1");
            SEND_Active = 0;
            EPPROM_Active = 0;
            breakFlag = 0;
            oneSecCount2 = 0;
            EPPROM_Active = 0;
            checkBreakDown = 0;
            state = 0;
        }

    case 8: // register new order
        Serial.println("state 8");
        delim1 = str.indexOf(";");
        delim2 = str.indexOf(";", delim1 + 1);
        startString = str.substring(0, delim1);
        Serial.println("startString: " + startString);
        if (startString == "register3")
        {
            changePage(3);
            state = 0;
        }
        break;

    case 9: // break Reason
        Serial.println("state 9");
        delim1 = str.indexOf(";");
        delim2 = str.indexOf(";", delim1 + 1);
        delim3 = str.indexOf(";", delim2 + 1);
        startString = str.substring(0, delim1);
        errorCode = str.substring(delim1 + 1, delim2);
        operatorName1 = str.substring(delim2 + 1, delim3);
        breakReason = str.substring(delim3 + 1);
        Serial.println("startString: " + startString);
        Serial.println("Error Code: " + errorCode);
        Serial.println("operatorName1: " + operatorName1);
        Serial.println("break Reason: " + breakReason);

        if (startString == "breakReason")
        {
            changePage(5);
            Breakstatus = "YES";
            updateTextBox("t2", operatorName);
            updateTextBox("t3", operatorID);
            updateTextBox("t9", Breakstatus);
            setVisibility("vis b2,1");
            setVisibility("vis p21,0");
            state = 0;
            oneSecCount2 = 0;
            breakFlag = 1;
            SEND_Active = 1;
            EPPROM_Active = 1;
            checkBreakDown = 1;
        }
        break;

    case 10:
        Serial.println("state 10");
        delim1 = str.indexOf(";");
        delim2 = str.indexOf(";", delim1 + 1);
        startString = str.substring(0, delim1);
        operatorName = str.substring(delim1 + 1, delim2);
        operatorID = str.substring(delim2 + 1);
        Serial.println("startString: " + startString);
        Serial.println("operator Name: " + operatorName);
        Serial.println("operator ID: " + operatorID);
        if (operatorName != "" && operatorID != "")
        {
            changePage(6);
            updateTextBox("t2", operatorName);
            updateTextBox("t3", operatorID);
            state = 0;
        }
        break;

    default:
        break;
    }

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
    Serial.println("pageActive:" + (String)pageActive);
}

void fristTimeSetup()
{
    changePage(5);
    if (echeckBreakDown)
    {
        Breakstatus = "YES";
        updateTextBox("t2", operatorName);
        updateTextBox("t3", operatorID);
        updateTextBox("t4", fabricBatchWeight);
        updateTextBox("t5", fabricWidth);
        updateTextBox("t6", fabricBatchNo);
        updateTextBox("t7", GSMValue);
        updateTextBox("t8", targetWeight);
        updateTextBox("t9", Breakstatus);
        setVisibility("vis p21,0"); // red
        setVisibility("vis b2,1");
        state = 0;
        pageActive = 1;
        breakFlag = 1;
        SEND_Active = 1;
        EPPROM_Active = 1;
    }
    else
    {
        updateTextBox("t2", operatorName);
        updateTextBox("t3", operatorID);
        updateTextBox("t4", fabricBatchWeight);
        updateTextBox("t5", fabricWidth);
        updateTextBox("t6", fabricBatchNo);
        updateTextBox("t7", GSMValue);
        updateTextBox("t8", targetWeight);
        updateTextBox("t9", Breakstatus);
        setVisibility("vis b2,0");
        setVisibility("vis p21,1");
        state = 0;
        pageActive = 1;
    }
}
