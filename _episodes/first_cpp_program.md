---
layout: episode
title: "First C++ program"
teaching: 2
exercises: 0
questions:
- ""
objectives:
- ""
keypoints:
- ""
---

~~~
$ nano hello.cpp
~~~
{: .bash}

~~~
#include <iostream>

int main(){
  std::cout<<”Hello, world!\n”;
}
~~~

~~~
$ g++ hello.cpp -o hello
$ ./hello
~~~
{: .bash}

~~~
Hello, world!
~~~
{: .output}


