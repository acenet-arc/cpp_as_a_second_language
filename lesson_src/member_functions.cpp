#include <iostream>

class Vector{
public:
  int size;
  int* data;
  void display(){
    std::cout<<"Vector: size="<<size;
    std::cout<<", contents=(";
    for(int i=0;i<size-1;++i){
      std::cout<<data[i]<<",";
    }
    std::cout<<data[size-1]<<")\n";
  }
};

int main(){
  Vector a;
  a.size=10;
  a.data=new int[a.size];
  a.data[9]=15;
  a.display();
  delete[] a.data;
}
