# CAN BUS Packet Sniffing
---
CAN-BUS is a ubiquitous industrial BUS commonly used in cars. Because CAN BUS consists only of two wires (CAN-High and CAN-Low), it allows for medium speed communication (up to 1Mbit/sec) and high reliability. In this repository, we'll build a two-node network with one node sending packets and another receiving them. Our goal is to design a reciever that will sniff packets from the CAN BUS and broadcast them to Arduino Serial Monitor. We will use two Arduino Uno boards, <mcp_can.h> library and two modules that include MCP2515 CAN Controller IC and TJA1050 CAN Transceiver IC. Finally, we'll design code for transmitting "The Last Leaf" narrative by O. Henry, and broadcasting it to our Laptop using our "sniffer" node.

General files:  
'sender.ino'  
'receiver.ino'  

Henry files:


Here is how devices should be connected:
![Circuit](https://www.electronicshub.org/wp-content/uploads/2018/08/Arduino-MCP2515-CAN-Bus-Interface-Circuit-Diagram.jpg)

Source: https://www.electronicshub.org/arduino-mcp2515-can-bus-tutorial/
