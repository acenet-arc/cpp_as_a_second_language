---
layout: episode
title: "Templates"
teaching: 10
exercises: 10
questions:
- "What are templates?"
- "What is generic programming?"
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
