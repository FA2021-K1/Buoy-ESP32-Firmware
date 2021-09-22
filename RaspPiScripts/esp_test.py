import serial
import io
import json

def main():
    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = "/dev/ttyAMA1"
    ser.open()

    data = ser.readline()
    
    j = json.loads(data)
    print("got data\n")
    print(j['data']['data'])
    print(j['cmd'])

if __name__=="__main__":
    main()
