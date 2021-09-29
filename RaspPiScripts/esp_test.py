#!/usr/bin/python3

import serial
import io
import json

dirpath = "/buoy/data/"

def main():
    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = "/dev/ttyAMA0"
    ser.open()
    ser.write("test")
    data = ser.readline()
    
    j = json.loads(data)
    print("got data\n")
    print(j['data']['data'])
    print(j['cmd'])

    filepath = dirpath + j['data']['data']['buoyId'] + '_' + j['data']['data']['measurementId'] + '.json'

    with open(filepath,"w") as outfile:
        outfile.write(j['data']['data'])

if __name__=="__main__":
    main()
