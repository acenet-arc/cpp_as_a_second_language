---
layout: episode
title: "Inheritance"
teaching: 10
exercises: 5
questions:
- "What is inheritance?"
- "What is inheritance used for?"
objectives:
- "Create a derived class specialized for 3D vectors"
keypoints:
- "Inheritance allows reuse of code in related classes."
- "Inheritance can happen in one of three ways `public`, `protected` or `private` and affects how the inherited members are accessed in the derived class."
---

We have so far been using our `Vector` class to store some number of integers. However, what if we instead wanted to have a vector that we could use for 3D positions, would we have to build a new class to do this from scratch or could we somehow reuse what we have already done for our more general `Vector` class? The answer is yes we can reuse much of what we have already done, and we can do that using **inheritance**.

As a starting point let's copy our previous program.
~~~
$ cp operator.cpp inheritance.cpp
$ nano inheritance.cpp
~~~
{: .bash}

Then modify it to add a new class `Vec3` which inherits our previous `Vector` class. Another way of saying this is that the `Vec3` class is a derived class from the base class `Vector`. You can specify that one class will inherit another class's member variables and functions by adding a `:` after the new class name in the class declaration followed by an access method `public`, `private` or `protected` and then the name of the class to be inherited.

Types of inheritance access modifiers:
 * `public`: base class's public and protected members are public and protected in the derived class.
 * `protected`: base class's public and protected members are protected and protected in the derived class.
 * `private`: base class's public and protected members are private and private in the derived class.

Private members in the base class are not accessible in the derived class. Exceptions to this can arise if using [friend declarations](https://en.cppreference.com/w/cpp/language/friend), which we will not cover.

For more details about types of inheritance see this [cppreference.com](https://en.cppreference.com/w/cpp/language/derived_class) page.

<div class="gitfile" markdown="1">
~~~
#include <iostream>

class Vector{...};

class Vec3:public Vector{
public:
  Vec3():Vector(3){
  };
};
int main(){
  Vec3 a;
  a.data[0]=1;
  a.data[1]=2;
  a.data[2]=3;
  a.display();
}
~~~
[inheritance.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/inheritance.cpp)
</div>
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

<div class="gitfile" markdown="1">
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
[inheritance.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/inheritance_member_function.cpp)
</div>
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
> $ g++ multiple_inheritance.cpp -o multiple_inheritance
> $ ./multiple_inheritance
> ~~~
> {: .bash}
> 
> ~~~
> B constructor called
> A constructor called
> C constructor called
> ~~~
> {: .output}
> Base class constructors are called in the order they are listed in the class's inheritance list.
{: .callout}

> ## Private inheritance
> ~~~
> ...
> 72 class Vec3:private Vector{
> 73 public:
> 74   Vec3():Vector(3){
> 75   };
> 76   void display(){
> 77     std::cout<<"Vec3: ("<<data[0]<<","<<data[1]<<","<<data[2]<<")\n";
> 78   }
> 79 };
> 80
> 81 int main(){
> 82   Vec3 a;
> 83   a.data[0]=10;
> 84   a.display();
> 85 }
> ~~~
> If we take the most recent version of `inheritance.cpp` and copy it to `private_inheritance.cpp` and only change line 72 from `class Vec3:public Vector{` to `class Vec3:private Vector{` what will happen when we try to compile it?
> <ol type="a">
> <li markdown="1">
> It will compile fine.
> </li>
> <li markdown="1">
> Generate the following errors:
> ~~~
> private_inheritance.cpp: In member function ‘void Vec3::display()’:
> private_inheritance.cpp:77:27: error: ‘int* Vector::data’ is private within this context
>    77 |     std::cout<<"Vec3: ("<<data[0]<<","<<data[1]<<","<<data[2]<<")\n";
>       |                           ^~~~
> private_inheritance.cpp: In function ‘int main()’:
> private_inheritance.cpp:83:5: error: ‘int* Vector::data’ is private within this context
>    83 |   a.data[0]=10;
>       |     ^~~~
> ~~~
> {: .output}
> </li>
> <li markdown="1">
> Generate the following error:
> ~~~
> private_inheritance.cpp: In function ‘int main()’:
> private_inheritance.cpp:83:5: error: ‘int* Vector::data’ is private within this context
>    83 |   a.data[0]=10;
>       |     ^~~~
> ~~~
> {: .output}
> </li>
> </ol>
> > ## Solution
> > <ol type="a">
> > <li markdown="1">
> > **NO**: private inheritance causes the derived class to inherit the base classes members as private members. In the main function the inherited member `data` is accessed which is not allowed and would generate a compiler error.
> > </li>
> > <li markdown="1">
> > **NO**: While it is correct that it will generate a compiler error similar to this, the class member function `display` can access its own private members. Since the `data` member is `public` in the base class it will be inherited as a `private` member in the derived class.
> > </li>
> > <li markdown="1">
> > **YES**: `data` will be inherited as a private member in the derived class and as such can not be accessed outside class member functions.
> > </li>
> > </ol>
> {: .solution}
{: .challenge}
