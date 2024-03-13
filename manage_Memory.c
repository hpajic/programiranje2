#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ovo je meni reko da nemam pa sam stavio
   alocira memoriju za ili inventar ili admina
   i onda vraća taj pointer (osim ako nije puklo u if-u),
   a if(!nešto) ti je isto što i if(nešto == NULL), ne znam
   što traži, ako traži ovo drugo, onda samo svugdje izmijeniš
   sa !nešto na nešto == NULL i to je to */

ADMIN* allocate_Admin(ADMIN* admin_Str, int admins_Number) {
	admin_Str = malloc(admins_Number * sizeof(ADMIN));
	if (!admin_Str) {
		exit(EXIT_FAILURE);
	}
	return admin_Str;
}

INV* allocate_Inventory(INV* inv_Str, int inventory_Number) {
	inv_Str = malloc(inventory_Number * sizeof(INV));
	if (!inv_Str) {
		exit(EXIT_FAILURE);
	}
	return inv_Str;
}

/* kad se logiraš pisat će ti logged as [admin] sa ovim
   da nema ovoga, bilo bi ovako
   logged as [admin
   ]
   zato jer fgets uzima string + \n + \0
   ja sam napravio ovdje da taj \n se zamijeni
   sa terminirajućim charom \0, tako da bude
   u jednoj liniji, da nema te nove linije 
   
   i ako te pita zašto calloc umjesto malloc
   calloc ti se što je alocirano popunjava s 0
   tako da je osigurano da će \0 bit negdje u polju
   dok kod malloca je rijetko da se dogodi ALI se
   može dogoditi da ti totalno uništi taj string 
   koji je unesen u to alocirano polje 
   evo ti i obje definicije
   
   void *calloc(size_t nitems, size_t size)
	- nitems − This is the number of elements to be allocated -> npr. 2 ili bilo koji broj
	- size − This is the size of elements -> npr. sizeof(int)
   Return Value
	- This function returns a pointer to the allocated memory, or NULL if the request fails

   void *malloc(size_t size)
	- size − This is the size of the memory block, in bytes
   s tim da smo mi radili ovako
   void *malloc(size_t nitems * size_t size) -> npr. 
   int* ptr;
   ptr = (int*) malloc(100 * sizeof(int));
	 - Since the size of int is 4 bytes, this statement will allocate 400 bytes of memory.
	   And, the pointer ptr holds the address of the first byte in the allocated memory.
   Return Value
	 - This function returns a pointer to the allocated memory, or NULL if the request fails. */

void prepare_Logged(char* admin, int num) {
	logged_Admin = calloc(num + 2, sizeof(char));
	if (!logged_Admin) {
		exit(EXIT_FAILURE);
	}
	strncpy(logged_Admin, admin, num);
	*(logged_Admin + strlen(logged_Admin)) = '\0';
}