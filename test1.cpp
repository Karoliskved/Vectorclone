#include <iostream>
#include "Vector.h"
#include <vector>
#include <chrono>
#include <time.h>
int main(){
auto start = std::chrono::high_resolution_clock::now();
unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
std::vector<int> v1;
int count1=0;
for (int i = 1; i <= sz; ++i){
     v1.push_back(i);
     if(v1.capacity() == v1.size())
     count1++;
}

 
std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
std::cout << "vector laikas:" << diff.count() <<std::endl;
std::cout << "perskirstymas ivyko " << count1 << std::endl;

// Baigti v1 užpildymo laiko matavimą

// Pradėti v2 užpildymo laiko matavimą
Vector<int> v2;
int count2=0;
auto start1 = std::chrono::high_resolution_clock::now();
for (int i = 1; i <= sz; ++i){
    v2.push_back(i);
  if(v2.capacity() == v2.size())
     count2++;
}
std::chrono::duration<double> diff1 = std::chrono::high_resolution_clock::now() - start1;
std::cout << "vector laikas:" << diff1.count() <<std::endl;
std::cout << "perskirstymas ivyko " << count2 << std::endl;
// Baigti v2 užpildymo laiko matavimą
}
