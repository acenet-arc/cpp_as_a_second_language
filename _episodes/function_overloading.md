---
layout: episode
title: "Function overloading"
teaching: 5
exercises: 5
questions:
- "What is function overloading?"
- "What is the 'this' keyword?"
objectives:
- ""
keypoints:
- ""
---

It might be nice to not always have a way to display only part of our vector, particularly if it is long.

Function overloading allows you to declare multiple functions with the same name that are distinguished by the type and number of parameters passed to the function. We could overload our display function to take an extra `int` argument to maybe indicate how many elements we want it to output.
~~~
$ cp member_functions.cpp function_overload.cpp
$ nano function_overload.cpp
~~~
and modify it to look like this:
<div class="gitfile" markdown="1">
~~~
#include <iostream>

class Vector{
public:
  int size;
  int* data;
  
  void display(int num){
    int numToDisplay=size;
    if(num<size){
      numToDisplay=num;
    }
    
    std::cout<<"Vector: size="<<size;
    std::cout<<", contents=(";
    for(int i=0;i<numToDisplay-1;++i){
      std::cout<<data[i]<<",";
    }
    if(num<size){
      std::cout<<data[numToDisplay-1]<<"...)\n";
    }
    else{
      std::cout<<data[numToDisplay-1]<<")\n";
    }
  }
  void display(){
    display(size);
  }
};

int main(){
  Vector a;
  a.size=10;
  a.data=new int[a.size];
  a.data[9]=15;
  a.display();
  a.display(5);
  delete [] a.data;
}
~~~~
[function_overload.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/function_overload.cpp)
</div>
To avoid having two functions with fairly similar duplicate code, we also now call our new function from the old function but just pass the size of the vector. This will help with maintainability in that we only need to make changes to the display function in one place.

We can now distinguish between which of these two function we wish to call, by either including an `int` parameter or not in the function call, e.g.
~~~
a.display();
~~~
vrs.
~~~
a.display(5);
~~~

Lets build and run it
~~~
$ g++ function_overload.cpp -o function_overload
$ ./function_overload
~~~
{: .bash}
~~~
Vector: size=10, contents=(0,0,0,0,0,0,0,0,0,15)
Vector: size=10, contents=(0,0,0,0,0...)
~~~
{: .output}

The elements 0-8 are zeros, but we didn't set them to zero. C and also C++ don't initialize variables to zero so we just got lucky that all these values where zero. The only one value that we can rely on is the one we actually set, the 15 at index 9.

Function overloading works not just for class member functions, but also for regular independent functions.

## The `this` keyword
There is a special keyword that can be used in class member functions `this`, which is a pointer to the class object that the function was invoked from (e.g. the `a` object in the `a.display();` line). We could have written our class member function like this:
~~~
class A{
public:
  int foo;
  void display(){
    std::cout<<"foo="<<this->foo<<"\n";
  }
};
~~~
You might like to use the `this` keyword to make it clear when you are and aren't referencing the class object, but it isn't needed in this example.
