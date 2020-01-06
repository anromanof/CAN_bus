# CAN BUS Packet Sniffing
---
CAN-BUS is a ubiquitous industrial BUS commonly used in cars. Because CAN BUS consists only of two wires (CAN-High and CAN-Low), it allows for medium speed communication (up to 1Mbit/sec) and high reliability. In this repository, we'll build a two-node network with one node sending packets and another one receiving them. Our goal is to design a reciever that will sniff packets from the CAN BUS and broadcast them to Arduino Serial Monitor. We will use two Arduino Uno boards, <mcp_can.h> library and two modules that include MCP2515 CAN Controller IC and TJA1050 CAN Transceiver IC. Finally, we'll design code for transmitting a part of "Crime and Punishment" novel by Fyodor Dostoevsky, and broadcasting it to our Laptop using our "sniffer" node.


General files:  
'sender.ino'  
'receiver.ino'  


Dostoevsky data flow chart: Crime_Punishment.txt -> PC_sender -> serial_port -> arduino_transmitter -> CAN_BUS -> arduino_receiver -> serial_port -> PC_receiver

Dostoevsky files:
communication.py  
PC_receiver.py  
PC_sender.py  
novel_receiver.ino  
novel_sender.ino  

Here is how devices should be connected:
![Circuit](https://www.electronicshub.org/wp-content/uploads/2018/08/Arduino-MCP2515-CAN-Bus-Interface-Circuit-Diagram.jpg)

Source: https://www.electronicshub.org/arduino-mcp2515-can-bus-tutorial/
