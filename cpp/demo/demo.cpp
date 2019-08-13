/*************************************************************************
    > File Name: demo.cpp
    > Author: raoqiyu
    > Mail: raoqiyu@gmail.com 
    > Created Time: 2019年08月13日 星期二 11时24分58秒
 ************************************************************************/

#include "demo.h" 
#include <iostream> 

namespace demo {
 
    MyDemo::MyDemo () {}
 
    MyDemo::MyDemo (int a) {
        this->a = a; 
    }
 
    MyDemo::~MyDemo () {}
 
    int MyDemo::mul(int m) {
        return this->a*m;
    }

    int MyDemo::add (int b) {
        return this->a+b;
    }
    void MyDemo::sayHello(char* name){
        cout<<"hello modify"<<name<<"!"<<endl;
    }

   
}
