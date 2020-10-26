from flask import Flask, request, jsonify
import datetime
import json
import sqlite3

app = Flask(__name__)


def db_connection():
    conn = None
    try:
        conn = sqlite3.connect("microgreens.sqlite")
    except sqlite3.error as e:
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


@app.route("/api/v1/today", methods=["GET"])
def today():
    conn = db_connection()
    cursor = conn.cursor()

    # + str(datetime.date.today()))

    cursor = conn.execute(
        "SELECT * FROM grow WHERE date(datetime(date)) = date('now')"
    today=[
        dict(id=row[0], date=row[1], temp=row[2])
        for row in cursor.fetchall()
    ]
    if today is not None:
        return jsonify(today)
