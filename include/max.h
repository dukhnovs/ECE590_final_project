#ifndef _ELMA_STOP_WATCH_OFF_H
#define _ELMA_STOP_WATCH_OFF_H

#include "weather_app.h"

namespace weather_app {

    using namespace std::chrono;
    using namespace elma;

    class WeatherApp; // Declare containing class so it can be refered to here
                     // before it is defined in weather_app.h

    //! A State class to represen the state in which the weather_app is max
    class MaxState : public State {

        public:
        //! Construct a new max state
        MaxState() : State("max") {}
        void entry(const Event& e) {}
        void during() {}

        //! Perform actions required when switching from max to on
        //! \param e The event that triggered the transition
        void exit(const Event& e);

        //! \return A reference to the containing finite state machine object
        WeatherApp& weather_app();

    };

}

#endif