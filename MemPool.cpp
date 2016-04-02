
#include <iostream>
#include "MemPool.h"


Pool::Pool(int size){

  //create the pool, or char array...
  pool = new unsigned char[size]; 
  
  //create temp which is a temp pointer to the beginning of pool
  int* temp=(int*)pool;
  
  //The value of *temp becomes the size of our array
  *temp=size;

  //Out puts the size and where the char array is!
  std::cout<<*temp<<" "<<temp<<std::endl;
  
  //Create a new ptr in our pool which points nowhere but is casted as a int*
  long* ptr_b=(long*)temp+1;
  *ptr_b=(long)NULL;
  
  //Create a new ptr in our pool which points nowhere but is casted as a int*
  long* ptr_f=ptr_b+1;
  *ptr_f=(long)NULL;
  
  //Set our firstNode as the beginning of our empty array
  firstNode=temp;

}


void* Pool::allocate (unsigned int bytes){
  //find where we can start allocating!
  int* temp=firstNode;

  if(firstNode==NULL){
    std::cout<<"You are out of memory!"<<std::endl;
    return NULL;
  }
  
    
  //This is the next node where we can store data
  long* next=(long*)temp+2;
  
  //We need this loop to be able to loop through to find an appropriate space
  //to allocate the variable.
  while(true){
    //This first if statement finds if the size of empty space is smaller than
    //the wanted size. If true we need to check if the next slot is available.
    //If so then we loop around and do the check again! If not there is no
    //space available for the variable and we just return the NULL pointer.
    if(*temp<bytes){
      if(*next==(long)NULL){
	std::cout<<"No space available for this item!"<<std::endl;
	return NULL;
      }
      else{
	temp=(int*) *next;
	next=(long*)temp+2;
      }
    }

    //This is when the variable fits perfectly into the slot! If our current
    //slot is the only node we need to show that our memory is full and set 
    //the firstNode to Null returning our memory.  If it is not but is the
    //firstNode we change the memory area pointed to in next as the new
    //firstNode. 
    else if(*temp==bytes){
      std::cout<<"Warning your memory is getting full!!"<<std::endl;
      if(temp==firstNode){
	if(*next==(long)NULL){
	  std::cout<<"You're memory is now full!"<<std::endl;
	  //*temp alread is equivalent to the bytes
	  //there are no more nodes!
	  //and we need to send the pointer to the memory slot!
	  firstNode=NULL;
	  return temp+1;
	}
	else{
	  firstNode==(int*)*next;
	  return temp+1;
	}
      }

      //Otherwise our node is in the middle and we need to close it and set
      //the appropriate pointers to the right places.
      else{

	long* ptr_b=(long*)temp+1;
	long* ptr_f=(long*)temp+2;

	int* tempb=(int*)*ptr_b;
	long* ptrb_f=(long*)tempb+2;
	*ptrb_f=*ptr_f;

	int* tempf=(int*)*ptr_f;
	long* ptrf_b=(long*)tempf+1;
	*ptrf_b=*ptr_b;

      }


    }

    //This is when our space does not exactly equal the space wanted and we
    //split the area.
    else{
      //std::cout<<"Help\n";
      void* ptr=temp+1;
      long* pb=(long*) temp+1;
      long* pf=pb+1;
      int* temp2=temp+1+(bytes/sizeof(int));
      *temp2=*temp-bytes-sizeof(int);
      *temp=bytes;
      long* ptr_b=(long*)temp2+1;
      *ptr_b=*pb;
      long* ptr_f=ptr_b+1;
      *ptr_f=*pf;
      firstNode=temp2;
      std::cout<<*temp<<' '<<ptr<<std::endl
	       <<*temp2<<' '<<temp2<<' '<<ptr_b<<' '<<ptr_f<<std::endl
	       <<firstNode<<std::endl;
      return ptr;  
      
    }
  }
}


//Deallocate function

void Pool::deallocate (void* ptr){ 
  int* a=(int*) ptr;
  a-=1;

  int* b=firstNode;
  long* next=(long*) b+2;

  //if the firstNode is full we know our vector is full and have to make a
  //a node that will become our firstNode
  if(firstNode==NULL){
    //size remains the same
    long* aptr_b=(long*)a+1;
    long* aptr_f=aptr_b+1;

    *aptr_b=(long)NULL;
    *aptr_f=(long)NULL;
    firstNode=a;

  }

  //If the slot comes before our firstNode

  else if(a<firstNode){
    std::cout<<"1";
    // std::cout<<a+(*a/sizeof(int))+1<<std::endl;

    //Is the slot connected to the first node?
    if(a+*a/sizeof(int)+1==b){
      //Node pointers for a
      std::cout<<"a"<<std::endl;
      int* aptr_b=a+1;
      int* aptr_f=aptr_b+1;
      //Node pointers for b
      int* c=b+1;
      int* d=c+1;
      *a=*a+*b+sizeof(int);
      *aptr_b=*c;
      *aptr_f=*d;
      firstNode=a;
    }
    //When it is not connected to the firstNode
    else{
      std::cout<<"b"<<std::endl;
      long* aptr_b=(long*) a+1;
      long* aptr_f=aptr_b+1;
      //The size stays the same! *a=*a
      *aptr_b=(long)NULL;
      *aptr_f=(long) b;
      firstNode=a;
    }
  }

  //When the deallocation spot comes after our firstNode
  else{
    //std::cout<<"else"<<std::endl;
    //Finding where our slot is in the memory
    while((long)a>*next){
      std::cout<<"loop"<<std::endl;
      if(a>(int*) *next){
	b=(int*) *next;
	next=(long*) b+2;
      }
    }
    long* bptr_b=(long*) b+1;
    long* bptr_f=bptr_b+1;

    int* x=(int*) *bptr_f;
    long* xptr_b=(long*) x+1;
    long* xptr_f=xptr_b+1;

    //These are our test cases
    std::cout<<"2";

    //connected on both sides to free space
    if(a==b+*b/sizeof(int)+1 and x==a+*a/sizeof(int)+1){
      std::cout<<"a"<<std::endl;
      *b=*b+*a+*x+2*sizeof(int);
      *bptr_f=*xptr_f;
    }
    //connected on the front side
    else if(a==b+*b/sizeof(int)+1){
      std::cout<<"b"<<std::endl;
      *b=*b+*a+sizeof(int);
    }
    //connected on the back side
    else if(x==a+*a/sizeof(int)+1){
      std::cout<<"c"<<std::endl;
      long* aptr_b=(long*)a+1;
      long* aptr_f=aptr_b+1;
      *a=*a+*x+sizeof(int);
      *aptr_b=*xptr_b;
      *aptr_f=*xptr_f;
    }
    //not connected to any free space
    else{
      std::cout<<"d"<<std::endl;
      long* aptr_b=(long*)a+1;
      long* aptr_f=aptr_b+1;
      //size stays the same! *a=*a
      *aptr_b=*xptr_b;
      *aptr_f=*bptr_f;
      *xptr_b=(long)a;
      *bptr_f=(long)a;
    }
  }
}

 
void Pool::print_size(){
  int* temp=firstNode;
  std::cout<<*temp<<" "<<temp<<std::endl;

}
