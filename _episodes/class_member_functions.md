---
layout: episode
title: "Class member functions"
teaching: 10
exercises: 10
questions:
- "What is a class member function?"
- "How do you create a class member function?"
- "How do you call a class member function?"
- "What data can class member functions access?"
objectives:
- "Add a class member function to display our object"
keypoints:
- "Class member functions have access to object members implicitly."
- "Access modifiers apply to both class member functions and variables."
---

It might be nice to start to move some of the common things we do, such as displaying information about the Vector into a function to allow for easier reuse. C++ actually allows you to associate functions with classes, these functions are called members of a class, or member functions. Lets add a new `display` member function which will display our vector on the terminal.

~~~
$ cp classes.cpp member_functions.cpp
$ nano member_functions.cpp
~~~
and modify it to look like the following

<div class="gitfile" markdown="1">
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
[member_functions.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/member_functions.cpp)
</div>
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


> ## Class member functions and function pointers
> One wrinkle with using class member functions is if you want to use pointers to those functions, say for a callback. It can get very tricky because the function has access to and potentially uses data from within the object it is called from. If you use the function pointer in isolation as you would normally the function has no knowledge of which object it should access the data it might need from. If you need to reference a class member function as a function pointer, the simplest solution is to make it a stand alone function which has a parameter of the class type as is illustrated above.
>
> It is possible however, using [boost::bind](https://www.boost.org/doc/libs/1_66_0/libs/bind/doc/html/bind.html). Boost is a very large C++ library that adds heaps of additional functionality, but can be a bit of work to get and integrate into your projects, not to mention your compile times will definitely increase if you are using it.
{: .callout}

> ## Separating declarations and implementations
> 
> It is common in both C and C++ to separate the declarations of structs, classes, and function from the implementation. To move a class member function implementation out of the class declaration you need to prefix it with the class namespace. For example if we moved our display function out of our class declaration we would have
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
Build methods and tools is a huge topic in and of its self. Build tools are independent of the compiler you use but allow you to specify dependencies and commands to run to build the components of your exectubale. I usually prefer to keep this as simple as possible and use the [GNU make](https://www.gnu.org/software/make/) tool. If I really want to get fancy I may sometimes use the [GNU Autotools](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html) which allows you to make a distribution package that would follow the `./configure` `make` `make install` process. On Windows I actually also use GNU make, see [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm). There are lots of build tools out there, but make has been around for a long time and as far as I can tell is the simplest I have come across.
{: .callout}

> ## Member function variables
> ~~~
> #include <iostream>
> 
> class A{
> public:
>   int foo;
>   void display(){
>     std::cout<<foo<<" ";
>   }
> }
> int main(){
>   A a,b;
>   a.foo=1;
>   b.foo=2;
>   b.display();
>   a.display();
> }
> ~~~
> What is the output when the above file `member_function_variables.cpp` is compiled and executed?
> <ol type="a">
> <li markdown="1">
> 1 1 
> </li>
> <li markdown="1">
> 2 2 
> </li>
> <li markdown="1">
> 1 2 
> </li>
> <li markdown="1">
> 2 1
> </li>
> <li markdown="1">
> foo foo
> </li>
> </ol>
> > ## Solution
> > <ol type="a">
> > <li markdown="1">**NO**: the memory which stores `foo` in `a` and `b` is separate so they have distinct values for each object. When the function `display` is invoked the `foo` variable takes on the value of the object the function is invoked on.
> > </li>
> > <li markdown="1">**NO**: same reason as answer a.
> > </li>
> > <li markdown="1">**NO**: not quite, note the order the functions are called in `b.display()` is called first then `a.display()`.
> > </li>
> > <li markdown="1">**YES**: when `b.display()` is called, `foo` takes on the value of `2` and is printed out followed by a space. When `a.display()` is called, `foo` takes on the value of `1` and is printed out followed by a space.
> > </li>
> > <li markdown="1">**No**: you would need to have quotes around `foo` to get this output so that it would be a string rather than a variable.
> > </li>
> > </ol>
> {: .solution}
{: .challenge}

> ## Access modifiers revisited
> ~~~
>  1 #include <iostream>
>  2 
>  3 class A{
>  4 public:
>  5   int foo;
>  6   void display(){
>  7     std::cout<<"foo="<<foo<<" bar="<<bar<<"\n";
>  8   }
>  9 private:
> 10   int bar;
> 11   void setBar(int barIn){
> 12     bar=barIn;
> 13   }
> 14 };
> 15 
> 16 int main(){
> 17   A a;
> 18   a.foo=1;
> 19   a.bar=2;
> 20   a.setBar(3);
> 21   a.display();
> 22 }
> ~~~
> Given the above `access_modifiers.cpp` file what happens when the above is compiled and run?
> <ol type="a">
> <li markdown="1">
> Compiles with out issue and the following is printed out when run:
> ~~~
> foo=1 bar=3
> ~~~
> {: .output}
> </li>
> <li markdown="1">
> The following compiler error is generated:
> ~~~
> access_modifiers.cpp: In function ‘int main()’:
> access_modifiers.cpp:19:5: error: ‘int A::bar’ is private within this context
>    19 |   a.bar=2;
>       |     ^~~
> access_modifiers.cpp:10:7: note: declared private here
>    10 |   int bar;
>       |       ^~~
> access_modifiers.cpp:20:13: error: ‘void A::setBar(int)’ is private within this context
>    20 |   a.setBar(3);
>       |             ^
> access_modifiers.cpp:11:8: note: declared private here
>    11 |   void setBar(int barIn){
>       |        ^~~~~~
> ~~~
> {: .output}
> </li>
> <li markdown="1">
> The following compiler error is generated:
> ~~~
> access_modifiers.cpp: In function ‘int main()’:
> access_modifiers.cpp:19:5: error: ‘int A::bar’ is private within this context
>    19 |   a.bar=2;
>       |     ^~~
> access_modifiers.cpp:10:7: note: declared private here
>    10 |   int bar;
>       |       ^~~
> ~~~
> {: .output}
> </li>
> </ol>
> > ## Solution
> > <ol type="a">
> > <li markdown="1">
> > **NO**: the program actually fails to compile since both class members `bar` and `setBar` are declared as private, they can not be accessed by functions which are not members of the `A` class.
> > </li>
> > <li markdown="1">
> > **YES**: both class members `bar` and `setBar` are private and can not be accessed outside class `A` member functions.
> > </li>
> > <li markdown="1">
> > **NO**: while it is true that `bar` can not be accessed outside, the member function `setBar` is also a private member of the `A` class.
> > </li>
> > <li markdown="1">
> > **NO**: while it is true that `setBar` can not be accessed outside, the member function `bar` is also a private member of the `A` class.
> > </li>
> > </ol>
> {: .solution}
{: .challenge}
