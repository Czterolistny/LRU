#ifndef __LRU__
#define __LRU__

class LRU{
	int size = 0;

public:
	LRU();
	
	void init();
	
	void updateCache(int val);
	
	inline bool isFull();
	
	void evict_recent_and_add(int val);
	
	void put(int val);
};

#endif