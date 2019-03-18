#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "gtest/gtest.h"
#include "stopwatch.h"

namespace {
 
    using namespace elma;
    using namespace stopwatch;

    TEST(StopWatch,Construction) { 
        StopWatch sw; 
        ASSERT_EQ("off", sw.current().name());
    }

    // More tests go here. You should aim to test every
    // method of every object, either directly or indirectly,
    // although testing user interfaces is notoriously 
    // difficult.

    // test problem 1
    TEST(API, GetWeatherDataSample) {
        Client c;
        json data;
        c.get("api.openweathermap.org/data/2.5/weather?q=London,uk&APPID=d0fcd7e3aea1a3bc4f2c6095671223e8", data, [this](json& response) {
            cout<<response.dump()<<endl;
        });
        // wait for response
        while(target_responses != 1) {
        }
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        EXPECT_EQ(1,c.num_responses());
        c.process_responses();
    }

}