Example Elma Project: Weather_App
===

[Elma](http://klavinslab.org/elma) is an event loop manager designed to teach embedded and reactive systems programming. This repository contains an example Elma project, showing how to use many Elma features, as well as illustrating how to arrange the files and directories in an Elma project.

The source code for this project is available [on github](https://github.com/klavinslab/elma_project).

Installation from Microsoft Visual Code Terminal in Windows 10
---
For Linux and Mac just change $PWD/: to $PWD:

    git clone https://github.com/dukhnovs/ECE590_final_project.git
    cd ECE590_final_project.git
    docker run -v $PWD/:/source -it klavins/elma:latest bash
    make
    make docs


Execution
---
To run the weather_app, type

    bin/weather_app

The weather_app is controlled via the keyboard, via these keys:
- **s**: Select city of Seattle, USA
- **l**: Select city of London, UK
- **r**: Reset
- **q**: Quit

Testing
---
To run tests, do
```bash
bin/test
```

Architecture
---
Design
--
The project is designed using a finite state machine. There are two states: min and max.
State min represents when the user wants to check the lowest temperature in the forecast.
State max represents when the user wants to check the highest temperature in the forecast.

First, the user selects a city (Seattle or London). This is not stored in a state but simply saved 
in the weather_app class as a variable. Second, the user selects a temperature type (min or max).
This causes the transation from the current state to the selected state. 

The selected state is then used to figure out which temperature value to return and display on
the user interface. If the state is min, then the min temperature is displayed. If the state is
max, then the max temperature state is displayed. Both values are stored in the weather_app class
independent of the state but only one is used depending on the state.

Organization
--
The max state is in max.h.

The min state is in min.h.

The weather_app main parts are in weather_app.h. 
This is where the json file with weather data is obtained with an API from openweathermap.org.
This is also where the user selections are stored and all weather data are stored.

The user interface is in user_interface.h. This controls what is displayed on the terminal.

Results
---
Describe the results of testing and running your code. Include visuals when possible.

Acknowledgements
---
Professor Klavins' code was used as the starting base for this project.

References
---
https://github.com/klavinslab/elma_project
https://stackoverflow.com/questions/1153548/minimum-double-value-in-c-c
https://en.cppreference.com/w/cpp/types/numeric_limits/max
http://www.cplusplus.com/reference/vector/vector/clear/
