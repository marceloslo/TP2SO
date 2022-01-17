#ifndef LRU_H
#define LRU_H
#include <string>
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

void readOperationLRU(int position, memory& m, pagetable& p, statistics& stat)
{
    //ve se pagina ja está na memória
    int frame = p.get_frame(position);
    //caso contrário, aloque a pagina
    if (frame == -1)
    {
        allocatePageLRU(m, p, position, stat);
        frame = p.get_frame(position);
    }
    //acesse a memória
    m.access(frame);
    //return mem[frame].data
}

void writeOperationLRU(int position, memory& m, pagetable& p, statistics& stat)
{
    //ve se pagina ja está na memória(tenta fazer escrita)
    int frame = p.write_op(position);
    //caso contrário, aloque a pagina
    if (frame == -1)
    {
        allocatePageLRU(m, p, position, stat);
        //faz a escrita
        frame = p.write_op(position);
    }
    //acesse a memória
    m.access(frame);
    //mem[frame].data=data
}



#endif // !LRU_H

