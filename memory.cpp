#include "memory.hpp"
#include <chrono>
#include <iostream>
using namespace std::chrono;

memory::memory()
{
	mem_pages = 0;
	top = 0;
	pages = nullptr;
}

memory::memory(unsigned int size)
{
	mem_pages = size;
	top = 0;
	pages = new mempage[size];
}

memory::~memory()
{
	delete [] pages;
}

bool memory::used(unsigned int location)
{
	return pages[location].used;
}

void memory::free(unsigned int location)
{
	pages[location].used = false;
}

void memory::alocate(unsigned int location)
{
	pages[location].last_access = high_resolution_clock::now();
	pages[location].used = true;
}

mempage memory::access(unsigned int location)
{
	pages[location].last_access = high_resolution_clock::now();
	return pages[location];
}

unsigned int memory::leastRecent()
{
	high_resolution_clock::time_point oldest=high_resolution_clock::now();
	unsigned int oldest_position=0;
	duration<double> time_span;
	for (unsigned int i = 0; i < mem_pages; i++)
	{
		time_span = duration_cast<duration<double>>(oldest - pages[i].last_access);
		if (time_span.count()>=0)
		{
			oldest = pages[i].last_access;
			oldest_position = i;
		}
	}
	top = oldest_position;
	return oldest_position;
}

