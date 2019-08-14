/*************************************************************************
    > File Name: demo.h
    > Author: raoqiyu
    > Mail: raoqiyu@gmail.com 
    > Created Time: 2019年08月13日 星期二 11时24分11秒
 ************************************************************************/

#ifndef DEMO_H
#define DEMO_H

using namespace std;
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
}
#endif

