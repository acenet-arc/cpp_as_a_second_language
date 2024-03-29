---
layout: episode
title: "Where does C++ fit in?"
teaching: 8
exercises: 0
questions:
- "How does C++ compare to other languages?"
- "What is C++ used for?"
- "When should I use C++?"
- "What is C++'s relationship to C?"
objectives:
- "Understand C++ role in programming"
keypoints:
- "C++ is a low level language offering great flexibility."
- "C++ allows the creation of very performant programs."
- "If starting from scratch use a higher level language such as Python and convert performance critical parts to C++."
- "Do not try to use all the features of C++"
---

## C/C++ as compared to other languages
* C/C++ is a powerful low level language which allows you to work closer to the hardware, a little above assembly.
  * With great power comes great responsibility
  * Write fast code slowly
* Other modern languages, C#, Java, Python, etc. generally provide higher level control of computers
  * Less responsibility but also less power/flexibility
  * Write slow code fast
* Fortran
  * Fast (comparable to well written C/C++)
  * Specialized for numerical computing
  * Awkward for some tasks (I/O, string manipulation, code reuse)
  * Smaller user community

## What is C/C++ used for?
C++ is used for lots of things, which is why it has a much larger user community than say Fortran for example.
* Operating systems: Windows, MacOS, iOS, Linux
* Web browsers: Firefox, Chrome
* Applications: Adobe Photoshop, Spotify, MySQL
* Games
* Research software

## When should I use C++?
If a program you are working on already uses C++, or uses C++ to write extensions. In new programs, if you aren't writing highly performance critical programs, something like Python might be a better choice. It is easy to use and you can write your programs much faster. When you find slow parts of your code use libraries that can do those parts faster, e.g. numpy. If there isn't a library for it, use Cython to generate C/C++ code from your python by adding type information to your variables. See our parallel computing summer school [materials on using Cython](https://acenet-arc.github.io/ACENET_Summer_School_Dask/cython/index.html) for more information about how to get started using Cython. While converting your Python code to Cython it can be useful to know some C/C++ and can give you more flexibility
in how you do it, for example you could write your performance critical bits directly using C++ as python modules.

## What does C++ add to C?
Three main components added:
* Function overloading: multiple functions can be defined with the same name which are distinguished by the type and number of arguments they are given.
* Classes: forms the basis for what is known as Object Oriented Programming (OOP)
* Templates: allows for generic programming, write code that can be used on multiple data types

There are certainly many other bits that C++ adds, but these are the conceptually most important additions.

## C and C++ interoperability
* You can often compile C programs as C++ programs (for comments/details see this [isocpp.org](https://isocpp.org/wiki/faq/c#is-c-a-subset) page on the topic).
* However, you can not compile C++ programs as C programs.

## Versions of C++ and its Complexity

Versions: C++98, C++03, C++11, C++14, C++17, C++20, C++23

Lots of additional components added in each iteration. The C++ language is vast and complex (one of the main [criticisms of the language](https://en.wikipedia.org/wiki/C%2B%2B#Criticism)) and it is not feasible to cover all the different ways things can be done and all the features from all the versions in just 4 hrs. However, we will cover the core concepts and language components and features that are present through many of the versions of C++ with the hope that this will provide a sufficient foundation to allow learning additional features and components of the language as needed.

Indeed **many professional developers who use C++ restrict themselves to a subset of features** to reduce the complexity of code and allow more people to understand and use it. I would highly recommend this approach to help keep yourself sane.

