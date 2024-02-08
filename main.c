// função "main" principal
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor_tarefas.h"

int main() {
  
  g.qtdTarefas = 0;
  g.capacidade = 10;

  g.tarefas = (tarefa*) malloc(10 * sizeof(tarefa));
  if (g.tarefas == NULL) {
    printf("Falha ao alocar memória.\n");
    return 1;
  }
  
  //um ponteiro recebe o endereco de g
  gerenciador *g1 = &g;
  
  ler_tarefas(&g1);

  printf("     -----------------------");
  printf("\n <<< GESTOR DE TAREFAS EM C! >>> \n");
  printf("     -----------------------");


  // Menu de opçãoes
  printf("\n\nMenu de opções:");
    printf("\n\n0 - Cadastrar nova tarefa\n");
    printf("1 - Remover tarefa\n");
    printf("2 - Listar todas as tarefas cadastradas\n");
    printf("3 - Procurar tarefa pelo identificador\n");
    printf("4 - Listar tarefas concluídas\n");
    printf("5 - Listar tarefas pendentes\n");
    printf("6 - Listar tarefas em progresso\n");
    printf("7 - Listar tarefas canceladas\n");
    printf("8 - Modificar tarefa existente\n");
    printf("9 - Mostrar quantidade de tarefas cadastradas\n");
    printf("Sair - Para encerrar o programa\n\n");
  
  char opcao[10];

  do{
    printf("\nDigite a opcao desejada ('M' Para menu de opções)\n-> ");

    fgets(opcao, sizeof(opcao), stdin);

    if(strcmp(opcao, "Sair\n") == 0) {
      break;
    }

    switch(opcao[0]){

      case '0':{
        //Cadastra nova tarefa
        cadastrar_tarefa(&g1);
      }break;

      case '1':{
        //Remover tarefa pelo id
        remover_tarefa(&g1);
      }break;

      case '2':{
        //Lista todas as tarefas cadastradas
        listar_tarefas(g1);
      }break;

      case '3':{
        //Procura a tarefa pelo id
        procurar_tarefa(&g1);
      }break;

      case '4':{
        //Lista tarefas com o status concluída
        status_tarefa(1, &g1);
      }break;

      case '5':{
        //Lista tarefas com o status pedente
        status_tarefa(2, &g1);
      }break;
      
      case '6':{
        //Lista tarefas com o status em progresso
        status_tarefa(3, &g1);
      }break;
      
      case '7':{
        //Lista tarefas com o status cancelada
        status_tarefa(4, &g1);
      }break;
      
      case '8':{
        //Função modificar tarefas existentes
        modificar_tarefa(&g1);
      }break;

      case '9':{
        printf("\nQuantidade de tarefas no sistema: %d\n", g1->qtdTarefas);
      }break;

      case 'M': {
        printf("\n\n0 - Cadastrar nova tarefa\n");
        printf("1 - Remover tarefa\n");
        printf("2 - Listar todas as tarefas cadastradas\n");
        printf("3 - Procurar tarefa pelo identificador\n");
        printf("4 - Listar tarefas concluídas\n");
        printf("5 - Listar tarefas pendentes\n");
        printf("6 - Listar tarefas em progresso\n");
        printf("7 - Listar tarefas canceladas\n");
        printf("8 - Modificar tarefa existente\n");
        printf("9 - Mostrar quantidade de tarefas cadastradas\n");
        printf("Sair - Para encerrar o programa\n\n");
      }break;
      
      default:{
        printf("\n[Escolha uma opção valida]\n");
      }break;
    }
  }while(1);

  free(g.tarefas);
  g.tarefas = NULL;
  
  return 0;
}
