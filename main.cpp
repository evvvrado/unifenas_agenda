//#define _CRT_SECURE_NO_WARNINGS
#include "menu.hpp"
#include "regit.hpp"
#include <iostream>
#include <string.h>

// "Verificar tamanho do arquivo" - 0
// "Gerar arquivo" - 1
// "Criar Registro" - 2
// "Consultar Registro" - 3
// "Deletar Registro" - 4

int main() {
  int usuario_comando = 0;
  int comando_saida = 5;

  FILE *arq;

  if ((arq = fopen("registros.dat", "rb+")) == NULL) {
    if ((arq = fopen("registros.dat", "wb+")) == NULL) {
      printf("Falha ao abrir o arquivo!\n");
    }
  }

  iniciar();

  while (usuario_comando != comando_saida) {
    printf("Digite seu comando: \n");
    menu();

    printf("\n\n$: ");
    scanf("%i", &usuario_comando);

    if (usuario_comando == comando_saida)
      break;

    system("clear");
    printf("Comando selecionado: %s\n\n", comandos[usuario_comando]);

    switch (usuario_comando) {
    case 0:
      getArchiveSize(arq);
      break;
    case 1:
      generateTextFile(arq);
      break;
    case 2:
      createRegister(arq);
      break;
    case 3:
      getRegisterInfo(arq);
      break;
    case 4:
      deleteRegister(arq);
      break;
    default:
      printf("\n\nComando inválido\n\n");
      break;
    }
  }

  encerrar();

  return 0;
}
