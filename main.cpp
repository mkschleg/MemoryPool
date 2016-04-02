
#include "MemPool.h"
#include <iostream>



//case allocating something where there is no room for it!
int main(){
  Pool pool(200*sizeof(int));
  //allocate a good portion
  int *x = (int*)pool.allocate(150*sizeof(int));
  //try to allocate something larger than what can be held.
  int *y = (int*)pool.allocate(150*sizeof(int));

}


/*
//Case 1-a
//   One slot taken with memory space.
int main(){
  Pool pool(1024*1024);
  int* x= (int*)pool.allocate(1024*sizeof(int));
  *x=500;
  std::cout<<x<<std::endl
  	   <<*x<<std::endl;
  pool.deallocate(x);
  pool.print_size();
}


/*

//case 1-b and 2-a
//  1-b->dealocation of a slot not connected to the first Node but before
//  2-a->dealocation of a slot connected on both ends by free space.

int main (){
  Pool pool(1024*1024); // allocate 1M bytes
  // allocate 1024 int values
  int *x = (int *)pool.allocate(1024*sizeof(int));
  // allocate 1024 int values
  int *y = (int *)pool.allocate(1024*sizeof(int));
  // use x and y
  *x = 500;
  *y = 600;

  std::cout<<*x<<" "<<*y<<std::endl;

  // finally, deallocate them
  pool.deallocate(x);
  pool.deallocate(y);
  pool.print_size();
}
*/

//case 1-b, 2-b, 2-c
// 1-b->seen before
// 2-a->seen begore
// 2-b->slot connected at the front.
/*
int main(){
  Pool pool(1024*1024);
  // allocate 1024 int values
  int *x = (int *)pool.allocate(1024*sizeof(int));
  // allocate 1024 int values
  int *y = (int *)pool.allocate(1024*sizeof(int));
  // allocate 1024 int values
  int *z = (int *)pool.allocate(1024*sizeof(int));

  *x=500;
  *y=600;
  *z=700;

  pool.deallocate(x);
  pool.deallocate(y);
  pool.deallocate(z);
  pool.print_size();
}
*/

//Case 1-b, 2-d, 2-a, 2-a
// 2-d->Deallocate a slot not connected to any free space.

/*
int main(){
  Pool pool(1024*1024);
  // allocate 1024 int values
  int *x = (int *)pool.allocate(1024*sizeof(int));
  // allocate 1024 int values
  int *y = (int *)pool.allocate(1024*sizeof(int));
  // allocate 1024 int values
  int *z = (int *)pool.allocate(1024*sizeof(int));
  // allocate 1024 int values
  int *a = (int *)pool.allocate(1024*sizeof(int));

  *x=500;
  *y=600;
  *z=700;

  pool.deallocate(x);
  pool.deallocate(z);
  pool.deallocate(y);
  pool.deallocate(a);
  pool.print_size();
}

*/

//case memory pool is full!
// see what happens when the pool becomes too full to use anything!
/*
int main(){
  Pool pool(200*sizeof(int));
  //allocate all
  int *x = (int*)pool.allocate(200*sizeof(int));
  //try to allocate more
  int *y = (int*)pool.allocate(1*sizeof(int));
  //deallocate x
  pool.deallocate(x);
  pool.print_size();



}
*/
