import sqlite3

conn = sqlite3.connect("microgreens.sqlite")

cursor = conn.cursor()
sql_query = """ CREATE TABLE grow (
    id integer PRIMARY KEY,
    date text NOT NULL,
    temp integer,
    humidity integer,
    light_top integer,
    light_bottom integer,
    soil_topleft integer,
    soil_topright integer,
    soil_bottomleft integer,
    soil_bottomright integer
)"""
cursor.execute(sql_query)
