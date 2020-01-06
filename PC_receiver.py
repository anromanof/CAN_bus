"""
PC_receiver.py

Establishes the connection with a given serial port and broadcasts all the data
received from it without formatting. Uses HELLO-protocol and sends hello-messages
by default every second to the master when connection is established.
Doesn't crash when connection is lost - continuously tries to reconnect.

Note: Hello-messages is the only information that PC_receiver sends to serial.

Date: January 5, 2020
Author: anromanof
"""

import serial
import time
from communication import Communication


class Receiving(Communication):
    def __init__(self, device_name, rate, hello_interval=1):
        """
        :param device_name: name of the used serial port
        :param rate: used baud rate
        :param hello_interval: time interval in sec between hello-messages
        """
        Communication.__init__(self, device_name, rate)
        self.last_hello = None
        self.hello_interval = hello_interval # in seconds

    def send_hello(self):
        if ((self.last_hello is None) or
                (time.perf_counter() - self.last_hello > self.hello_interval)):
            self.node.write("H".encode(encoding='UTF-8'))
            self.last_hello = time.perf_counter()

    def broadcast(self):
        while True:
            try:
                self.send_hello()
                val = self.node.read().decode(encoding='UTF-8')
                print(val, end="")
            except serial.SerialException:
                self.handle_disconnection()
            except:
                print("\n!!!Unexpected error occurred in send_message()!!!\n")


if __name__ == '__main__':
    node = Receiving("/dev/tty.usbmodem14301", 115200)
    node.broadcast()
    pass

