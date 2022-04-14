#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#ifdef _WIN32
# define LIMPAR_TELA system ("cls")
#else
# define LIMPAR_TELA puts("\x1b[H\x1b[2J")
#endif

struct ListaEncadeada{
    int valor;
    struct ListaEncadeada *prox;
    struct ListaEncadeada *antes;
    
};

void pressAny(){
    printf("\n\nPressione qualquer tecla...\n\n");
    getch();
}

struct ListaEncadeada *inserir(struct ListaEncadeada **no,struct ListaEncadeada **raiz){
	struct ListaEncadeada *noatual;
	struct ListaEncadeada *nonovo;
	int num;
	printf("===============\n");
	printf("Digite o valor a ser inserido OBS:Tem que ser maior que 0\n");
	scanf("%d",&num);
	printf("===============\n");
	if(num<=0){
	printf("Digite um valor válido!\n");
	void pressAny();
	return NULL;
	}else if(*no == NULL){
	*no = (struct ListaEncadeada*) malloc(sizeof(struct ListaEncadeada*));
		(*no)->valor = num;
		(*no)->prox = NULL;
		(*no)->antes = *raiz;
		return *no;
	}else{
		noatual = *no;
		while(noatual->prox != NULL){
			noatual = noatual->prox;	
	}
		nonovo = (struct ListaEncadeada*) malloc(sizeof(struct ListaEncadeada*));
		nonovo->valor = num;
		nonovo->prox = NULL;
		nonovo->antes = noatual;
		noatual->prox = nonovo;
		return nonovo;
	}	 

}

void imprimirLista(struct ListaEncadeada *temp){
	int i = 1;
	printf("===============\n");
	while(temp != NULL){
		if(temp->valor != 0){
		printf("%d)%d\n",i,temp->valor);	
		}
		temp= temp->prox;
		i++;
	}
	printf("===============\n");
		
}

void swap(struct ListaEncadeada *a, struct ListaEncadeada *b) {
    if (a == b) {
    return;	
    }

    int aux = a->valor;
    a->valor = b->valor;
    b->valor = aux;
}

struct ListaEncadeada *particiona( struct ListaEncadeada *inicio, struct ListaEncadeada *fim) {
    int x = (int)fim -> valor;
    struct ListaEncadeada *i = inicio -> antes;

    for(struct ListaEncadeada *j = inicio; j != fim; j = j -> prox) {
        if((int)(j -> valor) <= x) {
            i = (i == NULL) ? inicio : i -> prox;
            swap(i, j);
        }
    }
    i = (i == NULL) ? inicio : i -> prox;
    swap(i, fim);
    return i;
}

void quicksort(struct ListaEncadeada *raiz,struct ListaEncadeada *fim){
  if(raiz != fim && raiz != fim->prox && fim != NULL) {
      struct ListaEncadeada *p = particiona(raiz, fim);
      quicksort(raiz, p->antes);
      quicksort(p -> prox, fim);
  }
}

void opcaosMenu(){
    printf("===============\n");
    printf("Escolha uma op��oo\n");
    printf("1)Imprimir a lista\n");
    printf("2)Ordernar os Valores\n");
    printf("3)Adicionar elementos a lista\n");
    printf("4)Remover elementos da lista\n");
    printf("5)Sair\n");
    printf("===============\n");
}

void excluirElemento(int num,struct ListaEncadeada **raiz,struct ListaEncadeada *aux){
	struct ListaEncadeada *aux2;
	aux2 = (struct ListaEncadeada*) malloc(sizeof(struct ListaEncadeada*));
	aux2 = aux;
	aux = aux->prox;
	if((*raiz)->prox == NULL){
		printf("N�o foi possivel remover mais um elemento/n");
		pressAny();
		return;		
	}
	if(num == aux->valor){	
 		aux2->prox = aux->prox;
 		free(aux);
 		return;	
	}
	if((*raiz)->valor == aux2->valor){
		(*raiz) = (*raiz)->prox;
		free(aux2);
		return;	  
	}
	
	excluirElemento(num,&(*raiz),aux);
	
}

void menu(struct ListaEncadeada *inicio,struct ListaEncadeada *fim,struct ListaEncadeada *raiz){
	LIMPAR_TELA;
	int op,num;
	opcaosMenu();
	scanf("%d",&op);
	switch (op){

    case 1:
        imprimirLista(inicio);
        pressAny();
        menu(inicio,fim,raiz);
        break;

    case 2:	
    	quicksort(raiz,fim);
    	printf("Valores reestruturados");
    	pressAny();
    	menu(inicio,fim,raiz);
        break;
        
    case 3:
    	fim = inserir(&inicio,&raiz);
    	menu(inicio,fim,raiz);
    	break;
    
    
    case 4:
		printf("Digite o n�mero a ser excluido\n");
		scanf("%d",&num);
		excluirElemento(num,&inicio,inicio);
    	menu(inicio,fim,raiz);
    	break;
    
	case 5:
		 break;	
    	
    
    default:
        printf("===============\n");
        printf("Digite uma opçao valida\n");
        printf("===============\n");
        menu(inicio,fim,raiz);
        break;
    }
			
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	struct ListaEncadeada *raiz = (struct ListaEncadeada*) malloc(sizeof(struct ListaEncadeada*));
	raiz->valor = 0;
 	raiz->antes = NULL;
	struct ListaEncadeada *inicio = NULL;
	struct ListaEncadeada *fim = NULL;	
	fim = inserir(&inicio,&raiz);
	raiz->prox = inicio;
    menu(inicio,fim,raiz);
    


    return 0;
}
