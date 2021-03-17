---
layout: episode
title: "A first class"
teaching: 10
exercises: 10
questions:
- "What is a class?"
- "How do you create a class?"
- "How do you do use a class?"
objectives:
- "Create our first class to store some integers."
keypoints:
- "Use the `class` keyword to create a new class."
- "Class access modifiers control what parts of the program can access the classes members."
- "Class members can be accessed with the `.` operator."
---

Previously we created an array of integers. It is very handy to be able to dynamically allocate memory of a given size that could potentially be determined at run time. However, as we just saw this introduces having to manage the dynamically allocated memory with `new`/`new[]` and `delete`/`delete[]`. The main way C++ tries to organize the management of these sorts of things is to use classes. So lets try that out and create a new `Vector` class which will allow us to more easily manage allocation of dynamic arrays of integers.

Start by coping our `memory.cpp` program from last episode.
~~~
$ cp memory.cpp classes.cpp
$ nano classes.cpp
~~~

Then modify it to look like the code below.
<div class="gitfile" markdown="1">
~~~
#include <iostream>

class Vector{
public:
  int size;
  int* data;
};

int main(){
  Vector a;
  a.size=10;
  a.data=new int[a.size];
  a.data[9]=15;
  std::cout<<"a.size="<<a.size<<"\n";
  std::cout<<"a.data[9]="<<a.data[9]<<"\n";
  delete[] a.data;
}
~~~
[classes.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/classes.cpp)
</div>
Here we have put the variable `size` and the array `a` renamed to `data` into our new `Vector` class. We have also used the `.` operator to access the classes `public` members.
~~~
$ g++ classes.cpp -o classes
$ ./classes
~~~
{: .bash}
~~~
a.size=10
a.data[9]=15
~~~
{: .output}

### Class keyword

`class` is a keyword like, `struct` is a key word. It is used to declare a new class and is followed by the class name, an open `{` and close `}` as is the case with a `struct`. Inside the `{}` is the definition of the class, e.g. the member variables like `size` above.

### Class access modifiers

`public` is a class access modifier. It describes how the members of the class after the access modifier are to be treated.
* `public`: indicates that the following members can be accessed from anywhere.
* `private`: indicates that the following members can be accessed only from within the class (this will make more sense when we talk about member functions).
* `protected`: indicates that the following members can only be accessed by the class and any child classes (child classes will make more sense when we talk about inheritance).

### Using classes

You can declare new objects as that type of class. Think data type (e.g. int, a struct you created, etc.) and the object as the variable you create. You can access members of a class (in the case of classes this is both member functions and member variables) with the `.` operator as you would with C structs, note the line `a.size=10;` above.

> ## Access modifiers
> ~~~
>  1 #include <iostream>
>  2 
>  3 class A{
>  4 private:
>  5   int foo;
>  6 public:
>  7   int bar;
>  8 };
>  9 
> 10 int main(){
> 11  A a;
> 12  a.foo=1;
> 13  a.bar=2;
> 14  std::cout<<"foo="<<a.foo<<" bar="<<a.bar<<"\n";
> 15 }
> ~~~
> Given the above `access_modifiers.cpp` file what happens when the above is compiled and run?
> <ol type="a">
> <li markdown="1">
> The following compiler error is generated:
> ~~~
> access_modifiers.cpp: In function ‘int main()’:
> access_modifiers.cpp:12:5: error: ‘int A::foo’ is private within this context
>    a.foo=1;
>      ^~~
> access_modifiers.cpp:5:7: note: declared private here
>    int foo;
>        ^~~
> access_modifiers.cpp:14:24: error: ‘int A::foo’ is private within this context
>    std::cout<<"foo="<<a.foo<<" bar="<<a.bar<<"\n";
>                         ^~~
> access_modifiers.cpp:5:7: note: declared private here
>    int foo;
>        ^~~
> ~~~
> {: .output}
> </li>
> <li markdown="1">
> The following output is generated:
> ~~~
> foo=1 bar=2
> ~~~
> {: .output}
> </li>
> <li markdown="1">
> The following compiler error is generated:
> ~~~
> access_modifiers.cpp: In function ‘int main()’:
> access_modifiers.cpp:12:5: error: ‘int A::foo’ is private within this context
>    a.foo=1;
>      ^~~
> access_modifiers.cpp:5:7: note: declared private here
>    int foo;
>        ^~~
> access_modifiers.cpp:13:5: error: ‘int A::bar’ is private within this context
>    a.bar=2;
>      ^~~
> access_modifiers.cpp:7:7: note: declared private here
>    int bar;
>        ^~~
> access_modifiers.cpp:14:24: error: ‘int A::foo’ is private within this context
>    std::cout<<"foo="<<a.foo<<" bar="<<a.bar<<"\n";
>                         ^~~
> access_modifiers.cpp:5:7: note: declared private here
>    int foo;
>        ^~~
> access_modifiers.cpp:14:40: error: ‘int A::bar’ is private within this context
>    std::cout<<"foo="<<a.foo<<" bar="<<a.bar<<"\n";
>                                         ^~~
> access_modifiers.cpp:7:7: note: declared private here
>    int bar;
>        ^~~
> ~~~
> {: .output}
> </li>
> </ol>
> > ## Solution
> > <ol type="a">
> > <li markdown="1">
> > **YES**: correct, `foo` has been declared a private member, however `bar` is public and so is fine to access outside of the class.
> > </li>
> > <li markdown="1">
> > **NO**: if `foo` was declared as public this is what we would have gotten. Unfortunately `foo` is private and so can not be accessed from outside the class.
> > </li>
> > <li markdown="1">
> > **NO**: while `foo` is indeed private, `bar` has been declared as public so it is accessible from outside the class.
> > </li>
> > </ol>
> {: .solution}
{: .challenge}
