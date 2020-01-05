import serial
import time


class Communication:
    def __init__(self, device_name, rate):
        self.delay = 0.01
        self.rate = rate
        self.name = device_name
        while True:
            try:
                self.node = serial.Serial(device_name, rate, write_timeout=0.5)
                self.node.reset_output_buffer()
                time.sleep(3)
                print("Device " + device_name + " was connected successfully.")
                break
            except serial.SerialException:
                print("Divice " + device_name + " is busy or not connected.")
                print("Retrying...\n")
                time.sleep(5)

    def msg_gnrtr(self, name):
        with open(name, "r") as input_data:
            while True:
                msg = input_data.read(8)
                if msg == "":
                    break
                yield str.encode(msg)

    def send_message(self, msg):
        if msg is not None:
            try:
                self.node.write(msg)
                time.sleep(self.delay)
            except serial.serialutil.SerialTimeoutException:
                self.handle_congestion(msg)
            except serial.SerialException:
                self.handle_disconnection(msg)
            except:
                print("\n!!!Unexpected error occurred!!!\n")
            finally:
                return False
        return True

    def handle_congestion(self, msg):
        print("\nNetwork is congested! Sending rate is decreased.\n")
        self.delay *= 2
        time.sleep(1)
        self.send_message(msg)

    def connect(self):
        while True:
            try:
                self.node = serial.Serial(self.name, self.rate, write_timeout=0.5)
                print("Connection established\n")
                return
            except serial.SerialException:
                print("Retrying...")
                time.sleep(5)
            except:
                print("\n!!!Unexpected error occurred!!!\n")



    def handle_disconnection(self, msg):
        print("\nDevice was disconnected! Please plug it back.\n")
        self.connect()
        self.send_message(msg)

    def send_text(self, file_name):
        print("Sending...\n")
        msg_generator = self.msg_gnrtr(file_name)
        EOF = False
        while not EOF:
            msg = next(msg_generator, None)
            EOF = self.send_message(msg)
        print(file_name + " was transmitted successfully!")


if __name__ == '__main__':
    node = Communication("/dev/tty.usbmodem14101", 115200)
    file_name = input("What text file would you like to transmit?\n")
    node.send_text(file_name)
    pass
