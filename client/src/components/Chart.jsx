import React, { useContext, useEffect, useRef } from "react";
import * as d3 from "d3";
// import { Context } from "../store";

const Chart = () => {
  // const [store, dispatch] = useContext(Context);
  const chartEl = useRef(null);

  useEffect(() => {
    const margin = { top: 50, right: 50, bottom: 50, left: 50 },
      width = window.innerWidth / 2 - margin.left - margin.right,
      height = window.innerHeight / 2 - margin.top - margin.bottom;

    const n = 21;

    const xScale = d3
      .scaleLinear()
      .domain([0, n - 1])
      .range([0, width]);

    // const dataXrange = d3.extent(dataset, (d) => d.month);
    // const xScale = d3.time.scale().range([0, width]).domain(dataXrange);

    const yScale = d3.scaleLinear().domain([0, 1]).range([height, 0]);

    const line = d3
      .line()
      .x((d, i) => xScale(i))
      .y((d) => yScale(d.y))
      .curve(d3.curveMonotoneX);

    const dataset = d3.range(n).map((d) => {
      return { y: d3.randomUniform(1)() };
    });

    console.log(dataset);

    const svg = d3
      .select(chartEl.current)
      .attr("width", width + margin.left + margin.right)
      .attr("height", height + margin.top + margin.bottom)
      .append("g")
      .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    console.log(chartEl.current);

    svg
      .append("g")
      .attr("class", "x axis")
      .attr("transform", "translate(0," + height + ")")
      .call(d3.axisBottom(xScale));

    svg.append("g").attr("class", "y axis").call(d3.axisLeft(yScale));

    svg.append("path").datum(dataset).attr("class", "line").attr("d", line);

    svg
      .selectAll(".dot")
      .data(dataset)
      .enter()
      .append("circle")
      .attr("class", "dot")
      .attr("cx", (d, i) => xScale(i))
      .attr("cy", (d) => yScale(d.y))
      .attr("r", 5)
      .on("mouseover", (a) => {
        console.log(a);
      })
      .on("mouseout", () => {});

    const focus = svg
      .append("g")
      .attr("class", "focus")
      .style("display", "none");

    focus.append("circle").attr("r", 4.5);

    focus.append("text").attr("x", 9).attr("dy", ".35em");

    svg
      .append("rect")
      .attr("class", "overlay")
      .attr("width", width)
      .attr("height", height)
      .on("mouseover", () => {
        focus.style("display", null);
      })
      .on("mouseout", () => {
        focus.style("display", "none");
      });
  }, [chartEl]);

  return <svg ref={chartEl}></svg>;
};

export default Chart;
