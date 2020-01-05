import serial
import time
from communication import Communication


class Receiving(Communication):
    def __init__(self, device_name, rate, hello_interval = 1):
        Communication.__init__(self, device_name, rate)
        self.last_hello = None
        self.hello_interval = hello_interval #second

    def broadcast(self):
        while True:
            val = self.node.read().decode(encoding='UTF-8')
            print(val, end="")


if __name__ == '__main__':
    node = Receiving("/dev/tty.usbmodem14301", 115200)
    node.broadcast()
    pass

