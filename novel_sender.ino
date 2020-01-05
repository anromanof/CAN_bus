// 0.Documentation Section
// novel_sender.ino

// Sends text messages received from Serial to the CAN bus
// Runs on Arduino UNO
// Output to MCP2515 CAN Controller, using SPI
// Standard Arduino SPI pins:
// SO - 12
// SI - 11
// SCK - 13
// Outline:
// 1) Create a unique 11-bit sender ID - 0x7FF
// 2) Create and Initialize an instance of type MCP_CAN with rate 500 KBPS
// 3) Send any information arrived from Serial to CAN bus in 8 bit messages

// Date: January 5, 2019
// Author: anromanof

// 1. Pre-processor Directives Section
#include <SPI.h>
#include <mcp_can.h>

// 2. Declarations Section
//   Global Variables
const int SPI_CS_PIN = 10;                     // explicit initialization of CS_PIN for Arduino UNO
const int ID = 0x7FF;                          // random ID
unsigned char buf[8];                          // buffer for messages

MCP_CAN node(SPI_CS_PIN);

// 3. CAN Node Initialization
void setup() {

  Serial.begin(115200);                           // initialize Serial

  while(CAN_OK != node.begin(CAN_500KBPS)){              // function node.begin(rate) returns CAN_OK if successfull
    Serial.println("CAN BUS failed to initialize");
    Serial.println("Retrying...");
    delay(100);
    }

  Serial.println("CAN bus initialized successfully!");
}


// 4. Main body: Sending message from the Serial port whenever ready
void loop() {
  if (Serial.available()){                         // If data is coming to Serial, read it and submit to the CAN bus
    int len = Serial.readBytes(buf, 8);
    node.sendMsgBuf(ID, 0, len, buf);              // 0 means we use 11-bit ID, 8 - length of the message, buf - message
  }
}
