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

	// checa se a página location da memória está sendo usada
	bool used(unsigned int location);

	// libera página da memória
	void free(unsigned int location);

	// aloca página na memória
	void alocate(unsigned int location);

	// acessa página da memória
	mempage access(unsigned int location);

	// encontra pagina usada menos recentemente (LRU)
	unsigned int leastRecent();

	unsigned int mem_pages;
	unsigned int top;
private:
	mempage* pages;
};


#endif // !MEMORY_H

