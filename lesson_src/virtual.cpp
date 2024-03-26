#include <iostream>

class Vector{
public:
  int size;
  int* data;
  Vector operator=(const Vector& rhs){
    if(&rhs!=this){
      delete [] data;
      data=new int[rhs.size];
      size=rhs.size;
      for(int i=0;i<rhs.size;++i){
        data[i]=rhs.data[i];
      }
    }
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
  ~Vector(){
    delete[] data;
  }
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
    if(num<size){
      std::cout<<data[numToDisplay-1]<<"...)\n";
    }
    else{
      std::cout<<data[numToDisplay-1]<<")\n";
    }
  }
  virtual void display(){
     display(size);
  }
};

class Vec3:public Vector{
public:
  Vec3(): Vector(3){
  };
  void display(){
    std::cout<<"Vec3: ("<<data[0]<<","<<data[1]<<","<<data[2]<<")\n";
  }
};

void nameAndDisplay(const char* name,Vector& v){
  std::cout<<name<<"=";
  v.display();
}

int main(){
  Vec3 a,b;
  a.data[0]=10;
  b.data[0]=22;
  Vector c=a+b;
  nameAndDisplay("a",a);
  nameAndDisplay("b",b);
  nameAndDisplay("c",c);
}
