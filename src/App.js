/* eslint-disable no-unused-expressions */
import React, {useState, useEffect } from 'react';
import { useAlert } from 'react-alert';
import Temperature from './components/Temperature';
import Humidity from './components/Humidity';
import Weather from './components/Weather';
import Article from './components/Article';
import UV from './components/UV';
import { positions } from 'react-alert';
import background from "./components//images/background.jpg";
import './App.css';

function App() {
  var date = new Date();
  var dateStr = date.getFullYear() + "-" + date.getMonth() + "-" + date.getDate() + " " + 
                date.getHours() + ":" + (date.getMinutes()<10?'0':'') + date.getMinutes() + " ";
  const [location, setLocation] = useState([]);
  const [tag, setTag] = useState([]);
  const [temperatures, setTemperatures] = useState([]); //channel 1 field 1
  const [humidities, setHumidities] = useState([]); //channel 1 field 2
  const [knockOne, setKnockOne] = useState([]); //channel 1 field 3
  const [uvs, setUv] = useState([]); //channel 2 field 1
  const [knockTwo, setKnockTwo] = useState([]); //channel 2 field 2
  const [weathers, setWeathers] = useState([]);
  const [articles, setArticles] = useState([]);
  const [timeField, setTimeField] = useState(dateStr + 'EST');
  var alert = useAlert();
  
  useEffect(() => {
    const urls = [
      'http://localhost:4005/api/notes/search?active=true',
      'https://api.thingspeak.com/channels/1292014/feeds.json?api_key=5HX70GFJB36ILGO6&results=10',
      'https://api.thingspeak.com/channels/1323243/feeds.json?api_key=CZCL2QP71YWST6P5&results=10',
      'http://api.openweathermap.org/data/2.5/weather?q='+location+'&appid=d1118046076544b562399e8deaf8653a',
      'https://newsapi.org/v2/everything?q='+tag+'&from='+date.getFullYear()+'-'+date.getMonth()+'-'+date.getDate()+'&sortBy=popularity&pageSize=6&apiKey=7a4826f801d84e739cf7292a7e78f597'
    ];
    Promise.all(urls.map(url =>
      fetch(url)
          .then(checkStatus)
          .then(parseJSON)
          .catch(error => console.log('There was a problem!', error))
  ))
      .then(data => {
        if (data != null)
        setLocation(data[0].location);
        setTag(data[0].newstag);
        setTemperatures(data[1].feeds);
        setHumidities(data[1].feeds);
        setKnockOne(data[1].feeds);
        setUv(data[2].feeds);
        setKnockTwo(data[2].feeds);
        setWeathers(data[3].weather);
        setArticles(data[4].articles)
      })

  }, [timeField]);

  function checkStatus(response) {
    if (response.ok) {
        return Promise.resolve(response);
    } else {
        return Promise.reject(new Error(response.statusText));
    }
  }

  function parseJSON(response) {
    return response.json();
  }

  var temperatureDisplay;
  var humidityDisplay;
  var weatherDisplay;
  var uvDisplay;
  var articleDisplay;
  var knockDisplay = false;
  cleanOutput(temperatures, 1);
  cleanOutput(humidities, 2);
  cleanOutput(uvs, 1);

  for (let index = 0; index < knockTwo.length; index++) {
    if(knockTwo[index].field2 === 1) knockDisplay = true;
  }

  (temperatures != null) ? temperatureDisplay = temperatures.map((temperature, index) => <Temperature key={index} temperature={temperature.field1}/>) : '';
  (humidities != null) ? humidityDisplay = humidities.map((humidity, index) => <Humidity key={index} humidity={humidity.field2}/>) : '';
  (weathers != null) ? weatherDisplay = weathers.map((weather, index) => <Weather key={index} weather={weather.id}/>) : '';
  (uvs != null) ? uvDisplay = uvs.map((uv, index) => <UV key={index} uv={uv.field1}/>) : '';
  (articles != null) ? articleDisplay = articles.map((article, index) => <Article key={index} article={article}/>) : '';

  function cleanOutput(arr, field) {
    var count = 0;
    for (let index = 0; index < arr.length; index++) {
      if (field === 1) {
        if (arr[index].field1 !== null && count === 0) {
          count++;
        }else if (arr[index].field1 !== null && count > 0) {
          arr[index].field1 = null;
        }
      }
      if (field === 2) {
        if (arr[index].field2 !== null && count === 0) {
          count++;
        }else if (arr[index].field2 !== null && count > 0) {
          arr[index].field2 = null;
        }
      }
    }
  }

  const showAlert = () => {alert.error('Oh look, an alert!'), { position: positions.TOP_LEFT }};

  //<div className="App" style="width: 100%; height: 100%;"{{ backgroundImage: `url(${background})`}}>
  return (
    <div className="App">
      <header className="AppHeader">
        <input className="timeInput" onChange={e=> setTimeField(e.target.value)} value={timeField} />
      </header>
      <div className="weathers">
        {weatherDisplay}
      </div>
      <div className="temperatures">
        {temperatureDisplay}
      </div>
      <div className="humidities">
        {humidityDisplay}
      </div>
      <div className="uvs">
        {uvDisplay}
      </div>
      <div className="articles">
        {articleDisplay}
      </div>
      <div className="alerts">
        { (knockDisplay) ? showAlert : '' }
      </div>
    </div>
  );

}
//https://api.thingspeak.com/channels/1292014/field/1.json?api_key=5HX70GFJB36ILGO6
//https://api.thingspeak.com/channels/1292014/feeds.json?api_key=5HX70GFJB36ILGO6
//http://api.openweathermap.org/data/2.5/weather?q=ottawa&appid=588e400beded3a443795235c32b3be8d

export default App;