#ifndef FIFO_H
#define FIFO_H
#include <string>
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

void readOperationFIFO(int position, memory& m, pagetable& p, statistics& stat)
{
    //ve se pagina ja est� na mem�ria
    int frame = p.get_frame(position);
    //caso contr�rio, aloque a pagina
    if (frame == -1)
    {
        allocatePageFIFO(m, p, position, stat);
        frame = p.get_frame(position);
    }
    //acesse a mem�ria
    m.access(frame);
    //return mem[frame].data
}

void writeOperationFIFO(int position, memory& m, pagetable& p, statistics& stat)
{
    //ve se pagina ja est� na mem�ria(tenta fazer escrita)
    int frame = p.write_op(position);
    //caso contr�rio, aloque a pagina
    if (frame == -1)
    {
        allocatePageFIFO(m, p, position, stat);
        //faz a escrita
        frame = p.write_op(position);
    }
    //acesse a mem�ria
    m.access(frame);
    //mem[frame].data=data
}


#endif // !FIFO_H
