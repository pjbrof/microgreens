import React, { useReducer } from "react";
import { initialState, Context, reducer } from "../store";

const App = () => {
  const [store, dispatch] = useReducer(reducer, initialState);
  return (
    <>
      <Context.Provider value={{ store, dispatch }}>
        <h1>{store.title}</h1>
        <p>Date: {store.date}</p>
        <table border="1">
          <tr>
            <th>Temp</th>
            <th>Humidity</th>
            <th>Light 1</th>
            <th>Light 2</th>
            <th>Grow Tray 1 Soil 1</th>
            <th>Grow Tray 1 Soil 2</th>
            <th>Grow Tray 2 Soil 1</th>
            <th>Grow Tray 2 Soil 2</th>
          </tr>
          <tr>
            <td>{store.temp}</td>
            <td>{store.humidity}</td>
            <td>{store.light1}</td>
            <td>{store.light2}</td>
            <td>{store.growTray1Soil1}</td>
            <td>{store.growTray1Soil2}</td>
            <td>{store.growTray2Soil1}</td>
            <td>{store.growTray2Soil2}</td>
          </tr>
        </table>
      </Context.Provider>
    </>
  );
};

export default App;
