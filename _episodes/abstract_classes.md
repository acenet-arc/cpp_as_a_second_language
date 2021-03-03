---
layout: episode
title: "Abstract classes"
teaching: 10
exercises: 10
questions:
- "What makes a class abstract?"
- "What are abstract classes used for?"
objectives:
- ""
keypoints:
- ""
---

~~~
#include <iostream>

class A{
public:
  int foo;
  void display(){
    std::cout<<"foo="<<foo<<"\n";
  }
  A(){
    foo=10;
  }
  ~A(){
    std::cout<<"destructor\n";
  }
  A operator+(A& rhs){
    A temp;
    temp.foo=foo+rhs.foo;
    return temp;
  }
};

class B:public A{
public:
  int extra;
};

int main(){
  A a;
  B b;
}
~~~

(https://www.cplusplus.com/doc/tutorial/templates/)[https://www.cplusplus.com/doc/tutorial/templates/]
