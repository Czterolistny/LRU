#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LRU_TEST

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cstdbool>
#include "lru.cpp"

void print_all()
{
	std::cout<<"list: ";
	auto it = mem.begin();
	for(;it != mem.end(); ++it)
		std::cout<< *it <<" ";
	std::cout<<std::endl;
	
	std::cout<<"hash: ";
	auto lru_it = lru_cache.begin();
	for(;lru_it != lru_cache.end(); ++lru_it){
		std::cout<< lru_it->first;
		if( lru_it->first != *lru_it->second ){
			std::cout<<"->"<<*lru_it->second<<" ";
		}else
			std::cout<<" ";
	}
	std::cout<<std::endl;
}

void print_region()
{	std::cout<<"region ";
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
	auto it = lru_cache.begin();
	for(int i = 0; i < region_size - 1; ++i)
		it++;
	//std::cout<<"last"<< it->first <<std::endl;
	return it->first;
}

int getFirstRecent()
{
	return lru_cache.begin()->first;
}

int getRegionVal(int pos_id)
{
	return *regions[pos_id].val_ptr;
}

BOOST_AUTO_TEST_SUITE( LRU_SUIT )
	
BOOST_AUTO_TEST_CASE( testInit )
{

	BOOST_CHECK(initTest() == 0);
	for(int i = 0; i < region_size; ++i){
		find(i);
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

BOOST_AUTO_TEST_CASE( first_lastRecentElementTest )
{
	BOOST_CHECK(getLastRecent() == 0);
	BOOST_CHECK(getFirstRecent() == region_size - 1);
}

BOOST_AUTO_TEST_CASE( randomTest )
{
	find(20);
	//regions should be 20-1-2-3-4
	BOOST_CHECK(getLastRecent() == 1);
	BOOST_CHECK(getFirstRecent() == 20);
	find(1);
	BOOST_CHECK(getFirstRecent() == 1);
	BOOST_CHECK(getLastRecent() == 2);
	//Value 2 should be replaced
	int last = getLastRecent();
	find(30);
	//Last recent should be replaced by 30
	BOOST_CHECK(getRegionVal(last - 1) != 2);
	BOOST_CHECK(getRegionVal(getLastRecent() - 1) == 30);
	find(40);
	BOOST_CHECK(getRegionVal(getLastRecent() - 1) == 40);
}
BOOST_AUTO_TEST_SUITE_END()