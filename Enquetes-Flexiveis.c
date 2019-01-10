#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// As descrições das funções aqui prototipadas, estão no final do código, junto com as mesmas.
typedef struct pergunta{
	char enunciado[100];
	int codEscala;	
} Pergunta;

typedef struct escala{
	int codEscala;
	int qtdItens;
	char itens[10][100];
} Escala;
void exibirMenu();

int lerPerguntas(FILE *arqPerguntas, char titulo[], Pergunta perguntas[]);

int lerEscalas(FILE *arqEscalas, char titulo[]);

int main(){
	FILE *arq_perguntas, *arq_escalas, *arq_respostas;
	int menu;
	int controle = 0, exito_perguntas = 0, exito_escalas = 0;
	char titulo_perguntas[100], titulo_escalas[100];
	Pergunta perguntas[100];
	Escala escalas[10];
	
	setlocale(LC_ALL, "Portuguese");
	do{
		do{
			system("cls");
			exibirMenu();
			scanf("%d", &menu);
			if (menu < 1 || menu > 4){
				printf("Escolha uma opção válida! \n");
				system("pause");
			}
		} while (menu < 1 || menu > 4);
		getchar();
		switch(menu){
			case 1:
				do {
					printf("Digite o nome do arquivo das perguntas (utilize a extensão .txt)\n");
					gets(titulo_perguntas);
					exito_perguntas = lerPerguntas(arq_perguntas, titulo_perguntas, perguntas);
				} while (exito_perguntas == 0);
				
				do{
					printf("\nDigite o nome do arquivo das escalas (utilize a extensão .txt)\n");
					gets(titulo_escalas);
					exito_escalas = lerEscalas(arq_escalas, titulo_escalas);
				} while (exito_escalas == 0);
				break;
			case 2:

				break;
			case 3:
				
				break;
			case 4:
				
				break;
		}
	} while (controle == 0);
}

// Esta função, como o nome diz, exibe as opções do menu.
void exibirMenu(){
	printf("Bem vindo ao Fast Research, escolha a opção desejada: \n");
	printf("[1] Preparar Pesquisa\n[2] Aplicar Pesquisa\n[3] Ver resultado\n[4] Sair\n");
}

// Esta função lê as perguntas do arquivo
int lerPerguntas(FILE *arqPerguntas, char titulo[], Pergunta perguntas[]){
	int posicao = 0;
	printf("Entrou na função lerPerguntas\n");
	arqPerguntas = fopen(titulo, "r");
	if (arqPerguntas == NULL){
		printf("Erro ao abrir o arquivo! Tente novamente... \n");
		return 0;
	}
	else{
		while(!feof(arqPerguntas)){
			fgets(perguntas[posicao].enunciado, 100, arqPerguntas);
			fscanf(arqPerguntas, "%d\n", &perguntas[posicao].codEscala);
			posicao++;
			printf("%d", posicao);
		}
		return 1;
	}	
}

// Esta função, lê as escalas do arquivo
int lerEscalas(FILE *arqEscalas, char titulo[]){
	int posicao = 0;
	printf("Entrou na função lerEscalas\n");
	arqEscalas = fopen(titulo, "r");
	if (arqPerguntas == NULL){
		printf("Erro ao abrir o arquivo! Tente novamente... \n");
		return 0;
	}
	else {
		while(!feof(arqEscalas)){
			fscanf(arqEscalas, "%d\n", &escalas)
		}
	}
}

// Esta função separa os itens da escala
// Arrumar como vai ficar essa função
void separarEscala(char stringCompleta[], char item[]){
	int i;
	while (stringCompleta[i] != 0){
		if (stringCompleta[i] != ',')
	}
}
