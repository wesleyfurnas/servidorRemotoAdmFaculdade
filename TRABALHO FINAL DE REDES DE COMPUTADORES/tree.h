
typedef struct Arvore No;
struct Arvore{
	long int   chave;
	No* esq;
	No* dir;
	char aluno[120];	
	char curso[120];
	int idade;
	int mensalidade;
	int tempo;
};


// FUNCAO DO MENU
void op3(No *raiz);
void op4(No* raiz);
void erroDeCPF(char buffer[]);
void  flagSucesso(char buffer[]);
//FUNCAO PARA CONVERTER CORRETAMENTE CPF
void tiraZero(char CPF[]);
int soNumero(char CPF[]);
void separa(char operacao[],char chave[],char curso[],char nome[],char idade[],char tempo[], char mensalidade[], char msg_recebido[]);


// FUNÇOES PARA TRABALHAR COM O ARQUIVO
No* readARQ (No* raiz, char nome[], char curso[], long int , int ,int , int );
void writeARQ(No* raiz, FILE *p);
No* openARQ(No* raiz, FILE *);

void imprime(No* raiz);
// FUNCOES VISTAR EM SALA
void menuMudanca();
void imprimeAluno(No* raiz);
int totalNo(No* raiz );
No* criar(long  int );
No* buscar(No* raiz, long int    );
No* inserir(No* raiz, long int  );
int lucro(No* raiz);
void imprime(No* raiz);
No* buscar(No* raiz,long int    );
No* liberarArvore(No* raiz);
No* removeRaiz(No* raiz);
No* remover(No* raiz, long int );
No* buscarPai(No* raiz, long int  );
int altura(No* raiz);
int level(No* raiz, long  int    );
void MENU();
int folha(No* raiz);
long  int    soma(No* raiz);
void MENU2();
No* minimo(No* raiz);
No* maximo(No* raiz);

No* inserirDoCliente(No* raiz,long int chave,char nome[],char curso[],int ,int ,int );

void converteLongInteiro(char string[], long int );
void converteInteiro(char string[], int );

void enviarRaiz(No *raiz, int *sock,char msg_enviar[]);

void enviaAluno(No* raiz,int *sock,char msg_enviar[]);

// Parte da lista


//funcoes para a lista
