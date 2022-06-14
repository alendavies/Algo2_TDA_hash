#include "src/hash.h"
#include "pa2m.h"
#include <stdlib.h>

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

void creo_un_hash_y_devuelve_un_hash_valido(){

	hash_t *hash = hash_crear(10);

	pa2m_afirmar(hash != NULL, "Creo un hash y me devuelve un hash no nulo");
	pa2m_afirmar(hash_cantidad(hash) == 0, "Creo un hash y está vacío");
	pa2m_afirmar(hash->tabla != NULL, "Creo un hash y tiene su tabla inicializada");

	hash_destruir(hash);
}

void inserto_un_elemento_y_se_inserta_correctamente(){

	hash_t *hash = hash_crear(10);
	void *anterior = NULL;

	char *mariano = "Mariano";
	char *lucas = "Lucas";
	char *manu = "Manu";
	char *guido = "Guido";
	char *matias = "Matias";
	char *azul = "Azul";

	pa2m_afirmar(hash_insertar(hash, "AC123BD", mariano, anterior) != NULL, "Inserto un elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene un elemento.");

	pa2m_afirmar(hash_insertar(hash, "OPQ976", lucas, anterior) != NULL, "Inserto un segundo elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 2, "El hash tiene dos elementos.");

	pa2m_afirmar(hash_insertar(hash, "A421ACB", manu, anterior) != NULL, "Inserto un tercer elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 3, "El hash tiene tres elementos.");

	pa2m_afirmar(hash_insertar(hash, "AA442CD", guido, anterior) != NULL, "Inserto un cuarto elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash tiene cuatro elementos.");

	pa2m_afirmar(hash_contiene(hash, "AC123BD"), "Busco un elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "AC123BD") == mariano, "El elemento de la clave pasada es el correcto");

	pa2m_afirmar(hash_contiene(hash, "OPQ976"), "Busco un segundo elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "OPQ976") == lucas, "El elemento de la clave pasada es el correcto");

	pa2m_afirmar(hash_contiene(hash, "A421ACB"), "Busco un tercer elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "A421ACB") == manu, "El elemento de la clave pasada es el correcto");

	pa2m_afirmar(hash_contiene(hash, "AA442CD"), "Busco un cuarto elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "AA442CD") == guido, "El elemento de la clave pasada es el correcto");

	pa2m_afirmar(hash_insertar(hash, "AC123BD", matias, anterior) != NULL, "Inserto un elemento con clave repetida correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash sigue teniendo la misma cantidad de elementos");

	pa2m_afirmar(hash_insertar(hash, "A421ACB", azul, anterior) != NULL, "Inserto otro elemento con clave repetida correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash sigue teniendo la misma cantidad de elementos");

	hash_destruir_todo(hash, free);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creacion de hash");
	creo_un_hash_y_devuelve_un_hash_valido();

	pa2m_nuevo_grupo("Pruebas de insertar");
	inserto_un_elemento_y_se_inserta_correctamente();

	return pa2m_mostrar_reporte();
}
