
#include <iostream>
#include <string.h>

// ================================ //
// FRAMEWORK DE SISTEMIFICAÇÃO
// ================================ //


char comandos[6][60] = {"Verificar tamanho do arquivo", "Gerar arquivo",
                        "Criar Registro", "Consultar Registro",
                        "Deletar Registro", "Sair"};



void menu() {
  int i = 1;
  while (i < 6) {
    printf("%i - %s;\n", i, comandos[i]);
    i++;
  };
}

void printer(const char *text) {
  printf("========================\n");
  printf("%s", text);
  printf("\n========================\n\n\n");
};



void iniciar(){
  system("clear");
  printer("agenda de alunos, seja bem vindo(a)");
}

void encerrar(){
  system("clear");
  printer("Encerrando a sua janela \nde atendimento, adeus.");
}
// ================================ //