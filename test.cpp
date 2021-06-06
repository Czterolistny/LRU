#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LRU_TEST

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cstdbool>
#include "lru.hpp"

MemoryRegion regions[region_size];

class LRU_Test : public LRU
{

public:
	
	LRU_Test(): LRU(){
	}
	void print_all()
	{
		std::cout<<"map: ";
		auto it = mem.begin();
		for(;it != mem.end(); ++it)
			std::cout<< *it <<" ";
		std::cout<<std::endl;
		
		std::cout<<"iter: ";
		auto iter_it = iter_list.begin();
		for(;iter_it != iter_list.end(); ++iter_it){
			std::cout<< iter_it->first<<"->"<< *(iter_it->second) <<" ";
		}
		std::cout<<std::endl;
		
		std::cout<<"hash: ";
		auto map_it = umap.begin();
		for(;map_it != umap.end(); ++map_it){
			std::cout<< map_it->first;
			if( map_it->first != *map_it->second->second ){
				std::cout<<"->"<<*map_it->second->second<<" ";
			}else
				std::cout<<" ";
		}
		
		std::cout<<std::endl<<std::endl;
	}
	
	void print_region()
	{	
		std::cout<<"region: ";
		for(int i = 0; i < region_size; ++i)
			std::cout<< *regions[i].val_ptr <<" ";
		std::cout<<std::endl;
	}
	
	int initTest(){
		
		for(int i = 0; i < region_size; ++i){
			if(*regions[i].val_ptr != -1){
				return -1;
			}
		}
		return 0;
	}
	
	int getLastRecent()
	{
		return *(--iter_list.end())->second;
	}
	
	int getFirstRecent()
	{
		return iter_list.begin()->first;
	}
	
	int getRegionVal(int pos_id)
	{
		return *regions[pos_id].val_ptr;
	}
	
};

LRU_Test lru;

BOOST_AUTO_TEST_SUITE( LRU_SUIT )

BOOST_AUTO_TEST_CASE( testInit )
{

	for(int i = 0; i < region_size; ++i){
		lru.put(i);
	}
	//regions should be 0-1-2-3-4
	int err = 0;
	for(int i = 0; i < region_size; ++i){
		if(*regions[i].val_ptr != i){
			err = -1;
		}
	}
	BOOST_CHECK(err == 0);
	
}

BOOST_AUTO_TEST_CASE( first_last_RecentElementTest )
{
	BOOST_CHECK(lru.getLastRecent() == 0);
	BOOST_CHECK(lru.getFirstRecent() == region_size - 1);
}

BOOST_AUTO_TEST_CASE( randomTest )
{
	lru.put(20);
	//regions should be 20-1-2-3-4
	BOOST_CHECK(lru.getLastRecent() == 1);
	BOOST_CHECK(lru.getFirstRecent() == 20);
	lru.put(1);
	BOOST_CHECK(lru.getFirstRecent() == 1);
	BOOST_CHECK(lru.getLastRecent() == 2);
	//Value 2 should be replaced
	int last = lru.getLastRecent();
	lru.put(30);
	//Last recent should be replaced by 30
	BOOST_CHECK(lru.getRegionVal(last - 1) != 2);
	BOOST_CHECK(lru.getRegionVal(lru.getLastRecent() - 1) == 30);
	lru.put(40);
	BOOST_CHECK(lru.getRegionVal(lru.getLastRecent() - 1) == 40);
}

BOOST_AUTO_TEST_SUITE_END()