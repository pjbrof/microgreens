import { createContext } from "react";

export const initialState = {
  title: "Microgreens",
  microgreenData: {},
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
