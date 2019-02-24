#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main(int argc, char* argv[])
{
  vector<int> vec={92,19,101,58,1053,91,26,78,10,13,-40,101,86,85,15,89,89,28,-5,41};
  vector<int> sortCopy(vec);
  sort(sortCopy.begin(), sortCopy.end());
  size_t size=vec.size();
  float divisor=static_cast<float>(size-1);
  for(unsigned int i=0; i<size; ++i)
    cout << "The percentile for item = " << sortCopy[i] << " at index = " << i << " is = " << static_cast<float>(i)/divisor << endl;  
  return(0);
}
