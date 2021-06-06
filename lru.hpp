#ifndef __LRU__
#define __LRU__

#define region_size 5
	
struct MemoryRegion
{
	int *val_ptr;
};

class LRU
{
	int size = 0;
	
protected:
	std::list<int> mem;
	std::list<std::pair<int, std::list<int>::iterator>> iter_list;
	std::unordered_map<int, std::list<std::pair<int, std::list<int>::iterator>>::iterator> umap;

private:
	void updateCache(int val);
	inline bool isFull();
	void evict_recent_and_add(int val);
	
public:
	LRU();
	void put(int val);
};

#endif