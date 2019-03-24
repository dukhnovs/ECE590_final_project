#include <chrono>
#include <vector>
#include <limits.h>

#include "stopwatch.h"

using namespace std;
using namespace std::chrono;
using namespace elma;
using namespace stopwatch;

StopWatch::StopWatch() : StateMachine("stopwatch") {

    // Define state machine initial states and transitions here
    set_initial(off);
    set_propagate(false);
    add_transition("start/stop", off, on);
    add_transition("reset", off, off);            
    add_transition("start/stop", on, off);
    add_transition("lap",   on, on);

    // Make sure we start in the right condition
    reset();
}

void StopWatch::get_api_data(string api_string) {
    Client c;
    c.get(api_string, [this](json& response) {
    auto res = response;
    vector<double> temp;
    // cout << res["list"] << endl;
    for (auto data : res["list"]) {
    //   cout << data["main"]["temp"] << ", " << endl;
        temp.push_back(data["main"]["temp"]);
    //   cout << temp.size() << endl;
    }
    _temp = temp;
    // cout<<response.dump(4)<<endl;
    });
    // wait for response
    while(c.num_responses() != 1) {
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    c.process_responses();
}

high_resolution_clock::duration StopWatch::value() {
    if ( current().name() == "on" ) {
        return high_resolution_clock::now() - _start_time + _elapsed;
    } else {
        return _elapsed;
    }
}

void StopWatch::begin() {
    _start_time = high_resolution_clock::now();
}

void StopWatch::reset() {
    _elapsed = high_resolution_clock::duration::zero();
    _laps.clear();
    _max = 0;
}

void StopWatch::stop() {
    _elapsed += high_resolution_clock::now() - _start_time;
}
void StopWatch::seattle() {
     get_api_data("http://api.openweathermap.org/data/2.5/forecast?q=Seattle,usa&APPID=d0fcd7e3aea1a3bc4f2c6095671223e8");
     set_max();
}

void StopWatch::lap() {
    _laps.insert(_laps.begin(), value());
}
void StopWatch::london() {
    _max = std::numeric_limits<double>::min();
     get_api_data("http://api.openweathermap.org/data/2.5/forecast?q=London,uk&APPID=d0fcd7e3aea1a3bc4f2c6095671223e8");
     set_max();
}

double StopWatch::max_temp() {
    // double max = std::numeric_limits<double>::min();
    // for (auto temp : _temp) {
    //     if (temp > max) {
    //         max = temp;
    //     }
    // }
    return _max;
}

void StopWatch::set_max() {
    double max = std::numeric_limits<double>::min();
    for (auto temp : _temp) {
        if (temp > max) {
            max = temp;
        }
    }
    _max = max;
}