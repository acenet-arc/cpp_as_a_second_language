---
layout: episode
title: "Inheritance"
teaching: 10
exercises: 10
questions:
- "What is inheritance?"
objectives:
- ""
keypoints:
- ""
---

We have so far been using our `Vector` class to store some number of integers, however what if we instead wanted to have a vector that we could use for 3D positions? Would we have to build a new class to do this from scratch or could we somehow reuse what we have already done for our more general `Vector` class. The answer is yes, and we can do that using **inheritance**.

As a starting point lets copy our previous program.
~~~
$ cp operator.cpp inheritance.cpp
$ nano inheritance.cpp
~~~
{: .bash}

Then modify it to add a new class `Vec3` which inherits our previous `Vector` class. Another way of saying this is that the `Vec3` class is a derived class from the base class `Vector`. You can specify that one class will inherit another classes member variables and functions by adding a `:` after the new class name in the class declaration followed by an access method `public`, `private` or `protected` and then the name of the class to be inherited.

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
  Vec3 p0;
  p0.data[0]=1;
  p0.data[1]=2;
  p0.data[2]=3;
  p0.display();
}
~~~


