#include <iostream>
#include <chrono>
#include <vector>

#include "weather_app.h"

using namespace std::chrono;
using namespace elma;
using namespace weather_app;

WeatherApp& MaxState:: weather_app() { return (WeatherApp&) state_machine(); }

void MaxState::exit(const Event& e) {
    if ( e.name() == "seattle" ) {
        weather_app().set_temp_type("max");
        weather_app().seattle();
        auto temp = weather_app().max_temp();
        weather_app().set_temp(temp);
    } else if ( e.name() == "london" ) {
        weather_app().set_temp_type("max");
        weather_app().london();
        auto temp = weather_app().max_temp();
        weather_app().set_temp(temp);
    } else if (e.name() == "reset") {
        weather_app().reset();
    }
    weather_app().set_responded(true);
}

