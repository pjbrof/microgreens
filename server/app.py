from flask import Flask, request, jsonify
from flask_cors import CORS
import datetime
import sqlite3

app = Flask(__name__)
CORS(app)

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
            dict(id=row[0], date=row[1], temp=row[2], humidity=row[3], light_top=row[4], light_bottom=row[5])
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


@app.route("/api/v1/current", methods=["GET"])
def current():
    conn = db_connection()
    cursor = conn.cursor()

    if request.method == "GET":
        cursor = conn.execute("SELECT * FROM grow ORDER BY ID DESC LIMIT 1")
        current = [
            dict(id=row[0], date=row[1], temp=row[2], humidity=row[3], light_top=row[4], light_bottom=row[5])
            for row in cursor.fetchall()
        ]
        if current is not None:
            return jsonify(current)


if __name__ == "__main__":
   app.run(host='0.0.0.0', port=5000)