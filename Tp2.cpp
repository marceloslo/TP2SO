#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

//pagetable primitiva(idealmente viraria uma classe mais bem feita em um .hpp)
typedef struct pagetable
{
    bool *valid;
    unsigned int *f;
}pagetable;

//memoria primitiva(idealmente viraria uma classe mais bem feita em um .hpp)
typedef struct memory
{
    bool *used;
}memory;

//obtem o s = número de bytes pouco significativos que serão removidos para encontrar a entrada da tabela de pags
unsigned int bytes(unsigned int page_size)
{

    unsigned int s, tmp;
    /* Derivar o valor de s: */
    tmp = page_size;
    s = 0;
    while (tmp>1)
    {
    tmp = tmp>>1;
    s++;
    }

    return s;
}

//obtem o offset do par (pag,offset)
unsigned int getOffset(unsigned address, unsigned int s)
{
    //obtem o offset a partir dos S digitos menos significativos
    unsigned mask=0;
    while(s!=0)
    {
        mask = (mask<<1) + 1;
        s--;
    }
    return address & mask;
}

//tenta alocar uma pagina
bool allocatePage(memory &m,pagetable &p,unsigned int position,unsigned int mem_pages)
{
    int i;
    for(i=0;i<mem_pages;i++)
    {
        //conseguiu alocar uma pagina
        if(!m.used[i])
        {
            p.f[position]=i;
            p.valid[position]=true;
            m.used[i]=true;
            return true;
        }
    }
    //falhou em alocar uma página
    return false;
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
    string op = "fifo";
    string filename = "compilador.log";
    unsigned int page_size=4 * 1024;
    unsigned int mem_size=16384 * 1024 ;
    unsigned int s = bytes(page_size);
    unsigned int n_entries=pow(2,(32-s));
    unsigned int mem_pages = mem_size/page_size;
    /*read input
    FILE *file;
    file = fopen(filename,"r");
    unsigned address;
    char rw;
    cout<<"Executando o simulador...\n";
    while(fscanf(file,"%x %c",&address,&rw)!= EOF)
    {
        printf("%x %c \n",address,rw);//use address and rw to query
    }
    fclose(file);
    */

    //teste breve
    unsigned address = 0x0041f7a0;
    pagetable p;
    memory m;
    m.used = new bool[mem_pages];
    p.f = new unsigned int[n_entries];
    p.valid = new bool[n_entries];
    allocatePage(m,p,address>>s,mem_pages);
    printf("Address: %x\n",address);
    cout<<"Page number:"<<hex<<(address>>s)<<" "<<"References:"<<p.f[address>>s]<<" Valid:"<<p.valid[address>>s]<<endl;
    cout<<"Physical memory:"<<m.used[p.f[address>>s]]<<" Offset:"<<getOffset(address,s)<<endl;
    delete [] p.f;
    delete [] p.valid;
    return 0;
}
