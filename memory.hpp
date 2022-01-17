#ifndef MEMORY_H
#define MEMORY_H
#include <chrono>
using namespace std::chrono;

struct mempage
{
	bool used=false;
	high_resolution_clock::time_point last_access;
};


class memory
{
public:
	memory();
	memory(unsigned int size);
	~memory();

	// checa se a p�gina location da mem�ria est� sendo usada
	bool used(unsigned int location);

	// libera p�gina da mem�ria
	void free(unsigned int location);

	// aloca p�gina na mem�ria
	void alocate(unsigned int location);

	// acessa p�gina da mem�ria
	mempage access(unsigned int location);

	// encontra pagina usada menos recentemente (LRU)
	unsigned int leastRecent();

	unsigned int mem_pages;
	unsigned int top;
private:
	mempage* pages;
};


#endif // !MEMORY_H

