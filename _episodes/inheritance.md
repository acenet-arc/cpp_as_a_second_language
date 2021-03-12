---
layout: episode
title: "Inheritance"
teaching: 10
exercises: 10
questions:
- "What is inheritance?"
- "What is inheritance used for?"
objectives:
- ""
keypoints:
- ""
---

We have so far been using our `Vector` class to store some number of integers. However, what if we instead wanted to have a vector that we could use for 3D positions, would we have to build a new class to do this from scratch or could we somehow reuse what we have already done for our more general `Vector` class? The answer is yes we can reuse much of what we have already done, and we can do that using **inheritance**.

As a starting point lets copy our previous program.
~~~
$ cp operator.cpp inheritance.cpp
$ nano inheritance.cpp
~~~
{: .bash}

Then modify it to add a new class `Vec3` which inherits our previous `Vector` class. Another way of saying this is that the `Vec3` class is a derived class from the base class `Vector`. You can specify that one class will inherit another class's member variables and functions by adding a `:` after the new class name in the class declaration followed by an access method `public`, `private` or `protected` and then the name of the class to be inherited.

Types of inheritance:
 * `public`: base class's public,protected, and private members are public,protected, and private in derived class.
 * `protected`: base class's public,protected, and private members are protected,protected, and private in derived class.
 * `private`: base class's public, protected, and private members are private, private, and private in derived class.

For more details about types of inheritance see this [cppreference.com](https://en.cppreference.com/w/cpp/language/derived_class) page.

~~~
#include <iostream>

class Vector{...};

class Vec3:public Vector{
public:
  Vec3():Vector(3){
  };
};
int main(){
  Vec3 p0;
  p0.data[0]=1;
  p0.data[1]=2;
  p0.data[2]=3;
  p0.display();
}
~~~
Our new `Vec3` class can be thought of as a combination of the two class declarations. First the original `Vector` class, then with the changes added for the `Vec3` class.

~~~
$ g++ inheritance.cpp -o inheritance
$ ./inheritance
~~~
{: .bash}

~~~
Vector: size=3, contents=(1,2,3)
~~~
{: .output}

Now that our `Vec3` class is explicitly 3 elements long, it seems a little redundant to display the size as 3, also it still says `Vector` but now it is a `Vec3`. Lets create a new `display` member function for our `Vec3` class.

~~~
$ nano inheritance.cpp
~~~
{: .bash}

~~~
#include <iostream>

class Vector{...};

class Vec3:public Vector{
public:
  Vec3():Vector(3){};
  void display(){
    std::cout<<"Vec3: ("<<data[0]<<","<<data[1]<<","<<data[2]<<")\n";
  }
};
int main(){
  Vec3 a;
  a.data[0]=10;
  a.display();
}
~~~
The new `display` member function declared in the `Vec3` class will now replace the `Vector` classes `display` member function for `Vec3` objects.

Lets build and run it to see the results.
~~~
$ g++ inheritance.cpp -o inheritance
$ ./inheritance
~~~
{: .bash}
~~~
Vec3: (10,0,0)
~~~
{: .output}

> ## Multiple inheritance
> C++ allows multiple inheritance, which means a class can have multiple base classes. For example:
> ~~~
> #include <iostream>
> 
> class A{
> public:
>   A(){std::cout<<"A constructor called\n";}
> };
> 
> class B{
> public:
>   B(){std::cout<<"B constructor called\n";}
> };
> 
> class C: public B, public A{//Note the order
> public:
>   C(){std::cout<<"C constructor called\n";}
> };
> 
> int main(){
>   C c;
> }
> ~~~
> 
> ~~~
> $ g++ multiple_inheratnace.cpp -o multiple_inheratnace
> $ ./multiple_inheratnace
> ~~~
> {: .bash}
> 
> ~~~
> B constructor called
> A constructor called
> C constructor called
> ~~~
> {: .output}
> Base class constructors are called in the order they are listed in the classes inheritance list.
{: .callout}
