/***************************************************************************

	Trabalho prático de Teoria das Linguagens Formais e Automatos 
	Universidade Federal de Mato Grosso 			- UFMT
	Faculdade de Engenharia de Várzea Grande 		- FAENG

	Grupo:
	Gustavo Mene Ale Primo 		
	Thayse Oliveira Pereira		
	Vitor de Morais Siqueira 	

***************************************************************************/

#include <stdio.h>


//definir tamanho da fita
#define TAMANHO_FITA 64 

/***************************************************************************
 *                  		ESTRUTURAS BASE
***************************************************************************/

enum {
	dir,
	esq,
	sta
};

enum {
	zer,
	um,
	sus,
	nul
};

enum nome_estados{
	q0,q1,q2,q3,q4,q5,q6,q7,
	q8,q9,q10,q11,q12,q13,q14,
	q15,q16,q17,q18,q19,q20,q21,
	q22,q23,q24,q25,q26,q27,q28,
	q29,q30,q31,q32,q33,q34,qM,
	qF
};

int fita[TAMANHO_FITA] = {[0 ... TAMANHO_FITA-1] = nul}; //fita da maquina preenchida com nul's 
// = {nul,1,0,0,1,sus,1,1,0,1,nul,nul,nul,nul,nul,nul,sus};
int head;       //cabeça da maquina
int passos;     //contador de passos dados (opcional)
int uso_fita;   //contador do uso da fita (opcional)

typedef struct {
	//estrutura da transição
	int lido;   
	int gravar;
	int mover;
	int proximo;
} transicao_t;

typedef struct {
	//estrutura do estado
	int nome;
	transicao_t transicao[4]; //tupla de transições do estado
} estado_t;

/***************************************************************************
 *                  		FUNÇÕES DE ESTÉTICA
***************************************************************************/

void mostrarFita(){
	//mostra a fita na tela
	//meramente estetico

	int i = 0;
	#ifdef __unix__
		printf("\x1b[1A");
	#else
		printf("\n");
	#endif

	while(i < uso_fita){
		
		#ifdef __unix__
			if(head == i){
				printf("\x1b[7m");
			}
		#endif

		if(fita[i] <= 1) 
			printf("%d",fita[i]);
		else if (fita[i] == sus)
			printf(".");
		else
			printf(" ");

		if(head == i){
			printf("\x1b[0m");
		}
		i++;
	}
	//printf(".");

}

/***************************************************************************
 *                  	FUNÇÕES DA MÁQUINA DE TURING
***************************************************************************/

int ler(){
	//le da fita
	return fita[head];
}

void mover(int direcao){
	//move a cabeça de leitura
	if(direcao == dir){
		head++;
	}
	if(direcao == esq){
		head--;
	}
}

void gravar(int estado){
	//grava na fita
	fita[head] = estado;
}


/***************************************************************************
 *                  	ESTADOS DA MAQUINA DE TURING
***************************************************************************/

//estados da maquina de turing, somador de n bits
estado_t estados[] =  \
{
	{q0,{{zer,zer,dir,q0},{um,um,dir,q0},{sus,sus,esq,q1},{nul,nul,sta,qM}}},
	{q1,{{zer,sus,dir,q3},{um,sus,dir,q2},{sus,sus,esq,q1},{nul,nul,sta,qM}}},
	{q2,{{zer,zer,dir,q2},{um,um,dir,q2},{sus,sus,dir,q2},{nul,nul,esq,q7}}},
	{q3,{{zer,zer,dir,q3},{um,um,dir,q3},{sus,sus,dir,q3},{nul,nul,esq,q4}}},
	{q4,{{zer,sus,dir,q6},{um,sus,dir,q9},{sus,sus,esq,q4},{nul,nul,sta,qM}}},
	{q5,{{zer,zer,dir,q5},{um,um,dir,q5},{sus,sus,dir,q5},{nul,nul,dir,q28}}},
	{q6,{{nul,nul,sta,qM},{nul,nul,sta,qM},{sus,sus,dir,q6},{nul,nul,dir,q15}}},
	{q7,{{zer,sus,dir,q9},{um,sus,dir,q8},{sus,sus,esq,q7},{nul,nul,sta,qM}}},
	{q8,{{zer,zer,dir,q8},{um,um,dir,q8},{sus,sus,dir,q8},{nul,nul,dir,q17}}},
	{q9,{{zer,zer,dir,q9},{um,um,dir,q9},{sus,sus,dir,q9},{nul,nul,dir,q10}}},
	{q10,{{zer,zer,esq,q11},{um,um,esq,q11},{sus,sus,esq,q11},{nul,nul,dir,q10}}},
	{q11,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,sta,qM},{nul,um,esq,q14}}},
	{q12,{{zer,zer,esq,q13},{um,um,esq,q13},{sus,sus,esq,q12},{nul,nul,dir,q33}}},
	{q13,{{zer,zer,esq,q13},{um,um,esq,q13},{sus,sus,esq,q1},{nul,nul,sta,qM}}},
	{q14,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,esq,q12},{nul,nul,esq,q14}}},
	{q15,{{zer,zer,esq,q16},{um,um,esq,q16},{sus,sus,esq,q16},{nul,nul,dir,q15}}},
	{q16,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,sta,qM},{nul,zer,esq,q14}}},
	{q17,{{zer,zer,esq,q18},{um,um,esq,q18},{sus,sus,esq,q18},{nul,nul,dir,q17}}},
	{q18,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,sta,qM},{nul,zer,esq,q19}}},
	{q19,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,esq,q20},{nul,nul,esq,q19}}},
	{q20,{{zer,zer,esq,q21},{um,um,esq,q21},{sus,sus,esq,q20},{nul,nul,dir,q30}}},
	{q21,{{zer,zer,esq,q21},{um,um,esq,q21},{sus,sus,esq,q22},{nul,nul,sta,qF}}},
	{q22,{{zer,sus,dir,q23},{um,sus,dir,q24},{sus,sus,esq,q22},{nul,nul,sta,qM}}},
	{q23,{{zer,zer,dir,q23},{um,um,dir,q23},{sus,sus,dir,q23},{nul,nul,esq,q25}}},
	{q24,{{zer,zer,dir,q24},{um,um,dir,q24},{sus,sus,dir,q24},{nul,nul,esq,q26}}},
	{q25,{{zer,sus,dir,q27},{um,sus,dir,q8},{sus,sus,esq,q25},{nul,nul,sta,qM}}},
	{q26,{{zer,sus,dir,q8},{um,sus,dir,q5},{sus,sus,esq,q26},{nul,nul,sta,qM}}},
	{q27,{{zer,zer,dir,q27},{um,um,dir,q27},{sus,sus,dir,q27},{nul,nul,dir,q31}}},
	{q28,{{zer,zer,esq,q29},{um,um,esq,q29},{sus,sus,esq,q29},{nul,nul,dir,q28}}},
	{q29,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,sta,qM},{nul,um,esq,q19}}},
	{q30,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,dir,q30},{nul,nul,dir,q10}}},
	{q31,{{zer,zer,esq,q32},{um,um,esq,q32},{sus,sus,esq,q32},{nul,nul,dir,q31}}},
	{q32,{{zer,zer,sta,qM},{um,um,sta,qM},{sus,sus,sta,qM},{nul,um,esq,q14}}},
	{q33,{{zer,zer,dir,q34},{um,um,dir,q34},{sus,sus,dir,q33},{nul,nul,dir,q33}}},
	{q34,{{zer,zer,dir,q34},{um,um,dir,q34},{sus,sus,sta,qF},{nul,nul,sta,qF}}}
};

/***************************************************************************
 *                  	SIMULADOR MAQUINA DE TURING
***************************************************************************/

int machine(int estado){
	//maquina de turing
	int lido = ler();
	transicao_t * aux = estados[estado].transicao;

	mostrarFita();
	printf("\tEstado: %2d | Passos %d",estado,passos);
	setbuf(stdin,NULL);
	getchar();

	if(estado == qM){
		//estado morte
		printf("\nRejeitado! Passos: %d\n",passos);
		return qM;
	}
	if(estado == qF){
		//estado final, aceitação
		printf("\nAceito! Passos: %d\n",passos);
		return qF;
	}

	if(lido != aux[lido].gravar){
		//grava na fita
		gravar(aux[lido].gravar); 
	}
	mover(aux[lido].mover); //move cabeçote
	
	passos++; //contador de passos (opcional)

	return aux[lido].proximo; //proximo estado

}

int main(){
	char aux[20];
	int curestado;

	printf("Fita: ");
	scanf("%[^\n]",aux);

	int i=0;

	while(aux[i] != '\0'){
		if(aux[i] == '0'){
			fita[i+1] = 0;
		}

		if(aux[i] == '1'){
			fita[i+1] = 1;
		}
		
		if(aux[i] == '.'){
			fita[i+1] = sus;
		}
		i++;
	}
	fita[2*i]=sus;
	fita[2*i+1]='\0';
	uso_fita = 2*i+1;
	mostrarFita();
	setbuf(stdin,NULL);
	getchar();

	printf("\n");
	head = 1;
	passos = 0;

	curestado = q0;
	do{
		curestado = machine(curestado);
	}while(curestado != qM && curestado != qF);
}
