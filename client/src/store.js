import { createContext } from "react";

const d = new Date();

export const initialState = {
  title: "Microgreens",
  date: d.toLocaleString(),
  temp: 0,
  humidity: 0,
  light1: 0,
  light2: 0,
  growTray1Soil1: 0,
  growTray1Soil2: 0,
  growTray2Soil1: 0,
  growTray2Soil2: 0,
};

export const reducer = (state, action) => {
  switch (action.type) {
    case "inc":
      return { ...state };
    default:
      return { ...state };
  }
};

export const Context = createContext();
