import React, { useState, useEffect } from "react";

const intervalConstant = 300000;

const ctof = (temp) => {
  return (temp * 9) / 5 + 32;
};

const Current = () => {
  const [microgreenData, setMicrogreenData] = useState([]);

  useEffect(() => {
    setInterval(async () => {
      await fetch("http://192.168.1.19:5000/api/v1/current")
        .then((res) => res.json())
        .then((data) => setMicrogreenData(data))
        .catch((err) => {
          throw new Error(err);
        });
    }, intervalConstant);
  }, []);

  return (
    <table border="1">
      <tr>
        <th>ID</th>
        <th>Date</th>
        <th>Temp</th>
        <th>Humidity</th>
        <th>Light Top Tray</th>
        <th>Light Bottom Tray</th>
      </tr>
      {microgreenData.map((value) => {
        return (
          <tr>
            <td>{value.id}</td>
            <td>{value.date.toLocaleString()}</td>
            <td>{ctof(value.temp)}&#8457;</td>
            <td>{value.humidity}%</td>
            <td>{value.light_top}</td>
            <td>{value.light_bottom}</td>
          </tr>
        );
      })}
    </table>
  );
};

export default Current;
