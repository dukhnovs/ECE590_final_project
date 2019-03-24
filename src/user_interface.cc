#include <unistd.h>
#include "weather_app.h"
#include <string.h>

using namespace weather_app;

UserInterface::UserInterface(WeatherApp& sw) : Process("user input"), _weather_app(sw) {
    initscr();   // Start ncurses
    timeout(1);  // Timeout for waiting for user input
    noecho();    // Do not echo user input to the screen
    curs_set(0); // Do not show the cursor
};

void UserInterface::show_best(string best) {

    // Print the time at the desired position.
    // mvprintw just calls sprintf
    mvprintw(1,2,best.c_str());
}

void UserInterface::update() {

    // USER INPUT
    // get a character from the user, if one is ready.
    // If no character is ready, getch() returns ERR (which is
    // ignored below since there is no condition in the switch statement)
    int c = getch();

    switch ( c ) {            
        case 's':
            _weather_app.set_responded(false);
            emit(Event("seattle"));
            _weather_app.set_city("Seattle");
            _weather_app.set_mode(1);
            clear(); // Clear the screen of old stuff
            break;
        case 'r':
            emit(Event("reset"));
            _weather_app.set_city("None");
            _weather_app.set_mode(0);
            clear(); // Clear the screen of old stuff
            break;
        case 'l':
            _weather_app.set_responded(false);
            emit(Event("london"));
            _weather_app.set_city("London");
            _weather_app.set_mode(1);
            clear(); // Clear the screen of old stuff
            break;
        case 'q':
            std::cout << "halting\n";
            halt();
            break;
        case 'm':
            emit(Event("max_temp"));
            _weather_app.set_mode(2);
            clear(); // Clear the screen of old stuff
            break;
        case 'n':
            emit(Event("min_temp"));
            _weather_app.set_mode(2);
            clear(); // Clear the screen of old stuff
            break;
    }

    mvprintw(4,3,"Loading ...");
    // wait for api response
    while (_weather_app.responded() == false) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
   
    
    // OUTPUT

    if (_weather_app.mode() == 0) {
        mvprintw(1,3,"Select Seattle(s), Select London(l), reset(r), quit(q)"); 
    } else if (_weather_app.mode() == 1) {
        mvprintw(1,3,"Select Seattle(s), Select London(l), reset(r), quit(q)"); 
        mvprintw(2,3,"Selected City: %s", _weather_app.city().c_str()); 
        mvprintw(3,3,"Check Max Temperature(m) or Check Min Temperature(n)"); 
    } else if (_weather_app.mode() == 2) {
        mvprintw(1,3,"Select Seattle(s), Select London(l), reset(r), quit(q)"); 
        mvprintw(2,3,"Selected City: %s",  _weather_app.city().c_str()); 
        if (_weather_app.temp_type() == 0) {
            mvprintw(3,3,"Selected Temp Type: Max",  _weather_app.city().c_str()); 
        } else if (_weather_app.temp_type() == 1) {
            mvprintw(3,3,"Selected Temp Type: Min",  _weather_app.city().c_str()); 
        }
        mvprintw(4,3,"Temperature: %1.0f", _weather_app.temp_result());
    } 
    


    // NOTE: Since the weather_app is running every 10 ms, we should sleep
    //       the ui to give processing time back to the OS. It is debatable
    //       whether this is the right place to put this. It could also become
    //       an Elma feature, or it could go in the WeatherApp class, etc.
    //       The number 9999 should also be a parameter and not a constant.
    usleep(9999);

}