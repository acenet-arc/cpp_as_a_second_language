---
layout: episode
title: "First C++ program"
teaching: 5
exercises: 5
questions:
- "How do you create a C++ program?"
objectives:
- "Create, compile, and run your first C++ program"
keypoints:
- "`g++` can be used to compiler and link C++ programs."
- "Program execution starts in the `main` function."
- "`std::cout` allows you to write strings to the terminal using the `<<` operator."
- "A class is a datatype."
- "An object is a particular instance of that datatype or class."
- "Namespaces group names and help to avoid name clashes."
---

Here we will create our first C++ program and dissect its components and in doing so will introduce some important concepts that we will dive into in more detail as we go.

## Creating a first C++ program
~~~
$ nano hello.cpp
~~~
{: .bash}

~~~
#include <iostream>

int main(){
  std::cout<<"Hello, world!\n";
}
~~~

Use the GNU C++ compiler `g++` from the [GNU Compiler Collection (GCC)](https://gcc.gnu.org/) to build it:
~~~
$ g++ hello.cpp -o hello
$ ./hello
~~~
{: .bash}

~~~
Hello, world!
~~~
{: .output}

## Dissecting your first C++ program
### Objects and classes
* `cout` is an object, an object can be thought of as a particular instantiation of a class, think: `int a;` `a` is an instantiation of an `int`.
* A class is very much like a C struct with some associated functions.
* Classes can be thought of as a data type just like a struct can.
* `cout` is of type `ostream`, `ostream` is a class(see: [https://www.cplusplus.com/reference/iostream/cout/](https://www.cplusplus.com/reference/iostream/cout/))
* `#include <iostream>` includes a file that defines the `ostream` class and the `cout` object

### Namespaces
* Namespaces are a way of grouping names:
  * names of functions, names of constants, names of objects, etc.
  * `std` is the "standard" namespace which contains the C++ standard library [https://www.cplusplus.com/reference/](https://www.cplusplus.com/reference/)
  * Helps to avoid name clashes, e.g. `std::list` versus some custom made `list` class
  
### Operators
* `<<` is an operator. Like `+`, `-`, etc.
* Operators can behave differently depending on the data type/class they operate on. 
* For example the `<<` operator will shift all the bits of a basic type (e.g. `int`, `char `etc.) to the left a given amount.
* For a complete list of operators with explanations: [http://www.cplusplus.com/doc/tutorial/operators/](http://www.cplusplus.com/doc/tutorial/operators/)

> ## Nano line numbers
> When compiling programs a compiler usually reports errors it encounters by line number so it is particularly important to be able to find a particular line in your editor.
>
> There are a couple ways that nano can display line number/column information.
> <ol>
> <li markdown="1">
> Line numbers can be toggled on/off using `alt`+`shift`+`#`
> </li>
> <li markdown="1">
> When starting nano the `-l` option can be used to tell nano to display line numbers along the left hand side.
> </li>
> <li markdown="1">
> While in nano press `alt`+`c` to display line number and column information for the line the cursor is currently on. This work for this particular nano session.
> </li>
> <li markdown="1">
> Tell nano to always display line numbers and current line information:
> ~~~
> $ nano ~/.nanorc
> ~~~
> {: .bashrc}
> and enter the following two lines and save and exit
> ~~~
> set linenumbers
> set constantshow
> ~~~
> </li>
> </ol>
{: .callout}

> ## Useful Nano shortcuts
> Here are some shortcuts that are helpful while editing text in nano
>
> <ul>
> <li markdown="1">
> `alt`+`a`: mark or select text starting from where the cursor is when these keys are pressed to where you move the cursor. Then selected text can be cut, or pasted over.
> </li>
> <li markdown="1">
> `ctl`+`k`: cut text
> </li>
> <li markdown="1">
> `ctl`+`u`: uncut (e.g. paste) previously cut text either from nano or elsewhere
> </li>
> <li markdown="1">
> `alt`+`u`: undo last changes
> </li>
> </ul>
{: .callout}
