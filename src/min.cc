#include <iostream>
#include <chrono>
#include <vector>

#include "weather_app.h"

using namespace std::chrono;
using namespace elma;
using namespace weather_app;

WeatherApp&MinState:: weather_app() { return (WeatherApp&) state_machine(); }

void MinState::exit(const Event& e) {
    if ( e.name() == "seattle" ) {
        weather_app().seattle();
        auto temp = weather_app().min_temp();
        weather_app().set_temp(temp);
        weather_app().set_temp_type(1);
    } else if ( e.name() == "london" ) {
        weather_app().london();
        auto temp = weather_app().min_temp();
        weather_app().set_temp(temp);
        weather_app().set_temp_type(1);
    } else if (e.name() == "reset") {
        weather_app().reset();
    }
}
