#ifndef FIFO_H
#define FIFO_H
#include <string>
#include "memory.hpp"
#include "pagetable.hpp"
#include "auxiliaries.hpp"

void allocatePageFIFO(memory& m, pagetable& p, unsigned int position, statistics& stat)
{
    if (m.used(m.top))
    {
        //remove primeira pagina a ser alocada dentre aquelas da memoria
        swapoutPage(m.top, m, p, stat);
    }
    //coloca nova pagina no lugar
    swapinPage(m.top, m, position, p, stat);
    m.top++;
    if (m.top >= m.mem_pages)
    {
        m.top = m.top % m.mem_pages;
    }
}


#endif // !FIFO_H
