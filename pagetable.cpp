#include "pagetable.hpp"
#include <iostream>

pagetable::pagetable(int n_entries)
{
	this->n_entries = n_entries;
	entries = new entry[n_entries];
}

pagetable::~pagetable()
{
	delete[] entries;
}

void pagetable::set_entry(int position,int frame)
{
	entries[position].frame = frame;
	entries[position].valid = true;
}


int pagetable::get_frame(int position)
{
	//se a referencia é valida, retorne ela
	if (entries[position].valid)
	{
		return entries[position].frame;
	}
	//caso contrário: pagefault
	return -1;
}

void pagetable::print_entry(int i)
{
	std::cout<< "References:"<<entries[i].frame<<" Valid:"<<entries[i].valid<<"\n";
}

int pagetable::find_valid(int frame)
{
	for (int i = 0; i < n_entries; i++)
	{
		if (entries[i].frame == frame && entries[i].valid)
		{
			return i;
		}
	}
	//falhou em achar
	return -1;
}

void pagetable::write_op(int position)
{
	entries[position].dirty = true;
}

bool pagetable::is_dirty(int position)
{
	return entries[position].dirty;
}

void pagetable::set_invalid(int position)
{
	entries[position].valid = false;
}

