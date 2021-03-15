include <iostream>
#include <vector>

template <typename T>
void displayVector(std::vector<T>* vec){
  for(int i=0;i<vec->size();++i){
    std::cout<<(*vec)[i]<<" ";
  }
  std::cout<<"\n";
}

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
