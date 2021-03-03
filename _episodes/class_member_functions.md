---
layout: episode
title: "Class member functions"
teaching: 15
exercises: 10
questions:
- "What is a class member function?"
- "How do you create a class member function?"
- "How do you call a class member function?"
- "What data can class member functions access?"
- "What is function overloading?"
objectives:
- ""
keypoints:
- ""
---

It might be nice to start to move some of the common things we do, such as displaying information about the Vector into a function to allow for easier reuse. C++ actually allows you to associate functions with classes, these functions are called members of a class, or member functions. Lets add a new `display` member function which will display our vector on the terminal.

~~~
$ cp classes.cpp member_functions.cpp
$ nano member_functions.cpp
~~~
and modify it to look like the following

~~~
#include <iostream>

class Vector{
public:
  int size;
  int* data;
  
  void display(){
    std::cout<<"Vector: size="<<size;
    std::cout<<", contents=(";
    for(int i=0;i<size-1;++i){
      std::cout<<data[i]<<",";
    }
    std::cout<<data[size-1]<<")\n";
  }
  
};

int main(){
  Vector a;
  a.size=10;
  a.data=new int[a.size];
  a.data[9]=15;
  a.display();
  delete [] a.data;
}
~~~

~~~
$ g++ member_functions.cpp -o member_functions
$ ./member_functions
~~~
{: .bash}
~~~
Vector: size=10, contents=(0,0,0,0,0,0,0,0,0,15)
~~~
{: .output}

We created a function called `display` inside the `Vector` class. This function doesn't take any parameters, but has access to the all the members of the class. When we reference `size` in the `display` member function, it is referring to the `size` member of the class. When we invoke the function with the line `a.display()` in the `main` function, the `display` function will be accessing the data in the `a` object.

This functionally is nearly identical to the following:

~~~
#include <iostream>

struct Vector{
public:
  int size;
  int* data;
};

void display(Vector *a){
  std::cout<<"Vector: size="<<a->size;
  std::cout<<", contents=(";
  for(int i=0;i<a->size-1;++i){
    std::cout<<a->data[i]<<",";
  }
  std::cout<<a->data[a->size-1]<<")\n";
}

int main(){
  Vector a;
  a.size=10;
  a.data=new int[a.size];
  a.data[9]=15;
  display(&a);
  delete [] a.data;
}
~~~
Note I used the `->` operator which acts like the `.` operator but works when you have a pointer to the object rather than the object itself. I also used the `&` operator to get the address of the object to pass to the function.

## Function overloading
It might be nice to not always have a way to display only part of our vector, particularly if it is long.

Function overloading allows you to declare multiple functions with the same name that are distinguished by the type and number of parameters passed to the function. We could overload our display function to take an extra `int` argument to maybe indicate how many elements we want it to output.
~~~
$ cp member_functions.cpp function_overload.cpp
$ nano function_overload.cpp
~~~
and modify it to look like this:
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

> ## Separating declarations and definitions
> 
> It is common in both C and C++ to separate the definition of structs, classes, and function declarations from the implementation. To move a class member function implementation out of the class declaration you need to prefix it with the class namespace. For example if we moved our display function out of our class declaration we would have
> ~~~
> #include <iostream>
> 
> class A{
> public:
>   int foo;
>   void display();
> };
> 
> void A::display(){
>   std::cout<<"foo="<<foo<<"\n";
> }
> 
> int main(){
>   A a;
>   a.foo=1;
>   a.display();
> }
> ~~~
> 
> this could allow you to put your class member functions into a separate ".cpp" file and have your class definition in a ".h" file. This allows you to gain access to your class definition in other ".cpp" files where you might want to use your class. This is a common and fairly standard practice but not required. It allows you to compile each ".cpp" file separately and then link it together in the final exe. One alternative build method is what are called "Unity builds", where all the files are `#included` it into a single compilation unit (see [wiki page on single compilation unit](https://en.wikipedia.org/wiki/Single_Compilation_Unit) for a quick explanation).
{: .callout}
> ## Quick comment on build tools
Build methods and tools is a huge topic in and of its self. Build tools are independent of the compiler you use but allow you to specify dependencies and commands to run to build the components of your exectubale. I usually prefer to keep this as simple as possible and use the GNU make tool. If I really want to get fancy I may sometimes use the [GNU Autotools](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html) which allows you to make a distribution package that would follow the `./configure` `make` `make install` process. On Windows I actually also use GNU make, see [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm). There are lots of build tools out there, but make has been around for a long time and as far as I can tell is the simplest I have come across.
{: .callout}

> ## Class member functions and function pointers
> One wrinkle with using class member functions is if you want to use pointers to those functions, say for a callback. It can get very tricky because the function has access to and potentially uses data from within the object it is called from. Therefore you can't use class member functions for function pointers without a lot of work, for example have a look at [boost::bind](https://www.boost.org/doc/libs/1_66_0/libs/bind/doc/html/bind.html). Boost is a very large C++ library that adds heaps of additional functionality, but can be a bit of work to get and integrate into your projects, not to mention your compile times will definately increase if you are using it.
{: .callout}