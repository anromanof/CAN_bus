import serial
import time


def init(device_name, rate):
    while True:
        try:
            device = serial.Serial(device_name, rate)
            print("Divice " + device_name + " was connected successfully.")
            return device
        except:
            print("Divice " + device_name + " is busy or not connected.")
            print("Retrying...\n")
            time.sleep(5)


def wait_till_free_buf(device):
    while True:
        val = device.read(8)
        if val == "11111111".encode():
            return
        time.sleep(0.1)

def msg_gnrtr(name):
    with open(name, "r") as input_data:
        while True:
            msg = input_data.read(8)
            if msg == "":
                break
            yield str.encode(msg)


if __name__ == '__main__':

    while True:
        device = init("/dev/tty.usbmodem14101", 115200)
        print("\nSending...")

        Error_occurred = False
        for msg in msg_gnrtr("Crime_Punishment.txt"):
            try:
                wait_till_free_buf(device)
                device.write(msg)
            except:
                print("\nError occurred while sending! File will be resent.\n")
                Error_occurred = True
                break


        if Error_occurred:
            continue
        else:
            print("\nFile was sent successfully!")
            break

    pass