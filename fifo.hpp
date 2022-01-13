#ifndef FIFO_H
#define FIFO_H
#include <string>
#include "pagetable.hpp"
#include "auxiliaries.hpp"

void allocatePageFIFO(memory& m, pagetable& p, unsigned int position, statistics& stat)
{
    if (m.used[m.top])
    {
        swapoutPage(m.top, m, p, stat);
    }
    swapinPage(m.top, m, position, p, stat);
    m.top++;
    if (m.top >= m.mem_pages)
    {
        m.top = m.top % m.mem_pages;
    }
}

void readOperationFIFO(int position, memory& m, pagetable& p, statistics& stat)
{
    //ve se pagina ja está na memória
    int frame = p.get_frame(position);
    //caso contrário, aloque a pagina
    if (frame == -1)
    {
        allocatePageFIFO(m, p, position, stat);
        frame = p.get_frame(position);
    }
    //return mem[frame].data
}

void writeOperationFIFO(int position, memory& m, pagetable& p, statistics& stat)
{
    //ve se pagina ja está na memória
    int frame = p.get_frame(position);
    //caso contrário, aloque a pagina
    if (frame == -1)
    {
        allocatePageFIFO(m, p, position, stat);
        frame = p.get_frame(position);
    }
    //muda dirty bit
    p.write_op(position);
    //mem[frame].data=data
}

//first in first out reposition
void fifo(statistics& stat, unsigned int s, unsigned int n_entries, pagetable& p, memory& m, FILE* instructions)
{
    unsigned address;
    char rw;
    unsigned int position;
    int frame;
    //data *data;
    //le instruções
    while (fscanf(instructions, "%x %c", &address, &rw) != EOF)
    {
        position = address >> s;
        //use address and rw to query
        if (rw == 'R')
        {
            //data = readOperation(frame,m)
            readOperationFIFO(position, m, p, stat);
        }
        else
        {
            //writeOperation(position,data)
            writeOperationFIFO(position, m, p, stat);
        }
    }
}


#endif // !FIFO_H
