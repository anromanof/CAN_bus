// 0.Documentation Section
// novel_receiver.ino

// Receives text messages from CAN bus and broadcasts them to Serial if PC is ready to receive them.
// PC_Receiver sends hello-messages "H" to Serial every second to let Arduino know that it is ready to
// receive information. Arduino only sends data after it received the first hello-message.
// If Arduino doesn't hear from PC for more than 4 hello-intervals, it decides that PC lost
// the connection and stops sending until the next hello-message.
// Runs on Arduino UNO
// Input from MCP2515 CAN Controller, using SPI
// Output to Serial if receiver is ready
// Standard Arduino SPI pins:
// SO - 12
// SI - 11
// SCK - 13
// Outline:
// 1) Create and Initialize an instance of type MCP_CAN with rate 500 KBPS
// 2) If message is being sent to CAN BUS and PC is ready to receive it, broadcast it to Serial
// Note: we can use MCP_CAN.init_Mask() and MCP_CAN.node.init_Filt() to filter received messages


// Date: January 5, 2020
// Author: anromanof


// 1. Pre-processor Directives Section
#include <mcp_can.h>
#include <SPI.h>


// 2. Declarations Section
//   Global Variables

const int SPI_CS_PIN = 10;          // explicit initialization of CS_PIN for Arduino UNO
const int hello_interval = 1000;    // interval between messages in msecs used in HELLO protocol

// HELLO-protocol fucntions
void run_hello(unsigned long * last_hello, int hello_interval);     // runs HELLO-protocol
void update_hello(unsigned long * last_hello);              // reads data from serial and updates last_hello
void establish_connection(unsigned long * last_hello);      // used to reestablish connection


MCP_CAN node(SPI_CS_PIN);


// 3. CAN Node Initialization
void setup() {

  Serial.begin(115200);             // allow monitoring using Arduino Serial Monitor

  while(CAN_OK != node.begin(CAN_500KBPS)){             // function begin(rate) returns CAN_OK if successful
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

}


// 4. Main body: Broadcasting received messages to PC if they are from 0x7FF and PC is reaady

unsigned char buf[8];               // buffer for received messages
unsigned char msg_len;              // length of received messages
unsigned long last_hello = 0;       // last time hello-message was received in msecs

void loop() {
  if (CAN_MSGAVAIL == node.checkReceive()){
      run_hello(&last_hello, hello_interval);
      node.readMsgBuf(&msg_len, buf);
      Serial.write(buf, msg_len);
    }
}


// 5. Hello-protocol functions

/*********************************************************************************************************
** Function name:           run_hello
** Input:                   last_hello - last time hello-message was received,
**                          hello_interval - expected interval between hello messages in stable system
** Descriptions:            Updates last_hello. If no hello messages have been received for more than 4
**                          hello_intervals, run establish connection.
*********************************************************************************************************/
void run_hello(unsigned long * last_hello, int hello_interval) {
  update_hello(last_hello);
  if ((*last_hello == 0) || (millis() - *last_hello > 4 * hello_interval)){
      establish_connection(last_hello);
  }
}

/*********************************************************************************************************
** Function name:           update_hello
** Input:                   last_hello - last time hello-message was received,
** Descriptions:            Reads a byte from serial input buffer. If it is "H", updates last_hello.
*********************************************************************************************************/
void update_hello(unsigned long * last_hello){
  if (Serial.available()){
    char rcvd = Serial.read();
    if (rcvd == 'H'){
      *last_hello = millis();
    }
  }
}

/*********************************************************************************************************
** Function name:           establish_connection
** Input:                   last_hello - last time hello-message was received,
** Descriptions:            While connection is not established updates last_hello.
*********************************************************************************************************/
void establish_connection(unsigned long * last_hello){
  while ((*last_hello == 0) || (millis() - *last_hello > 4 * hello_interval)){
    update_hello(last_hello);
    delay(100);
  }
}
