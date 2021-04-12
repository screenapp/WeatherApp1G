import React from 'react';
//import ReactDOM from 'react-dom';
import { render } from 'react-dom';
import { transitions, positions, types, Provider as AlertProvider } from 'react-alert';
import AlertTemplate from 'react-alert-template-basic';
import './index.css';
import App from './App';

/*ReactDOM.render(
  <React.StrictMode>
      <App></App>
  </React.StrictMode>,
  document.getElementById('root')
);*/

const options = {
  position: positions.BOTTOM_CENTER,
  types: types.ERROR,
  timeout: 5000,
  offset: '30px',
  transition: transitions.SCALE
}

const Root = () => (
  <AlertProvider template={AlertTemplate} {...options}>
    <App />
  </AlertProvider>
)

render(<Root />, document.getElementById('root'))