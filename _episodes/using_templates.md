---
layout: episode
title: "Using templates"
teaching: 10
exercises: 10
questions:
- "What are templates?"
- "What is generic programming?"
- "What is the STL?"
- "How do you use the STL?"
objectives:
- ""
keypoints:
- ""
---

Templates allow for **generic types**. With templates it is possible to write a function or a class which can operator on any type of data. For example our `Vector` class only works with `int`s but using templates we could create it in such a way that it would work with any type, including types created by us or other programmers.

However, before we rush off and learn about creating templates to further generalize and extend our `Vector` class it turns out that there is already a class available in the [standard template library](https://www.cplusplus.com/reference/stl/) which does something similar. The standard template library (or STL) is composed of many different types of container classes, `vector`, `queue`, `stack`, `list`, `set`, `map` ... which can be used to contain basic or user created types. Lets try out using the STL `vector` class as an example of how to use these containers.

~~~
$ nano stl_vector.cpp
~~~
{: .bash}

<div class="gitfile" markdown="1">
~~~
#include <iostream>
#include <vector>

void displayVector(std::vector<int>* vec){
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
}
~~~
[stl_vector.cpp](https://github.com/acenet-arc/cpp_as_a_second_language/blob/master/lesson_src/stl_vector.cpp)
</div>
From looking at the [standard template library reference](https://www.cplusplus.com/reference/stl/) we can see that `std::vector` has a `push_back` member function, which allows us to add new items to the end of the vector. It has an `operator[]` which allows us to access items within the vector. Finally it has a `size` member function which lets us know how big the vector is.

~~~
$ g++ stl_vector.cpp -o stl_vector
$ ./stl_vector
~~~
{: .bash}
~~~
0 1 2
~~~
{: .output}

The container `std::vector` is a template class. What this means is that when we have a line in our code like `std::vector<int>` and we compile the code, the compiler will create a vector class that works for `int` data types at compile time based on the template provided in the 'vector' header we included with `#include <vector>`. If we had multiple different lines with `std::vector<some type>` a new version would be created at compile time for each type. This means that compile times can get rather lengthy when templates re used heavily. However, putting this time and work into compile time can sometimes result in faster code at run time as different code paths are decided at compile time rather than run time.


> ## Iterators
> It is common with the STL containers to support the 'iterator' method of looping over elements.
> While what we did above works just fine for `std::vector`, it will not work for containers which
> do not behave like arrays. For example it will not work for `std::list`, while the iterator method shown below will work for most STL containers (e.g. `array`, `list`, `map`, `set`, `vector`).
> ~~~
> std::vector<int> a;
> std::vector<int::iterator it;
> for(it=a.begin();it!=v.end();++it){
>   std::cout<<*it<<"\n";
> }
> ~~~
> For more information about using iterators see [this programming tutorial][https://www.cprogramming.com/tutorial/stl/iterators.html]
{: .callout}
