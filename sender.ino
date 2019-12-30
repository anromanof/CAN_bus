// 0.Documentation Section 
// sender.ino

// Runs on Arduino UNO 
// Output to MCP2515 CAN Controller, using SPI
// Standard Arduino SPI pins:
// SO - 12
// SI - 11
// SCK - 13
// Otline:
// 1) Create a unique 11-bit sender ID - 0x7FF
// 2) Create an 8-byte message (buf)
// 2) Create and Initilize an instance of type MCP_CAN with rate 500 KBPS
// 3) Send message every 15 ms

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

// 4. Main body: Sending message every 15 ms
void loop() {
  node.sendMsgBuf(ID, 0, 8, buf);              // 0 means we use 11-bit ID, 8 - length of the message, buf - message
  delay(15); 
}

