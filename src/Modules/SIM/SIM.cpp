#include <HardwareSerial.h>

HardwareSerial sim800(2);

char phoneNumber[12];

bool SIM_SendCommand(const String& command, String& response, uint32_t timeout = 2000)
{
    // Clear old response
    response = "";

    // Remove any leftover bytes from previous commands
    while (sim800.available())
        sim800.read();

    // Send the AT command
    sim800.println(command);

    // Remember when we started waiting
    uint32_t start = millis();

    // Wait until timeout
    while (millis() - start < timeout)
    {
        // Read incoming bytes
        while (sim800.available())
        {
            response += (char)sim800.read();
        }
    }

    // Return true if SIM800 replied with OK
    return response.indexOf("OK") != -1;
}

bool SIM_ModuleTest()
{
    sim800.begin(9600, SERIAL_8N1, 16, 17);
    delay(1000);

    String response;
    return SIM_SendCommand("AT", response);
}

bool SIM_SIMCardTest()
{
    delay(250);
    String response;

    if (!SIM_SendCommand("AT+CPIN?", response))
        return false;

    return response.indexOf("READY") != -1;
}

bool SIM_NetworkTest(uint32_t timeout = 30000)
{
    uint32_t start = millis();
    String response;

    while (millis() - start < timeout)
    {
        if (SIM_SendCommand("AT+CREG?", response))
        {
            if (response.indexOf(",1") != -1 ||
                response.indexOf(",5") != -1)
            {
                return true;
            }
        }

        delay(500); // Try again in 0.5 second
    }

    return false;
}

int SIM_GetSignalLevel() {

    // Clear old data from serial buffer
    while (sim800.available()) {
        sim800.read();
    }

    sim800.println("AT+CSQ");

    String response = "";
    unsigned long start = millis();

    while (millis() - start < 2000) {
        while (sim800.available()) {
            response += (char)sim800.read();
        }

        if (response.indexOf("OK") != -1) {
            break;
        }
    }

    int csq = -1;

    int pos = response.indexOf("+CSQ:");
    if (pos != -1) {
        csq = response.substring(pos + 6).toInt();
    }

    Serial.print("CSQ = ");
    Serial.println(csq);

    // Error
    if (csq < 0 || csq == 99) {
        return 0;
    }

    // Weak
    if (csq <= 9) {
        return 1;
    }

    // Bad
    if (csq <= 14) {
        return 2;
    }

    // Good
    if (csq <= 24) {
        return 3;
    }

    // Excellent
    return 4;
}

bool waitForResponse(const char *expected, unsigned long timeout)
{
    unsigned long start = millis();
    String response;

    while (millis() - start < timeout)
    {
        while (sim800.available())
        {
            char c = sim800.read();
            response += c;

            if (response.indexOf(expected) != -1)
                return true;

            if (response.indexOf("ERROR") != -1)
                return false;
        }
    }

    return false;
}

bool sendSMS(const char *phoneNumber, const String &message)
{
    // Make sure SIM800 is responding
    sim800.println("AT");
    if (!waitForResponse("OK", 1000))
        return false;

    // SMS text mode
    sim800.println("AT+CMGF=1");
    if (!waitForResponse("OK", 1000))
        return false;

    // Set recipient
    sim800.print("AT+CMGS=\"");
    sim800.print(phoneNumber);
    sim800.println("\"");

    if (!waitForResponse(">", 3000))
        return false;

    // Send message
    sim800.print(message);

    // CTRL+Z
    sim800.write(26);

    // Wait until the modem confirms sending
    if (!waitForResponse("+CMGS:", 15000))
        return false;

    return true;
}

bool MakeCall(const char* number)
{
    sim800.print("ATD");
    sim800.print(number);
    sim800.println(";");

    unsigned long timeout = millis();

    while (millis() - timeout < 5000)
    {
        if (sim800.available())
        {
            String response = sim800.readString();

            Serial.println(response);

            if (response.indexOf("OK") != -1)
                return true;

            if (response.indexOf("ERROR") != -1)
                return false;
        }
    }

    return false;
}