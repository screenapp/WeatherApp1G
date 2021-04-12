import React from 'react';
import sun from './images/sun.png';
import few from './images/few.png';
import scattered from './images/scattered.png';
import broken from './images/broken.png';
import shower from './images/shower.png';
import rain from './images/rain.png';
import thunderstorm from './images/thunderstorm.png';
import snow from './images/snow.png';
import mist from './images/mist.png';

function DisplayElement(props) {
    var displayIcon, iconAlt;
    switch(props.weather) {
        case 200: case 201: case 202: case 210: case 211: case 212: case 221: case 230: case 231: case 232:
            displayIcon = thunderstorm;
            iconAlt = 'Thunderstorm';
            break;
        case 300: case 301: case 302: case 310: case 311: case 312: case 313: case 314: case 321:
            displayIcon = shower;
            iconAlt = "Drizzle"
            break;
        case 500: case 501: 
            displayIcon = rain;
            iconAlt = 'Rain';
            break;
        case 502: case 503: case 504:
            displayIcon = rain;
            iconAlt = 'Heavy Rain';
            break;
        case 511:
            displayIcon = snow;
            iconAlt = 'Freezing Rain';
            break;
        case 520: case 521: case 522: case 531:
            displayIcon = shower;
            iconAlt = 'Shower Rain';
            break;
        case 600: case 601: case 612: case 613: case 615: case 616: case 620: case 621:
            displayIcon = snow;
            iconAlt = 'Snow';
            break;
        case 602: case 611: case 622:
            displayIcon = snow;
            iconAlt = 'Heavy Snow';
            break;
        case 701: case 711: case 721: case 731: case 741: case 751: case 761: case 771:
            displayIcon = mist;
            iconAlt = 'Atmospheric'
            break;
        case 762:
            displayIcon = mist;
            iconAlt = 'Volcanic Ash'
            break;
        case 781:
            displayIcon = mist;
            iconAlt = 'Tornado'
            break;
        case 800:
            displayIcon = sun;
            iconAlt = 'Clear Sky'
            break;
        case 801:
            displayIcon = few;
            iconAlt = 'Few Clouds'
            break;
        case 802:
            displayIcon = scattered;
            iconAlt = 'Scattered Clouds'
            break;
        case 803:
            displayIcon = broken;
            iconAlt = 'Broken Clouds'
            break;
        case 804:
            displayIcon = broken;
            iconAlt = 'Overcast'
            break;
        default:
            displayIcon = sun;
            iconAlt = 'Undefined';
    }




    return (
        <weather>
            <h3><img src={displayIcon} className="weatherIcon" alt={iconAlt} width="120"/></h3>
            <h6>{iconAlt}</h6>
        </weather>
    )
}
export default DisplayElement;