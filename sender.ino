// 0.Documentation Section 
// sender.ino

// Sends a message to the CAN bus
// Runs on Arduino UNO
// Output to MCP2515 CAN Controller, using SPI
// Standard Arduino SPI pins:
// SO - 12
// SI - 11
// SCK - 13
// Outline:
// 1) Create a unique 11-bit sender ID - 0x7FF
// 2) Create an 8-byte message (buf)
// 3) Create and Initialize an instance of type MCP_CAN with rate 500 KBPS
// 4) Send message every 15 ms

// Date: December 28, 2019
// Author: anromanof

// 1. Pre-processor Directives Section
#include <SPI.h>
#include <mcp_can.h>

// 2. Declarations Section
//   Global Variables
const int SPI_CS_PIN = 10;                        // explicit initialization of CS_PIN for Arduino UNO
const int ID = 0x7FF;                             // random ID
unsigned char buf[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  // random message

MCP_CAN node(SPI_CS_PIN);

// 3. CAN Node Initialization
void setup() {

  Serial.begin(115200);                           // allow monitoring using Arduino Serial Monitor

  while(CAN_OK != node.begin(CAN_500KBPS)){              // function begin(rate) returns CAN_OK if successfull
    Serial.println("CAN BUS failed to initialize");
    Serial.println("Retrying...");
    delay(100);
    }

  Serial.println("CAN bus initialized successfuly!");
}


// 4. Main body: Sending message from the Serial port whenever ready
void loop() {
    unsigned long enter_time = millis();
    int len = Serial.readBytes(buf, 8);
    node.sendMsgBuf(ID, 0, len, buf);              // 0 means we use 11-bit ID, 8 - length of the message, buf - message
    delay(15 - (millis() - enter_time)));
}
