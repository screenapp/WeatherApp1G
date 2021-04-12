import React from 'react';

function Humidity(props) {
  if (props.humidity != null) {
    return (
      <humidity>
        <h3>Humidity: {Number(props.humidity).toPrecision(2)}%</h3>
      </humidity>
    )
  }
  return null;
}

export default Humidity;