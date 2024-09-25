import serial
import time
from time import sleep
import struct

m1 = 2
m2 = 1
m3 = 2
m4 = 1

packedData = struct.pack('iiiii', m1, m2, m3, m4, -2)
print(packedData)

# Set up the serial connection to the Arduino
ser = serial.Serial('COM6', 9600, timeout=1)  # Open serial port (COM6), baud rate 9600

# Allow some time for the connection to initialize
time.sleep(2)  # Wait for the Arduino to reset
a=0
start = time.time()
while True:
# Write data to the Arduino
    i = input("Enter info: ")
    if (i==''):
        break
    else:
        m1 = int(i[0])
        m2 = int(i[1])
        m3 = int(i[2])
        m4 = int(i[3])
    print(str(m1).encode('utf-8'))
    ser.write(str(m1).encode('utf-8'))
    ser.write(str(m2).encode('utf-8'))
    ser.write(str(m3).encode('utf-8'))
    ser.write(str(m4).encode('utf-8'))
    ser.write(str(9).encode('utf-8'))   # Send the string 'hello' to the Arduino
    # ser.write(packedData)
    res = " "
    while str(res) != "b''":  # Wait for the Arduino to send a response
        res = ser.read()
        print('RES', end=' ')
        while "n" not in str(res) and str(res) != "b''":
            print(res, end=' ')
            res = ser.read()
        print("END")
    sleep(.25)
    if (time.time()-start>19):
        print("RESET")
        ser.close()
        ser = serial.Serial('COM6', 9600, timeout=1)  # Open serial port (COM6), baud rate 9600
        sleep(2)
        start = time.time()
    


# Close the serial port
ser.close()
