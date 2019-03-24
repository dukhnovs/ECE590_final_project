#ifndef _ELMA_STOP_WATCH_ON_H
#define _ELMA_STOP_WATCH_ON_H

#include "weather_app.h"

namespace weather_app {

    using namespace std::chrono;
    using namespace elma;

    class WeatherApp;  // Declare containing class so it can be refered to here
                      // before it is defined in weather_app.h 

    //! The min state of the weather_app
    class MinState : public State {        

        public:
        //! Build a new min state
        MinState() : State("min") {}
        void entry(const Event& e) {}
        void during() {}

        //! Perform actions required when switching from max to on
        //! \param e The event that triggered the transitimin        
        void exit(const Event&);

        WeatherApp& weather_app();        

    };

}

#endif