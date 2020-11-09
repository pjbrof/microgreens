import serial
import time
 
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flush()
 
while (1):
  send_string = ("My name is Raspberry Pi\n")
  # Send the string. Make sure you encode it before you send it to the Arduino.
  ser.write(send_string.encode('utf-8'))
  # Do nothing for 500 milliseconds (0.5 seconds)
  time.sleep(0.5)
  # Receive data from the Arduino
  receive_string = ser.readline().decode('utf-8').rstrip()
  # Print the data received from Arduino to the terminal
  print(receive_string)