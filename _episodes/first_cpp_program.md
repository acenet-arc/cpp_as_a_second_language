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
> There are a couple ways that nano can display line number/column information. Which methods are available will depend on your version of Nano.
> <ol>
> <li markdown="1">
> While in nano press `alt`+`c` to display line number and column information for the line the cursor is currently on. This works for this particular nano session and on the version of nano on our **training cluster**.
> </li>
> <li markdown="1">
> Line numbers can be toggled on/off using `alt`+`shift`+`#`. This is nice, but only works on newer versions of nano.
> </li>
> <li markdown="1">
> When starting nano the `-l` option can be used to tell nano to display line numbers along the left hand side. Again only works with newer versions of nano.
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
> Note that `set linenumbers` will only work on newer versions of nano while `set constantshow` will work on older versions of nano also.
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

> ## What is a class?
> Is a class:<br/>
> <ol type="a">
> <li markdown="1">
> a variable which can have multiple members like a struct
> </li>
> <li markdown="1">an object which can have multiple members like a struct
> </li>
> <li markdown="1">a datatype which can have multiple members like a struct
> </li>
> <li markdown="1">a datatype which can have only a single value like `int`,`float`,etc.
> </li>
> </ol>
> > ## Solution
> > <ol type="a">
> > <li markdown="1">**NO**: while a class can have multiple members like a struct, a class defines a new datatype where as a variable or object are the instantiation of that class or datatype.
> > </li>
> > <li markdown="1">**NO**: while an object has a class type, the object is not the class its self.
> > </li>
> > <li markdown="1">**Yes**: a class is a kind of datatype that can have multiple members.
> > </li>
> > <li markdown="1">**No**: classes can have multiple members, it is possible that they only have one member but they are not restricted to holding a single value.
> > </li>
> > </ol>
> {: .solution}
{: .challenge}