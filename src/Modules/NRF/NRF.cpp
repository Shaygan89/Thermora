#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 4
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

uint8_t msg = 0;

bool initNRF() {
    if (!radio.begin())
        return false;

    radio.stopListening();
    radio.setChannel(76);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);

    radio.openWritingPipe(address);
    radio.stopListening();
    return true;
}

void SendNRF() {

    const int maxRetries = 200; 
    bool sent = false;

    for (int i = 0; i < maxRetries; i++) {
      sent = radio.write(&msg, sizeof(msg));  // returns true if success
      if (sent) {
          //communicateProblem = false;
        Serial.print("Message sent successfully on attempt ");
        Serial.println(i+1);
        break; // stop retrying once sent
      }
      if (i > 198) {
        //communicateProblem = true;
        break;
      }
      delay(18);
    }
}