"""
PC_sender.py

Establishes the connection with a given serial port and then sends text data from
a given text file without formatting. Doesn't crash when connection is lost or
channel is congested (timeouts occur) - continuously tries to reconnect. If the
connection was lost in the middle of submission, sending will continue from the
point where it stopped when connection is reestablished.


Date: January 5, 2020
Author: anromanof
"""

import serial
import time
from communication import Communication


class Submission(Communication):

    def __init__(self, device_name, rate):
        """
        :param device_name: used serial port name
        :param rate: used baud rate
        """
        Communication.__init__(self, device_name, rate)
        self.delay = 1.2/rate  # small delay between sending messages to avoid packet drops

    def msg_gnrtr(self, name):
        """
        :param name: text file name
        :return: yields not-encoded 8-byte message strings from the text file
        """
        with open(name, "r") as input_data:
            while True:
                msg = input_data.read(8)
                if msg == "":
                    break
                yield msg

    def send_message(self, msg):
        """
        Sends given message to Serial.
        :param msg: not-encoded 8-byte message string
        :return: True if the message means EOF, False otherwise.
        """
        if msg is not None:
            try:
                self.node.write(msg.encode(encoding='UTF-8'))
                time.sleep(self.delay)
            except serial.serialutil.SerialTimeoutException:
                self.handle_congestion()
                self.send_message(msg)
            except serial.SerialException:
                self.handle_disconnection()
                self.send_message(msg)
            except:
                print("\n!!!Unexpected error occurred in send_message()!!!\n")
            finally:
                return False
        return True

    def handle_congestion(self):
        """
        Increases the delay between sending messages and waits for 1 second before
        next submission attempt.
        :return: None
        """
        print("\nNetwork is congested! Sending rate is decreased.\n")
        self.delay *= 1.2
        time.sleep(1)

    def send_text(self, file_name):
        """
        :param file_name: name of the text file we wish to send to Serial
        :return: None
        """
        print("Sending...\n")
        msg_generator = self.msg_gnrtr(file_name)
        EOF = False
        while not EOF:
            msg = next(msg_generator, None)
            EOF = self.send_message(msg)
        print(file_name + " was transmitted successfully!")


if __name__ == '__main__':
    node = Submission("/dev/tty.usbmodem14101", 115200)
    file_name = input("What text file would you like to transmit?\n")
    node.send_text(file_name)
    pass
