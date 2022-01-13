#ifndef AUXILIARIES_H
#define AUXILIARIES_H
#include <string>
#include "pagetable.hpp"

using namespace std;
//struct auxiliar que simplesmente guarda as estatisticas relevantes e fornece uma impressão simples
struct statistics
{
    unsigned int mem_size;
    unsigned int page_size;
    string reposition;
    string filename;
    int page_faults = 0;
    int paginas_escritas = 0;

    void printstatistics()
    {
        cout << "Arquivo de entrada: " << filename << "\n";
        cout << "Tamanho da memoria: " << mem_size / 1024 << "KB\n";
        cout << "Tamanho das paginas: " << page_size / 1024 << "KB\n";
        cout << "Tecnica de reposicao: " << reposition << "\n";
        cout << "Paginas lidas: " << page_faults << "\n";
        cout << "Paginas escritas: " << paginas_escritas << "\n";
    }
};


//memoria primitiva(idealmente viraria uma classe mais bem feita em um .hpp)
typedef struct memory
{
    unsigned int mem_pages = 0;
    unsigned int top = 0;
    bool* used = nullptr;
}memory;

//obtem o s = número de bytes pouco significativos que serão removidos para encontrar a entrada da tabela de pags
unsigned int bytes(unsigned int page_size)
{

    unsigned int s, tmp;
    /* Derivar o valor de s: */
    tmp = page_size;
    s = 0;
    while (tmp > 1)
    {
        tmp = tmp >> 1;
        s++;
    }

    return s;
}

//obtem o offset do par (pag,offset)
unsigned int getOffset(unsigned address, unsigned int s)
{
    //obtem o offset a partir dos S digitos menos significativos
    unsigned mask = 0;
    while (s != 0)
    {
        mask = (mask << 1) + 1;
        s--;
    }
    return address & mask;
}

//tenta alocar uma pagina(sem reposição, exemplo)
bool allocatePage(memory& m, pagetable& p, unsigned int position)
{
    unsigned int i;
    for (i = 0; i < m.mem_pages; i++)
    {
        //conseguiu alocar uma pagina
        if (!m.used[i])
        {
            p.set_entry(position, i);
            m.used[i] = true;
            return true;
        }
    }
    //falhou em alocar uma página
    return false;
}

void swapoutPage(unsigned int memory_page, memory& m, pagetable& p, statistics& stat)
{
    int pagetable_entry;
    //update page table
    pagetable_entry = p.find_valid(memory_page);
    //se já houve escrita, incremente pags escritas
    if (p.is_dirty(pagetable_entry))
    {
        //reescreve no disco
        //disco.reescreve()
        //incremente pags escritas
        stat.paginas_escritas++;
    }
    //remove pagina da memoria
    m.used[memory_page] = false;
    //seta entrada da tabela de paginas como invalida
    p.set_invalid(pagetable_entry);
}

void swapinPage(unsigned int memory_page, memory& m, unsigned int pagetable_entry, pagetable& p, statistics& stat)
{
    //adiciona pagina à memoria
    m.used[memory_page] = true;
    //update page table
    p.set_entry(pagetable_entry, memory_page);
    stat.page_faults++;
}

#endif // !AUXILIARIES_H
