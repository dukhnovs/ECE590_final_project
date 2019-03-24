#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>

#include "weather_app.h"

using namespace std::chrono;
using namespace elma;
using namespace weather_app;

int main() {

    Manager m;
    WeatherApp weather_app;
    UserInterface ui(weather_app);

    m.schedule(ui, 10_ms)
     .schedule(weather_app, 10_ms)     
     .init()
     .run();

    endwin();     
     
}