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

using namespace std;


void half(int num, int size)
{
    random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : time(nullptr)+num;
    mt19937 eng(static_cast<mt19937::result_type>(seed));
    uniform_int_distribution<int> dist(0,1);

    auto gen = std::bind(dist, eng);

    vector<int> vec(size);
    generate(begin(vec), end(vec), gen);
    float average = accumulate( vec.begin(), vec.end(), 0.0)/vec.size();      
    cout << average << " has value " << endl;

}


int main(int nNumberofArgs, char* pszArgs[]){
unsigned int nThreads = thread::hardware_concurrency();
cout << "number of threads " << nThreads << endl;
float curtime = clock();


vector<thread> threads
for (int i=0; i<10; ++i) {
    threads.push_back(thread{ half, {i, 1000000}});
}
for (auto& t : threads){
    t.join();
}
//thread t1(half, 1, 1000000);
//thread t2(half, 2, 1000000);
//thread t3(half, 3, 1000000);
//thread t4(half, 4, 1000000);
//t1.join();
//t2.join();
//t3.join();
//t4.join();

cout << "Time :"<< (clock() - curtime)/CLOCKS_PER_SEC << endl;
return 0;
}

