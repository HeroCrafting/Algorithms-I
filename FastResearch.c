#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


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
	char curso[25];
	char sexo[10];
	int idade;
	//int respostas[]
} Participante;

// As descrições das funções aqui prototipadas, estão no final do código, junto com as mesmas.

void exibirMenu();

int lerPerguntas(FILE *arqPerguntas, char titulo[], Pergunta perguntas[]);

int lerEscalas(FILE *arqEscalas, char titulo[], Escala escalas[]);

int lerResultados(FILE *arqResultado, char titulo[], Participante resultados[], int respostas[][100], int retorno[2]);

int inicializarCursos(char cursos[][25]);

void separarEscala(Escala escalas[], char stringCompleta[], int nEscala);

int salvarRespostas(FILE *arqRespostas, Participante participantes[], char titulo[], int qtd_perguntas, int qtd_participantes, int respostas[][100]);

int obterRespostas(char linha[], int respostas[][100], int nParticipante);

void exibirErro(int resposta, int min, int max);

int main(){
	FILE *arq_perguntas, *arq_escalas, *arq_respostas, *arq_resultados;
	int respostas[1000][100], respostas_arquivo[1000][100], retorno_duplo[2];
	int menu, sexo, curso, idade, compativel, resposta, limite;
	int controle = 0, exito_perguntas = 0, exito_escalas = 0, exito_resultados = 0, qtd_cursos = 0, fim_entrevistas = 0, participante = 0;
	int i = 0, j = 0, k = 0;
	char titulo_perguntas[100], titulo_escalas[100], titulo_respostas[100], titulo_resultados[100], cursos[27][25];
	Pergunta perguntas[100];
	Escala escalas[10];
	Participante participantes[1000], resultados[1000];
	
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
				// A variável qtd_cursos guarda a quantidade de cursos participantes
				qtd_cursos = inicializarCursos(cursos);
				break;
			case 2:
				do{
					// Colocar o curso aqui;
					do{
						printf("Selecione o curso do entrevistado: \n");
						for(i = 0; i < qtd_cursos; i++){
							printf("[%d] ", i+1);
							puts(cursos[i]);
						}
						scanf("%d", &curso);
					} while (curso < 1 || curso > qtd_cursos);
					strcpy(participantes[participante].curso, cursos[curso-1]);
					
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
				printf("Digite o nome para o arquivo de respostas (utilize a extensão .txt): \n");
				gets(titulo_respostas);
				salvarRespostas(arq_respostas, participantes, titulo_respostas, exito_perguntas, participante+1, respostas);
				break;
			case 3:
				printf("Qual o nome do arquivo de respostas que você deseja consultar? (utilize a extensão .txt)\n");
				gets(titulo_resultados);
				// A variável exito_resultados recebe a quantidade de entrevistados no arquivo
				exito_resultados = lerResultados(arq_resultados, titulo_resultados, resultados, respostas_arquivo, retorno_duplo);
				printf("Obtido respostas de %d participantes! \n", exito_resultados);
				system("pause");
				printf("1 = %d\n0 = %d\n", retorno_duplo[1], retorno_duplo[0]);
				for (i = 0; i < retorno_duplo[0]; i++){
					printf("\nEntrevistado %d\n", i + 1);
					for (j = 0; j < retorno_duplo[1]; j++){
						printf("%d ", respostas_arquivo[i][j]);
					}
				}
				system("pause");
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
	printf("[1] Preparar Pesquisa\n[2] Aplicar Pesquisa\n[3] Ver resultados\n[4] Sair\n");
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
		fclose(arqEscalas);
		return posicao;
	}
}

//Este procedimento recupera as respostas escritas no arquivo
int lerResultados(FILE *arqResultado, char titulo[], Participante resultados[], int respostas[][100], int retorno[2]){
	int i = 0;
	char linha_respostas[202];
	arqResultado = fopen(titulo, "r");
	if (arqResultado == NULL){
		printf("Não foi possível abrir o arquivo, tente novamente!\n");
		return 0;
	}
	else{
		while(!feof(arqResultado)){
			fgets(resultados[i].curso, 100, arqResultado);
			fgets(resultados[i].sexo, 100, arqResultado);
			fscanf(arqResultado, "%d\n", &resultados[i].idade);
			fgets(linha_respostas, 202, arqResultado);
			puts(resultados[i].curso);
			puts(resultados[i].sexo);
			printf("%d\n", resultados[i].idade);
			puts(linha_respostas);
			retorno[1] = obterRespostas(linha_respostas, respostas, i);
			i++;
		}
		retorno[0] = i;
		fclose(arqResultado);
		return i;
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
			if (i > 0){
				fprintf(arqRespostas, "\n");
			}
			fputs(participantes[i].curso, arqRespostas);
			fprintf(arqRespostas, "\n");
			fputs(participantes[i].sexo, arqRespostas);
			fprintf(arqRespostas, "%d\n", participantes[i].idade);
			for (j = 0; j < qtd_perguntas; j++){
				fprintf(arqRespostas, "%d ", respostas[i][j]);
			}
		}
		fclose(arqRespostas);
		return i;
	}
}

int obterRespostas(char linha[], int respostas[][100], int nParticipante){
	int i = 0, j = 0;
	puts(linha);
	printf("%d \n", sizeof(linha));
	while (linha[i] != 0){
		printf("%c", linha[i]);
		if (linha[i] != ' '){
			respostas[nParticipante][j] = linha[i] - '0';
			printf("\n Participante %d \n", nParticipante);
			printf("%d ", respostas[nParticipante][j]);
			j++;
		}
		i++;
	}
	return j;
}

int inicializarCursos(char cursos[][25]){
	int finalizado = 0, i = 0, j = 0, selecionado;
	char lista_cursos[27][25] = {"Administraçao", "Agronomia", "Ciencias Biologicas", "Ciencias Contabeis", "Ciencias Economicas", "Direito",
	"Educaçao Fisica", "Enfermagem", "Engenharia Civil", "Engenharia de Alimentos", "Engenharia da Computaçao", "Farmacia",
	"Fisica", "Filosofia", "Geografia", "Historia", "Letras Vernaculas", "Letras c/ Espanhol", "Letras c/ Ingles", 
	"Letras c/ Frances", "Matematica", "Medicina", "Musica", "Odontologia", "Pedagogia", "Psicologia", "Quimica"};
	printf("Selecione os cursos que deseja que participem da pesquisa: \n");
	do{
		for (i = 0; i < 27; i++){
			printf("%d)", i + 1);
			puts(lista_cursos[i]);			
		}
		do{
			scanf("%d", &selecionado);
			exibirErro(selecionado, 1, 27);
		} while (selecionado < 1 || selecionado > 27);
		if(strcmp(lista_cursos[selecionado - 1], "SELECIONADO") != 0){
			strcpy(cursos[j], lista_cursos[selecionado - 1]);
			j++;
			strcpy(lista_cursos[selecionado - 1], "SELECIONADO");
		}
		do{
			printf("Deseja adicionar mais cursos?\n[1] Sim\n[2] Não \n");
			scanf("%d", &finalizado);
			exibirErro(finalizado, 1, 2);
		} while (finalizado < 1 || finalizado > 2);
	} while (finalizado == 1);
	return j;
}

// Funções de cálculos
int freqAbsoluta(int respostas[][100], int nQuestao, int qtdItens, int qtdEntrevistados){
	int i = 0, frequencia[10];
	for (i = 0; i < qtdEntrevistados; i++){
		
	}
}
