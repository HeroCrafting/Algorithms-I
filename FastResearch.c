/*******************************************************************************
Autor: Diego do Carmo Silva
Componente Curricular: Algoritmos I
Concluido em: 22/11/2018
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


// Esta função exerce o papel de menu.
int acessar_menu(){
	int menu;
	do{
		system("cls");
		printf("Bem vindo ao Fast Research, o que deseja? \n");
		printf("[1] Aplicar Pesquisa \n[2] Preparar pesquisa \n[3] Ver resultados \n[4] Sair\n");
		scanf("%d", &menu);
		getchar();
	} while (menu < 1 || menu > 4);
	return menu;	
}

// Esta função coloca a palavra de forma adequada nas matrizes em que se faz necessário (Curso e Sexo, por exemplo)
void padronizarString(int linha, char matriz_resposta[][11], char string[]){
	int i, j;
	for(i = 0; i < strlen(string); i++){
		matriz_resposta[linha][i] = string[i];
		j = i + 1;
	}
	matriz_resposta[linha][j] = 0;
}
// Esta função é uma solução rápida para um bug que tive
int correcao(int num){
	if (num < 0){
		return 0;
	}
	else if (num == 0){
		return 1;
	}
	else
		return num;
}
// Esta função zera os campos de uma matriz de inteiros
void zerarMatriz(int matriz[1000][100]){
	int i, j;
	for (i = 0; i < 1000; i++){
		for(j = 0; j < 100; j++){
			matriz[i][j] = 0;
		}
	}
}
// Esta função zera os campos de um vetor
void zerarVetor(int vetor[100]){
	int j;
	for(j = 0; j < 100; j++){
			vetor[j] = 0;
		}
}

//Esta função calcula a frequência absoluta e a moda
int freqAbsoluta(int linhas, int colunas, int respostas[1000][100], int freq[1000][100], int mod[1000][100]){
	int i, j, maior = 0, posicao;
	for (i = 0; i < colunas; i++){
		for (j = 0; j < linhas; j++){
			if (respostas[j][i] == i + 1){
				freq[j][i]++;
				mod[j][i]++;
			}	
		}
	}
	for (i = 0; i < 100; i++){
		if (mod[i] > maior){
			maior = mod[i];
			posicao = i;
		}
	}
	return posicao;
}

int main() {
	// ponteiros para os arquivos perguntas, respostas e escalas
	FILE *quest, *resp, *esc, *arq_respostas;
	char *exibir, questExibir[100], perguntas[100][100];
	char escalas[15][15][255], escalas_conjunto[100][100];
	char titulo[30], nome[55], cursos[29], resposta_sexo[1000][11];
	char titulo_resp[30], nome_curso[29][25], arq_resp[25], sexo_recupera[1000][11], idade_recupera[1000], curso_recupera[29][50], resposta_recupera[1000][100];
	int *cod_escala_vetor[100], cod_escala_arquivo[100], qtd_itens_escala[100], resposta_curso[1000], resposta_idade[1000], respostas_geral[1000][100];
	int freqAbsoluta_matriz[1000][100], moda[1000][100];
	int a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, p = 0, x = 0, y = 0, z = 0;
	int controle = 1, preparacao = 0, relacao, finalizar = 0, limite, entrevistado = 0, sexo, idade, curso;
	int menu, resposta, questoes = 0, cod_escala, qtd_curso, moda_num;
	
	setlocale (LC_ALL, "Portuguese");
	zerarMatriz(respostas_geral);
	zerarMatriz(freqAbsoluta_matriz);
	zerarMatriz(moda);
	do{
		switch(acessar_menu()){
			case 1:
				if (preparacao == 0){
					printf("Primeiramente, prepare a pesquisa!\n");
				}
				else {
					printf("Escolha o nome para o seu arquivo de respostas: (Não esqueça o .txt!) \n");
					gets(titulo_resp);
					resp = fopen(titulo_resp, "w");
					do{
						// Obtenção do sexo do entrevistado
						do{
							printf("Qual o sexo do entrevistado?\n[1] Masculino\n[2] Feminino");
							scanf("%d", &sexo);
						} while (sexo < 1 || sexo > 2);
						if (sexo == 1){
							padronizarString(entrevistado, resposta_sexo, "masculino\n");
						}
						else
							padronizarString(entrevistado, resposta_sexo, "feminino\n");
						fputs(resposta_sexo[entrevistado], resp);
						
						// Obtenção do curso do entrevistado
						do{
							printf("Qual o curso? \n");
							for(i = 0; i < qtd_curso; i++){
								printf("[%d] %s \n", i + 1, nome_curso[i]);
							}
							scanf("%d", &curso);
						} while (curso > qtd_curso);
						resposta_curso[entrevistado] = curso;
						fputs(nome_curso[resposta_curso[entrevistado] - 1], resp);

						// Obtenção da idade do entrevistado
						do{
							printf("Qual a idade do entrevistado? \n");
							scanf("%d", &idade);
						}while (idade <= 0);
						resposta_idade[entrevistado] = idade;
						fputs("\n", resp);
						fprintf(resp, "%d \n", idade);
												
						// Aqui começa a exibição das perguntas
						for(i = 0; i < questoes; i++){
							do {
							printf("%d) %s \n", i + 1, perguntas[i]);
							// Relação entre o código e a escala
							for(k = 0; k <= questoes; k++){
								if (cod_escala_vetor[i] == cod_escala_arquivo[k]){
									//relacao = k - 1;
									relacao = correcao(k - 1);
									k = questoes + 1;
								}
							}
								for(j = 0; j < qtd_itens_escala[relacao]; j++){
									printf("[%d] %s \n", j + 1, escalas[relacao][j]);
									limite = j + 1;
								}
								scanf("%d", &resposta);
								if (resposta < 0 || resposta > limite){
									printf("Digite uma resposta no intervalo! \n");
								}
								respostas_geral[entrevistado][i] = resposta;
							} while ( resposta < 1 || resposta > limite);	
							fprintf(resp, "%d ", respostas_geral[entrevistado][i]);						
						}
						fputs("\n", resp);
						entrevistado++;
						do{
						printf("Deseja entrevistar outra pessoa? \n[0] Sim\n[1] Não");
						scanf("%d", &finalizar);
						}while (finalizar < 0 || finalizar > 1);
					} while (finalizar == 0);
					fclose(resp);
				}
				break;
			case 2:
				printf("Digite o título da pesquisa (nome_do_arquivo.txt): \n");
				gets(titulo);
				quest = fopen(titulo, "r");
				if (quest == NULL){
					printf("Erro ao abrir ao arquivo, verifique e tente novamente! \n");
					system("pause");
					preparacao = 0;
					controle = 0;
					break;
				}
				else{
					while(!feof(quest)){
						fgets(perguntas[a], sizeof(perguntas[a]), quest);
						for(i = 0; i < strlen(perguntas[a]); i++){
							if (perguntas[a][i] == '\n'){
								perguntas[a][i] = 0;
							}
						}
						a++;
						fscanf(quest, "%d\n", &cod_escala_vetor[b]);
						b++;
						questoes++;
					}
					fclose(quest);
				}
				printf("Qual o nome do arquivo das escalas? Siga o padrao nome_do_arquivo.txt. \n");
				gets(titulo);
				esc = fopen(titulo, "r");
				if (esc == NULL){
					printf("Erro ao abrir ao arquivo, verifique e tente novamente! \n");
					system("pause");
					controle = 0;
					break;
				}
				else{
					while(!feof(esc)){
						fscanf(esc, "%d\n", &cod_escala_arquivo[x]);
						x++;
						fscanf(esc, "%d\n", &qtd_itens_escala[y]);
						y++;
						fgets(escalas_conjunto[z], sizeof(escalas_conjunto[z]), esc);
						//organizarEscalas(escalas_conjunto, escalas);
						for(i = 0; i < strlen(escalas_conjunto[z]); i++){
							if (escalas_conjunto[z][i] == '\n'){
								escalas[j][k][l] = 0;
								l = 0;
								k = 0;
								j++;
							}
							else if (escalas_conjunto[z][i] == ','){
								escalas[j][k][l] = 0;
								l = 0;
								k++;
							}
							else{
								escalas[j][k][l] = escalas_conjunto[z][i];
								l++;
							}
						}
					}
				}
				printf("Quantos cursos você deseja entrevistar? \n");
				scanf("%d", &qtd_curso);
				getchar();
				for (i = 0; i < qtd_curso; i++){
					printf("Digite o nome do %dº curso: \n", i+1);
					gets(nome_curso[i]);
				}
				preparacao = 1;
				printf("Pesquisa criada com sucesso!\n");
				system("pause");
				controle = 0;
				fclose(esc);
				break;
			case 3:
				printf("Digite o nome do seu arquivo de respostas: \n");
				gets(arq_resp);
				arq_respostas = fopen(arq_resp, "r");
				if (esc == NULL){
					printf("Erro ao abrir ao arquivo, verifique e tente novamente! \n");
					system("pause");
					controle = 0;
					break;
				}
				else{
					while(!feof(arq_respostas)){
						fgets(sexo_recupera[m], sizeof(sexo_recupera[m]), arq_respostas);
						for(i = 0; i < strlen(perguntas[a]); i++){
							if (sexo_recupera[m][i] == '\n'){
								sexo_recupera[m][i] = 0;
							}
						}
						fgets(curso_recupera[n], sizeof(curso_recupera[n]), arq_respostas);
						for(i = 0; i < strlen(perguntas[a]); i++){
							if (curso_recupera[m][i] == '\n'){
								curso_recupera[m][i] = 0;
							}
						}
						m++;
						n++;
						fscanf(arq_respostas, "%d\n", idade_recupera[p]);
						p++;
						/*fgets(resposta_recupera[c], sizeof(resposta_recupera[c]), arq_respostas);
						for(i = 0; i < strlen(resposta_recupera[c]); i++){
							if (resposta_recupera[c][i] == '\n'){
								i = strlen(resposta_recupera[c]);
							}
							else{
								
							}*/
					}	
					printf("Estatísticas: \n");
					moda_num = freqAbsoluta(entrevistado, questoes, respostas_geral, freqAbsoluta_matriz, moda);
					printf("O valor da moda é: %d \n", moda[moda_num]);
					for (i = 0; i < questoes; i++){
						for (j = 0; j < qtd_itens_escala[i]; j++){
							printf("Frequencia Absoluta: \nQ%d) Item%d: %d\n", i + 1, j + 1, freqAbsoluta_matriz[j][i]);
						}
				}
				controle = 1;
				}
				fclose(arq_respostas);
				break;
			case 4:
				printf("Obrigado por utilizar o Fast Research!");
				exit(0);
		}
 	system("pause");
	} while(controle == 0); // A variável controle, auxilia na "volta" ao menu, em casos necessários.
	printf("%s", &escalas[0][10]);
	printf("\nFinal");
	return 0;
}

