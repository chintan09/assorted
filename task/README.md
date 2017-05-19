# README #

### Testing ###
Running make from the folder will generate a binary `accel`. 
This binary is used for passing accel inputs and generating outputs. 

For example, 
`./accel input/test1\[1\].bin test1.out`

Note: Tested on a Mac running macOS 10.12.4 and a linux machine.

### Folder Structure ###
* main.c - As name suggests, contains main function & code for read, write and processing the data.
* circular-buf.c / .h - A generic circular buffer implementation. Used for getting last 32 samples in the end. 
* min-heap.c / .h - A generic binary min-heap implementation. Used for getting sorted max values in the end. 

### Design ###

* Processing the input
Since the accel data is of size 12 bits, we need to be careful on how we parse inputs. 
For an odd element access, we need to read two bytes and then store the other nibble for the next even element. 
Example, first read would mean reading two bytes where as reading for second element requires reusing last nibble 
plus the new one byte read. 

fread() size could be optimized further, for example by reading 3 bytes at once and then dividing up that into
three elements. But I didn't aim to optimize this as in real system we would be getting raw 12 bit data from accel 
driver and won't require to parse a binary file. 


* Getting sorted max 32 elements
This is a place where I spent most time in optimizing & design. 
Questions considered were, do you keep a sorted list at all times or keep a list of max 32 elements and then sort 
in the end. 

Since we require a sorted list in the end, I decided to keep in memory list of max elements and sort in the end. 
For this binary heap structure seemed like an excellent choice, as it provides minimum element access in constant
time and we could do a sort in O(nlongn) in the end. 

Also under the hood, the heap uses a constant size memory (32 uint16_t in this case). So we know a predictable 
amount of memory usage. 

One concern for not using min heap was that it uses a recursion for heapify() in the cases of an insertion or deletion. 
However the call stack is not deep, and worst case it is equal to the height of the tree which is 5 in this case. 
I've optimized heapify() to make sure it is using as few variables possible on the stack.


* Getting last 32 elements
Circular buffer was an ideal choice here, as we can keep last 32 elements easily in the memory. 


### Time ###
Overall I would say coding took 3-4 hours, and couple of hours more to test with various inputs & writing documentation.

