#include <iostream>
#include <vector>

void displayVector(std::vector<int>& vec){
  for(int i=0;i<vec.size();++i){
    std::cout<<vec[i]<<" ";
  }
  std::cout<<"\n";
}

int main(){
  std::vector<int> a;
  a.push_back(0);
  a.push_back(1);
  a.push_back(2);
  displayVector(a);
}
