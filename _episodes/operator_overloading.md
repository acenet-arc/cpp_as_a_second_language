---
layout: episode
title: "Operator overloading"
teaching: 10
exercises: 10
questions:
- "Can we define operators for our classes?"
- "Where can you define operators?"
- "What operators can we define?"
- "Does the order matter?"
objectives:
- ""
keypoints:
- ""
---

It would be nice to be able to add two of our `Vectors` together into one vector. We can use operator overloading to create a new `+` operator that will add two of our `Vectors` together.

Operator overloading works similar to how function overloading works.

To create a new operator function you need to use the `operator` keyword followed by the operator you wish to overload, for example `operator+`. The rest of the syntax for creating an operator is similar to how a function is created.

Lets add a new `+` operator to our `Vector` class. 

~~~
$ cp destructor.cpp operator.cpp
$ nano operator.cpp
~~~

~~~
#include <iostream>

class Vector{
public:
  int size;
  int* data;
  Vector(){
    size=1;
    data=new int[size];
  }
  Vector(int size_in){
    size=size_in;
    data=new int[size];
  }
  Vector(const Vector& vec_in){
    size=vec_in.size;
    data=new int[size];
    for(int i=0;i<vec_in.size;++i){
      data[i]=vec_in.data[i];
    }
  }
  ~Vector(){
    delete [] data;
  }
  Vector operator+(Vector& rhs){
    Vector temp(size+rhs.size);
    int tempIndex;
    for(tempIndex=0;tempIndex<size;++tempIndex){
      temp.data[tempIndex]=data[tempIndex];
    }
    int rhsIndex=0;
    for(tempIndex=size;tempIndex<temp.size;++tempIndex){
      temp.data[tempIndex]=rhs.data[rhsIndex];
      ++rhsIndex;
    }
    return temp;
  }
  void display(){
    display(size);
  }
  void display(int num){

    int numToDisplay=size;
    if(num<size){
      numToDisplay=num;
    }

    std::cout<<"Vector: size="<<size;
    std::cout<<", contents=(";
    for(int i=0;i<numToDisplay-1;++i){
      std::cout<<data[i]<<",";
    }
    if(numToDisplay<size){
      std::cout<<data[numToDisplay-1]<<"...)\n";
    }
    else{
      std::cout<<data[numToDisplay-1]<<")\n";
    }
  }
};

int main(){
  Vector a(10);
  a.data[9]=15;
  Vector b=a;
  b.data[8]=10;
  a.display();
  b.display();
  Vector c=a+b;
  c.display();
}
~~~

This new `+` operator returns a `Vector` object and has a `Vector` object as an argument. In a statement like `Vector c=a+b;` where `a` and `b` are objects of type `Vector` you can think of it being like `Vector d=a.operator+(b);` and in fact you can actually use it like that if you wish. In this way `operator+` acts exactly like any other class member function, except that it can also be invoked directly like `a+b` rather that using the `.` and the full function name.

Lets try out the new operator
~~~
$ g++ operator.cpp -o operator
$ ./operator
~~~
{: .bash}
~~~
Vector: size=10, contents=(0,0,0,0,0,0,0,0,0,15)
Vector: size=10, contents=(0,0,0,0,0,0,0,0,10,15)
Vector: size=20, contents=(0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,10,15)
~~~
{: .output}
As we can see it added the two vectors together, with `a` preceding `b`.

Some operators can be declared as class member functions and some must be declared outside the class and some can be declared either way depending on how we want to use them. There are quite a few different operators, combining those with the different constructors, different data types, and how the operators work together can lead to quite a few different ways to create operators and you can really spend a lot of time trying to create operators to cover all the possible ways you might want to use operators with your class.

**Be careful not to spend too much time written code you might not need**.

For a list of operators and where each can be declared see:
[https://www.cplusplus.com/doc/tutorial/templates/](https://www.cplusplus.com/doc/tutorial/templates/)

> ## Mixing types with operators
> You can add additional overloaded versions of an operator to allow different types to be added together. For example if we wanted to be able to add an `Vector` object and an `int` we could add the following member function to our `Vector` class:
> ~~~
> Vector operator+(int rhs){
>   Vector temp(size+1);
>   
>   //copy data into temp with a for loop
>   
>   temp.data[size]=rhs;
>   return temp;
> }
> ~~~
> 
> Then we could add them like so:
> ~~~
> Vector a;
> Vector b=a+21;
> ~~~
> However, the order is important here we could not do the following:
> ~~~
> Vector a;
> Vector b=21+a;
> ~~~
> as it would try to call the `operator+` for an integer with a RHS of type `Vector` and that operator doesn't exist. We could add that in a slightly different way with a stand alone function.
> ~~~
> Vector operator+(int lhs,Vector rhs){
>   Vector temp(rhs.size+1);
>   temp.data[0]=lhs;
>   
>   //copy data into temp with a for loop starting a 1
>   
>   return temp;
> }
> ~~~
{: .callout}

> ## operator=
> We have so far used the `+` operator we defined like so, `Vector a,b; Vector c=a+b;`, however if we wanted to use it this way `Vector a,b,c; c=a+b;` we would have an issue. So far we have been relying on our copy constructor which gets called when we do `Vector c=`some other vector, however when we do `c=a+b` it will invoke the compiler created assignment operator (`operator=`) which will just copy our pointers over. Then when the destructors get called for the two `Vector` objects with the same pointer it will cause a double free error again like we got before we created our copy constructor for exactly the same reason. We then would need to add an assignement operator like below.
> ~~~
> void operator=(Vector rhs){
>   if(&rhs!=this){
>   
>     delete[] data;
>     data=new int[rhs.size];
>     size=rhs.size;
>     for(int i=0;i<rhs.size;++i){
>       data[i]=rhs.data[i];
>     }
>   }
> }
> ~~~
> Notice that we check to see if the rhs has the same address as the current object (self assignment), if so there is nothing to do. Otherwise we would delete our data and then try to assign the new data to the new uninitialized data to itself, this doesn't seem like a good thing to do.
{: .callout}
