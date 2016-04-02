# MemoryPool
A simple Memory Pool with test cases in C++

To run other test cases go and uncomment which test case to run.

->Issues needing to be addressed

 * When allocating memory there is an issue if the space is not exactly the same size but is only a few bytes larger creating a free space that cannot fit our node idea.  The code will start to rewrite the next area of allocated memory and was not taken into account durring this assignment.

->Overall style and notes

 * I added another int* to the class for Pool to keep track of our firstNode instead of having the pointer directly to pool being used, this seemed safer.

 * When storing the hexographical information for the memory location in an int, I used a long int because this stored the data without any loss of precision.

 * I created many test cases that test all the allocation and deallocation scenarios.  In the terminal there will be debug information denoted by a 1 or 2 which signifies which path the data took while going through deallocation.  This is used to help me test every case but also will help you find what is going on more quickly.

 * When allocating there is a line that I have commented out that will print to the terminal what is getting allocated and where it is located and then will print the new free space of where it came from.  This can be used at your leisure.

 * I created a print_size() function inside Pool to print the size of the first Node in our memory pool.  This was used as a check at the end of each case to make sure our array was back to empty before quiting the program


