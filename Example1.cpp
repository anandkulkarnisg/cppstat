#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<cmath>

#include"winsor.h"

using namespace std;

int main(int argc, char* argv[])
{
  vector<int> arr= { 92, 19, 101, 58, 1053, 91, 26, 78, 10, 13, -40, 101, 86, 85, 15, 89, 89, 28, -5, 41};
  printArrayToConsole("before : ", arr);
  float winsorSize=0;
  if(argc>1)
  {
    try
    {
      winsorSize=stof(argv[1]);
    } catch(exception& e)
    {
      cout << "warning : The first argument" << argv[1] << " could not be converted to float.Defaulting to zero." << endl;
    }
  }
  winsorize(arr, winsorSize);
  printArrayToConsole("after  : ", arr);
  return(0);
}
