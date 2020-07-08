# digitalwatch

## Components
- WeMos D1 (ESP8266)
- micro 5pin cable
- 92 inch text OLED display
- DHT11

## About this project
Show the digital watch on OLED display which has alarm, stopwatch, timer function.

It also has humidity and temperature on the display.

## How it works
There are four buttons on each corner of the screen.

_**Left-top button**_ is a Mode button which can change mode.

( day-changing mode -> time-changing mode -> alarm mode -> stopwatch mode -> timer mode)

If you choose this buttom, a line will be drawn on the function that is about to change.

_**Left-bottom button**_ is a adjust button which can adjust the setting.

_**Right-top button**_ can raise the time setting.

_**Right-bottom button**_ can set down the time setting.

## Output
![그림1](https://user-images.githubusercontent.com/49015100/86437238-07d1ca00-bd3f-11ea-89cd-75176b914f62.jpg)

# forecast_wemosd1
 
## Components
- WeMos D1 (ESP8266)
- micro 5pin cable
- 92 inch text OLED display

## About this project
Get current weather data for a particular city on Earth from OpenWeatherMap.org.

## How it works
Connect to the openWeatherMap API https://openweathermap.org/.

You have to sign up and create API key to get current weather data.

Data is in JSON, XML, or HTML format. In this project, I use JSON format.

So you should download a libarary called ArduinoJson version 5.

## Output
![시연사진](https://user-images.githubusercontent.com/49015100/86336790-46a64800-bc8b-11ea-8b07-c9013bea8be6.jpg)
