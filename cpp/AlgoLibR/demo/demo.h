/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-09 14:55:06
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/demo/demo.h
 * @Description: 
 */

#ifndef DEMO_H
#define DEMO_H

using namespace std;

namespace AlgoLibR{
namespace demo {

class MyDemo {
    public:
        int a;
        MyDemo();
        MyDemo(int a );
        ~MyDemo();
        int mul(int m );
        int pymul(int m);
        int add(int b);
        void sayHello(char* name);
};

} // namespace demo
} // namespace AlgoLibR
#endif

