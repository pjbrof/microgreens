import React, { useReducer } from "react";
import { initialState, Context, reducer } from "../store";
import Table from "./Table";

import "../app.scss";

const App = () => {
  const [store, dispatch] = useReducer(reducer, initialState);
  return (
    <>
      <Context.Provider value={{ store, dispatch }}>
        <h1>{store.title}</h1>
        <Table />
      </Context.Provider>
    </>
  );
};

export default App;
