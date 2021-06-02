#include <iostream>
#include <list>
#include <unordered_map>
#include <array>
#include <cstdbool>
#include "lru.hpp"

#define region_size (sizeof(regions) / sizeof(regions[0]))

struct MemoryRegion
{
	int *val_ptr;
};

MemoryRegion regions[5];

std::list<int> mem(region_size, -1);
std::unordered_map<int, std::list<int>::iterator> lru_cache;

LRU::LRU(){
	init();
}

void LRU::init()
{	
	auto it = mem.begin();
	for(int i = 0; i < region_size; ++i)
	{
		regions[i].val_ptr = &*it;
	}
}
	
void LRU::updateCache(int val)
{
	auto it = lru_cache[val];
	lru_cache.erase(val);
	lru_cache.insert({val ,it});
}
	
inline bool LRU::isFull()
{
	return (mem.back() != -1);
}
	
void LRU::evict_recent_and_add(int val)
{
	auto it = lru_cache.begin(); 
	it = std::next(it, region_size - 1);
	
	auto tmp_it = it->second;
	*it->second = val;
	lru_cache.erase(it);
	lru_cache[val] = tmp_it;
}
	
void LRU::put(int val)
{	

	auto iter = lru_cache.find(val);
	if(iter != lru_cache.end()){
		updateCache(val);
	}else{
		if(!isFull()){
			mem.push_front(val);
			regions[size].val_ptr = &mem.front();
			lru_cache[val] = mem.begin();
			mem.erase(--mem.end());
		}else{
			evict_recent_and_add(val);
		}
	}
	if(!isFull())
		size++;
}

class LRU lru;

MemoryRegion *find(int val)
{	
	lru.put(val);	
	return &regions[0];
}

int main()
{
	std::cout<<"Hello"<<std::endl;

return 0;
}
