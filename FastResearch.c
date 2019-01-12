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
	char itens[1][10][255];
} Escala;

void exibirMenu();

int lerPerguntas(FILE *arqPerguntas, char titulo[], Pergunta perguntas[]);

int lerEscalas(FILE *arqEscalas, char titulo[], Escala escalas[]);

void separarEscala(Escala escalas[], char stringCompleta[], int nEscala);

int main(){
	FILE *arq_perguntas, *arq_escalas, *arq_respostas;
	int menu, sexo, curso, idade, compativel;
	int controle = 0, exito_perguntas = 0, exito_escalas = 0, fim_entrevistas = 0;
	int i = 0, j = 0, k = 0;
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
					exito_escalas = lerEscalas(arq_escalas, titulo_escalas, escalas);
				} while (exito_escalas == 0);
				break;
			case 2:
				do{
					// Colocar o curso aqui;
					do{
						printf("\nQual o sexo do participante?\n[1] Masculino \n[2] Feminino\n");
						scanf("%d", &sexo);
						if (sexo < 1 || sexo > 2){
							printf("Selecione uma opção válida!");
							system("pause");
						}
					} while (sexo < 1 || sexo > 2);
					
					do{
						printf("\nQual a idade do entrevistado?\n");
						scanf("%d", &idade);
						if (idade <= 0){
							printf("Idade negativa? Digite uma válida!");
							system("pause");
						}
					} while (idade <= 0);
					
					for(i = 0; i < exito_perguntas; i++){
						printf("%d)", i+1);
						puts(perguntas[i].enunciado);
						for (j = 0; j < sizeof(escalas); j++){
							if (escalas[j].codEscala == perguntas[i].codEscala){
								compativel = j;
							}
						}
						for (j = 0; j < escalas[compativel].qtdItens; j++){
							printf("[%d]", j+1);
							puts(escalas[compativel].itens[0][j]);
							printf("\n");
						}
					}
				} while (fim_entrevistas == 0);
				break;
			case 3:
				
				break;
			case 4:
				exit(1);
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
		return posicao;
	}	
}

// Esta função, lê as escalas do arquivo
int lerEscalas(FILE *arqEscalas, char titulo[], Escala escalas[]){
	int posicao = 0;
	char escalas_agrupadas[100];
	printf("Entrou na função lerEscalas\n");
	arqEscalas = fopen(titulo, "r");
	if (arqEscalas == NULL){
		printf("Erro ao abrir o arquivo! Tente novamente... \n");
		return 0;
	}
	else {
		while(!feof(arqEscalas)){
			printf("Posição da escala atual: %d", posicao);
			system("pause");
			fscanf(arqEscalas, "%d\n", &escalas[posicao].codEscala);
			fscanf(arqEscalas, "%d\n", &escalas[posicao].qtdItens);
			fgets(escalas_agrupadas, 100, arqEscalas);
			separarEscala(escalas, escalas_agrupadas, posicao);
			posicao++;
		}
	}
}

// Esta função separa os itens da escala
void separarEscala(Escala escalas[], char stringCompleta[], int nEscala){
	int i = 0, j = 0, nItem = 0;
	while (stringCompleta[i] != 0){
		if (stringCompleta[i] == ','){
			escalas[nEscala].itens[0][nItem][j] = 0;
			j = 0;
			nItem++;
		}
		else{
			escalas[nEscala].itens[0][nItem][j] = stringCompleta[i];
			j++;
		}
		i++;
	}
}