#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#define MAXBUF 256
#define MAXCPF 99999999999
#define MINCPF 01000000000 


void printAluno(char linhaATUAL[])
{
			char buffer[100];
	        printf("###########################################################################################\n");
			printf("                     																       \n");
			printf("                                ALUNO 						                               \n");
			printf("                                                                                           \n");
		    char *campo = (char*)strtok(linhaATUAL, ":");
		    //printf("  Lixo: %s\n", campo); 
		    campo = (char*)strtok(NULL, ",");
			printf("  CPF : %s\n", campo); 
			campo = (char*)strtok(NULL, ",");
			printf("  Curso: %s\n", campo);
			campo = (char*)strtok(NULL, ",");
			printf("   NOME: %s\n", campo);
			campo = (char*)strtok(NULL, ",");
			printf("  IDADE: %s\n", campo);
			campo = (char*)strtok(NULL, ",");
			printf("  TEMPO: %s\n", campo);
			campo = (char*)strtok(NULL, ",");
			printf("  MENSALIDADE: %s\n", campo);

            printf("                       																	   \n");
			printf("###########################################################################################\n");
		
}


void listAluno(char linhaATUAL[])
{			char *campo = (char*)strtok(linhaATUAL, ":");
			char controle[100];
			char controle2[100];
	        printf("###########################################################################################\n");
			printf("                     																       \n");
			printf("                                     Lista de clientes                                     \n");
			printf("                                                                                            \n");
			int i = 1;
		    campo = (char*)strtok(NULL, ",");
			printf("  CPF: %s\n", campo);
			strcpy(controle,campo);
			printf("controle: %s\n",controle); 
			campo = (char*)strtok(NULL, ",");
			printf("  Curso: %s\n", campo);
			campo = (char*)strtok(NULL, ",");
			printf("  NOME: %s\n", campo);
			
			campo = (char*)strtok(NULL, ",");
			printf("  IDADE: %s\n", campo);
			campo = (char*)strtok(NULL, ",");
			printf("  TEMPO: %s\n", campo);
			campo = (char*)strtok(NULL, ",");
			printf("  MENSALIDADE: %s\n", campo);
			volta:
		while(campo != NULL && strcmp(controle,controle2) != 0){
			if(campo == NULL ) return;
			else if (campo != NULL) {
				printf("\n");      																	  
		        campo = (char*)strtok(NULL, ",");
		        if(campo != NULL){
		        	strcpy(controle2,campo);
		        	if(strcmp(controle2,controle) == 0){
		        			goto volta;
		        	}else {
		        		printf("  CPF: %s\n", campo); 
					}
				}

				campo = (char*)strtok(NULL, ",");

				if(campo != NULL)
				printf("  Curso: %s\n", campo);

				campo = (char*)strtok(NULL, ",");

				if(campo != NULL)
				 printf("  Nome : %s\n", campo);
				
				campo = (char*)strtok(NULL, ",");

				if(campo != NULL)
				printf("  IDADE: %s\n", campo);

				campo = (char*)strtok(NULL, ",");

				if(campo != NULL)
				printf("  TEMPO: %s\n", campo);

				campo = (char*)strtok(NULL, ",");

				if(campo != NULL)
				printf("  MENSALIDADE: %s\n", campo);
			}
			
    	}
            printf("                       																	   \n");
			printf("###########################################################################################\n");	
}


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


int main()
{

		
	char *curso = (char*)malloc(MAXBUF* sizeof(char*));
	char *nome = (char*)malloc(MAXBUF* sizeof(char*));
	char *idade= (char*)malloc(MAXBUF* sizeof(char*));
	char *mensalidade = (char*)malloc(MAXBUF* sizeof(char*));
	char *tempo = (char*)malloc(MAXBUF* sizeof(char*));
	int s;
	char* cpf = (char*)malloc(sizeof(char*));
	char *msg_enviar;
	struct sockaddr_in dest;
	char msg_write[MAXBUF];
	char *msg_read = (char*)malloc(MAXBUF*sizeof(char*));

	s = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(9300);
	dest.sin_addr.s_addr = inet_addr("127.0.0.1");
	

	//No* raiz = NULL;
	int soLetra = 0;           // VARIAVEL PRA VER SE TEM LETRA EM UMA STRING
	//No* aux = NULL;
	long  int CPF;              // VARIAVEL CPF DO ALUNO            // BUFFER QUE ARMAZENA A OPCAO DIGITADA POR UM ALUNO
	int ganho;					// VARIAVEL PARA ARMAZENAR GANHO TOTAL
	int escolha = 1;             // VARIAVEL PARA ESCOLHER O MOMENTO DE SAIR DO PROGRAMA
	int qtdNo;                  // variavel que diz quantos há


	connect(s, (struct sockaddr*)&dest, sizeof(dest));
	msg_enviar = (char*)malloc(MAXBUF*sizeof(char*));
	char *opcao = (char*)malloc(MAXBUF*sizeof(char*));



	/*opcao = (char*)malloc(MAXBUF*sizeof(char*));
		msg_enviar = (char*)malloc(MAXBUF*sizeof(char*));
		msg_read = (char*)malloc(30*MAXBUF*sizeof(char*)) ;
		curso= (char*)malloc(MAXBUF*sizeof(char*));
		nome = (char*)malloc(MAXBUF*sizeof(char*));
		idade = (char*)malloc(MAXBUF*sizeof(char*));
		mensalidade = (char*)malloc(MAXBUF*sizeof(char*)) ;
		cpf = (char*)malloc(MAXBUF*sizeof(char*));*/
	int i = 0;
	while(i == 0)
	{		
		strcpy(opcao," ");
		strcpy(msg_read," ");
		msg_enviar = (char*)malloc(MAXBUF*sizeof(char*));
		strcpy(msg_enviar,"\0");
		__fpurge(stdin);	
		volta:
		system("clear || clean");
		printf("         	########################################\n");
		printf("          	##                                    ##\n");
		printf("          	##             MENU                   ##\n");
		printf("          	##                                    ##\n");
		printf("          	##     1. Adicionar Aluno/Curso       ##\n");
		printf("          	##     2. Excluir                     ##\n");
		printf("        	##     3. Listar Aluno/Curso          ##\n");
		printf("        	##     4. Buscar Aluno/Curso          ##\n");
		printf("          	##     5. Deletar todos os alunos     ##\n");
		printf("	        ##     6. Sair do programa.           ##\n");
		printf("		##                                    ##\n");
		printf("		########################################\n");
		//printf("esta a opcao %s\n",opcao);
		
		printf("Escolha uma opcao: ");
		scanf("%[^\n]", opcao);
		__fpurge(stdin);
		if(soNumero(opcao) != 0 | atoi(opcao) < 1 | atoi(opcao) > 7) {
			printf("OPCAO INVALIDA\n");
			goto volta;
			
		}else{
			switch(atoi(opcao)){
					case 1: 
						volta2:
						printf("          Insira o  CPF: ");		
						scanf("%[^\n]", cpf);
						__fpurge(stdin);
						//tira o zero da primeira posicao caso tenha 
						//evita erro no atol
						tiraZero(cpf);
						if(soNumero(cpf) != 0 | atol(cpf) < 1000000000| atol(cpf) > 99999999999){
							system("clear || clean");
							printf("CPF INVALIDO\n");
							printf("1.VOLTA PARA O MENU.\n");
							printf("2.QUALQUER TECLA PARA DIGITAR NOVAMENTE.\n");
							printf("Escolha:  ");
							scanf("%[^\n]", cpf);
							__fpurge(stdin);
							if(strcmp(cpf,"1") == 0){
								goto volta;
							}else if (strcmp(cpf,"2") == 0){
								goto volta2;
							}else goto volta2;
						}
						
						printf("          Insira o curso: ");		
						scanf("%[^\n]", curso);
						__fpurge(stdin);
						
						printf("          Insira o  nome: ");		
						scanf("%[^\n]", nome);
						__fpurge(stdin);
						
						volta3:
						printf("           Insira a idade: ");		
						scanf("%[^\n]", idade);
						__fpurge(stdin);
						//tira o zero da primeira posicao caso tenha 
						//evita erro no ato
						tiraZero(idade);
						if(soNumero(idade) != 0 | atoi(idade) < 1 | atoi(idade) > 200){
							system("clear || clean");
							printf("IDADE INVALIDA\n");
							printf("1.VOLTA PARA O MENU.\n");
							printf("2.QUALQUER TECLA PARA DIGITAR NOVAMENTE.\n");
							printf("Escolha:  ");
							scanf("%[^\n]", cpf);
							__fpurge(stdin);
							if(strcmp(cpf,"1") == 0){
								goto volta;
							}else if (strcmp(cpf,"2") == 0){
								goto volta3;
							}else goto volta3;
						}
						
						volta4:
						printf("            Insira o tempo do curso: ");		
						scanf("%[^\n]", tempo);
						__fpurge(stdin);
						tiraZero(tempo);
						if(soNumero(tempo) != 0 | atoi(tempo) < 1 ){
							system("clear || clean");
							printf("        TEMPO INVALIDO\n");
							printf("1.VOLTA PARA O MENU.\n");
							printf("2.QUALQUER TECLA PARA DIGITAR NOVAMENTE.\n");
							printf("Escolha:  ");
							scanf("%[^\n]", cpf);
							__fpurge(stdin);
							if(strcmp(cpf,"1") == 0){
								goto volta;
							}else if (strcmp(cpf,"2") == 0){
								goto volta4;
							}else goto volta4;
						}
					
						volta5:
						printf("            Insira a mensalidade do curso: ");		
						scanf("%[^\n]", mensalidade);
						__fpurge(stdin);
						tiraZero(mensalidade);
						if(soNumero(mensalidade) != 0 | atoi(tempo) < 1 ){
							system("clear || clean");
							printf("         MENSALIDADE INVALIDA\n");
							system("clear || clean");
							printf("CPF INVALIDO\n");
							printf("1.VOLTA PARA O MENU.\n");
							printf("2.QUALQUER TECLA PARA DIGITAR NOVAMENTE.\n");
							printf("Escolha:  ");
							scanf("%[^\n]", cpf);
							__fpurge(stdin);
							if(strcmp(cpf,"1") == 0){
								goto volta;
							}else if (strcmp(cpf,"2") == 0){
								goto volta5;
							}else goto volta;
						}
						// junta todos os dados e envia ao servidor		
						strcat(msg_enviar ,"add:");
						strcat(msg_enviar,cpf);
						strcat(msg_enviar,",");
						strcat(msg_enviar,curso);
						strcat(msg_enviar,",");
						strcat(msg_enviar,nome);
						strcat(msg_enviar,",");
						strcat(msg_enviar,idade);
						strcat(msg_enviar,",");
						strcat(msg_enviar,tempo);
						strcat(msg_enviar,",");
						strcat(msg_enviar,mensalidade);					
						send(s,msg_enviar,MAXBUF,0);
						//printf("mesagem enviada :%s\n",msg_enviar);
						read (s, msg_read, MAXBUF);
						if(strcmp(msg_read,"1") == 0)
						printf("FALHA AO INSERIR.\n");
						else printf("SUCESSO AO INSERIR.\n");
						printf("Digite uma tecla...\n");
						//scanf("%s", msg_read);
						break;
					case 2:
					    volta7:
						printf("Insira o  CPF a ser deletado: ");		
						scanf("%[^\n]", cpf);
						__fpurge(stdin);
						//tira o zero da primeira posicao caso tenha 
						//evita erro no atol
						tiraZero(cpf);
						if(soNumero(cpf) != 0 | atol(cpf) < 1000000000| atol(cpf) > 99999999999){
							//enquanto nao for valido ele volta para o inicio de digitar cpf
							system("clear || clean");
							printf("CPF INVALIDO\n");
							printf("1.VOLTA PARA O MENU.\n");
							printf("2.QUALQUER TECLA PARA DIGITAR NOVAMENTE.\n");
							printf("Escolha:  ");
							scanf("%[^\n]", cpf);
							__fpurge(stdin);
							if(strcmp(cpf,"1") == 0){
								goto volta;
							}else if (strcmp(cpf,"2") == 0){
								goto volta7;
							}else goto volta7;
						}
						//neste caso isso só completa o restante das informaçoes por padrao
						strcat(msg_enviar ,"rem:");
						strcat(msg_enviar,cpf);
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");	
						send(s,msg_enviar,MAXBUF,0);
						//printf("mesagem enviada :%s\n",msg_enviar);
						read (s, msg_read, MAXBUF);
						if(strcmp(msg_read,"1") == 0)
						printf("Falha na exclusao.\n");
						else printf("Sucesso na exclusao.\n");
						printf("Digite uma tecla...\n");
						scanf("%s", msg_read);
						break;
					case 3 :
						strcat(msg_enviar ,"lst:");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");	
						//envia uma mensagem com o codigo lst para listar
						send(s,msg_enviar,MAXBUF,0);
						//printf("mesagem enviada :%s\n",msg_enviar);
						//printf("Esta eh a lista \n");
						strcpy(msg_read, " ");
						//printf("mensagem recebida antes do read: %s\n",msg_read);
						read (s, msg_read, MAXBUF);
						//printf("mensagem recebida apos o comando list: %s\n",msg_read);
						//printf("mensagem rebecida depois do read: %s\n",msg_read);
						//printf("\n");
						if(msg_read[0] == '0' && msg_read[1] == ':' | msg_read[0] != '1'){
							//printf("mensagem recebida apos o comando list: %s\n",msg_read);
							listAluno(msg_read);
							
						}else
							printf("A lista esta vazia.\n");
							printf("Digite uma tecla...\n");
							scanf("%s", msg_read);
						break;
					case 4:
						volta11:
						printf("          Insira o CPF do aluno procurado: ");		
						scanf("%[^\n]", cpf);
						__fpurge(stdin);
						//tira o zero da primeira posicao caso tenha 
						//evita erro no atol
						tiraZero(cpf);
						if(soNumero(cpf) != 0 | atol(cpf) < 1000000000| atol(cpf) > 99999999999)
						{
							system("clear || clean");
							printf("CPF INVALIDO\n");
							printf("1.VOLTA PARA O MENU.\n");
							printf("2.QUALQUER TECLA PARA DIGITAR NOVAMENTE.\n");
							printf("Escolha:  ");
							scanf("%[^\n]", cpf);
							__fpurge(stdin);
							if(strcmp(cpf,"1") == 0) goto volta;
							else
							goto volta11;
						}
						strcat(msg_enviar ,"bus:");      // busca um aluno 
						strcat(msg_enviar,cpf);
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						send(s,msg_enviar,MAXBUF,0);
						//printf("mesagem enviada :%s\n",msg_enviar);
						read (s, msg_read, MAXBUF);
						//printf("Mensagem recebida: %s\n",msg_read);
						if(msg_read[0] == '0' && msg_read[1] == ':' | msg_read[0] != '1'){
							printAluno(msg_read);
						}else
							printf("Aluno nao encontrado.\n");
							printf("Mensagem recebida: %s\n",msg_read);
							printf("Digite uma tecla...\n");
							scanf("%s", msg_read);
						break;
					case 5: 
						strcat(msg_enviar ,"del:");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						send(s,msg_enviar,MAXBUF,0);
						read(s,msg_read,MAXBUF);
						//printf("mesagem enviada :%s\n",msg_enviar);
						if(strcmp(msg_read,"del") == 0){
							//printf("mensagem recebida: %s\n",msg_read);
							printf(" Lista esvaziada.\n");
						}
						break;
					case 6:
						strcat(msg_enviar ,"ext:");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						strcat(msg_enviar,",");
						strcat(msg_enviar,"1");
						send(s,msg_enviar,MAXBUF,0);
						//printf("mesagem enviada :%s\n",msg_enviar);
						read (s, msg_read, MAXBUF);
						//printf("mensagem recebida: %s\n",msg_read);
						close(s);
						i = 1;
						if(strcmp(msg_read,"6") == 0){
							printf("mensagem recebida: %s\n",msg_read);
							printf("Conexao fechada...\n");
							i = 1;
						}
						break;

			}
		}	
		free(msg_enviar);
	}
		free(msg_read);
		free(opcao);

		free(curso);
		free(nome );
		free(idade);
		free(mensalidade);
		free(tempo);
		free(cpf);
    close(s);
}

