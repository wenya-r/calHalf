#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <algorithm>
#include <functional>
#include <ctime>
#include <atomic>
#include <chrono>

using namespace std;


void half(int num, int size)
{
    random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : time(nullptr)+num;
    mt19937 eng(static_cast<mt19937::result_type>(seed));
    uniform_int_distribution<int> dist(0,1);

    auto gen = std::bind(dist, eng);
    
    this_thread::sleep_for(chrono::milliseconds(10000));

    vector<int> vec(size);
    generate(begin(vec), end(vec), gen);
    float average = accumulate( vec.begin(), vec.end(), 0.0)/vec.size();      
    cout << average << " has value " << endl;
//    return average;
}


int main(int nNumberofArgs, char* pszArgs[]){
unsigned int nThreads = thread::hardware_concurrency();
cout << "number of threads " << nThreads << endl;
auto curtime = chrono::high_resolution_clock::now();


//vector<thread> threads
//for (int i=0; i<10; ++i) {
  //  threads.push_back(thread{ half, {i, 10000000}});
//}
//for (auto& t : threads){
  //  t.join();
//}
int turns = 800000000;

thread t1(half, 1, turns);
thread t2(half, 2, turns);
thread t3(half, 3, turns);
thread t4(half, 4, turns);

thread t5(half, 5, turns);
thread t6(half, 6, turns);
thread t7(half, 7, turns);
thread t8(half, 8, turns);
thread t9(half, 9, turns);


t1.join();
t2.join();
t3.join();
t4.join();
t5.join();
t6.join();
t7.join();
t8.join();
t9.join();


chrono::duration<double, milli> elapsed = chrono::high_resolution_clock::now() - curtime;

cout << "Time :"<< elapsed.count() << endl;
return 0;
}


