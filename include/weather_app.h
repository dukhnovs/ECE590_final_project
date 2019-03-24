#ifndef _ELMA_STOP_WATCH_H
#define _ELMA_STOP_WATCH_H

#include "elma/elma.h" // Note installation directory for elma

#include "min.h"
#include "max.h"
#include "user_interface.h"
#include <vector>
#include <string.h>

namespace weather_app {

    using namespace std::chrono;
    using namespace elma;    

    //! A stop watch class, that inherits from StateMachine
    class WeatherApp : public StateMachine {

        public:
        //! Make a new weather_app
        WeatherApp();

        //! Start the weather_app
        // void begin();

        //! Reset the weather_app to zero and erase laps
        void reset();

        //! Stop the weather_app
        // void stop();
        void seattle();

        //! Add a lap time to the list of lap times.
        // void lap();
        void london();

        //! Get the time stored by the weather_app
        high_resolution_clock::duration value();

        //! Get a list of lap times
        // const vector<high_resolution_clock::duration>& laps() { return _laps; }
        // //! Get a list of temperatures
        // inline vector<double> temp() { return _temp; }
        inline string city() { return _city; }
        inline int mode() { return _mode; }
        inline int temp_type() { return _temp_type; }
        inline bool responded() { return _responded; }

        double max_temp();
        double min_temp();
        double temp_result();
        void set_temp(double temp);
        void get_api_data(string api_string);
        void set_max_min();
        void set_city(string city);
        void set_mode(int mode);
        void set_temp_type(int temp_type);
        void set_responded(bool responded);


        private:
        vector<double> _temp; // vector of all temperatures from the json result of the api call
        double _temp_result; // min or max temp depending on user selection
        double _max; // max temp
        double _min; // min temp

        // When overriding the StateMachine class, put state declarations here.
        MinState min;
        MaxState max;

        // Other private variables
        bool _responded;
        int _mode;
        int _temp_type;
        string _city;
        // high_resolution_clock::time_point _start_time;
        // high_resolution_clock::duration _elapsed;
        // vector<high_resolution_clock::duration> _laps;

    };

}

#endif