#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TMAX 15

struct subseq
{
    int indice_menor;
    int indice_maior;
};

typedef struct subseq seq;

void quick_sort(int* a , int esquerda , int direita);

seq retorna_subsequencia(int* V, int soma);

void imprimirvet(int* V);

void quick_sort(int *a, int esquerda, int direita) {
    int i, j, pivo, y;
     
    i = esquerda;
    j = direita;
    pivo = a[(esquerda + direita) / 2];
     
    while(i <= j) {
        while(a[i] < pivo && i < direita) {
            i++;
        }
        while(a[j] > pivo && j > esquerda) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > esquerda) {
        quick_sort(a, esquerda, j);
    }
    if(i < direita) {
        quick_sort(a, i, direita);
    }
}

seq retorna_subsequencia(int* V, int soma){
    seq resposta;
    int i,j,acm;

    resposta.indice_maior=-1;

    for(i=0;i<TMAX;i++){
        if(V[i]<soma){
            acm=V[i];
            for(j=i+1;j<TMAX;j++){
                if(acm+V[j]>soma) break;
                else if(acm+V[j]==soma){
                    printf("Sequencia possível para a soma %d = %d + %d = V[%d] + V[%d]\n",soma,V[i],V[j],i,j);
                    resposta.indice_maior=j;
                    resposta.indice_menor=i;
                }
        }
        }else if (V[i]==soma){printf("Sequencia possível para a soma %d  = %d = V[%d]\n",soma,V[i],i);resposta.indice_maior=i;resposta.indice_menor=-1;}
        else return resposta;
    }

    return resposta;
}

void imprimirvet(int* V){
    int i;
    for(i=0;i<TMAX;i++){
        printf("%d ",V[i]);
    }
    printf("\n\n");
}

int main(void){

//cria o vetor e variáveis auxiliares
int* V=NULL;
int seed,i,carocos,soma;
seq resposta;

V=(int*)malloc(sizeof(int)*TMAX);
if(V==NULL){printf("Deu erro aqui ó\n"); exit(1);}

// printf("Quantos carocos tinha na maca que Jose Caolho comeu?\n");
// scanf("%d",&carocos);

 printf("Quantos carocos tem a SOMA que salva Jose Caolho?\n");
 scanf("%d",&soma);

//gera uma semente para geração de um vetor aleatório
srand(time(NULL));

//Preenchimento do vetor com valores aleatórios
for(i=0;i<TMAX;i++){
    V[i]=(rand()%10);// A quantidade de caroços vai de 0 a 1089, logo o rand é % 1840
}

printf("Vetor desordenado: ");
imprimirvet(V);

quick_sort(V,0,TMAX-1);

printf("Vetor ordenado: ");
imprimirvet(V);

resposta=retorna_subsequencia(V,soma);

if(resposta.indice_maior==-1) printf("Não há sequências possíveis\n");



    return 0;
}
