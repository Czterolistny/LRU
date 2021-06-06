#include <iostream>
#include <list>
#include <unordered_map>
#include <cstdbool>
#include "lru.hpp"

MemoryRegion regions[region_size];

LRU::LRU()
{
	for(int i = 0; i < region_size; ++i)
	{
		mem.push_front(-1);
		regions[i].val_ptr = &*mem.begin();
		iter_list.push_front({-1, mem.begin()});
	}
}

void LRU::updateCache(int val)
{
	auto map_it = umap.find(val);
	auto it = map_it->second->second;
		
	iter_list.erase(map_it->second);
	iter_list.push_front({val, it});
	umap[val] = iter_list.begin();
}
	
inline bool LRU::isFull()
{
	return (mem.back() != -1);
}
	
void LRU::evict_recent_and_add(int val)
{
	auto it = (--iter_list.end())->second;
	int _val = (--iter_list.end())->first;

	iter_list.pop_back();
	umap.erase(umap.find(_val)); 

	*it = val;
	iter_list.push_front({val, it});
	umap.insert({val, iter_list.begin()});
}
	
void LRU::put(int val)
{	

	auto map_it = umap.find(val);
	if(map_it != umap.end()){
		updateCache(val);
	}else{
		if(!isFull()){
			mem.push_front(val);
			regions[size].val_ptr = &mem.front();
			iter_list.push_front({val, mem.begin()});
			umap.insert({val, iter_list.begin()});
			mem.pop_back();
			iter_list.pop_back();
			size++;
		}else{
			evict_recent_and_add(val);
		}
	}
}


MemoryRegion *find(int val)
{	
	//lru.put(val);	
	return &regions[0];
}

/*int main()
{
	std::cout<<"Hello"<<std::endl;

return 0;
}*/
