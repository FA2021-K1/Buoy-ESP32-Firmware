#!/usr/bin/python3

import serial
import io
import json

filepath = "/buoy/data/measurement.json"

def main():
    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = "/dev/ttyAMA1"
    ser.open()
    ser.write("test")
    data = ser.readline()
    
    j = json.loads(data)
    print("got data\n")
    print(j['data']['data'])
    print(j['cmd'])

    with open(filepath,"w")as outfile:
        outfile.write(j['data']['data'])

if __name__=="__main__":
    main()
