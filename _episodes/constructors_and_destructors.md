---
layout: episode
title: "Constructors and destructors"
teaching: 10
exercises: 10
questions:
- "Can class members be automatically initialized?"
- "Are there different types of constructors?"
- "Can resources be automatically freed?"
objectives:
- "Add a constructors to allocate memory for our object."
- "Add a destructor to deallocated memory for our object."
keypoints:
- "Constructors are called when objects are first created."
- "Destructors are called when objects go out of scope."
- "Copy constructors are called when a new object is initialized from an existing object."
---

We are still allocating and deallocating the memory for our Vector in the main function, however it would be nice to move this into the class so we don't have to think about it where we use our Vector. The best way to do this is to use constructors and destructors.

Constructors and destructors are special member functions that are called automatically when an object is created or destroyed. Objects are destroyed when they go out of scope, think execution moves outside of the set of curly braces `{...}` where the object was declared.

**Constructors** can be used to initialize class members and allocate memory or resources that your class might need.

**Destructors** are used for clearning up resources that your constructor may have acquired, such as freeing memory or closing files.

If you don't create constructors or destructors the compiler will create them for you. However depending on the complexity of your class they might not be good enough for your situation. When the compiler creates these constructors and destructors it assumes there aren't any special resources that need to be cleaned up, for example dynamically allocated memory.

In our situation we actually want to dynamically allocate memory in our constructor(s) and free it in our destructor. In this case we need to do this ourselves.

### Types of constructors
There are different types of constructors, which makes use of the C++ function overloading feature mentioned previously which allows multiple functions with the same name to be declared and are distinguished by the number and type of arguments they take.

* **Default**: has the form `A()` and is used when no parameters are given e.g. `A a;`.
* **Parameterized**: has the form `A(int a, int b)` and is used in statements like `A a(10,15);`.
* **Copy**: has the form `A(const A& a_in)` and constructs a new object from an existing e.g. in statements like `A a;A b=a;`.<br/> The `&` in the parameter list of a C++ function indicates that the object should be passed by reference rather than by value. This works quite similarly to passing a pointer in C as `const A* a_in` except that in the body of the function you can use the `.` operator rather than the `->` operator.

In our case we can't rely on the constructors the compiler creates because we want to move our allocation of memory into the constructors. In each of the three different constructors we need to allocate enough memory to hold our newly constructed vector.

In our case it will be very important to create a **copy** constructor or bad things can happen as the compiler created copy constructor will just copy our data pointer from one object to the next. Meaning that two objects will point to the same underlying data. This can have bad implications when we want to free that memory later in the destructor, leading to something called a **double free**, meaning it will try to free the same memory twice which isn't allowed.

## Add the three constructor types
Lets start by copying our last program as a starting point
~~~
$ cp function_overload.cpp constructor.cpp
$ nano constuctor.cpp
~~~
{: .bash}

and then add the three types of constructors. 

Note that the `...` in the lines `void display(){...}` and `void display(int num){...}` below are used to indicate that there is still code in those functions but we aren't showing them to improve readability and help highlight the changes we made.

<div class="gitfile" markdown="1">
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
  
  void display(){...}
  void display(int num){...}
};

int main(){
  Vector a(10);
  a.data[9]=15;
  Vector b=a;
  b.data[8]=10;
  a.display();
  b.display();
  delete [] a.data;
  delete [] b.data;
}
~~~
[constructor.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/constructor.cpp)
</div>
~~~
$ g++ constructor.cpp -o constructor
$ ./constructor
~~~
{: .bash}
~~~
Vector: size=10, contents=(0,0,0,0,0,0,0,0,0,15)
Vector: size=10, contents=(0,0,0,0,0,0,0,0,10,15)
~~~
{: .output}
Above we have added all three constructor types `Vector()`, `Vector(int size_in)`, and `Vector(const Vector& vec_in)`. We also moved the allocation of the member `data` into the constructors.

The `const` keyword used in the copy constructor indicates that we will not modify the `vec_in` object within the copy constructor, which is actually a requirement of the copy constructor.

As you can see from the output our two `Vectors` `a` and `b` have completely independent memory in which to store their data and that the `15` stored in the last element of `a` was copied over to the `b` vector.

If we use the default constructor for our `Vector` class (e.g. `Vector a;`) we will get a vector of `size=1`, if we use the parameterized constructor (`Vector a(15);`) we will get a vector of the size we specify.

### When is a copy constructor called
A copy constructor is invoked in a statement like `A a; A b=a;` However, it isn't used in the following situation `A a; A b; b=a;` instead the `=` operator is used. We will learn more about the `=` operator in the next lesson.

> ## Initializer lists
> You can also use an initializer list in your constructor, as shown below to initialize class member variables.
> ~~~
> class A{
> public:
>   int foo;
>   int bar;
>   A():foo(10),bar(5){
>   }
> }
> ~~~
{: .callout}

> ## Using placement new to invoke a constructor
> The new operator we saw previously can be use to call a constructor on already allocated memory. When used in this way it is called the placement new operator. You could use it in the following way:
> ~~~
> Vector* v;
> v=malloc(sizeof(Vector));
> new(v) Vector();
> ~~~
> This allocates enough memory to hold a `Vector` and sets `v` to point to it. However, the constructor isn't called until the `new` operator is called with the pointer `v` passed to it.
{: .callout}

## Add a destructor
Lets start by making a copy of our last program
~~~
$ cp constructor.cpp destructor.cpp
$ nano destructor.cpp
~~~
{: .bash}
and edit it to look like the following
<div class="gitfile" markdown="1">
~~~
#include <iostream>

class Vector{
public:
  int size;
  int* data;
  
  ~Vector(){
    delete [] data;
  }
  
  Vector(){...}
  Vector(int size_in){...}
  Vector(const Vector& vec_in){...}
  void display(){...}
  void display(int num){...}
};

int main(){
  Vector a(10);
  a.data[9]=15;
  Vector b=a;
  b.data[8]=10;
  a.display();
  b.display();
}
~~~
[destructor.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/destructor.cpp)
</div>
Here we have added the destructor `~Vector()` which deallocates the memory allocated by the constructor. We no longer need to worry about allocating and deallocating memory where we create our vector objects, it happens automatically when we declare them and when they go out of scope.
~~~
$ g++ destructor.cpp -o destructor
$ ./destructor
~~~
{: .bash}
~~~
Vector: size=10, contents=(0,0,0,0,0,0,0,0,0,15)
Vector: size=10, contents=(0,0,0,0,0,0,0,0,10,15)
~~~
{: .output}

> ## When is the copy constructor called?
> ~~~
>  1 #include <iostream>
>  2 
>  3 class Vector{
>  4 public:
>  5   int size;
>  6   int* data;
>  7   
>  8   ~Vector(){
>  9     std::cout<<"Destructor\n";
> ...
> 11   }
> 12   Vector(){
> 13     std::cout<<"Default constructor\n";
> ...
> 16   }
> 17   Vector(int size_in){
> 18     std::cout<<"Parameterized constructor with size_in="<<size_in<<"\n";
> ...
> 21   }
> 22   Vector(const Vector& vec_in){
> 23     std::cout<<"Copy constructor\n";
> ...
> 29   }
> 30   void display(){...}
> 38   void display(int num){...}
> 58 };
> 59
> 60 int main(){
> 61   Vector a(10);
> 62   a.data[9]=15;
> 63   Vector b=a;
> 64   b.data[8]=10;
> 65   a.display();
> 66   b.display();
> 67 }
> ~~~
> Above we have taken our `destructor.cpp` program and added print outs in the three constructors and the destructor. If we compile and run this program we get the following output:
> ~~~
> Parameterized constructor with size_in=10
> Copy constructor
> Vector: size=10, contents=(0,0,0,0,0,0,0,0,0,15)
> Vector: size=10, contents=(0,0,0,0,0,0,0,0,10,15)
> Destructor
> Destructor
> ~~~
> {: .output}
> During the execution of which line of the `main` function does the output `Copy constructor` get generated?
> <ol type="a">
> <li markdown="1">line 61
> </li>
> <li markdown="1">line 62
> </li>
> <li markdown="1">line 63
> </li>
> </ol>
> > ## Solution
> > <ol type="a">
> > <li markdown="1">
> > **NO**: this is when the first line of output gets generated `Parameterized constructor with size_in=10`. This line uses the parameterized constructor.
> > </li>
> > <li markdown="1">
> > **NO**: this line actually generates no output at all. On this line the class member `data` has its ninth element assigned the value `15`.
> > </li>
> > <li markdown="1">
> > **YES**: This line creates a new `Vector` object and initializes it using the copy constructor from the existing `a` `Vector` object.
> > </li>
> > </ol>
> {: .solution}
{: .challenge}

> ## What happens if we don't have a copy constructor?
> Lets comment out our copy constructor and find out
> ~~~
>  1 #include <iostream>
>  2 
>  3 class Vector{
>  4 public:
>  5   int size;
>  6   int* data;
>  7   
>  8   ~Vector(){...}
> 
> 12   Vector(){...}
> 
> 17   Vector(int size_in){...}
> 
> 22   //Vector(const Vector& vec_in){
> 23   //  std::cout<<"Copy constructor\n";
> 24   //  size=vec_in.size;
> 25   //  data=new int[size];
> 26   //  for(int i=0;i<vec_in.size;++i){
> 27   //    data[i]=vec_in.data[i];
> 28   //  }
> 29   //}
> 30   void display(){...}
> 
> 38   void display(int num){...}
> 
> 58 };
> 59
> 60 int main(){
> 61   Vector a(10);
> 62   a.data[9]=15;
> 63   Vector b=a;
> 64   b.data[8]=10;
> 65   a.display();
> 66   b.display();
> 67 }
> ~~~
> Then compile and run.
> ~~~
> $ g++ destructor.cpp -o destructor
> $ ./destructor
> ~~~
> {: .bash}
> > ## Solution
> > We get the following output:
> > ~~~
> > Parameterized constructor with size_in=10
> > Vector: size=10, contents=(0,0,0,0,0,0,0,0,10,15)
> > Vector: size=10, contents=(0,0,0,0,0,0,0,0,10,15)
> > Destructor
> > Destructor
> > free(): double free detected in tcache 2
> > Aborted (core dumped)
> > ~~~
> > {: .output}
> > Except for the last two lines, the output looks similar to before. These last two lines are generated some time after the second destructor gets called. These lines indicate that we have the **double free** issue mentioned above. That is the same memory, in this case the `data` member of both the `a` and `b` objects point to the same memory. This happened because  line 63 invokes the compiler generated copy constructor which just does a straight member by member copy from object `a` to the new object `b`.  When the destructor gets called we try to free the memory pointed to by the `data` member twice, resulting in this error.
> {: .solution}
{: .challenge}