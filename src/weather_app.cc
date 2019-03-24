#include <chrono>
#include <vector>
#include <limits.h>

#include "weather_app.h"

using namespace std;
using namespace std::chrono;
using namespace elma;
using namespace weather_app;

WeatherApp::WeatherApp() : StateMachine("weather_app") {

    _mode = 0;
    _responded = true;
    _temp_type = "min"; // min
    _city = "None";
    // Define state machine initial states and transitions here
    set_initial(min);
    set_propagate(false);
    add_transition("seattle", max, max);
    add_transition("seattle", min, min);
    add_transition("london", max, max);
    add_transition("london", min, min);
    add_transition("reset", max, max);
    add_transition("reset", min, max); 

    add_transition("max_temp", min, max);  
    add_transition("max_temp", max, max);

    add_transition("min_temp", min, min);  
    add_transition("min_temp", max, min);             


    // Make sure we start in the right condition
    reset();
}

void WeatherApp::get_api_data(string api_string) {
    Client c;
    c.get(api_string, [this](json& response) {
    auto res = response;
    _temp.clear();
    // cout << res["list"] << endl;
    for (auto data : res["list"]) {
    //   cout << data["main"]["temp"] << ", " << endl;
        double kelvin = data["main"]["temp"];
        _temp.push_back(9.0 / 5.0 * (kelvin - 273.0) + 32.0 ); // convert kelvin to fahrenheit and add to temperature vector
    //   cout << temp.size() << endl;
    }
    });
    // wait for response
    while(c.num_responses() != 1) {
    }
    _responded = true;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    c.process_responses();
    
}

void WeatherApp::reset() {
    // _elapsed = high_resolution_clock::duration::zero();
    // _laps.clear();
    _max = 0;
    _min = 0;
    _temp_type = "min";
}

// void WeatherApp::stop() {
//     _elapsed += high_resolution_clock::now() - _start_time;
// }
void WeatherApp::seattle() {
     get_api_data("http://api.openweathermap.org/data/2.5/forecast?q=Seattle,usa&APPID=d0fcd7e3aea1a3bc4f2c6095671223e8");
     set_max_min();
}

// void WeatherApp::lap() {
//     _laps.insert(_laps.begin(), value());
// }
void WeatherApp::london() {
     get_api_data("http://api.openweathermap.org/data/2.5/forecast?q=London,uk&APPID=d0fcd7e3aea1a3bc4f2c6095671223e8");
     set_max_min();
}

double WeatherApp::max_temp() {
    return _max;
}

double WeatherApp::min_temp() {
    return _min;
}

double WeatherApp::temp_result() {
    return _temp_result;
}

void WeatherApp::set_temp(double temp) {
    _temp_result = temp;
}

void WeatherApp::set_max_min() {
    double max = std::numeric_limits<double>::min();
    double min = std::numeric_limits<double>::max();
    for (auto temp : _temp) {
        if (temp > max) {
            max = temp;
        }
        if (temp < min) {
            min = temp;
        }
    }
    _max = max;
    _min = min;
}

void WeatherApp::set_city(string city) {
    _city = city;
}

void WeatherApp::set_mode(int mode) {
    _mode = mode;
}

void WeatherApp::set_temp_type(string temp_type) {
    _temp_type = temp_type;
}

void WeatherApp::set_responded(bool responded) {
    _responded = responded;
}

