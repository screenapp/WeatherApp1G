import React from 'react';

function UV(props) {
  if (props.uv != null) {
    return (
      <uv>
        <h3>UV: {Number(props.uv).toPrecision(2)}%</h3>
      </uv>
    )
  }
  return null;
}

export default UV;