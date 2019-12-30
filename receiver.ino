// 0.Documentation Section 
// receiver.ino

// Receives messages from CAN bus and broadcasts them to Arduino Serial Moninor
// In the format: time ID B0 B1 B2 B3 B4 B5 B6 B7
// Runs on Arduino UNO 
// Input from MCP2515 CAN Controller, using SPI
// Standard Arduino SPI pins:
// SO - 12
// SI - 11
// SCK - 13
// Otline:
// 1) Create and Initilize an instance of type MCP_CAN with rate 500 KBPS
// 2) If message is being sent to CAN BUS, broadcast it to Arduino Serial Moninor
// Note: we can use MCP_CAN.init_Mask() and MCP_CAN.node.init_Filt() to filter received messages


// Date: December 28, 2019
// Author: anromanof


// 1. Pre-processor Directives Section
#include <mcp_can.h>
#include <SPI.h>


// 2. Declarations Section
//   Global Variables
const int SPI_CS_PIN = 10;          // explicit initialization of CS_PIN for Arduino UNO
MCP_CAN node(SPI_CS_PIN);


// 3. CAN Node Initialization
void setup() {
  
  Serial.begin(115200);             // allow monitoring using Arduino Serial Monitor
  
  while(CAN_OK != node.begin(CAN_500KBPS)){             // function begin(rate) returns CAN_OK if successfull
    Serial.println("CAN bus failed to initialize");
    Serial.println("Retrying...");
    delay(200);
    }
  Serial.println("CAN bus initialized Successfully");
  
  // Filtering all mesages but from 0x7FF (only for 11-bit IDS)
  // Removing these three lines will allow receiving all messages from CAN bus
  node.init_Mask(0, 0, 0x7FF);      
  node.init_Mask(1, 0, 0x7FF);      // We need to initilize both masks to avoid errors related to different values in masks
  node.init_Filt(0, 0, 0x7FF);      
  
  Serial.println("time\tID\tB0\tB1\tB2\tB3\tB4\tB5\tB6\tB7");

}


// 4. Main body: Broadcasting received messages if they are from 0x7FF
void loop() {
  
  unsigned char buf[8];               // buffer for received messages
  unsigned char msg_len;              // length of received messages
  unsigned int rcvID;                 // ID of sender of recieved messages
  unsigned long int rcvTime;          // time of recieving since the Arduino powerup
  
  if (CAN_MSGAVAIL == node.checkReceive()){
    
      // obtaining infromation about receiving 
      rcvTime = millis();
      node.readMsgBuf(&msg_len, buf);
      rcvID = node.getCanId();

      // printing received data along with rcvTime and rcvID to Serial monitor
      Serial.print(rcvTime);
      Serial.print("\t");
      Serial.print("0x");
      Serial.print(rcvID, HEX);
      Serial.print("\t");

      for(int i = 0; i < msg_len; ++i){
        if(buf[i] > 15) {
          Serial.print("0x");
          Serial.print(buf[i], HEX);
          Serial.print("\t");
        } else {
          Serial.print("0x0");
          Serial.print(buf[i], HEX);
          Serial.print("\t");
        }
      }
      Serial.println();
    }
}

