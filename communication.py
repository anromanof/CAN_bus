"""
communication.py

Parent class for receiving and submission. Establishes connection to a given device via Serial.
Doesn't crash if device is disconnected and tries to reconnect. Informs user about the current state.

Date: January 5, 2020
Author: anromanof
"""

import serial
import time


class Communication:
    def __init__(self, device_name, rate):
        """
        Establishes serial connection with a given port.
        :param device_name: name of the port that device is connected
        :param rate: used baud rate
        """
        self.rate = rate
        self.name = device_name
        while True:
            try:
                self.node = serial.Serial(device_name, rate, timeout=1, write_timeout=0.5)
                self.node.reset_output_buffer()
                self.node.reset_input_buffer()
                time.sleep(3)
                print("Device " + device_name + " was connected successfully.")
                break
            except serial.SerialException:
                print("Divice " + device_name + " is busy or not connected.")
                print("Retrying...\n")
                time.sleep(5)

    def handle_disconnection(self):
        """
        Called when disconnection occurred.
        :return: None
        """
        print("\nDevice was disconnected! Please plug it back.\n")
        self.connect()

    def connect(self):
        """
        Runs until the connection is established.
        :return: None
        """
        while True:
            try:
                self.node = serial.Serial(self.name, self.rate, timeout=1, write_timeout=0.5)
                print("Connection established\n")
                return
            except serial.SerialException:
                print("Retrying...")
                time.sleep(5)
            except:
                print("\n!!!Unexpected error occurred in connect()!!!\n")