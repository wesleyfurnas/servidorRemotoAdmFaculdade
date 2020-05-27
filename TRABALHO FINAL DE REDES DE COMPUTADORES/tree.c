#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#define MAXCPF 99999999999
#define MINCPF 01000000000
//Remove uma raiz 
No* removeRaiz(No* raiz){
    No *pai, *novaRaiz;
    if(raiz->dir == NULL) novaRaiz = raiz->esq;
    else if(raiz->esq == NULL) novaRaiz = raiz->dir;
    else{
        pai = raiz;
        No* sucessor = raiz->dir;
 
        while(sucessor->esq != NULL){
            pai = sucessor;
            sucessor = sucessor->esq;
        }
 
        raiz->chave = sucessor->chave;
        pai->esq = removeRaiz(sucessor);
        return raiz;
    }
    free(raiz);
    return novaRaiz;
}
 
No* remover(No* raiz, long int chave){
    if(raiz->chave == chave) return removeRaiz(raiz);
 
    No *no = raiz, *pai = NULL;
    while(no->chave != chave){
        pai = no;
        if(chave < no->chave) no = no->esq;
        else no = no->dir;
    }
 
    if(pai->chave > chave) pai->esq = removeRaiz(no);
    else pai->dir = removeRaiz(no);
 
    return raiz;
}
	

//Libera a arvore inteira
No* liberarArvore(No* raiz){
    if(raiz != NULL){
        No* esq = raiz->esq;
        No* dir = raiz->dir;
        free(raiz);
        liberarArvore(esq);
        liberarArvore(dir);
    }
}
//Devolve uma arvore que tem a chave igual ao parametro
No* buscar(No* raiz, long  int   key){
	if (raiz == NULL) return NULL;
	if (raiz->chave == key) return raiz;
	else if ( raiz->chave > key) return buscar(raiz->esq,key);
	else return buscar(raiz->dir,key);
}
No* buscarPai(No *raiz,long int chave){
	No* pai = NULL;
	No* raizAtual =raiz;
	while(raiz->chave != chave){
		pai = raizAtual;
		if(raizAtual->chave > chave){
			raizAtual = raizAtual->esq;
		}else raizAtual = raizAtual->dir;
	}
	return pai;

}
//retorna a quantidade nos
int totalNo(No* raiz){
	if (raiz == NULL) return 0;
	return totalNo(raiz->esq) + totalNo(raiz->dir) + 1 ;
}





void writeARQ(No* raiz, FILE *p){
	if(raiz == NULL) return;
	if(raiz != NULL)
	{		 
		writeARQ(raiz->esq, p);
		fprintf(p,"%s°%s°%ld°%d°%d°%d°\n", raiz->aluno, raiz->curso,raiz->chave, raiz->idade,raiz->mensalidade, raiz->tempo);
		writeARQ(raiz->dir, p);
	}
}












No* readARQ (No* raiz, char nome[], char curso[], long int chave, int idade,int mensalidade, int tempo){

	No* novo = (No*) malloc (sizeof(No));
	// PREENCHENDO INFORMACOES DO ALUNO
	novo->chave = chave;
	strcpy(novo->curso,curso);
	strcpy(novo->aluno,nome);		
	novo->idade = idade;	                           
	novo->tempo = tempo;	                            
	novo->mensalidade = mensalidade; 
     // CASO A ARVORE ESTEJA VAZIA ELE SERA A RAIZ
	if(raiz == NULL)
	{
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	// CASO ELE JA ESTEJA NA ARVORE, RETORNA A ARVORE NORMAL
	if (raiz->chave == chave) return raiz;
	else{
		No* pai = NULL;
		No *raizAtual = raiz;
			while (raizAtual != NULL){
				pai = raizAtual;
				if(chave > raizAtual->chave) raizAtual = raizAtual->dir;
				else if (raizAtual->chave > chave) raizAtual = raizAtual->esq;
				else return raiz;
			}
		if (pai->chave > chave)  
				pai->esq = novo;
		else 
				pai->dir = novo;	
	}
	return raiz;
}


	// PREENCHENDO INFORMACOES DO ALUNO

			                                                       
	


// FUNCAO QUE LÊ O ARQUIVO
No* openARQ(No* raiz, FILE *f){                 
	// VARIAVEIS PARA ARMAZENAR OS CAMPOS DA STRUCT
	char *campo;
	char aluno[100];
	char curso[100];
	char opcao[100];
    long int chave;
	int idade = 10, mensalidade =100, tempo =1000;
	char linhaATUAL[400];
	int i = 0;

	if(f == NULL){
		printf("ERRO AO LER ARQUIVO .\n");
	}
	
	// Navega entre as linhas do arquivo
	while( fgets(linhaATUAL,sizeof(linhaATUAL),f) != NULL)              
	{	
		printf("\n\n");
		i = 0;
		// PEGA O NOME DO ALUNO
		campo = (char*)strtok(linhaATUAL, "°");
		strcpy(aluno,campo);
		//printf("O aluno eh: %s\n", aluno);
		//PEGA O RESTANTE DAS INFORMAÇOES
		while(campo!= NULL ){
			opcao[0] = '\0';
			campo = (char*)strtok(NULL, "°");
			if(i == 0){
				strcpy(curso, campo);
				//printf("O curso eh: %s\n", curso);
				i++;
			}else if(i == 1){
				strcpy(opcao,campo);
			     tiraZero(opcao);
				chave = atol(opcao);
				//printf("O CPF eh: %ld\n", chave);
				i++;
			}else if(i == 2){
				strcpy(opcao, campo);
				idade = atoi(opcao);
				i++;
				//printf("A idade eh: %d\n", idade);
			}else if(i == 3){
				strcpy(opcao, campo);
				mensalidade = atoi(opcao);
				i++;
				//printf("A mensalidade eh: %d\n", mensalidade);
			}else if(i == 4){
				strcpy(opcao, campo);
				tempo = atoi(opcao);
				//printf("O tempo eh: %d\n", tempo);
				i++;
			}
  		}
		// ADICIONA O ALUNO NA ARVORE 
		raiz = readARQ (raiz,aluno, curso, chave, idade,mensalidade, tempo);  
	}
	// RETORNA A ARVORE COM OS ALUNO ADICIONADOS
	return raiz;
}



// CONVERTE. RECEBE UMA STRING INICIADA POR ZERO E DEVOLVE SEM O ZERO .EX.:  tiraZero(070234566) = 70234566
void tiraZero(char CPF[]){
	int i;
	int j = 1;

	while (CPF[0] == '0' && CPF[1] != '\0'){
		if(strlen(CPF) > 1){
			for(i = 1; i < strlen(CPF); i++)
			{
				CPF[i-1] = CPF[i];			
			}
		    CPF[strlen(CPF)-1] = '\0';	
		}
	}
}
// FUNCAO QUE PRINTA MENU PRA MUDAR CAMPOS DO ALUNO

// FUNCAO QUE VERIFICA SE TEM ALGUMA LETRA, RETORNA 1 SE TEM LETRA E ZERO CASO NAO TENHO LETRA
int soNumero(char CPF[]){ 
	int i = 0;
	int controle = 0 ; 
	
	while (CPF[i] != '\0' ){
 		if(CPF[i] != '1' && CPF[i] != '2' && CPF[i] != '3' && CPF[i] != '4' && CPF[i] != '5' && CPF[i] != '6' && CPF[i] != '7' && CPF[i] != '8' && CPF[i] != 			'9'  && CPF[i] != '0') 		
				controle = 1; 	
		else controle = controle ; 	i++; 
	} 	

	return controle; 
}









// funcao separa rebece a operacao e diz os campos 
void separa(char operacao[],char chave[],char curso[],char nome[],char idade[],char tempo[], char mensalidade[], char msg_recebido[]){
		int i = 0;
		char *campo = (char*)strtok(msg_recebido, ":");
		strcpy(operacao,campo);

		//PEGA O RESTANTE DAS INFORMAÇOES
		
		while(campo!= NULL ){
			campo = (char*)strtok(NULL, ",");
			if(i == 0){
				strcpy(chave, campo);
				i++;
			}else if(i == 1){
				strcpy(curso,campo);
				i++;
			}else if(i == 2){
				strcpy(nome, campo);
				i++;
			}else if(i == 3){
				strcpy(idade, campo);
				i++;
			}else if(i == 4){
				strcpy(tempo, campo);
				i++;
			}else if(i == 5){
				strcpy(mensalidade, campo);
				i++;
			}
  		}
}

No* inserirDoCliente(No* raiz,long int chave,char nome[],char curso[],int idade,int tempo,int mensalidade){
	No * novo = (No*)malloc(sizeof(No));
	strcpy(novo->aluno,nome);
	strcpy(novo->curso,curso);
	novo->chave = chave;
	novo->idade = idade;
	novo->tempo = tempo;
	novo->mensalidade = mensalidade;
	novo->esq = NULL;
	novo->dir = NULL;
	if(raiz == NULL) return novo;
	if (raiz-> chave == chave) return raiz;
	else{
		No* pai = NULL;
		No *raizAtual = raiz;
			while (raizAtual != NULL){
				pai = raizAtual;
				if(chave  > raizAtual->chave ) raizAtual = raizAtual->dir;
				else if (raizAtual->chave > chave ) raizAtual = raizAtual->esq;
				else return raiz;
			}
		if (pai->chave > chave)  
				pai->esq = novo;
		else 
				pai->dir = novo;	
	}
	return raiz;
}



// funcao que recebe um inteiro e transforma em char para enviar para cliente
void converteLongInteiro(char string[], long int numero){
	char *str;
	str = (char *)malloc(sizeof(numero));
	sprintf(str,"%ld",numero);
	printf("%s \n",str);
	strcpy(string,str);
}

void converteInteiro(char string[], int numero){
	char *str;
	str = (char *)malloc(sizeof(numero));
	sprintf(str,"%d",numero);
	printf("%s \n",str);
	strcpy(string,str);
}


void enviarRaiz(No *raiz, int *sock,char msg_enviar[]){
	if(raiz == NULL) return ;

	char cpf[100];
	char mensalidade[100];
	char tempo[100];
	char idade[100];
	//if (raiz == NULL) return;
	//if (raiz != NULL) {
		enviarRaiz(raiz->esq,sock,msg_enviar);

		//converte as informacoes da raiz e guarda nos buffers
		converteLongInteiro(cpf,raiz->chave);
		converteInteiro(mensalidade,raiz->mensalidade);
		converteInteiro(tempo,raiz->tempo);
		converteInteiro(idade,raiz->idade);

		//copia todos em um unico buffer colocando 0 para indicar que ainda há informacao
		strcat(msg_enviar,cpf);
		strcat(msg_enviar,",");
		strcat(msg_enviar,raiz->curso);
		strcat(msg_enviar,",");
		strcat(msg_enviar,raiz->aluno);
		strcat(msg_enviar,",");
		strcat(msg_enviar,idade);
		strcat(msg_enviar,",");
		strcat(msg_enviar,tempo);
		strcat(msg_enviar,",");
		strcat(msg_enviar,mensalidade);
		strcat(msg_enviar,",");
		 enviarRaiz(raiz->dir,sock,msg_enviar);
		//enviarRaiz(raiz->dir);

	///}
}

//funcoes para a lista


void enviaAluno(No* raiz,int *sock,char msg_enviar[]){

	char cpf[100];
	char mensalidade[100];
	char tempo[100];
	char idade[100];
	//if (raiz == NULL) return;
	//if (raiz != NULL) {
		//converte as informacoes da raiz e guarda nos buffers
		converteLongInteiro(cpf,raiz->chave);
		converteInteiro(mensalidade,raiz->mensalidade);
		converteInteiro(tempo,raiz->tempo);
		converteInteiro(idade,raiz->idade);

		//copia todos em um unico buffer colocando 0 para indicar que ainda há informacao
		strcat(msg_enviar,cpf);
		strcat(msg_enviar,",");
		strcat(msg_enviar,raiz->curso);
		strcat(msg_enviar,",");
		strcat(msg_enviar,raiz->aluno);
		strcat(msg_enviar,",");
		strcat(msg_enviar,idade);
		strcat(msg_enviar,",");
		strcat(msg_enviar,tempo);
		strcat(msg_enviar,",");
		strcat(msg_enviar,mensalidade);
		strcat(msg_enviar,",");
}


void imprime(No* raiz){
	if (raiz == NULL) return;
	if (raiz != NULL) {
		imprime(raiz->esq);
		printf("\n");
		printf("Nome:            %s \n", raiz->aluno);
		printf("CURSO:           %s \n", raiz->curso);
		if(raiz->chave >= 1000000000 && raiz->chave <= 9999999999)
		printf ("CPF :            0%ld \n", raiz->chave);
		else
		printf ("CPF :            %ld \n", raiz->chave);
		printf("Mensalidade:     %d \n", raiz->mensalidade);
		printf("Tempo:           %d \n", raiz->tempo);
		printf("Idade:           %d  \n",raiz->idade);
		printf("\n");
		imprime(raiz->dir);
	}
}