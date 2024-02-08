// implementação das funções decladas no arquivo "gestor_tarefas.h"
#include "gestor_tarefas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variavel global
gerenciador g;

//Abre o arquivo, lê os dados e armazena no vetor global
void ler_tarefas(gerenciador **t) {

  if ((*t)->qtdTarefas >= (*t)->capacidade) {
    (*t)->capacidade += 10;
    (*t)->tarefas = realloc((*t)->tarefas, (*t)->capacidade * sizeof(tarefa));
    if ((*t)->tarefas == NULL) {
      printf("\n[Falha ao alocar memória]\n");
      return;
    }
  }

  FILE *arquivo;
  int i = 0;
  arquivo = fopen("arquivo.txt", "r");

  if (arquivo == NULL) {
    perror("\n[ERRO! Nao foi possivel abrir arquivo]\n");
    return;
  } else {
    // Inicializar a descrição
    (*t)->tarefas[i].descricao[0] = '\0';

    while (fscanf(arquivo, "%d", &(*t)->tarefas[i].id) == 1) {
      // Ler a descrição com fgets para incluir espaços
      fgets((*t)->tarefas[i].descricao, sizeof((*t)->tarefas[i].descricao), arquivo);
      // Remover o caractere de nova linha da descrição
      (*t)->tarefas[i].descricao[strcspn((*t)->tarefas[i].descricao, "\n")] = '\0';

      // Ler o status e prazo
      fscanf(arquivo, "%d %s", &(*t)->tarefas[i].status, (*t)->tarefas[i].prazo);

      // Incrementar o índice
      i++;

      // Se o tamanho do vetor atingiu o limite, realocar
      if (i >= (*t)->capacidade) {
        (*t)->capacidade += 10;
        (*t)->tarefas = realloc((*t)->tarefas, (*t)->capacidade * sizeof(tarefa));
        if ((*t)->tarefas == NULL) {
          printf("\n[Falha ao alocar memória]\n");
          fclose(arquivo);
          return;
        }
      }
    }
  }
  (*t)->qtdTarefas = i;
  fclose(arquivo);
}

// Funcao para escrever a tarefa no arquivo
void escrever_nova_tarefa(tarefa t){

  FILE *arquivo;

  // Abre o arquivo para escrita
  arquivo = fopen("arquivo.txt", "a");

  //validação de abertura corretamente
  if( arquivo == NULL ){
    printf("\n[Erro ao abrir o arquivo]\n");
    return;
  }

  //escrever a nova tarefa no arquivo txt
  fprintf(arquivo, "%d %s\n %d %s\n", t.id, t.descricao, t.status, t.prazo);

  //fechar arquivo
  fclose(arquivo);
}

//Funcao para ler os dados da nova tarefa e adicionar no fim do vetor
void cadastrar_tarefa(gerenciador **t) {
  tarefa nova;
  int id_existente;

  do {
    // Ler o id da tarefa
    printf("\nInforme o id da nova tarefa\n->");
    scanf("%d", &nova.id);
    getchar();  // Limpar o buffer do teclado

  // Verificar se o ID já existe
    id_existente = id_existe(*t, nova.id);

    if (id_existente) {
      printf("\n[ID já existe. Informe um ID diferente]\n");
    }
  } while (id_existente);

  //Pede para o usuário digitar o retante dos dados da nova tarefa
  printf("\nInforme a descricao da tarefa\n->");
  fgets(nova.descricao, 50, stdin);
  printf("\nInforme o status da tarefa:\n1 - Concluída\n2 - Pendente\n3 - Em Progresso\n4 - Cancelada\n->");
  scanf("%d", &nova.status);
  while(nova.status < 1 || nova.status > 4){
    printf("\n[Opção inválida. Por favor, insira uma opção válida]\n->");
    scanf("%d", &nova.status);
  } 

  getchar(); //limpar o buffer do teclado
  printf("\nInforme o prazo da tarefa (Formato DD-MM-AAAA)\n->");
  fgets(nova.prazo,11, stdin);
  while(!(verifica_data(nova.prazo))) {
    printf("\n[Data inválida. Por favor, insira a data no formato DD-MM-AAAA]\n->");
    fgets(nova.prazo, 11, stdin);
  }

  //chamar a função para escrever a nova tarefa no arquivo txt
  escrever_nova_tarefa(nova);

  //verifica se ha espaco para adicionar a nova tarefa no vetor
  if ((*t)->qtdTarefas >= (*t)->capacidade) {
    (*t)->capacidade += 10;
    (*t)->tarefas = realloc((*t)->tarefas, (*t)->capacidade * sizeof(tarefa));
    if ((*t)->tarefas == NULL) {
      printf("\n[Falha ao alocar memória]\n");
      return;
    }
  }
  //Adiciona a nova tarefa no final do vetor
  (*t)->tarefas[(*t)->qtdTarefas] = nova;
  (*t)->qtdTarefas++;
  printf("\n\n >>> Nova tarefa inserida <<<\n\n");
  imprime_tarefa(&(*t)->tarefas[(*t)->qtdTarefas - 1], (*t)->qtdTarefas);
}

// Função para listar todas as tarefas cadastradas
void listar_tarefas(gerenciador *t) {

  if (t->qtdTarefas == 0) {
    printf("\n[Nao há tarefas]\n");
    return;
  }

  printf("\n >> Lista De Tarefas <<\n");

  for (int j = 0; j < t->qtdTarefas; j++) {
    imprime_tarefa(&t->tarefas[j], j);
  }
}

//Função que Procura a tarefa pelo ID e mostra na tela
void procurar_tarefa(gerenciador **t){
  
  if((*t)->qtdTarefas == 0) {
    printf("\n[Nao há tarefas]\n");
    return;
  }
  else{
    int id1;
    printf("\nInforme o identificador da tarefa\n->");
    scanf("%d", &id1);
    int flag = 0;

    for(int i = 0; i < (*t)->qtdTarefas; i++){
      if(id1 == (*t)->tarefas[i].id){
        flag = 1;
        printf("\n\n >> Tarefa encontrada <<\n");
        imprime_tarefa(&(*t)->tarefas[i], i);
      }
    }
    if(flag == 0) {
      printf("\n[Tarefa não encontrada]\n");
    }
  }
  getchar();
}

//Mostra a tarefas de acordo com o status (concluída, pendente, em progresso, cancelada);
void status_tarefa(int stts, gerenciador **t){

  if((*t)->qtdTarefas == 0) {
    printf("[Nao há tarefas]");
    return;
  }
  else{
    int flag = 0;
    switch(stts){
      case 1:{
        printf("\n >> Tarefas Concluídas <<\n");
      }break;
      case 2:{
        printf("\n >> Tarefas Pedentes <<\n");
      }break;
      case 3: {
        printf("\n >> Tarefas em Progresso <<\n");
      }break;
      case 4:{
        printf("\n >> Tarefas Canceladas <<\n");
      }break;
    }

    for(int i = 0; i < (*t)->qtdTarefas; i++){
      if(stts == (*t)->tarefas[i].status){
        flag = 1;
        imprime_tarefa(&(*t)->tarefas[i], i);
      }
    }
    
    if(flag == 0){
     printf("\n[Nao há tarefas cadastradas com esse status]\n");
    }
  }
}

//Remove a tarefa com o ID fornecido pelo usuário
void remover_tarefa(gerenciador **t) {

  if ((*t)->qtdTarefas == 0) {
    printf("\n[Nao há tarefas para remover]\n");
    return;
  }

  // Ler id da tarefa a ser removida
  int id_remover;
  printf("\nInforme o id da tarefa que deseja remover\n->");
  scanf("%d", &id_remover);

  // Procurar a tarefa com o id fornecido
  int indice = -1;

  for (int i = 0; i < (*t)->qtdTarefas; i++) {
    if (id_remover == (*t)->tarefas[i].id) {
      indice = i;
      break;
    }
  }

  // Se encontrar a tarefa, remover
  if (indice != -1) {
    
    // Salvar a tarefa a ser removida em uma variável temporária
    tarefa tarefa_removida = (*t)->tarefas[indice];

    // Deslocar todos os elementos a partir do indice + 1 para a esquerda
    for (int i = indice; i < (*t)->qtdTarefas - 1; i++) {
      (*t)->tarefas[i] = (*t)->tarefas[i + 1];
    }

    // Diminuir o tamanho do vetor
    (*t)->qtdTarefas--;

    FILE *arquivo = fopen("arquivo.txt", "w");
    if (arquivo == NULL) {
      printf("[Erro ao abrir o arquivo]\n");
      return;
    }

    // Escrever as tarefas restantes no arquivo
    for (int i = 0; i < (*t)->qtdTarefas; i++) {
      fprintf(arquivo, "%d %s\n %d %s\n", (*t)->tarefas[i].id, (*t)->tarefas[i].descricao, (*t)->tarefas[i].status, (*t)->tarefas[i].prazo);
    }

    fclose(arquivo);
    printf("\n Tarefa removida: \n");
    imprime_tarefa(&tarefa_removida, indice);

  } else {
    printf("\n[Tarefa com o Id %d não foi encontrada]\n", id_remover);
  }
  getchar();
}

//Altera a tarefa com o ID fornecido pelo usuário
void modificar_tarefa(gerenciador **t) {
  
  tarefa nova;
  int id_editar;
  int id_existente;
  FILE *arquivo;

  if ((*t)->qtdTarefas == 0) {
    printf("\n[Não há tarefas para editar]\n");
    return;
  }

  do {
    // Ler o id da tarefa que será modificada
    printf("\nInforme o id da tarefa que deseja editar\n->");
    scanf("%d", &id_editar);
    getchar(); 

    // Verificar se o ID existe no arquivo
    id_existente = id_existe(*t, id_editar);

    if (!(id_existente)) {
      printf("\n[ID inválido]\n");
    }
  } while (!(id_existente));

  do {
    // Ler o novo id da tarefa
    printf("\nInforme o novo id da tarefa\n->");
    scanf("%d", &nova.id);
    getchar();

    // Verificar se o ID já existe
    id_existente = id_existe(*t, nova.id);

    if (id_existente) {
      printf("\n[ID já existe. Digite um ID diferente]\n");
    }
  } while (id_existente);

  // Solicita ao usuário para inserir os outros dados da nova tarefa
  printf("\nInforme a nova descricao da tarefa\n->");
  fgets(nova.descricao, 50, stdin);
  printf("\nInforme o novo status da tarefa:\n1 - Concluída\n2 - Pendente\n3 - Em Progresso\n4 - Cancelada\n->");
  scanf("%d", &nova.status);
  while (nova.status < 1 || nova.status > 4){
    printf("\n[Opção inválida. Por favor, insira uma opção válida]\n->");
    scanf("%d", &nova.status);
  } 

  getchar();
  printf("\nInforme o novo prazo da tarefa (formato DD-MM-AAAA)\n->");
  fgets(nova.prazo,11, stdin);
  while (!(verifica_data(nova.prazo))) {
    printf("\n[Data inválida. Por favor, insira a data no formato DD-MM-AAAA]\n->");
    fgets(nova.prazo, 11, stdin);
  }

  // Modifica a tarefa desejada no vetor
  for(int i = 0; i < (*t)->qtdTarefas; i++){
    if((*t)->tarefas[i].id == id_editar) {
      (*t)->tarefas[i] = nova;
    }
  }

  // Abre o arquivo no modo de escrita
  arquivo = fopen("arquivo.txt", "w");

  if (arquivo == NULL) {
    printf("\n[Não foi possível abrir o arquivo]\n");
    return;
  }

  // Escreve o vetor de volta no arquivo
  for(int i = 0; i < (*t)->qtdTarefas; i++){
    fprintf(arquivo,"%d %s\n %d %s\n", (*t)->tarefas[i].id, (*t)->tarefas[i].descricao, (*t)->tarefas[i].status, (*t)->tarefas[i].prazo);
  }
  
  fclose(arquivo);
  printf("\n >> Tarefa editada com sucesso <<\n");
}

//Função para verificar se o id da tarefa exste no arquivo
int id_existe(gerenciador *t, int id) {
  for(int i = 0; i < t->qtdTarefas; i++) {
    if (t->tarefas[i].id == id) {
      printf("1");
      return 1;  // ID já existe
    }
  }
  return 0;  // ID não existe
}

//Função para mostrar as tarefas na tela
void imprime_tarefa(tarefa *t, int n) {
  
  char *statusop;
  
  switch(t->status){
    
    case 1:{
      statusop = malloc(10 * sizeof(char));
      strcpy(statusop, "concluida");
    }break;
    
    case 2:{
      statusop = malloc(9 * sizeof(char));
      strcpy(statusop, "pendente");
    }break;
    
    case 3: {
      statusop = malloc(13 * sizeof(char));
      strcpy(statusop, "em progresso");
    }break;
    
    case 4:{
      statusop = malloc(10 * sizeof(char));
      strcpy(statusop, "cancelada");
    }break;
  }
  
  printf("\nTAREFA: %d\n\n", n + 1);
  printf("|   ID: %d\n|   Descricao: %s\n|   Status: %s\n|   Prazo: %s\n", t->id, t->descricao, statusop, t->prazo);
  free(statusop);
}

//Função para verificar se a data está no formato correto[DD-MM-AAAA]
int verifica_data(char *data) {
  int dia, mes, ano;
  if (sscanf(data, "%2d-%2d-%4d", &dia, &mes, &ano) != 3) {
    return 0; // Formato incorreto
  }
  if (strlen(data) != 10) {
    return 0; // Quantidade de caracteres incorreta
  }
  return 1; // Formato correto
}
