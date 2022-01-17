#ifndef PAGETABLE_H
#define PAGETABLE_H

struct entry
{
	//é valida
	bool valid=false;
	//houve escrita
	bool dirty = false;
	int frame;
};


class pagetable
{
public:
	pagetable(int n_entries);
	~pagetable();

	//seta entrada de uma posição da tabela para frame
	void set_entry(int position,int frame);

	//obtem a pagina referenciada, retorna -1 caso falhe
	int get_frame(int position);

	//imprime entrada da tabela
	void print_entry(int i);

	//busca entrada valida que referencia pagina frame da memoria, retorna -1 caso falhe
	int find_valid(int frame);

	//marca como se tivesse tido operação de escrita(dirty bit = true) e obtem pagina referenciada
	int write_op(int position);

	bool is_dirty(int position);

	void set_invalid(int position);

private:
	int n_entries;
	entry* entries;
};






#endif //PAGETABLE_H
