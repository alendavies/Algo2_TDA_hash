#include "hash.h"
#include <stdlib.h>

#define FACTOR 0.75

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
		free(hash);
		return NULL;
	}
	hash->tabla = tabla;
	
	return hash;
}

int funcion_hash(const char *clave){

	return (int)clave[0];
}

nodo_t *nodo_crear(const char *clave, void *elemento){

	if(!clave || !elemento){
		return NULL;
	}

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if(!nodo){
		return NULL;
	}
	nodo->clave = clave;
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	return nodo;
}

hash_t *rehash(hash_t *hash_original){

	hash_t *nuevo_hash = hash_crear((size_t)hash_original->capacidad*2);
	int i = 0;
	while(i < hash_original->capacidad){
		nodo_t *aux = hash_original->tabla[i];
		while(aux != NULL){
			hash_insertar(nuevo_hash, aux->clave, aux->elemento, NULL);
		}
		aux = aux->siguiente;
		i++;
	}

	hash_t auxiliar;
	auxiliar = *hash_original;
	*hash_original = *nuevo_hash;
	*nuevo_hash = auxiliar;
	hash_destruir(nuevo_hash);

	return hash_original;
}

nodo_t *insertar_nodo(nodo_t *inicio, nodo_t *nodo, void ***anterior)
{
	if(!nodo || !anterior){
		return NULL;
	}

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
	if(actual->clave == nodo->clave){
		anterior = actual->elemento;
		actual->elemento = nodo->elemento;
	}

	return inicio;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento, void **anterior)
{
	if(!hash || !clave || !elemento){
		return NULL;
	}

	int factor_carga = hash->ocupados / hash->capacidad;

	if(factor_carga >= FACTOR){
		rehash(hash);
	}

	int posicion = funcion_hash(clave) % hash->capacidad;

	nodo_t *nuevo_nodo = nodo_crear(clave, elemento);

	if(!nuevo_nodo){
		return NULL;
	}

	nodo_t *lista_inicio = insertar_nodo(hash->tabla[posicion], nuevo_nodo, &anterior);

	if(!lista_inicio){
		return NULL;
	}
	hash->tabla[posicion] = lista_inicio;

	return hash;
}

void *quitar_nodo(nodo_t *inicio, const char *clave){

	nodo_t *actual = inicio;
	nodo_t *anterior = NULL;
	void *elemento = NULL;

	while(actual && actual->clave != clave){
		anterior = actual;
		actual = actual->siguiente;
	}

	if(!actual){
		return NULL;
	}
	elemento = actual->elemento;

	if(anterior){
		anterior->siguiente = actual->siguiente;
	}
	else{
		inicio = actual->siguiente;
	}
	free(actual);
	return elemento;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if(!hash || !clave){
		return NULL;
	}
	int posicion = funcion_hash(clave) % hash->capacidad;

	void *elemento = quitar_nodo(hash->tabla[posicion], clave);
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
			if(actual->clave == clave){
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
		nodo_t *aux = hash->tabla[i];
		while(aux != NULL){
			if(aux->clave == clave){
				return true;
			}
			aux = aux->siguiente;
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
	if(!hash){
		return;
	}
	for(int i = 0; i < hash->capacidad; i++){
		free(hash->tabla[i]);
	}
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
}

size_t hash_con_cada_clave(hash_t *hash, bool (*f)(const char *clave, void *valor, void *aux), void *aux)
{
	return 0;
}
