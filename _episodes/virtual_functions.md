---
layout: episode
title: "Virtual functions"
teaching: 10
exercises: 5
questions:
- "What is a virtual function?"
- "What is polymorphism?"
objectives:
- "Explore virtual functions"
- "See polymorphism in action"
keypoints:
- "Polymorphism allows different member functions to be called depending on the object's base class"
- "Polymorphism is achieved using the `virtual` keyword in function declarations"
---

Previously we have been displaying multiple vectors at once, it would be nice to also include a label when we output them to identify that particular vector. Lets add a new function which takes a pointer to a `Vector` and a name and displays both.

First copy our last program to a new file and open the new file to create this function.
~~~ 
$ cp inheritance.cpp virtual.cpp
$ nano virtual.cpp
~~~
{: .bash}

<div class="gitfile" markdown="1">
~~~
class Vector{...};

class Vec3:public Vector{...};

void nameAndDisplay(const char* name,Vector& v){
  std::cout<<name<<"=";
  v->display();
}

int main(){
 Vec3 a,b;
 a.data[0]=10;
 b.data[0]=22;
 Vector c=a+b;
 nameAndDisplay("a",a);
 nameAndDisplay("b",b);
 nameAndDisplay("c",c);
}
~~~
[virtual.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/pre_virtual.cpp)
</div>

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
Looking at the output we can see that the `display` member function of the original `Vector` class is being called even in the case of `a` and `b` which are declared as `Vec3`'s. What is going on here? When we call our `nameAndDisplay` function our `Vec3`s are being converted to `Vector`s. Since `Vec3` inherits the `Vector` class this is actually allowed and is one of the nice things about inheritance. Without any extra work we can still use our `nameAndDisplay` function with our `Vec3` objects even though they get converted to `Vectors` for use in the function. However, that means that in our `nameAndDisplay` function, the wrong `display` member function is getting called.

It would be nice if we did not have to create two `nameAndDisplay` functions one for each of `Vector` and `Vec3`. It turns out there is a way to do that. Using the `virtual` keyword. The `virtual` keyword can be used on a class member function to indicate that, at run time, it should check to see if this object is a class which was derived from the base class. If so, check to see if the `virtual` member function has been overridden in the derived class, if it has use that instead of the member function in the base class. In other words, we add the `virtual` keyword to our `display` member function in the `Vector` class and our `nameAndDisplay` function will call either the `display` defined in the `Vector` class if the passed object was originally a `Vector` or it will call the `display` member function defined in the `Vec3` class if the object was originally a `Vec3`. That's a pretty cool trick for a statically typed language like C++!

Lets try it out.

~~~
$ nano virtual.cpp
~~~
{: .bash}
<div class="gitfile" markdown="1">
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

void nameAndDisplay(const char* name,Vector& v){...}

int main(){
 Vec3 a,b;
 a.data[0]=10;
 b.data[0]=22;
 Vector c=a+b;
 nameAndDisplay("a",a);
 nameAndDisplay("b",b);
 nameAndDisplay("c",c);
}
~~~
[virtual.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/virtual.cpp)
</div>
Note that the only addition we have made is the `virtual` keyword before the `void display()` function declaration in the `Vector` class.

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

When the pointer to a `Vector` class is treated differently depending on whether it points to a `Vector` class, or child classes is something that is referred to as **polymorphism**.

This is a pretty cool thing, in that you can have a bunch of objects of different classes being handled by the same function with potentially different behaviours if they all inherit the same base class.

> ## Manual polymorphism
> I would like to point out that this sort of polymophic flexibility can be achieved in a somewhat manual sense using the basic features of C. The example below utilizes `void*` pointers and casting between different pointer types. The file shown bellow, `polymanual.cpp`, demonstrates one way this similar level of flexibility of inheritance and virtual functions could be achieved. It should also be noted that while the below code may seem like it would obviously be less perfromant than the virtual method, this difference might not be as large as you think based purely on the amount of lines of code, as polymophism using the `virtual` keyword does still require run time lookups into virtual function tables. If possible it is advised to avoid `virtual` member functions in performance critical code, and of course always profile to know what is performance critical.
> ~~~
> #include <iostream>
> 
> enum ObjectType{
>   ObjectType_A,
>   ObjectType_B,
> };
> 
> struct A{
>   int value;
> };
> 
> struct B{
>   int value;
> };
> 
> struct Object{
>   ObjectType type;
>   void* obj;
> };
> 
> void displayObject(Object* objToDisplay){
>   switch(objToDisplay->type){
>     case ObjectType_A:{
>       A* temp=(A*)objToDisplay->obj;
>       std::cout<<"A: value="<<temp->value<<"\n";
>       break;
>     }
>     case ObjectType_B:{
>       B* temp=(B*)objToDisplay->obj;
>       std::cout<<"B: value="<<temp->value<<"\n";
>       break;
>     }
>   }
> }
> 
> int main(){
>   A a;
>   a.value=20;
>   B b;
>   b.value=30;
>   
>   Object obj;
>   obj.type=ObjectType_A;
>   obj.obj=&a;
>   displayObject(&obj);
>   
>   obj.obj=&b;
>   obj.type=ObjectType_B;
>   displayObject(&obj);
> }
> ~~~
> 
> ~~~
> $ g++ polymanual.cpp -o polymanual
> $ ./polymanual
> ~~~
> {: .bash}
> ~~~
> A: value=20
> B: value=30
> ~~~
> {: .output}
{: .callout}
