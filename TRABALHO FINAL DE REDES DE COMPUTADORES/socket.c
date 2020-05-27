#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "tree.h"

#define MAXBUF 256
int main()
{
// Ponteiro para ler do arquivo
	FILE *p = fopen("sock.txt","r");
	No* raiz = NULL;
	raiz = openARQ(raiz,p);
	fclose(p);
/* declarar as variáveis */
	char *nome = (char*)malloc(MAXBUF*sizeof(char*));
	char *operacao = (char*)malloc(MAXBUF*sizeof(char*));
	char *curso = (char*)malloc(MAXBUF*sizeof(char*));
	char *opcao = (char*)malloc(MAXBUF*sizeof(char*));
    char *idade = (char*)malloc(MAXBUF*sizeof(char*));
	char *cpf = (char*)malloc(MAXBUF*sizeof(char*));
	char *mensalidade   = (char*)malloc(MAXBUF*sizeof(char*));
	char *tempo = (char*)malloc(MAXBUF*sizeof(char*));
	char *msg_recebido = (char*)malloc(MAXBUF*sizeof(char*));
	long int cpfConvertido;
	char *msg_enviar = (char*)malloc(MAXBUF*sizeof(char*));
	int qtdNos;
	char *lista1 = (char*)malloc(300*sizeof(No)); 
	char *lista2 = (char*)malloc(300*sizeof(No)); 
	

	 //imprime(raiz);
    // criando o descritor do socket e a estrutura
	 struct sockaddr_in exemplo;
	 int socket_entrada, socket_conexao;
	 int tamanho_estrutura_socket;

	/* inicializar o socket */
	 socket_entrada = socket(AF_INET, SOCK_STREAM, 0);
	 exemplo.sin_family = AF_INET;
	 exemplo.sin_port = htons(9300);
	 exemplo.sin_addr.s_addr = inet_addr("127.0.0.1");
	 tamanho_estrutura_socket = sizeof(exemplo);

	if(bind(socket_entrada, (struct sockaddr *)&exemplo, tamanho_estrutura_socket)==0)
	{

	   listen(socket_entrada, 0);
	   int i = 0;
	   int j = 0;
       socket_conexao=accept(socket_entrada, (struct sockaddr *)&exemplo, &tamanho_estrutura_socket);

	   while(j == 0){
	   	imprime(raiz);
	   		if(j != 0){
	   			//envia 5 antes de sair para cliente saber que a conexao foi fechada
	   			send(socket_conexao,"5",strlen("5"),0);
	   			close(socket_conexao);
				close(socket_entrada);
	   		}
	   		printf("Essa a %d vez do laço. \n", i);
	   		opcao[0] = '\0';
			msg_enviar[0] = '\0';
			msg_recebido[0]= '\0';
			nome[0] = '\0';
			strcpy(operacao," ");
			curso[0] ='\0';
    		idade[0] = '\0';
			 cpf[0] = '\0';
			mensalidade[0] = '\0';
			tempo[0] = '\0';
				
	   		//operacao[0] = '\0';
	   		printf("Voltei pro inicio .\n");
			read(socket_conexao, msg_recebido , MAXBUF);
	        separa(operacao,cpf,curso,nome,idade,tempo,mensalidade, msg_recebido);	
	        printf("operacao recebida :  %s\n",operacao);
		    // verifica o codigo da operacao de acordo com isso faz a operacao pedida pelo cliente
			if (strcmp(operacao,"add") == 0)
			{
				printf("estou na ADD.\n");
				cpfConvertido = atol(cpf);
				if(buscar(raiz,cpfConvertido) == NULL ){ 
					raiz = inserirDoCliente(raiz,cpfConvertido,nome,curso,atoi(idade),atoi(tempo),atoi(mensalidade));
					printf("ENTROU NOO IF DO INSERIR.\n");

					send(socket_conexao,"0" ,strlen("0"), 0);
				}else{
					send(socket_conexao,"1" ,strlen("1"), 0);								
				}		
			}else if(strcmp(operacao,"rem") == 0)
			{
					printf("estou na rem.\n");
					// retiro o cpf da mensagem recebida
					cpfConvertido = atol(cpf);
					//caso ele nao esteja na arvore
					if(buscar(raiz,cpfConvertido) == NULL)
					{
						printf("IF DA OPCAO 2 QUE DIZ QUE NÃO TA NA LISTA E ENVIOU 1 DIZENDO QUE NAO EXISTE\n");
						send(socket_conexao,"1" ,strlen("1"), 0);
					}else
					{
						raiz = remover(raiz,cpfConvertido);
						printf("IF DA OPCAO 2 QUANDO ESTA NA LISTA  E ENVIOU 0 DIZENDO QUE EXISTE\n");
						send(socket_conexao,"0" ,strlen("0"), 0);
					}
			}			// caso a operacao seja listar 
			else if(strcmp(operacao,"lst") == 0)
			{
				printf("estou na lst.\n");
					 // aloca espaço para a variavel buffer Lista
				qtdNos = totalNo(raiz);

					//converte o cpf em char para enviar na conexao
				if(raiz != NULL){
				 	enviarRaiz(raiz, &socket_conexao,lista1);
				 	printf("\n");
				 	printf("Esta eh a lista : %s \n",lista1);
				 	lista2[0] = '0';
				 	lista2[1] = ':';
				 	strcat(lista2,lista1);
				 	send(socket_conexao,lista2,strlen(lista2),0);

				 	// zera os buffer para nao da erro no loop
				 	lista1[0] = '\0'; 
		 			lista2[0] = '\0';
		 		}else {
				 	send(socket_conexao,"1",strlen("1"),0);
				}
			}else if(strcmp(operacao,"bus") == 0){  
					printf("estou na bus.\n");         //caso a operacao seja buscar
				    cpfConvertido = atol(cpf);
				    if(buscar(raiz,cpfConvertido) != NULL){
				     	No *aux = buscar(raiz,cpfConvertido);
				     	enviaAluno(aux,&socket_conexao,msg_enviar);
				     	printf("IF DO ALUNO BUSCADO E ENVIADA CASO ESTEJA NA LISTA.\n");
				     	opcao[0] = '0';
				 		opcao[1] = ':';
				 		strcat(opcao,msg_enviar);
				 		send(socket_conexao,opcao,strlen(opcao),0);
				 		printf("mensagem envada: %s\n",msg_enviar);
				    }else {
				     	send(socket_conexao,"1",strlen("1"),0);
				    }
			}else if(strcmp(operacao,"ext") == 0)
			{
				printf("if do sair .\n");
				printf("estou no sair.\n");
				j = 1;
				send(socket_conexao,"6",strlen("6"),0);
				printf("fechou \n");

			}else if(strcmp(operacao,"del") == 0){
				printf("Mensagem recebida:  %s\n",msg_recebido);
				raiz = liberarArvore(raiz);
				 send(socket_conexao,"del",strlen("del"),0);
				
			}else 
				printf("NAO FOI NENHUMA DAS OPCOES.\n");
			// i++;
			
		}
		printf("AInda nao deu core dumped.\n");
		//close(socket_conexao);
		//close(socket_entrada);
		free(nome); 
		free(operacao);
		free(curso);
		free( opcao);
	    free(idade); 
		free(cpf);
		free(mensalidade);
		free(tempo); 
		free(msg_recebido);
		free(msg_enviar);
		/* desconectar */
			send(socket_conexao,"sair",strlen("sair"),0);
	   		close(socket_conexao);
			close(socket_entrada);
			p = fopen("sock.txt","w");
			writeARQ(raiz,p);
			fclose(p);
	} 
	else
	{
	  printf("Vixe! Nao deu para abrir a porta!\n");
	  close(socket_conexao);
	  	close(socket_entrada);
	}
}









