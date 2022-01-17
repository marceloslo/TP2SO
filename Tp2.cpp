#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

#include "pagetable.hpp"
#include "auxiliaries.hpp"
#include "fifo.hpp"
#include "lru.hpp"
#include "memory.hpp"

using namespace std;


void readFile(statistics& stat, unsigned int s, unsigned int n_entries, pagetable& p, memory& m, FILE* instructions)
{
    unsigned address;
    char rw;
    unsigned int position;
    int nargs;
    //data *data;
    //le instruções
    while ((nargs=fscanf(instructions, "%x %c", &address, &rw)) != EOF)
    {
        //se a linha está com formato incorreto, continue execução sem considerá-la
        if (nargs != 2)
            continue;

        position = address >> s;
        // first in first out reposition
        if (stat.reposition.compare("fifo") == 0)
        {
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
        //least recently used reposition
        else if (stat.reposition.compare("lru") == 0)
        {
            //use address and rw to query
            if (rw == 'R')
            {
                //data = readOperation(frame,m)
                readOperationLRU(position, m, p, stat);
            }
            else
            {
                //writeOperation(position,data)
                writeOperationLRU(position, m, p, stat);
            }
        }
    }
}


int main(int argc,char*argv[])
{
    /* USANDO OS ARGUMENTOS EXTERNOS
    string op=argv[1];
    string filename=argv[2];
    unsigned int page_size= atoi(argv[3]) * 1024;//bytes
    unsigned int mem_size=atoi(argv[4) * 1024;//bytes
    */

    // Testando sem console
    statistics stat;
    stat.reposition = "lru";
    stat.filename = "compilador.log";
    stat.page_size=4 * 1024;
    stat.mem_size=128 * 1024 ;
    unsigned int s = bytes(stat.page_size);
    unsigned int n_entries=(int)pow(2,(32-s));
    unsigned int mem_pages = stat.mem_size/stat.page_size;
    pagetable p(n_entries);
    memory m(mem_pages);

    //read input
    FILE *file;
    file = fopen(stat.filename.c_str(),"r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        return 0;
    }
    cout<<"Executando o simulador...\n";
    readFile(stat, s, n_entries, p, m, file);
    fclose(file);
    stat.printstatistics();


    /*teste breve
    unsigned address = 0x0041f7a0;

    allocatePage(m,p,address>>s,mem_pages);
    printf("Address: %x\n",address);
    cout << "Page number:" << hex << (address >> s) << " "; p.print_entry(address >> s);
    cout<<"Physical memory:"<<m.used[p.get_frame(address>>s)]<<" Offset:"<<getOffset(address,s)<<endl;*/
    return 0;
}
