import React, { useState, useEffect } from "react";
import DataTable from "react-data-table-component";

const intervalConstant = 300000;

const columns = [
  {
    name: "Date",
    selector: "date",
    sortable: true,
  },
  {
    name: "Temperature",
    selector: "temp",
    sortable: true,
  },
  {
    name: "Humidity",
    selector: "humidity",
    sortable: true,
  },
  {
    name: "Light Top Tray",
    selector: "light_top",
    sortable: true,
  },
  {
    name: "Light Bottom Tray",
    selector: "light_bottom",
    sortable: true,
  },
];

const Table = () => {
  const [microgreenData, setMicrogreenData] = useState([]);

  useEffect(() => {
    setInterval(async () => {
      await fetch("http://192.168.1.19:5000/api/v1/grow")
        .then((res) => res.json())
        .then((data) => setMicrogreenData(data))
        .catch((err) => {
          throw new Error(err);
        });
    }, intervalConstant);
  }, []);

  return (
    <div className="dt">
      <DataTable
        columns={columns}
        data={microgreenData}
        highlightOnHover
        striped
        fixedHeader
        pagination
      />
    </div>
  );
};

export default Table;
