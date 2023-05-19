/*
  timesample.h - Class for model time series sample.
  Created by Matteo Fresta, February 28, 2023.
  Released into the public domain.
*/

#ifndef timesample_h
#define timesample_h
#include <array>
#include <string>
#include <iostream>
#include <vector>



using std::array;
using std::string;
using std::stringstream;
using std::vector;



class timesample{
  private:
  //variables
  
  //methods
  
  public:
  //variables
  
  vector<float> timeSampleArray;
  string timestamp;
  //string idMeasure;  //in the method POSTTimeseries
 
  
  
  //methods 
  string ArrayToString(vector<float> timeSampleArray);
 
  
  //constructors  
  timesample(const timesample&);
  timesample(string);
  
};

#endif 
