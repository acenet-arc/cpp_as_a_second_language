#include <iostream>

class Vector{
public:
  int size;
  int* data;
};

int main(){
  Vector a;
  a.size=10;
  a.data=new int[a.size];
  a.data[9]=15;
  std::cout<<"a.size="<<a.size<<"\n";
  std::cout<<"a.data[9]="<<a.data[9]<<"\n";
  delete[] a.data;
}
