#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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

typedef struct participante{
	char curso[20];
	char sexo[10];
	int idade;
	//int respostas[]
} Participante;

void exibirMenu();

int lerPerguntas(FILE *arqPerguntas, char titulo[], Pergunta perguntas[]);

int lerEscalas(FILE *arqEscalas, char titulo[], Escala escalas[]);

void separarEscala(Escala escalas[], char stringCompleta[], int nEscala);

int salvarRespostas(FILE *arqRespostas, Participante participantes[], char titulo[], int qtd_perguntas, int qtd_participantes, int respostas[][100]);

void exibirErro(int resposta, int min, int max);

int main(){
	FILE *arq_perguntas, *arq_escalas, *arq_respostas;
	int respostas[1000][100];
	int menu, sexo, curso, idade, compativel, resposta, limite;
	int controle = 0, exito_perguntas = 0, exito_escalas = 0, fim_entrevistas = 0, participante = 0;
	int i = 0, j = 0, k = 0;
	char titulo_perguntas[100], titulo_escalas[100], titulo_respostas[100];
	Pergunta perguntas[100];
	Escala escalas[10];
	Participante participantes[1000];
	
	setlocale(LC_ALL, "Portuguese");
	do{
		do{
			system("cls");
			exibirMenu();
			scanf("%d", &menu);
			exibirErro(menu, 1, 4);
		} while (menu < 1 || menu > 4);
		getchar();
		switch(menu){
			case 1:
				do {
					printf("Digite o nome do arquivo das perguntas (utilize a extensão .txt):\n");
					gets(titulo_perguntas);
					// A variável exito_perguntas recebe a quantidade de perguntas lidas
					exito_perguntas = lerPerguntas(arq_perguntas, titulo_perguntas, perguntas);
				} while (exito_perguntas == 0);
				
				do{
					printf("\nDigite o nome do arquivo das escalas (utilize a extensão .txt):\n");
					gets(titulo_escalas);
					// A variável exito_escalas recebe a quantidade de escalas lidas
					exito_escalas = lerEscalas(arq_escalas, titulo_escalas, escalas);
				} while (exito_escalas == 0);
				break;
			case 2:
				do{
					// Colocar o curso aqui;
					do{
						printf("\nQual o sexo do participante?\n[1] Masculino \n[2] Feminino\n");
						scanf("%d", &sexo);
						exibirErro(sexo, 1, 2);
					} while (sexo < 1 || sexo > 2);
					if (sexo == 1)
						strcpy(participantes[participante].sexo, "masculino\n");
					else
						strcpy(participantes[participante].sexo, "feminino\n");
						
					do{
						printf("\nQual a idade do entrevistado?\n");
						scanf("%d", &idade);
						exibirErro(idade, 0, 200);
					} while (idade <= 0);
					participantes[participante].idade = idade;
					
					for(i = 0; i < exito_perguntas; i++){
						printf("%d)", i+1);
						puts(perguntas[i].enunciado);
						// No laço for a seguir, o codigo de escala da pergunta é comparado
						// com o codigo que está vinculado às escalas, até ser encontrado o correspondente.
						for (j = 0; j < exito_escalas; j++){
							printf("Entrou no for de comparação \n");
							if (escalas[j].codEscala == perguntas[i].codEscala){
								compativel = j;
								printf("Encontrou o correspondente, %d \n", compativel+1);
								printf("Deveria ser: %d \n", perguntas[i].codEscala);
								j = exito_escalas;
							}
						}
						for (j = 0; j < escalas[compativel].qtdItens; j++){
							printf("[%d]", j+1);
							puts(escalas[compativel].itens[0][j]);
							//printf("\n");
							// A variável limite guarda a opção máxima, para tratamento de erros
							limite = j + 1;
						}
						do{
							scanf("%d", &resposta);
							exibirErro(resposta, 1, limite);
						} while (resposta < 0 || resposta > limite);
						respostas[participante][i] = resposta;
					}
					do{
						printf("Deseja entrevistar outro candidato?\n[1] Sim \n[2] Não\n");
						scanf("%d", &fim_entrevistas);
						exibirErro(fim_entrevistas, 1, 2);
						if (fim_entrevistas == 1){
							// O contador participante, guarda a quantidade de entrevistas realizadas
							participante++;
						}
					} while (fim_entrevistas < 1 || fim_entrevistas > 2);
				} while (fim_entrevistas == 1);
				getchar();
				printf("Agora, vamos salvar as respostas.. \n");
				system("pause");
				getchar();
				printf("Digite o nome para o arquivo de respostas (utilize a extensão .txt): \n");
				gets(titulo_respostas);
				salvarRespostas(arq_respostas, participantes, titulo_respostas, exito_perguntas, participante+1, respostas);
				break;
			case 3:
				
				break;
			case 4:
				exit(1);
				break;
		}
	} while (controle == 0);
}

// Este procedimento, como o nome diz, exibe as opções do menu.
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
		return posicao;
	}
}

// Este procedimento separa os itens da escala
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

// Este procedimento exibe uma mensagem de erro para respostas fora do intervalo definido
void exibirErro(int resposta, int min, int max){
	if (resposta < min || resposta > max){
		printf("Digite uma resposta válida!\n");
		system("pause");
	}
}

// Esta função, salva as respostas em um arquivo de texto
int salvarRespostas(FILE *arqRespostas, Participante participantes[], char titulo[], int qtd_perguntas, int qtd_participantes, int respostas[][100]){
	int i = 0, j = 0;
	arqRespostas = fopen(titulo, "a");
	if (arqRespostas == NULL){
		printf("Erro ao abrir o arquivo! Tente novamente. \n");
		return 0;
	}
	else{
		for(i = 0; i < qtd_participantes; i++){
			// Aqui vem o printf do curso;
			fputs(participantes[i].sexo, arqRespostas);
			fprintf(arqRespostas, "%d\n", participantes[i].idade);
			for (j = 0; j < qtd_perguntas; j++){
				fprintf(arqRespostas, "%d ", respostas[i][j]);
			}
			fprintf(arqRespostas, "\n");
		}
		return i;
	}
}
