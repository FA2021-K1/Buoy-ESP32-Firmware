#!/usr/bin/python3

import serial
import io
import json

dirpath = "/buoy/data/"

def main():

    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = "/dev/ttyUSB0"
    ser.open()

    while True:

        ser.write(bytes('r', 'ascii'))
        print("Waiting for data")
        data = ser.readline().decode('ascii')
        if data[:3] == "XXX":
                j = json.loads(data[3:])
                print("Got data")
                print(data[3:])
                filepath = f"{dirpath}{j['buoyId']}_{j['measurementId']}.json"
                with open(filepath,"w") as outfile:
                        outfile.write(data[3:])
        else:
                print("DEBUG: " + data)

if __name__=="__main__":
    main()
