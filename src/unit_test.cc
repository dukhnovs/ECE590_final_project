#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "gtest/gtest.h"
#include "weather_app.h"

namespace {
    using namespace std;
    using namespace elma;
    using namespace weather_app;

    TEST(WeatherApp,Construction) { 
        WeatherApp sw; 
        Manager m;
        m.schedule(sw,10_ms)
          .init()
          .start();
        ASSERT_EQ("off", sw.current().name());
    }

    // More tests go here. You should aim to test every
    // method of every object, either directly or indirectly,
    // although testing user interfaces is notoriously 
    // difficult.
    TEST(API, GetWeatherDataSample) {
      cout<<"API TEST"<<endl;
      Client c;
      c.get("http://api.openweathermap.org/data/2.5/forecast?q=Seattle,usa&APPID=d0fcd7e3aea1a3bc4f2c6095671223e8", [this](json& response) {
        auto res = response;
        vector<double> temp;
        // cout << res["list"] << endl;
        for (auto data : res["list"]) {
          cout << data["main"]["temp"] << ", " << endl;
          temp.push_back(data["main"]["temp"]);
          cout << temp.size() << endl;
        }
        // cout<<response.dump(4)<<endl;
      });
      // wait for response
      while(c.num_responses() != 1) {
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
      EXPECT_EQ(1,c.num_responses());
      c.process_responses();

    }
}