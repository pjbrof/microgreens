from flask import Flask, request, jsonify
import datetime
import json
import sqlite3
import serial

app = Flask(__name__)

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flush()

def db_connection():
    conn = None
    try:
        conn = sqlite3.connect("microgreens.sqlite")
    except sqlite3.Error as e:
        print(e)
    return conn

@app.route("/api/v1/grow", methods=["GET", "POST"])
def grow():
    conn = db_connection()
    cursor = conn.cursor()

    if request.method == "GET":
        cursor = conn.execute("SELECT * FROM grow")
        grow = [
            dict(id=row[0], date=row[1], temp=row[2])
            for row in cursor.fetchall()
        ]
        if grow is not None:
            return jsonify(grow)

    if request.method == "POST":
        new_date = datetime.datetime.now()
        new_temp = request.form["temp"]
        sql = """INSERT INTO grow (date, temp)
                 VALUES (?, ?)"""
        cursor = cursor.execute(sql, (new_date, new_temp))
        conn.commit()
        return f"Grow with the id: 0 created successfully", 201


# @app.route("/api/v1/today", methods=["GET"])
# def today():
#     conn = db_connection()
#     cursor = conn.cursor()

    # + str(datetime.date.today()))

    # cursor = conn.execute(
    #     "SELECT * FROM grow WHERE date(datetime(date)) = date('now')"
    # today=[
    #     dict(id=row[0], date=row[1], temp=row[2])
    #     for row in cursor.fetchall()
    # ]
    # if today is not None:
    #     return jsonify(today)

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


if __name__ == "__main__":
   app.run(host='0.0.0.0', port=80)