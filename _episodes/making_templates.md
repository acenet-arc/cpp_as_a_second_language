---
layout: episode
title: "Making templates"
teaching: 10
exercises: 5
questions:
- "How do you use templates to create generic functions that work with any type?"
- "What is a template parameter?"
objectives:
- "Learn about the template keyword and template parameters."
- "Create our own template function that works with any type that the `<<` operator is overloaded to support."
keypoints:
- "Create a new template with the `template` keyword."
- "Template parameters are specified inside `<>` brackets after the `typename` keyword."
- "Template parameters can be used in place of types and will be replace with actual types as needed at compile time."
---
In the last episode we created a function to display a `std::vector<int>` however one of the nice things about `std:vector` is that it can be used with different data types, however our function can only be used with the `int` type, can we use templates to create our own function template? Yes we can, so lets do that.

To create a template you use the `template` keyword followed by an open and close angle bracket `<>`. Inside those angle brackets we need to specify one or more template parameters. These parameters can be thought of like the macro `defines` and how they can be used to replace some text by the preprocessor before compilation for example:
~~~
#define MAX_SIZE 10
int array[MAX_SIZE]
~~~
where `MAX_SIZE` is replaced by 10 by the preprocessor.

~~~
$ cp stl_vector.cpp template.cpp
$ nano template.cpp
~~~
{: .bash}

<div class="gitfile" markdown="1">
~~~
#include <iostream>
#include <vector>

template <typename T>
void displayVector(std::vector<T>* vec){
  for(int i=0;i<vec->size();++i){
    std::cout<<(*vec)[i]<<" ";
  }
  std::cout<<"\n";
};

int main(){
  std::vector<int> a;
  a.push_back(0);
  a.push_back(1);
  a.push_back(2);
  displayVector(&a);
  
  std::vector<double> b;
  b.push_back(0.1);
  b.push_back(1.1);
  b.push_back(2.1);
  displayVector(&b);
}
~~~
[template.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/template.cpp)
</div>

In our case we are using `T` as a parameter for a datatype within our template function `displayVector`. We can replace any location we needed to specify a type with a `T`. We could have even specified more template parameters if we wanted separating them with commas like `template<typename T, typename U>`.

In our example we are making use of the fact that the `<<` operator on an output stream knows how to output both an `int` and a `double`.

~~~
$ g++ template.cpp -o template
$ ./template
~~~
{: .bash}
~~~
0 1 2
0.1 1.1 2.1
~~~
{: .output}
