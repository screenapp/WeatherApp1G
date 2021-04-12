import React from 'react';

function Temperature(props) {
  if (props.temperature != null) {
    return (
      <temperature>
        <h3>Temperature: {Number(props.temperature).toPrecision(2)}{'\u00b0'}C</h3>
      </temperature>
    )
  }
  return null;
}

export default Temperature;