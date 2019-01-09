#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// As descrições das funções aqui prototipadas, estão no final do código, junto com as mesmas.
typedef struct pergunta{
	char enunciado[100];
	int codEscala;
} Pergunta;

void exibirMenu();

void lerPerguntas(FILE *arqPerguntas, char titulo[]);

void lerEscalas(FILE *arqEscalas, char titulo[]);

int main(){
	FILE *arq_perguntas, *arq_escalas, *arq_respostas;
	int menu, controle = 0;
	char titulo_perguntas[100], titulo_escalas[100];
	
	setlocale(LC_ALL, "Portuguese");
	do{
		do{
			system("cls");
			exibirMenu();
			scanf("%d\n", &menu);
		} while (menu < 1 || menu > 4);
		system("pause");

		switch(menu){
			case 1:
				printf("Digite o nome do arquivo das perguntas (utilize a extensão .txt!");
				gets(titulo_perguntas);
				lerPerguntas(arq_perguntas, titulo_perguntas);
				
				printf("Digite o nome do arquivo das escalas (utilize a extensão .txt");
				gets(titulo_escalas);
				lerEscalas(arq_escalas, titulo_escalas)
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

// Essa função, como o nome diz, exibe as opções do menu.
void exibirMenu(){
	printf("Bem vindo ao Fast Research, escolha a opção desejada: \n");
	printf("[1] Preparar Pesquisa\n[2] Aplicar Pesquisa\n[3] Ver resultado\n[4] Sair");
}

// Essa função lê as perguntas do arquivo
void lerPerguntas(FILE *arqPerguntas, char titulo[]){
	arqPerguntas = fopen(titulo, "r");
	while(!feof(arqPErguntas)){
		fgets(enunciado)
	}
	
}

// Essa função, lê as escalas do arquivo
void lerEscalas(FILE *arqEscalas, char titulo[]){
	
}
