#ifndef LRU_H
#define LRU_H
#include <string>
#include "memory.hpp"
#include "pagetable.hpp"
#include "auxiliaries.hpp"

void allocatePageLRU(memory& m, pagetable& p, unsigned int position, statistics& stat)
{
    unsigned int top = m.top;
    if (m.used(top))
    {
        // encontra a pagina que foi usada menos recentemente
        top = m.leastRecent();
        // remove essa pagina
        swapoutPage(top, m, p, stat);
    }
    //coloca nova pagina no lugar
    swapinPage(top, m, position, p, stat);
    m.top++;
    if (m.top >= m.mem_pages)
    {
        m.top = m.top % m.mem_pages;
    }
}



#endif // !LRU_H

