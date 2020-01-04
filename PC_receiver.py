import serial
import binascii
import codecs

decode_hex = codecs.getdecoder("hex_codec")
ser = serial.Serial("/dev/tty.usbmodem14301", 115200)


while 1:
    val = ser.read(8).decode() #TODO: remove autoreset
    #n = int(val, 2)
    #n.to_bytes((n.bit_length() + 7) // 8, 'big').decode()
    print(val, end="")
