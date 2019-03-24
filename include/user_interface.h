#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>
#include <string.h>
#include "weather_app.h"


namespace weather_app {

    using namespace std::chrono;
    using namespace elma;
    using namespace weather_app;

    //! A user interface for the a WeatherApp object
    class UserInterface : public Process {

        public:

        //! Create a new weather_app user interface using curses
        //! \param sw A reference to a WeatherApp object
        UserInterface(WeatherApp& sw);

        void init() {}
        void start() {}

        //! Display the time at the given x,y positimin min the screen
        // void show_time(int x, int y, high_resolution_clock::duratimin d);
        void show_best(string best);

        //! Update the user interface by (a) reading keyboard input and (b) writing to the screen
        void update();
        void stop() {}

        private:
        WeatherApp& _weather_app;

    };

}