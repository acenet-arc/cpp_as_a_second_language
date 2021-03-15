#include <iostream>

int main(){
  int size=10;
  int* a=new int[size];
  a[9]=15;
  std::cout<<"a[9]="<<a[9]<<"\n";
  delete[] a;
}
