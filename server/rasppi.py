import serial
import sqlite3
import datetime

if __name__ == '__main__':

    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1) # Mac: /dev/tty.usbmodem14201
    ser.flush()

    def db_connection():
        conn = None
        try:
            conn = sqlite3.connect("microgreens.sqlite")
        except sqlite3.Error as e:
            print(e)
        return conn

    def writeToDB(arduinoData):
        conn = db_connection()
        cursor = conn.cursor()

        new_date = datetime.datetime.now()
        sql = """INSERT INTO grow (date, temp, humidity, light_top, light_bottom)
                    VALUES (?, ?, ?, ?, ?)"""
        cursor = cursor.execute(sql, (new_date, arduinoData[0], arduinoData[1], arduinoData[2], arduinoData[3]))
        conn.commit()
        return f"Grow with the id: 0 created successfully", 201

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip().split(',')
            writeToDB(line)