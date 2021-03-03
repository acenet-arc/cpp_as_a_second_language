---
layout: episode
title: "Virtual functions"
teaching: 10
exercises: 10
questions:
- "What is a virtual function?"
objectives:
- ""
keypoints:
- ""
---

Previously we have been displaying multiple vectors at once, it would be nice to also include a label when we output them to identify that particular vector. Lets add a new function which takes a pointer to a `Vector` and a name and displays both.

First copy our last program to a new file and open the new file to create this function.
~~~ 
$ cp inheritance.cpp virtual.cpp
$ nano virtual.cpp
~~~
{: .bash}

~~~
class Vector{...};

class Vec3:public Vector{...};

void nameAndDisplay(char* name,Vector* v){
  std::cout<<name<<"=";
  v->display();
}

int main(){
 Vec3 a,b;
 a.data[0]=10;
 b.data[0]=22;
 Vector c=a+b;
 char nameA[]={"a\0"};
 nameAndDisplay(nameA,&a);
 char nameB[]={"b\0"};
 nameAndDisplay(nameB,&b);
 char nameC[]={"c\0"};
 nameAndDisplay(nameC,&c);
}
~~~
Lets test out this new function.
~~~
$ g++ virtual.cpp -o virtual
$ ./virtual
~~~
{: .bash}
~~~
a=Vector: size=3, contents=(10,0,0)
b=Vector: size=3, contents=(22,0,0)
c=Vector: size=6, contents=(10,0,0,22,0,0)
~~~
{: .output}
Looking at the output we can see that the `display` member function of the original `Vector` class is being called here even in the cases for `a` and `b` which are declared as `Vec3`'s what is going on here. Well what is happening is that when we call our `nameAndDisplay` function our `Vec3`s are being converted to `Vector`s. Since `Vec3` inherits the `Vector` class this is actually allowed and is one of the nice things about inheritance. However, that means that in our `nameAndDisplay` function the wrong `display` member function is getting called. It would be nice if there was a way to not have to create two `nameAndDisplay` functions one for each of `Vector` and `Vec3`. It turns out there is a way to do that. Using the `virtual` keyword. The `virtual` keyword can be used on a class member function to indicate that, at run time, it should check to see if this object is a class which was derived from the base class. If so, check to see if the `virtual` member function has been overridden in the derived class, if it has use that instead of the member function in the base class. In other words, we add the `virtual` keyword to our `display` member function in the `Vector` class and then our `nameAndDisplay` function will call either the `display` defined in the `Vector` class if the passed object was originally a `Vector` or it will call the `display` member function defined in the `Vec3` class if the object was originally a `Vec3`.

Lets try it out.

~~~
$ nano virtual.cpp
~~~
{: .bash}

~~~
class Vector{
  int size;
  int* data;
  
  Vector operator+(Vector& rhs){...};
 ~Vector(){...}
  Vector(){...}
  Vector(int size_in){...}
  Vector(const Vector& vec_in){...}
  virtual void display(){...}
  void display(int num){...}
};

class Vec3:public Vector{...};

void nameAndDisplay(char* name,Vector* v){...}

int main(){
 Vec3 a,b;
 a.data[0]=10;
 b.data[0]=22;
 Vector c=a+b;
 char nameA[]={"a\0"};
 nameAndDisplay(nameA,&a);
 char nameB[]={"b\0"};
 nameAndDisplay(nameB,&b);
 char nameC[]={"c\0"};
 nameAndDisplay(nameC,&c);
}
~~~
Lets compile and run it and see what we get.
~~~
$ g++ virtual.cpp -o virtual
$ ./virtual
~~~
{: .bash}
~~~
a=Vec3: (10,0,0)
b=Vec3: (22,0,0)
c=Vector: size=6, contents=(10,0,0,22,0,0)
~~~
{: .output}