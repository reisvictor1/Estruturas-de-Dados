#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct LISTA_{
	NO *inicio;
	NO *fim;
	int tam;
};

struct NO_{
	TIPO item;
	NO *proximo;
};

LISTA *lista_criar(void){
	LISTA *new = (LISTA *)malloc(sizeof(LISTA));
	if(new != NULL){		
		new->inicio = NULL;
		new->fim = NULL;
		new->tam = 0;
	}
	return new;
}

void lista_apagar(LISTA *L){
	if(L != NULL && !lista_vazia(L)){
   		NO *no = L->inicio,*aux;
    	while(no != L->fim){
       	 	aux = no;
       	 	no = no->proximo;
        	free(aux);
    	}
    	free(L->fim);
    	L->inicio = NULL;
    	L->fim = NULL;
		free(L);
		L = NULL;
	}
}

TIPO lista_buscar_item(LISTA *L, TIPO chave){
	NO *aux = L->inicio;
	if(L != NULL){
		while(aux != NULL){
			if(aux->item == chave) return aux->item;
			aux = aux->proximo;
		}
	}
	return (ERRO);
}	

int lista_inserir_inicio(LISTA *L, TIPO item){
	NO *aux;
	if(L != NULL){
		aux = (NO *) malloc(sizeof(NO));
		if(aux != NULL){
			aux->item = item;
			aux->proximo = NULL;
			/*CASO DE PRIMEIRO ELEMENTO*/
			if(lista_vazia(L)){
				L->inicio = aux;
				L->fim = aux;
				L->tam++;
			}else{ /*CASO DE QUALQUER ELEMENTO QUE NÃO O PRIMEIRO*/
				aux->proximo = L->inicio;
				L->inicio = aux;
				L->tam++;
			}
			return 1; /*SUCESSO*/ 	
		}
	}
	return 0;
}

int lista_inserir_fim(LISTA *L, TIPO item){
	NO *aux = NULL;
	if(L == NULL) return (ERRO);
	aux = (NO *) malloc(sizeof(NO));
	if(aux != NULL){
		aux->item = item;
		aux->proximo = NULL;
		/*CASO DE PRIMEIRO ELEMENTO*/
		if(lista_vazia(L)){
			L->inicio = aux;
			L->fim = aux;
			L->tam++;
		}else{ /*CASO DE QUALQUER ELEMENTO QUE NÃO O PRIMEIRO*/
			L->fim->proximo = aux;
			L->fim = aux;
			L->tam++;
		}
		return 1; /*SUCESSO*/
 	}
	return 0; /*FALHA*/
}

int lista_remover_item(LISTA *L, TIPO chave){
	NO *p = NULL, *aux = NULL;
	if(L != NULL && !lista_vazia(L)){
		p = L->inicio;
		while((p != NULL) && (p->item != chave)){
			aux = p; /* aux_busca recebe o nó anterior de aux_remocao*/
			p = p->proximo;
		}
		if(p != NULL){
			if(p == L->inicio){ /*Exceção: chave no inicio*/
				L->inicio = p->proximo;
				p->proximo = NULL;
			}else{
				aux->proximo = p->proximo;
				p->proximo = NULL;
			}
			if(p == L->fim){ /* Se a chave está no último nó*/
				L->fim = aux;
			}
			L->tam--;
			free(p);	
			return 1;
		}
	}
	return 0;
}

int lista_vazia(LISTA *L){
	if(L != NULL && L->inicio == NULL) return 1;
 	return 0;
}

int lista_tamanho(LISTA *L){
	return (L != NULL ? L->tam : ERRO);	
}