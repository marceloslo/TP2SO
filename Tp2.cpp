#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <chrono>

#include "pagetable.hpp"
#include "auxiliaries.hpp"
#include "fifo.hpp"
#include "lru.hpp"
#include "memory.hpp"

using namespace std;

void readOperation(int position, memory& m, pagetable& p, statistics& stat)
{
	if(stat.debug.compare("debug")==0)
	{
		printf("Reading entry %x of table\n",position);
	}
    //ve se pagina ja está na memória
    int frame = p.get_frame(position);
    //caso contrário, aloque a pagina
    if (frame == -1)
    {
		if(stat.debug.compare("debug")==0)
		{
			printf("Reading failed, invalid reference, alocating page\n");
		}
		if(stat.reposition.compare("fifo") == 0)
		{
			allocatePageFIFO(m, p, position, stat);
		}
		else if (stat.reposition.compare("lru") == 0)
		{
			allocatePageLRU(m, p, position, stat);
		}
        frame = p.get_frame(position);
		if(stat.debug.compare("debug")==0)
		{
			printf("Reading %x again\n",position);
		}
    }
	if(stat.debug.compare("debug")==0)
	{
		printf("Accessing page %d of memory for reading\n",frame);
	}
    //acesse a memória
    m.access(frame);
    //return mem[frame].data
}

void writeOperation(int position, memory& m, pagetable& p, statistics& stat)
{
	if(stat.debug.compare("debug")==0)
	{
		printf("Writing to entry %x of table\n",position);
	}
    //ve se pagina ja está na memória(tenta fazer escrita)
    int frame = p.write_op(position);
    //caso contrário, aloque a pagina
    if (frame == -1)
    {
		if(stat.debug.compare("debug")==0)
		{
			printf("Writing failed, invalid reference, alocating page\n");
		}
		if(stat.reposition.compare("fifo") == 0)
		{
			allocatePageFIFO(m, p, position, stat);
		}
		else if (stat.reposition.compare("lru") == 0)
		{
			allocatePageLRU(m, p, position, stat);
		}
        //faz a escrita
        frame = p.write_op(position);
    }
	if(stat.debug.compare("debug")==0)
	{
		printf("Accessing page %d of memory for write\n",frame);
	}
    //acesse a memória
    m.access(frame);
    //mem[frame].data=data
}


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
		{
			if(stat.debug.compare("debug")==0)
			{
				printf("Badly formated instruction\n");
			}
            continue;
		}
        position = address >> s;
		//use address and rw to query
        if (rw == 'R')
        {
            //data = readOperation(frame,m)
            readOperation(position, m, p, stat);
        }
		else
        {
            //writeOperation(position,data)
            writeOperation(position, m, p, stat);
        }
    }
}


int main(int argc,char*argv[])
{
	statistics stat;
    //USANDO OS ARGUMENTOS EXTERNOS
    stat.reposition=(argc>1) ? argv[1] : "lru";
    stat.filename=(argc>2) ? argv[2] : "compilador.log";
    stat.page_size= (argc>3) ? atoi(argv[3]) * 1024 : 4*1024;//bytes
    stat.mem_size= (argc > 4) ? atoi(argv[4]) * 1024 : 128*1024;//bytes
    // use time para tempo e debug para todas informações da execução
    stat.debug= (argc>5) ? argv[5] : "";
	
	auto start_time = std::chrono::system_clock::now();
	
/*
    // Testando sem console
    stat.reposition = "lru";
    stat.filename = "compilador.log";
    stat.page_size=4 * 1024;
    stat.mem_size=128 * 1024 ;
	*/
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
	auto end_time = std::chrono::system_clock::now();
	if(!stat.debug.empty())
	{
		cout<<"Elapsed time(seconds): "<<(chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time)).count()/1000<<endl;
	}
    /*teste breve
    unsigned address = 0x0041f7a0;

    allocatePage(m,p,address>>s,mem_pages);
    printf("Address: %x\n",address);
    cout << "Page number:" << hex << (address >> s) << " "; p.print_entry(address >> s);
    cout<<"Physical memory:"<<m.used[p.get_frame(address>>s)]<<" Offset:"<<getOffset(address,s)<<endl;*/
    return 0;
}
