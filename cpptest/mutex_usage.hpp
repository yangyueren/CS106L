//
// Created by yryang on 2020/3/30.
//
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

int m_sum = 0;
std::mutex m_mtx;
void m_count(int t, int id){
    try{
        for (int i = 0; i < t; ++i) {
            {
                std::lock_guard<std::mutex> lk(m_mtx);
                if(id == 1) throw std::runtime_error("run time error");
                m_sum++;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }catch (const std::exception& e){
        std::cout << "id " << id << " " << e.what() << endl;
    }

}

void test_mutex(){
    thread t1(m_count, 1000, 1);
    thread t2(m_count, 1000, 2);
    t1.join();
    t2.join();
    cout << m_sum << endl;

}
