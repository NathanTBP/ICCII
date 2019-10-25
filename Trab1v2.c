#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct listaduplacabeca LISTA;

typedef struct nozinho NO;

struct listaduplacabeca{
    NO* inicio;
    int tamanho;
};

struct nozinho{
    struct nozinho* proximo;
    int item;
};

LISTA* lista_criar(void){
    LISTA* p=NULL;
    p=(LISTA*) malloc(sizeof(LISTA));
    if(p==NULL) {printf("ERRO NA ALOCAÇÃO"); exit (1);}

    p->inicio=NULL;
    p->tamanho=0;
    return p;
}

void lista_inserirnofim(LISTA* abas, int item){

    NO* p;
    p=abas->inicio;

    NO* novono=NULL;
    novono=(NO*) malloc(sizeof(NO));
    if(novono==NULL) {printf("ERRO NA ALOCAÇÃO"); exit (1);}
    
        while(p->proximo!=NULL){
            p=p->proximo;
        }

        p->proximo=novono;
        novono->proximo=NULL;
        abas->tamanho++;
    
    return;
}

void imprimirlista(LISTA* V){
    NO* p;
    p=V->inicio;
    while(p!=NULL){
        printf("%d ",p->item);
            p=p->proximo;
        }
        printf("\n");
        return;
}

//A função merge_lista recebe a referencia de duas listas em ordem crescente e reordena seus ponteiros para que, sem alocar novos nós, 
//a primeira lista recebe todos os elementos em ordem crescente 
//obs, B é excluida

LISTA* merge_lista(LISTA* (*sublistaA), LISTA* (*sublistaB)){

//Inicializa o ponteiro para a lista resultado e ponteiros auxiliares para percorrer as listas

	LISTA* listaOrdenada=NULL;
	NO* ponteiroAuxiliarR=NULL;
	NO* ponteiroAuxiliarA=NULL;
	NO* ponteiroAuxiliarB=NULL;
	int TamA;
	int TamB;
	//Verifica se as listas existem e aponta os ponteiros auxiliares para o primeiro valor válidos das listas
	if((*sublistaA)->inicio!=NULL) ponteiroAuxiliarA=(*sublistaA)->inicio->proximo;
	if((*sublistaB)->inicio!=NULL) ponteiroAuxiliarB=(*sublistaB)->inicio->proximo;

	if((*sublistaA)->inicio==NULL && (*sublistaB)->inicio==NULL) return NULL;
	listaOrdenada=lista_criar();

	ponteiroAuxiliarR=listaOrdenada->inicio;

	//Ajusta o tamanho das listas
	TamA=(*sublistaA)->tamanho;
	TamB=(*sublistaA)->tamanho;
	listaOrdenada->tamanho=TamA+TamB;

	if(TamA>0||TamB>0){
		//Verifica se ainda existem nós nas listas e faz a intercalação ordenada alterando os ponteiros dos nós
		while(TamA>0&&TamB>0){
			if(ponteiroAuxiliarA->item <= ponteiroAuxiliarB->item) {
                ponteiroAuxiliarR->proximo = ponteiroAuxiliarA;
                ponteiroAuxiliarA = ponteiroAuxiliarA->proximo; 
                TamA--;
            }
			else {
                ponteiroAuxiliarR->proximo = ponteiroAuxiliarB;
                ponteiroAuxiliarB = ponteiroAuxiliarB->proximo; 
                TamB--;
                }
		}
		while(TamA>0){
			ponteiroAuxiliarR->proximo = ponteiroAuxiliarA; 
            ponteiroAuxiliarA = ponteiroAuxiliarA->proximo; 
            TamA--;
		}
		while(TamB>0){
			ponteiroAuxiliarR->item = ponteiroAuxiliarB->item; 
            ponteiroAuxiliarB = ponteiroAuxiliarB->proximo; 
            ponteiroAuxiliarR = ponteiroAuxiliarR->proximo; 
            TamB--; 
		}

		ponteiroAuxiliarR->proximo=NULL;

	}
	//Exclui as listas(estruturas, não nós) A e B, dado que seus elementos só fazem sentido na lista ordenada

	(*sublistaA)->inicio=NULL;
	free((*sublistaA));
	(*sublistaB)->inicio=NULL;
	free((*sublistaB));
	return listaOrdenada;
}


void dividenomeio( LISTA* lista, LISTA* subLista1, LISTA* subLista2){
    NO* ponteirodafrente=NULL;
    NO* ponteirodomeio=NULL;

    if(lista != NULL) ponteirodomeio=lista->inicio;
    else return;
    if(lista->inicio != NULL) ponteirodafrente=lista->inicio->proximo;
    else return;

    // Começa a percorrer a lista com os ponteiros, para cada vez que o ponteirodomeio ainda, ponteirodafrente anda duas vezes, resultando nos elementos final e do meio do vetor.
    while (ponteirodafrente!=NULL){
        ponteirodafrente = ponteirodafrente->proximo;
        if(ponteirodafrente != NULL){
            ponteirodomeio = ponteirodomeio->proximo;
            ponteirodafrente = ponteirodafrente->proximo;
        }
        subLista1->inicio=lista->inicio;
        subLista2->inicio=ponteirodomeio->proximo;
        ponteirodomeio->proximo=NULL;
    }

}



// Função a ser chamada para realizar a ordenação de uma lista encadeada

void mergesort_lista(LISTA* lista){

    //  Se a lista está vazia, a função não faz nada

	if(lista==NULL) return;

    // Inicializando os ponteiros auxiliares
	NO* inicio=NULL;
    
    // Criam-se duas sublistas, sendo uma a metade da direita e outra a metade da esquerda
	LISTA* subLista1=NULL;
	LISTA* subLista2=NULL;

	inicio=lista->inicio;

	subLista1=lista_criar();
	subLista2=lista_criar();

	//Verifica se a lista tem tamanho 0 ou 1, que, por definição, já estão ordenadas
	if(inicio->proximo==NULL) return;
	if(inicio->proximo->proximo==NULL) return;

    //Chamada que divide a lista na metade, criando 2 sublistas
	dividenomeio(lista,subLista1,subLista2);

    //Chama recursivamente a ordenação para a lista dos primeiros elementos depois para o resto
	mergesort_lista(subLista1);
	mergesort_lista(subLista2);

    //Junta os vetores após a recursão ser encerrada
	lista=merge_lista(&subLista1,&subLista2);
	return;
}


int main (void){
//cria o vetor e variáveis auxiliares

LISTA* V=NULL;
V=lista_criar();

int i,t;

scanf("%d",&t);

srand(time(NULL));

for(i=0;i<t;i++){
    lista_inserirnofim(V, rand()%100);
}

printf("Lista desordenada: ");

imprimirlista(V);


mergesort_lista(V);


printf("Lista ordenada: ");

imprimirlista(V);

	return 0;
}