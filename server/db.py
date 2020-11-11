import sqlite3

conn = sqlite3.connect("microgreens.sqlite")

cursor = conn.cursor()
sql_query = """ CREATE TABLE grow (
    id integer PRIMARY KEY,
    date text NOT NULL,
    temp integer,
    humidity integer,
    light_top integer,
    light_bottom integer
)"""
cursor.execute(sql_query)
