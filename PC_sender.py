import serial
import time


def Init(device_name, rate):
    while True:
        try:
            device = serial.Serial(device_name, rate)
            print("Divice " + device_name + " was connected successfully.")
            return device
        except:
            print("Divice " + device_name + " is busy or not connected.")
            print("Retrying...\n")
            time.sleep(5)


def is_buf_free():
    return True


def msg_gnrtr(name):
    with open(name, "r") as input_data:
        while True:
            msg = input_data.read(8)
            if msg == "":
                break
            yield str.encode(msg)



"""while 1:
    val = ser.read(8).decode() #TODO: remove autoreset
    print(val, end = "")
    val = next(r)
    ser.write(val) #TODO: HELLO Message IDEA 0x80 0x80 0x80 0x80 0x80 0x80 0x80 0x80 because no asci character has it"""

if __name__ == '__main__':

    text = msg_gnrtr("Crime_Punishment.txt")
    while True:
        device = Init("/dev/tty.usbmodem14101", 115200)

        EOF = False
        print("\nSending:")

        while not EOF:
            if is_buf_free():
                try:
                    msg = next(text, None)
                    if msg is not None:
                        device.write(msg)
                        time.sleep(0.05)
                        print(msg.decode(), end= '')
                    else:
                        EOF = True
                        print()
                        print("File was sent successfully!")
                except:
                    print()
                    print("Error occurred while sending! Check the connection.")
                    break
        if EOF:
            break


    """for msg in msg_gnrtr("Crime_Punishment.txt"):
        out = ser.read(8).decode()
        print(out, end="")
        ser.write(msg)
        time.sleep(0.01)"""

    pass