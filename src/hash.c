#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define FACTOR_CARGA_MAX 70
#define DIVISOR_CLAVES 123456789

typedef struct nodo {
	void *elemento;
	const char *clave;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	nodo_t **tabla;
	int capacidad;
	int ocupados;
};

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if(!hash){
		return NULL;
	}
	hash->capacidad = (int)capacidad;

	nodo_t **tabla = calloc(capacidad, sizeof(nodo_t *));
	if(!tabla){
		hash_destruir(hash);
		return NULL;
	}
	hash->tabla = tabla;
	
	return hash;
}

size_t funcion_hash(hash_t* hash, const char* clave){

	size_t auxiliar = 0;
	for(int i = 0; i <= strlen(clave);i++){
	auxiliar += ((size_t)(clave[i])) % DIVISOR_CLAVES;
	}
	return auxiliar;
}

char *duplicar_clave(const char *string)
{
	if (!string)
		return NULL;

	char *duplicado = malloc(strlen(string) + 1);
	if (!duplicado)
		return NULL;

	strcpy(duplicado, string);

	return duplicado;
}

nodo_t *nodo_crear(const char *clave, void *elemento){

	if(!clave || !elemento){
		return NULL;
	}

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if(!nodo){
		return NULL;
	}

	char* duplicado = duplicar_clave(clave);

	nodo->clave = duplicado;
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	return nodo;
}

hash_t *rehash(hash_t *hash_original){

	hash_t *nuevo_hash = hash_crear((size_t)hash_original->capacidad*2);
	int i = 0;
	while(i < hash_original->capacidad){
		nodo_t *actual = hash_original->tabla[i];
		while(actual != NULL){
			hash_insertar(nuevo_hash, actual->clave, actual->elemento, NULL);
		}
		actual = actual->siguiente;
		i++;
	}

	hash_t auxiliar;
	auxiliar = *hash_original;
	*hash_original = *nuevo_hash;
	*nuevo_hash = auxiliar;

	hash_destruir_todo(nuevo_hash, NULL);

	return hash_original;
}

nodo_t *insertar_nodo(nodo_t *inicio, bool *repetida, nodo_t *nodo, void ***anterior)
{
	if(!inicio){
		return nodo;
	}

	nodo_t *actual = inicio;

	while(actual->siguiente != NULL && actual->clave != nodo->clave){
		actual = actual->siguiente;
	}

	if(!actual->siguiente){
		actual->siguiente = nodo;
		nodo->siguiente = NULL;
	}
	
	if(strcmp(actual->clave, nodo->clave) == 0){
		*repetida = true;
		if(anterior && *anterior){
			**anterior = actual->elemento;
			actual->elemento = nodo->elemento;
		}
	}

	return inicio;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento, void **anterior)
{
	if(!hash || !clave){
		return NULL;
	}

	int factor_carga = (((hash->ocupados+1)*100) / hash->capacidad);

	if(factor_carga > FACTOR_CARGA_MAX){
		rehash(hash);
	}

	int posicion = (int)funcion_hash(hash, clave) % hash->capacidad;

	nodo_t *nuevo_nodo = nodo_crear(clave, elemento);

	if(!nuevo_nodo){
		return NULL;
	}
	bool repetida = false;

	nodo_t *lista_inicio = insertar_nodo(hash->tabla[posicion], &repetida, nuevo_nodo, &anterior);

	hash->tabla[posicion] = lista_inicio;
	if(repetida == false){
		hash->ocupados++;
	}

	return hash;
}

nodo_t *quitar_nodo(nodo_t *inicio, const char *clave, void **elemento){

	nodo_t *actual = inicio;
	nodo_t *anterior = NULL;

	while(actual != NULL && strcmp(actual->clave, clave) != 0){
		anterior = actual;
		actual = actual->siguiente;
	}

	if(!actual){
		return inicio;
	}
	*elemento = actual->elemento;

	if(anterior){
		anterior->siguiente = actual->siguiente;
	}
	else{
		inicio = actual->siguiente;
	}
	free((char*)actual->clave);
	free(actual);
	return inicio;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if(!hash || !clave || hash->ocupados == 0){
		return NULL;
	}
	int posicion = (int)funcion_hash(hash, clave) % hash->capacidad;
	void *elemento = NULL;

	nodo_t *lista_inicio = quitar_nodo(hash->tabla[posicion], clave, &elemento);

	hash->tabla[posicion] = lista_inicio;

	if(elemento != NULL){
		hash->ocupados--;
	}

	return elemento;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if(!hash || !clave){
		return NULL;
	}
	int i = 0;
	while(i < hash->capacidad){
		nodo_t *actual = hash->tabla[i];
		while(actual != NULL){
			if(strcmp(actual->clave, clave) == 0){
				return actual->elemento;
			}
			actual = actual->siguiente;
		}
		i++;
	}
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if(!hash || !clave){
		return false;
	}
	int i = 0;
	while(i < hash->capacidad){
		nodo_t *actual = hash->tabla[i];
		while(actual != NULL){
			if(strcmp(actual->clave, clave) == 0){
				return true;
			}
			actual = actual->siguiente;
		}
		i++;
	}
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if(!hash){
		return 0;
	}
	return (size_t)hash->ocupados;
}


void hash_destruir(hash_t *hash)
{
	if(!hash || !hash->tabla){
		return;
	}
	free(hash->tabla);
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if(!hash){
		return;
	}
	int i = 0;
	while(i < hash->capacidad){
		nodo_t *actual = hash->tabla[i];
		while(actual!= NULL){
			nodo_t *aux = actual;
			if(destructor != NULL){
				destructor(actual->elemento);
			}
			actual = actual->siguiente;
			free((char*)aux->clave);
			free(aux);
		}
		i++;
	}

	hash_destruir(hash);
}

size_t hash_con_cada_clave(hash_t *hash, bool (*f)(const char *clave, void *valor, void *aux), void *aux)
{
	if(!hash || !f){
		return 0;
	}
	int i = 0;
	size_t cantidad = 0;
	while(i < hash->capacidad){
		nodo_t *actual = hash->tabla[i];
		while(actual != NULL){
			cantidad++;
			if(f(actual->clave, actual->elemento, aux) == false){
				return cantidad;
			}
			actual = actual->siguiente;
		}
		i++;
	}
	
	return cantidad;
}
