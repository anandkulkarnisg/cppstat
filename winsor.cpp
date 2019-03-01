#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<cmath>

#include "winsor.h"

using namespace std;

void printArrayToConsole(const char* phase, const vector<int>& arr)
{
  cout << phase;
  size_t size = arr.size();
  if(size)
  {
    for(unsigned int i=0; i<size-1; ++i)
      cout << arr[i] << ",";
    cout << arr[size-1] << '\n';
  }
}

void doSwapItems(int* item1, int* item2)
{
  int temp=*item1;
  *item1=*item2;
  *item2=temp;
}

bool doCompare(const int& item1, const int& item2, const SortOrder& sortOrder)
{
  if(sortOrder==SortOrder::asc)
    return(item1<item2);
  else
    return(item1>item2);
}

pair<int, int> doPartialSelectionSort(const vector<int>& orig, const float& lowWinsorSize=0, const float& highWinsorSize=0,
    const WinsorStyle& lowWinsorStyle=WinsorStyle::relaxed, const WinsorStyle& highWinsorStyle=WinsorStyle::relaxed
    )
{
  vector<int> arr(orig);
  size_t size=arr.size();
  size_t iterations;
  size_t relaxedPadUp=0;
  size_t minMaxIdx;
  size_t numIterations;
  vector<int> results;
  results.reserve(2);
  vector<SortOrder> sortTypes = { SortOrder::asc, SortOrder::desc };

  for(const auto& sortOrder : sortTypes)
  { 
    if(sortOrder == SortOrder::asc) 
    {
      iterations=round(lowWinsorSize*size)+1;
      if(lowWinsorStyle==WinsorStyle::relaxed)
        relaxedPadUp=1;
      else
        relaxedPadUp=0;
    }
    if(sortOrder == SortOrder::desc)
    {
      iterations=round(highWinsorSize*size)+1;
      if(highWinsorStyle==WinsorStyle::relaxed)
        relaxedPadUp=1;
      else
        relaxedPadUp=0;
    }
    numIterations=iterations+relaxedPadUp;
    for(unsigned int i=0; i<=numIterations; ++i)
    {
      minMaxIdx=i;
      for(unsigned int j=i+1; j<size; ++j)
      {
        if(doCompare(arr[j], arr[minMaxIdx], sortOrder))
          minMaxIdx=j;
      }
      if(minMaxIdx!=i)
        doSwapItems(&arr[i], &arr[minMaxIdx]);
    }   

    if(sortOrder == SortOrder::asc)
    {
      float percentileVal=static_cast<float>(numIterations-1)/static_cast<float>(size-1); 
      if(lowWinsorStyle == WinsorStyle::relaxed && percentileVal>lowWinsorSize)
        numIterations-=1;
      if(lowWinsorStyle == WinsorStyle::strict && percentileVal<lowWinsorSize)
      {
        float neighbourPercentile=static_cast<float>(numIterations)/static_cast<float>(size-1);
        if(abs(percentileVal-neighbourPercentile)<abs(lowWinsorSize-percentileVal))
          numIterations+=1;
      }
    }

    if(sortOrder == SortOrder::desc)
    {
      float percentileVal=static_cast<float>((size-1)-(numIterations-1))/static_cast<float>(size-1);
      if(highWinsorStyle == WinsorStyle::relaxed && percentileVal<(1-highWinsorSize))
        numIterations-=1;
      if(highWinsorStyle == WinsorStyle::strict && percentileVal>(1-highWinsorSize))
      {
        float neighbourPercentile=static_cast<float>(numIterations)/static_cast<float>(size-1);
        if(abs(percentileVal-neighbourPercentile)<abs((1-highWinsorSize)-percentileVal))
          numIterations+=1;
      }
    }
    results.emplace_back(arr[numIterations-1]);
  }
  return(make_pair(results[0], results[1]));
}

void winsorizeInternal(vector<int>& arr, const float& lowWinsorSize, const float& highWinsorSize, const WinsorStyle& lowWinsorStyle, const WinsorStyle& highWinsorStyle)
{
  pair<int, int> resultPair=doPartialSelectionSort(arr, lowWinsorSize, highWinsorSize, lowWinsorStyle, highWinsorStyle);

  int lowerBound=resultPair.first;
  int upperBound=resultPair.second;

  size_t size=arr.size();
  for(unsigned int i=0; i<size; ++i)
  {
    if(arr[i]<lowerBound)
      arr[i]=lowerBound;
    else
    {
      if(arr[i]>upperBound)
        arr[i]=upperBound;
    }
  }
}

void winsorize(vector<int>& arr, const float& winsorSize)
{
  winsorizeInternal(arr, winsorSize, winsorSize);
}

void winsorize(vector<int>& arr, const float& lowWinsorSize, const float& highWinsorSize)
{
  winsorizeInternal(arr, lowWinsorSize, highWinsorSize);
}

void winsorize(vector<int>& arr, const float& lowWinsorSize, const float& highWinsorSize, const WinsorStyle& lowWinsorStyle, const WinsorStyle& highWinsorStyle)
{
  winsorizeInternal(arr, lowWinsorSize, highWinsorSize, lowWinsorStyle, highWinsorStyle);
}
