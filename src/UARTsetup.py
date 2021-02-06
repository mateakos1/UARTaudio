#Script to set up serial port

import sys
import serial

if len(sys.argv)<3:
    print("Usage:\n\t{} <port> <baudrate>".format(sys.argv[0]))

ser = serial.Serial(port=sys.argv[1],
                    baudrate=int(sys.argv[2]),
                    bytesize=serial.EIGHTBITS,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    timeout=None,
                    xonxoff=False,
                    rtscts=False,
                    dsrdtr=False,
                    write_timeout=None,
                    inter_byte_timeout=None)
ser.close()
