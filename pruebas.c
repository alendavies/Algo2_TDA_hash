#include "src/hash.h"
#include "pa2m.h"

void creo_un_hash_y_devuelve_un_hash_valido(){

	hash_t *hash = hash_crear(10);

	pa2m_afirmar(hash != NULL, "Creo un hash y me devuelve un hash no nulo");
	pa2m_afirmar(hash_cantidad(hash) == 0, "Creo un hash y está vacío");
	//pa2m_afirmar(hash->tabla != NULL, "Creo un hash y tiene su tabla inicializada");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creacion de hash");
	creo_un_hash_y_devuelve_un_hash_valido();

	pa2m_nuevo_grupo("Pruebas de insertar");

	return pa2m_mostrar_reporte();
}
