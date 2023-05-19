/*
  sample.cpp - Class for model sample.
  Created by Francesco Tornatore, February 24, 2020.
  Released into the public domain.
*/

#include "timesample.h"
#include <sstream>
#include <array>
#include <vector>
using std::array;
using std::string;
using std::stringstream;
using std::vector;





timesample::timesample(string timestamp){
  this->timestamp=timestamp;
}

//copy constructor
timesample::timesample(const timesample &timesam){  
  this->timestamp = timesam.timestamp;
  this->timeSampleArray = timesam.timeSampleArray;  
}

//methods
string timesample::ArrayToString(vector<float> timeSampleArray){
  
  stringstream sstream;
  if(timeSampleArray.size() == 1){
    sstream << timeSampleArray[0];
  }else{
    sstream << "[";
    for(int i=0; i < timeSampleArray.size(); i++ ){
      sstream << timeSampleArray[i];
      if(i < (timeSampleArray.size()-1)){
          sstream << ",";
        }
    }
    sstream << "]";
  }
  return sstream.str();
}
