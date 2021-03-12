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

Taking the idea of polymorphism and inheritance mentioned previously a little further, what if we wanted to have a more general base class which we could pass to a function to allow displaying of any future class we might create? We could create what is known as an abstract base class.

Lets do that now by copying our `virtual.cpp` program to a new `abstract.cpp` program and opening it in `nano`.

~~~
$ cp virtual.cpp abstract.cpp
$ nano abstract.cpp
~~~
{: .bash}

<div class="gitfile" markdown="1">
~~~
#include <iostream>

class Displayable{
public:
  virtual void display()=0;
};

class Vector: public Displayable{...};

class Vec3:public Vector{...};

void nameAndDisplay(char* name,Displayable* v){...}

int main(){
  
  Vec3 a,b;
  a.data[0]=10;
  b.data[0]=22;
  Vector c=a+b;
  char nameA[]={"a\0"};
  nameAndDisplay(nameA,&a);
  char nameB[]={"b\0"};
  nameAndDisplay(nameB,&b);
  char nameC[]={"c\0"};
  nameAndDisplay(nameC,&c);
}
~~~
[abstract.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/abstract.cpp)
</div>
We have create a new class `Displayable`, this is an abstract class because of the line `virtual void display()=0;` which indicates we have not provided an implementation for this member function. A member function declared in this way with no implementation is referred to as a **pure virtual function**. Any class with one or more pure virtual functions is referred to as an **abstract** class.

Abstract classes with pure virtual functions can not be used to create objects directly as they are missing the implementation of at least one member function. This is part of the reason they are called 'abstract' because they can't be directly used. However, they can be used as base classes by other classes. In our above example we now have the `Vector` class inheriting the abstract class `Displayable`. We have also made our `nameAndDisplay` function take a pointer to a `Displayable` rather than a `Vector`. Now we can pass that function a pointer to any object that is of a class which inherits the `Displayable` abstract class. Classes which inherit an abstract class must override all the pure virtual member functions in order to not be abstract classes themselves.

We are using our `Displayable` abstract class in a way that is often called an **interface**. It is common for libraries to provide abstract classes from which you can create your own concrete classes that you can then pass to functions in the library. These functions will then have a guarantee that they can call these functions on the objects it is passed.

~~~
$ g++ abstract.cpp -o abstract
$ ./abstract
~~~
{: .bash}
~~~
a=Vec3: (10,0,0)
b=Vec3: (22,0,0)
c=Vector: size=6, contents=(10,0,0,22,0,0)
~~~
{: .output}