# TP2SO

## Descrição dos arquivos que já existem

- TP2.cpp -> apenas chama funções de outros hpps e inicializa as variáveis necessárias para a execução de qualquer tipo de reposição. PS:tem um disable warning no inicio, mas é por causa da bosta do visual studio q n aceita fscanf, creio q n muda nada pra rodar em outros ambientes, mas caso mude, pode tirar q n da nada.
- Pagetable.hpp / cpp -> classe pagetable com todas funções e elementos que achei necessários para o que já foi feito. Será necessário adicionar last access ao struct auxiliar entry(representa entrada da tabela) quando for fazer a reposição LRU, além de atualizar as funções para refletir isso.
- auxiliaries.hpp -> contém o struct memória(que é apenas um vetor de booleanos com um inteiro q marca proxima posição disponível/ pode ser mudada pra incluir dados, etc) e várias funções auxiliares úteis que não precisam ser mudadas para o desenvolvimento de métodos de reposição como por exemplo retirar pagina da memória e trocar pagina da memória. Além disso contém um exemplo de função de alocar uma pagina(sem metodo de reposição), a função de obter o número de bytes menos significativos(dada pelo professor na definição do tp) e obter o offset de um endereço(que não sei pra q usa até agr)
- FIFO.hpp -> contém a implementação do programa com algoritmo FIFO, pode-se usar de referencia para os demais.


## A fazer
- Ver se n fiz as coisas iguais mongol(provável pq odeio hardware e entendo exatos quase nada da matéria)
- reposição LRU(Least Recently Used)
- reposição criada por agnt msm (tinha pensado em usar o menos frequente, ai vi a aula e isso tá la tbm, triste dia)
- Makefile (dps q cansar de usar o visual studio posso fazer isso ¯\\\_(ツ)\_/¯)
