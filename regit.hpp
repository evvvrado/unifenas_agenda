
#include <iostream>
#include <string.h>
#include <stdio.h>



struct regit {
  char name[20];
  char tel[20];
  char email[20];
  bool soft_delete = false;
};

int getArchiveSize(FILE *arquivo){
  fseek(arquivo, 0, SEEK_END);
  return ftell(arquivo) / sizeof(regit);
};

void generateTextFile(FILE *arquivo){
	char nome_arquivo[20];

  printf("\nGerar arquivo dos registros \n");
  printf("\nDigite o nome do arquivo: ");
	scanf("%s", nome_arquivo);

	strcat(nome_arquivo, ".txt");
	FILE *arquivo_txt = fopen(nome_arquivo, "w");
	
  if (!arquivo_txt){
		printf("O arquivo foi impossibilitado de ser criado!\n\n");
    return;
	}
	
  fprintf(arquivo_txt, "Sua Agenda: \n");
	fprintf(arquivo_txt, "--------------------------------------------------\n");
  
	int contador;
	regit registro;
	for (contador = 0; contador < getArchiveSize(arquivo); contador++)	{
		fseek(arquivo, contador * sizeof(regit), SEEK_SET);
		fread(&registro, sizeof(regit), 1, arquivo);
    
    if(!registro.soft_delete){
      fprintf(arquivo_txt, "%-20s%-12s%-25s\n", registro.name, registro.tel, registro.email);
    };
	}
  
	fprintf(arquivo_txt, "--------------------------------------------------\n");
	fclose(arquivo_txt);

  printf("\nArquivo gerado com sucesso.....\n\n");
  
};

void createRegister(FILE *arquivo){
  regit registro;
  fflush(stdin);

  printf("\nCadastro de novo registro \n");
  printf("\nDigite: \nNome: ");
  scanf("%s", registro.name);
  printf("Email: ");
  scanf("%s", registro.email);
  printf("Telefone: ");
  scanf("%s", registro.tel);
  registro.soft_delete = false;
  
  printf("\nSalvando %s como novo registro...\n\n", registro.name);
  
  fseek(arquivo, 0, SEEK_END);
  fwrite(&registro, sizeof(regit), 1, arquivo);
  fflush(stdin);
};

void getRegisterInfo(FILE *arquivo){
  fflush(stdin);
  regit registro;
  int numero_registro;

  printf("\nConsulta de registro \n");
  printf("\nDigite o número do registro: ");
	scanf("%d", &numero_registro);

  if ((numero_registro  > getArchiveSize(arquivo)) || (numero_registro <= 0)) {
    printf("Número do registro inválido.\n\n");
    return;
  }

  fseek(arquivo, (numero_registro - 1) * sizeof(regit), SEEK_SET);
  fread(&registro, sizeof(regit), 1, arquivo);

  if (registro.soft_delete == true){
    printf("Registro não disponível.\n\n");
    return;
  }

  printf("\nNome: %s", registro.name);
  printf("\nTelefone: %s", registro.tel);
  printf("\nE-mail: %s\n\n\n", registro.email);
  
 fflush(stdin);
};

void deleteRegister(FILE *arquivo){
  fflush(stdin);
  
  regit registro;
  int numero_registro;
  
  printf("\nExclusão de registro \n");
  printf("\nDigite o número do registro: ");
	scanf("%d", &numero_registro);

  if ((numero_registro  > getArchiveSize(arquivo)) || (numero_registro <= 0)) {
    printf("Número do registro inválido.\n\n");
    return;
  }
  
  fseek(arquivo, (numero_registro - 1) * sizeof(regit), SEEK_SET);
  fread(&registro, sizeof(regit), 1, arquivo);

  if (registro.soft_delete){
    printf("Registro já excluído.\n\n");
    return;
  }

  registro.soft_delete = true;
  fseek(arquivo, (numero_registro - 1) * sizeof(regit), SEEK_SET);
  fwrite(&registro, sizeof(regit), 1, arquivo);
  printf("\nRegistro excluido com sucesso.......\n\n");
  fflush(stdin);  
};