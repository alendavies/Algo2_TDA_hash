#include "src/hash.h"
// #include "src/hash.c" // BORRAR DESPUES
#include "pa2m.h"

#include <stdlib.h>
#include <string.h>

// entrada_t *en_posicion(hash_t *hash, size_t posicion);

void pruebas_insercion_simple()
{
	hash_t *hash = hash_crear(10);

	void *anterior = NULL;

	pa2m_afirmar( hash_cantidad(hash) == 0, "El hash está vacío.");
	pa2m_afirmar( !!hash_insertar(hash, "AC123BD", "Mariano", &anterior), "Se insertó 'AC123BD'." );
	pa2m_afirmar( hash_cantidad(hash) == 1, "El hash tiene un elemento.");
	pa2m_afirmar( !!hash_insertar(hash, "OPQ976", "Lucas", &anterior), "Se insertó el 'OPQ976'." );
	pa2m_afirmar( hash_cantidad(hash) == 2, "El hash tiene dos elementos.");
	pa2m_afirmar( !!hash_insertar(hash, "A421ACB", "Manu", &anterior), "Se insertó el 'A421ACB'." );
	pa2m_afirmar( hash_cantidad(hash) == 3, "El hash tiene tres elementos.");

	pa2m_afirmar( hash_contiene(hash, "AC123BD"), "El hash contiene 'AC123BD'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "AC123BD"), "Mariano") == 0, "El elemento de la clave 'AC123BD' es Mariano.");
	pa2m_afirmar( hash_contiene(hash, "OPQ976"), "El hash contiene 'OPQ976'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "OPQ976"), "Lucas") == 0, "El elemento de la clave 'OPQ976' es Lucas.");
	pa2m_afirmar( hash_contiene(hash, "A421ACB"), "El hash contiene 'A421ACB'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "A421ACB"), "Manu") == 0, "El elemento de la clave 'A421ACB' es Manu.");
	
	hash_destruir_todo(hash, NULL);
}

void pruebas_insercion_con_claves_repetidas()
{
	hash_t *hash = hash_crear(10);

	void *anterior = NULL;

	pa2m_afirmar( hash_cantidad(hash) == 0, "El hash está vacío.");
	pa2m_afirmar( !!hash_insertar(hash, "AC123BD", "Mariano", &anterior), "Se insertó 'AC123BD'." );
	pa2m_afirmar( hash_cantidad(hash) == 1, "El hash tiene un elemento.");
	pa2m_afirmar( !!hash_insertar(hash, "OPQ976", "Lucas", &anterior), "Se insertó el 'OPQ976'." );
	pa2m_afirmar( hash_cantidad(hash) == 2, "El hash tiene dos elementos.");
	pa2m_afirmar( !!hash_insertar(hash, "A421ACB", "Manu", &anterior), "Se insertó el 'A421ACB'." );
	pa2m_afirmar( hash_cantidad(hash) == 3, "El hash tiene tres elementos.");

	pa2m_afirmar( hash_contiene(hash, "AC123BD"), "El hash contiene 'AC123BD'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "AC123BD"), "Mariano") == 0, "El elemento de la clave 'AC123BD' es Mariano.");
	pa2m_afirmar( hash_contiene(hash, "OPQ976"), "El hash contiene 'OPQ976'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "OPQ976") ,"Lucas") == 0, "El elemento de la clave 'OPQ976' es Lucas.");
	pa2m_afirmar( hash_contiene(hash, "A421ACB"), "El hash contiene 'A421ACB'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "A421ACB"), "Manu") == 0, "El elemento de la clave 'A421ACB' es Manu.");

	pa2m_afirmar( !!hash_insertar(hash, "AC123BD", "Alen", &anterior), "Se volvió a insertar 'AC123BD'." );
	// free(anterior);
	pa2m_afirmar( hash_cantidad(hash) == 3, "El hash sigue teniendo tres elementos.");
	pa2m_afirmar( hash_contiene(hash, "AC123BD"), "El hash contiene 'AC123BD'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "AC123BD"), "Alen") == 0, "El elemento de la clave 'AC123BD' es Alen.");

	pa2m_afirmar( !!hash_insertar(hash, "OPQ976", "Fabi", &anterior), "Se volvió a insertar 'OPQ976'." );
	// free(anterior);
	pa2m_afirmar( hash_cantidad(hash) == 3, "El hash sigue teniendo tres elementos.");
	pa2m_afirmar( hash_contiene(hash, "OPQ976"), "El hash contiene 'OPQ976'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "OPQ976"), "Fabi") == 0, "El elemento de la clave 'OPQ976' es Fabi.");

	pa2m_afirmar( !!hash_insertar(hash, "A421ACB", "Fran", &anterior), "Se volvió a insertar 'A421ACB'." );
	// free(anterior);
	pa2m_afirmar( hash_cantidad(hash) == 3, "El hash sigue teniendo tres elementos.");
	pa2m_afirmar( hash_contiene(hash, "A421ACB"), "El hash contiene 'A421ACB'.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "A421ACB"), "Fran") == 0, "El elemento de la clave 'A421ACB' es Fran.");

	hash_destruir_todo(hash, NULL);
	
}

void pruebas_rehash()
{
	hash_t *hash = hash_crear(3);

	void *anterior = NULL;

	/* char *mariano = (char *)malloc(8*sizeof(char));
	char *lucas = (char *)malloc(6*sizeof(char));
	char *manu = (char *)malloc(5*sizeof(char));
	char *alen = (char *)malloc(5*sizeof(char));
	char *fabi = (char *)malloc(5*sizeof(char));
	char *fran = (char *)malloc(5*sizeof(char)); */

	char *mariano = "Mariano";
	char *lucas = "Lucas";
	char *manu = "Manu";
	char *alen = "Alen";
	char *fabi = "Fabi";
	char *fran = "Fran";

	pa2m_afirmar( !!hash_insertar(hash, "AC123BD", mariano, &anterior), "Se insertó 'AC123BD'." );
	pa2m_afirmar( hash_cantidad(hash) == 1, "El hash tiene un elemento.");
	pa2m_afirmar( !!hash_insertar(hash, "OPQ976", lucas, &anterior), "Se insertó el 'OPQ976'." );
	pa2m_afirmar( hash_cantidad(hash) == 2, "El hash tiene dos elementos.");
	pa2m_afirmar( !!hash_insertar(hash, "A421ACB", manu, &anterior), "Se insertó el 'A421ACB'." );
	pa2m_afirmar( hash_cantidad(hash) == 3, "El hash tiene tres elementos.");
	pa2m_afirmar( !!hash_insertar(hash, "EFGHI", alen, &anterior), "Se insertó 'EFGHI'." );
	pa2m_afirmar( hash_cantidad(hash) == 4, "El hash tiene cuatro elementos.");
	pa2m_afirmar( !!hash_insertar(hash, "JKLMN", fabi, &anterior), "Se insertó el 'JKLMN'." );
	pa2m_afirmar( hash_cantidad(hash) == 5, "El hash tiene cinco elementos.");
	pa2m_afirmar( !!hash_insertar(hash, "OPQRST", fran, &anterior), "Se insertó el 'OPQRST'." );
	pa2m_afirmar( hash_cantidad(hash) == 6, "El hash tiene seis elementos.");

	hash_destruir_todo(hash, NULL);
}

void pruebas_de_insercion_replica_chanu()
{
	hash_t *hash = hash_crear(3);

	pa2m_afirmar( !!hash_insertar(hash, "CLAVE1", "1", NULL), "Inserto <CLAVE1,1>");
	pa2m_afirmar( !!hash_insertar(hash, "CLAVE2", "2", NULL), "Inserto <CLAVE2,2>");
	pa2m_afirmar( !!hash_insertar(hash, "CLAVE3", "3", NULL), "Inserto <CLAVE3,3>");
	pa2m_afirmar( !!hash_insertar(hash, "CLAVE4", "4", NULL), "Inserto <CLAVE4,4>");
	pa2m_afirmar( hash_contiene(hash, "CLAVE1"), "Busco CLAVE1");
	pa2m_afirmar( hash_contiene(hash, "CLAVE2"), "Busco CLAVE2");
	pa2m_afirmar( hash_contiene(hash, "CLAVE3"), "Busco CLAVE3");
	pa2m_afirmar( hash_contiene(hash, "CLAVE4"), "Busco CLAVE4");
	pa2m_afirmar( !!hash_insertar(hash, "CLAVE1", "5", NULL), "Inserto <CLAVE1,5>");
	pa2m_afirmar( !!hash_insertar(hash, "CLAVE2", "6", NULL), "Inserto <CLAVE2,6>");
	pa2m_afirmar( hash_contiene(hash, "CLAVE1"), "Busco CLAVE1");
	pa2m_afirmar( hash_contiene(hash, "CLAVE2"), "Busco CLAVE2");
	pa2m_afirmar( hash_contiene(hash, "CLAVE3"), "Busco CLAVE3");
	pa2m_afirmar( hash_contiene(hash, "CLAVE4"), "Busco CLAVE4");
	pa2m_afirmar( !!hash_insertar(hash, "CLAVE1", "7", NULL), "Inserto <CLAVE1,7>");
	pa2m_afirmar( !!hash_insertar(hash, "CLAVE2", "8", NULL), "Inserto <CLAVE2,8>");
	pa2m_afirmar( hash_contiene(hash, "CLAVE1"), "Busco CLAVE1");
	pa2m_afirmar( hash_contiene(hash, "CLAVE2"), "Busco CLAVE2");
	pa2m_afirmar( hash_contiene(hash, "CLAVE3"), "Busco CLAVE3");
	pa2m_afirmar( hash_contiene(hash, "CLAVE4"), "Busco CLAVE4");
	pa2m_afirmar( hash_cantidad(hash) == 4, "La cantidad de elementos del hash es 4.");

	hash_destruir_todo(hash, NULL);

}

void pruebas_de_eliminacion_replica_chanu()
{
	hash_t *hash = hash_crear(3);

	pa2m_afirmar( hash_quitar(hash, "CLAVE_QUE_NO_EXISTE") == NULL, "Elimino una clave que no existe de un hash, devuelve NULL");
	pa2m_afirmar( !!hash_insertar(hash, "1", "A", NULL), "Inserto <1,A>");
	pa2m_afirmar( !!hash_insertar(hash, "1", "A", NULL), "Inserto <1,A>");
	pa2m_afirmar( strcmp(hash_quitar(hash, "1"), "A") == 0, "Elimino la clave 1, devuelve el elemento.");
	pa2m_afirmar( hash_quitar(hash, "1") == NULL, "Elimino la clave 1 otra vez, devuelve error.");
	pa2m_afirmar( hash_cantidad(hash) == 0, "El tamaño del hash es 0");
	pa2m_afirmar( hash_obtener(hash, "1") == NULL, "Obtener una clave borrada devuelve NULL.");
	pa2m_afirmar( !!hash_insertar(hash, "1", "B", NULL), "Inserto <1,B>");
	pa2m_afirmar( strcmp(hash_obtener(hash, "1"), "B") == 0, "Obtengo la clave 1 y devuelve B");
	pa2m_afirmar( !!hash_insertar(hash, "4", "A", NULL), "Inserto <4,A>");
	pa2m_afirmar( strcmp(hash_quitar(hash, "1"), "B") == 0, "Elimino la clave 1, devuelve el elemento B.");
	pa2m_afirmar( strcmp(hash_quitar(hash, "4"), "A") == 0, "Elimino la clave 4, devuelve el elemento A.");
	pa2m_afirmar( hash_cantidad(hash) == 0, "El tamaño del hash es 0.");

	hash_destruir_todo(hash, NULL);
}

void pruebas_de_actualizacion_de_claves_replica_chanu()
{
	hash_t *hash = hash_crear(3);
	void *anterior = NULL;

	pa2m_afirmar( !!hash_insertar(hash, "1", "A", &anterior), "Inserto <1,A> exitosamente");
	pa2m_afirmar( anterior == NULL, "El elemento anterior reemplazado en el insertar es NULL.");
	pa2m_afirmar( !!hash_insertar(hash, "1", "B", &anterior), "Inserto <1,B> exitosamente");
	pa2m_afirmar( strcmp((char *)anterior, "A") == 0, "El elemento anterior reemplazado en el insertar es A.");
	// pa2m_afirmar( (char *)anterior == 'A', "El elemento anterior reemplazado en el insertar es A.");
	// printf("%s", *(char *)anterior);
	// pa2m_afirmar( printf("%c\n", *(char *)anterior), "A");
	pa2m_afirmar( strcmp(hash_obtener(hash, "1"), "B") == 0, "Obtengo 1 y vale B");
	pa2m_afirmar( strcmp(hash_quitar(hash, "1"), "B") == 0, "Elimino la clave 1 y devuelve B.");
	pa2m_afirmar( !!hash_insertar(hash, "1", "B", &anterior), "Inserto <1,B> exitosamente");
	pa2m_afirmar( anterior == NULL, "El elemento anterior reemplazado en el insertar es NULL.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "1"), "B") == 0, "Obtengo 1 y vale B");
	pa2m_afirmar( !!hash_insertar(hash, "1", "C", &anterior), "Inserto <1,C> exitosamente");
	pa2m_afirmar( strcmp((char *)anterior, "B") == 0, "El elemento anterior reemplazado en el insertar es B.");
	pa2m_afirmar( !!hash_insertar(hash, "1", "D", &anterior), "Inserto <1,D> exitosamente");
	pa2m_afirmar( strcmp((char *)anterior, "C") == 0, "El elemento anterior reemplazado en el insertar es C.");
	pa2m_afirmar( !!hash_insertar(hash, "1", "C", &anterior), "Inserto <1,C> exitosamente");
	pa2m_afirmar( strcmp((char *)anterior, "D") == 0, "El elemento anterior reemplazado en el insertar es D.");
	pa2m_afirmar( strcmp(hash_obtener(hash, "1"), "C") == 0, "Obtengo 1 y vale C");

	hash_destruir_todo(hash, NULL);

}

// void pruebas_con_muchas_inserciones_eliminaciones_replica_chanu()
// {
// 	// DAFUCK
// }

void pruebas_de_iterador_interno_replica_chanu()
{
	hash_t *hash = hash_crear(5);

	// hash_insertar(hash, "\001", "A", NULL);
	// hash_insertar(hash, "\002", "B", NULL);
	// hash_insertar(hash, "\003", "C", NULL);
	// hash_insertar(hash, "\004", "D", NULL);
	// hash_insertar(hash, "\005", "E", NULL);
	// hash_insertar(hash, "", "E", NULL);

	hash_insertar(hash, "\001", "A", NULL);
	hash_insertar(hash, "\002", "B", NULL);
	hash_insertar(hash, "\003", "C", NULL);
	hash_insertar(hash, "\004", "D", NULL);
	hash_insertar(hash, "\005", "E", NULL);
	hash_insertar(hash, "\006", "J", NULL);
	hash_insertar(hash, "\008", "K", NULL);
	hash_insertar(hash, "\010", "L", NULL);
	hash_insertar(hash, "\011", "N", NULL);
	hash_insertar(hash, "\012", "O", NULL);
	hash_insertar(hash, "\013", "P", NULL);
	hash_insertar(hash, "\014", "P", NULL);
	hash_insertar(hash, "\015", "P", NULL);
	hash_insertar(hash, "\016", "P", NULL);
	hash_insertar(hash, "\017", "P", NULL);
	hash_insertar(hash, "\020", "P", NULL);
	hash_insertar(hash, "\021", "P", NULL);
	hash_insertar(hash, "\022", "P", NULL);
	hash_insertar(hash, "\023", "P", NULL);
	hash_insertar(hash, "\024", "P", NULL);

	hash_insertar(hash, "1", "A", NULL);
	hash_insertar(hash, "2", "B", NULL);
	hash_insertar(hash, "3", "C", NULL);
	hash_insertar(hash, "4", "D", NULL);
	hash_insertar(hash, "5", "E", NULL);
	hash_insertar(hash, "6", "J", NULL);
	hash_insertar(hash, "7", "K", NULL);
	hash_insertar(hash, "8", "L", NULL);
	hash_insertar(hash, "9", "N", NULL);
	hash_insertar(hash, "10", "O", NULL);
	hash_insertar(hash, "11", "P", NULL);
	hash_insertar(hash, "12", "P", NULL);
	hash_insertar(hash, "13", "P", NULL);
	hash_insertar(hash, "14", "P", NULL);
	hash_insertar(hash, "15", "P", NULL);
	hash_insertar(hash, "16", "P", NULL);
	hash_insertar(hash, "17", "P", NULL);
	hash_insertar(hash, "18", "P", NULL);
	hash_insertar(hash, "19", "P", NULL);
	hash_insertar(hash, "20", "P", NULL);


	// hash_insertar(hash, "", "A", NULL);
	// hash_insertar(hash, "", "B", NULL);
	// hash_insertar(hash, "", "C", NULL);
	// hash_insertar(hash, "", "D", NULL);
	// hash_insertar(hash, "", "E", NULL);
	// hash_insertar(hash, "", "J", NULL);
	// hash_insertar(hash, "", "K", NULL);
	// hash_insertar(hash, "", "L", NULL);
	// hash_insertar(hash, "\010", "N", NULL);
	// hash_insertar(hash, "", "O", NULL);
	// hash_insertar(hash, "\011", "P", NULL);
	// hash_insertar(hash, "", "P", NULL);
	// hash_insertar(hash, "", "P", NULL);
	// hash_insertar(hash, "", "P", NULL);
	// hash_insertar(hash, "", "P", NULL);
	// hash_insertar(hash, "", "P", NULL);
	// hash_insertar(hash, "", "P", NULL);
	// hash_insertar(hash, "", "P", NULL);


	// const char *clave1 = "\001";
	// const char *clave2 = "\002";
	// const char *clave3 = "\0hola";

	// pa2m_afirmar( strcmp((const char *)clave1, (const char *)clave2) == 0, "lol");
	// pa2m_afirmar( clave1 == clave2, "lol");

	pa2m_afirmar( hash_cantidad(hash) == 12, "El hash tiene tamaño 16.");

	hash_destruir_todo(hash, NULL);
}

int main()
{
	/* pa2m_nuevo_grupo("Pruebas insercion simple.");
	pruebas_insercion_simple(); */
	
	/* pa2m_nuevo_grupo("Pruebas inserciones repetidas.");
	pruebas_insercion_con_claves_repetidas(); */

	/* pa2m_nuevo_grupo("Pruebas donde se rehashea.");
	pruebas_rehash(); */

	/* pa2m_nuevo_grupo("Pruebas de inserción");
	pruebas_de_insercion_replica_chanu(); */

	/* pa2m_nuevo_grupo("Pruebas de eliminación");
	pruebas_de_eliminacion_replica_chanu(); */

	/* pa2m_nuevo_grupo("Pruebas de actualización de claves.");
	pruebas_de_actualizacion_de_claves_replica_chanu();

	pa2m_nuevo_grupo("Pruebas de iterador interno");
	// pruebas_de_iterador_interno_replica_chanu(); */

	return pa2m_mostrar_reporte();
}