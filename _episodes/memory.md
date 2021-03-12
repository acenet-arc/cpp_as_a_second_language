---
layout: episode
title: "Memory"
teaching: 10
exercises: 5
questions:
- "How do I allocate memory?"
- "How do I free memory?"
objectives:
- "Learn to work with dynamic memory"
keypoints:
- "Every use of `new`/`new[]` should be match by a `delete`/`delete []`."
- "The amount of dynamic memory allocated can be determined at runtime."
- "Need to be careful about incorrect access and especially modification of memory."
---

C and C++ are fairly low level languages and as such you can manage your programs memory yourself. This means that you can have great control over how much memory is used and when and careful planning and usage can lead to lower memory usage and more performant code than in other languages which manage this for you. However, care must be take to avoid issues such as:
1. memory leaks (memory allocated but not freed) which if inside some looping code could cause your program to run out of memory and crash
2. writing outside of memory owned by your program (segmentation fault and crash)
3. writing past array bounds but still into memory owned by your program (no crash, but possibly subtly unexpected result may occur)

## Allocation
In C you use `malloc` to allocate memory, but in C++ you should use `new`. It is possible to use `malloc` but some additional steps need to be taken to ensure it works properly with C++ classes.

There are two flavors of `new` the straight up `new` keyword, or the array version `new[]`. The first will declare a new variable/object of the given type like:
~~~
#include <iostream>

int main(){
  int* a=new int;
  *a=10;
  std::cout<<"a="<<*a<<"\n";
}
~~~

Here we declare a pointer to an `int`, `a` and allocate enough memory using `new` to hold an integer.

However, if we wanted enough memory to hold some given number of integers we would create a dynamic array with the `new[]` for that number of integers. Lets do that now.
~~~
$ cp hello.cpp memory.cpp
$ nano memory.cpp
~~~
{: .bash}

and then modify it to look like the following:

<div class="gitfile" markdown="1">
~~~
#include <iostream>

int main(){
  int size=10;
  int* a=new int[size];
  a[9]=15;
  std::cout<<"a[9]="<<a[9]<<"\n";
}
~~~
[memory.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/memory_allocate.cpp)
</div>

~~~
$ g++ memory.cpp -o memory
$ ./memory
~~~
{: .bash}
~~~
a[9]=15
~~~
{: .output}

In this example we allocate enough memory to hold 10 integers and the pointer `a` points to the beginning of this memory. The `[]` operator is used to index into a given part of this memory and allow one to access and modify that memory.

Note that memory allocated using `new` or `new[]` is not freed if pointers that point to it go out of scope. This is different than memory that is allocated in statements like `int a[10];`. This can allow great flexibility in how the memory is used. By passing a pointer to different parts of your code it can access and modify that memory without having to copy the data. This can have huge performance improvements and avoids wasted memory. However it does mean that the programmer is responsible for keeping track of the memory and freeing it.

Generally it is a good idea to match every `new` and `new[]` allocation with a matching `delete` or `delete[]`. In the above program we haven't done this, and in this simple situation it actually doesn't cause any problems. When our program ends that memory is freed up, however if that new were inside a large loop we would have some serious issues.

## Deallocation
To deallocate or free memory in `C` the `free` function is used, however, in C++ you should use the `delete` operator instead. It also comes in two flavors `delete` and `delete[]` to match the two flavors of `new` and `new[]`. Lets free the memory we allocated above.

<div class="gitfile" markdown="1">
~~~
#include <iostream>

int main(){
  int size=10;
  int* a=new int[size];
  a[9]=15;
  std::cout<<"a[9]="<<a[9]<<"\n";
  delete[] a;
}
~~~
[memory.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/memory_deallocate.cpp)
</div>

~~~
$ g++ memory.cpp -o memory
$ ./memory
~~~
{: .bash}
~~~
a[9]=15
~~~
{: .output}
Because we used the `new[]` version we must use the `delete[]` version to match it. Notice that we don't have to tell it the size of the array, this information is tract for us.

> ## Debug tools
> It is possible to use a tool to help find bugs in your code. These tools usually let you inspect the values of variables in your code, step through execution line by line, set beak points in your code to stop execution and let you examine variables. They will also help in detecting some memory issues like accessing memory your program doesn't have access to (e.g. Segmentation faults) and stop on the line where it occurs.
> ### gdb
> One such tool is `gdb` the GNU debugger. It can be used from the command line.
> To use it you first need to compile your code including the `-g` option.
> ~~~
> $ g++ -g memory.cpp -o memory
> ~~~
> {: .bash}
> Then run the newly created executable using `gdb`.
> ~~~
> $ gdb memory
> ~~~
> {: .bash}
> You can the type `help` to show information about how to use `gdb`. For more details see: [gdb documentation](https://www.gnu.org/software/gdb/documentation/).
> 
> ### Valgrind
> Is a collection of useful tools which allows checking for memory errors, performance profiling, and more. See [valgrind.org](https://valgrind.org/) for more information.
{: .callout}
