/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2019-08-13 11:24:58
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/demo/demo.cpp
 * @Description: 
 */

#include "AlgoLibR/demo/demo.h" 
#include <iostream> 
#include "AlgoLibR/demo/mul.h"

namespace AlgoLibR{
namespace demo {
 
    MyDemo::MyDemo () {}
 
    MyDemo::MyDemo (int a) {
        this->a = a; 
    }
 
    MyDemo::~MyDemo () {}
 
    int MyDemo::mul(int m) {
        return this->a*m;
    }

    int MyDemo::pymul(int m) {
        return demo::mul(this->a, m);
    }
    int MyDemo::add (int b) {
        return this->a+b;
    }
    void MyDemo::sayHello(wchar_t* name){
        wcout<<"hello "<<name<<"!"<<endl;
    }

} // namespace demo
} // namespace AlgoLibR
