import serial

port = "/dev/ttyACM0"  # put your port here
baudrate = 9600
ser = serial.Serial(port, baudrate)


def tell(msg):
    msg = msg + '\n'
    x = msg.encode('ascii')  # encode n send
    ser.write(x)


def hear():
    msg = ser.read_until()  # read until a new line
