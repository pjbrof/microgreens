import React, { useState, useEffect } from "react";

const Table = () => {
  const [microgreenData, setMicrogreenData] = useState({});

  useEffect(() => {
    const fetchData = async () =>
      await fetch("http://192.168.1.19/api/v1/grow")
        .then((res) => res.json())
        .then((data) => setMicrogreenData(data))
        .catch((err) => {
          throw new Error(err);
        });

    fetchData();
  }, []);

  console.log(microgreenData);

  return (
    <table border="1">
      <tr>
        <th>ID</th>
        <th>Date</th>
        <th>Temp</th>
        <th>Humidity</th>
        <th>Light 1</th>
        <th>Light 2</th>
      </tr>
      {/* {microgreenData.map((value) => {
        return (
          <tr>
            <td>{value.id}</td>
            <td>{value.date.toLocaleString()}</td>
            <td>{value.temp}</td>
            <td>{value.humidity}</td>
            <td>{value.light_top}</td>
            <td>{value.light_bottom}</td>
          </tr>
        );
      })} */}
    </table>
  );
};

export default Table;
