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


void half(int num, atomic<int>& size, atomic<float>& sum, atomic<int>& times )
{
    random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : time(nullptr)+num;
    cout <<"private: "<< num << endl;
 //   num++;
    mt19937 eng(static_cast<mt19937::result_type>(seed));
    uniform_int_distribution<int> dist(0,1);

    auto gen = std::bind(dist, eng);

    vector<int> vec(size);
    generate(begin(vec), end(vec), gen);
    atomic<float> average(accumulate( vec.begin(), vec.end(), 0.0)/vec.size());      
    cout << average << " has value " << num << endl;
    sum = sum + average;
    times++;
}


int main(int nNumberofArgs, char* pszArgs[]){
unsigned int nThreads = thread::hardware_concurrency();
cout << "number of threads " << nThreads << endl;
//float curtime = clock();

atomic<int> counter(50000000), times(0);
atomic<float> sum;
vector<thread> threads;
for (int i=0; i<4; i++) {
    cout << i << "th run" << endl;
    threads.push_back(thread{ half, i, ref(counter), ref(sum), ref(times)});
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
//chrono::duration<double, std::milli> elapsed = end-start;
//cout << "Time :"<< (clock() - curtime)/CLOCKS_PER_SEC << endl;

cout << "Sum :" << sum<<"Times: " << times << endl;
cout << "Final average :" << sum/times << endl;
return 0;
}

