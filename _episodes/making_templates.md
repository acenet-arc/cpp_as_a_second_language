---
layout: episode
title: "Making templates"
teaching: 10
exercises: 10
questions:
- "How do you create your own templates?"
objectives:
- ""
keypoints:
- ""
---
In the last episode we created a function to display a `std::vector<int>` however one of the nice things about `std:vector` is that it can be used with different data types, however our function can only be used with the `int` type, can we use templates to create our own function template? Yes we can, so lets do that.
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
To create a template you use the `template` keyword followed by an open and close angle bracket `<>`. Inside those angle brackets we need to specify one or more template parameters. These parameters can sort of be thought of like the macro `defines` and how they can be used to replace some text by the preprocessor before compilation for example:
~~~
#define MAX_SIZE 10
int array[MAX_SIZE]
~~~
where `MAX_SIZE` is replaced by 10 by the preprocessor.

In our case we are using `T` as a parameter for a datatype within our template function `displayVector`. We can replace any location we needed to specify a type with the `T`. We could have even specified more template parameters if we wanted separating them with commands like `template<typename T, typename U>`.

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


## Further topics on templates
I may or may not want to talk about these other aspects of templates, probably want to do some more work on the earlier sections first
* Class Templates
* Template specialization
* Non-type parameters

## Further fairly important topics in C/C++
* [fstream](http://www.cplusplus.com/reference/fstream/) (file input/output)
* [assert](http://www.cplusplus.com/reference/cassert/assert/) (very good programming practice, not just a C++ topic but also a C topic)