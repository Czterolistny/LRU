#include <iostream>
#include "lru.hpp"

LRU lru;

extern 	MemoryRegion regions[region_size];

MemoryRegion *find(int val)
{	
	lru.put(val);	
	return &regions[0];
}

int main()
{
	std::cout<<"Hello"<<std::endl;
	find(10);
	MemoryRegion *mr = find(20);
	
	for(int i = 0; i < region_size; ++i){
		std::cout<< *mr[i].val_ptr <<std::endl;	
	}

return 0;
}