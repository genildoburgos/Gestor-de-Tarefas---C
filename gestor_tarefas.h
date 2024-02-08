// declaração de estrutura de dados e funções
#define A 50 
#define B 11

//estrutura para tarefa 
typedef struct{
  int id; // identificador 
  char descricao[A];
  int status;
  char prazo[B]; //Formato DD-MM-AAAA
}tarefa;

typedef struct{
  tarefa *tarefas;
  int qtdTarefas;
  int capacidade;
}gerenciador;

// declaração de todas as funções do gestor de tarefa
void cadastrar_tarefa(gerenciador **t);
void escrever_nova_tarefa(tarefa t);
void listar_tarefas(gerenciador *t);
void ler_tarefas(gerenciador **t);
void procurar_tarefa(gerenciador **t);
void status_tarefa(int stts, gerenciador **t);
void remover_tarefa(gerenciador **t);
void modificar_tarefa(gerenciador **t);
int id_existe(gerenciador *t, int id);
void imprime_tarefa(tarefa *t, int n);
int verifica_data(char *data);

// Declaração da variável global
extern gerenciador g;
