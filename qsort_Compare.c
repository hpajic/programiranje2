#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ako te pita što si koristio za sortiranje
   reci mu qsort, za ove tipove koji su int
   vidiš što je return (-), a za strcmp
   najbolje pročitaj online koje su njihove
   povratne vrijednosti
   otp. ovako ide deklaracija
   int strcmp(const char *str1, const char *str2)
   i onda vrijednosti ovog inta što vraća su

   if Return value < 0 then it indicates str1 is less than str2.
   if Return value > 0 then it indicates str2 is less than str1.
   if Return value = 0 then it indicates str1 is equal to str2. 
   
   sve te funkcije imaš povzane kod qsort funkcija
   ovisi jel treba asc (ascending - uzlazno) ili 
   desc (descending - silazno) */

int admin_ID_Asc(const void* x, const void* y) {
	ADMIN* ID_x = (ADMIN*)x;
	ADMIN* ID_y = (ADMIN*)y;
	return (ID_x->ID - ID_y->ID);
}

int admin_ID_Desc(const void* x, const void* y) {
	ADMIN* ID_x = (ADMIN*)x;
	ADMIN* ID_y = (ADMIN*)y;
	return (ID_y->ID - ID_x->ID);
}

int admin_Un_Asc(const void* a, const void* b) {
	ADMIN* userNA = (ADMIN*)a;
	ADMIN* userNB = (ADMIN*)b;
	return -(strcmp(userNB->username, userNA->username));
}

int admin_Un_Desc(const void* a, const void* b) {
	ADMIN* userNA = (ADMIN*)a;
	ADMIN* userNB = (ADMIN*)b;
	return strcmp(userNB->username, userNA->username);
}

int admin_Fn_Asc(const void* a, const void* b) {
	ADMIN* nameA = (ADMIN*)a;
	ADMIN* nameB = (ADMIN*)b;
	return -(strcmp(nameB->first_Name, nameA->first_Name));
}

int admin_Fn_Desc(const void* a, const void* b) {
	ADMIN* nameA = (ADMIN*)a;
	ADMIN* nameB = (ADMIN*)b;
	return strcmp(nameB->first_Name, nameA->first_Name);
}

int inventory_ID_Asc(const void* x, const void* y) {
	INV* ID_x = (INV*)x;
	INV* ID_y = (INV*)y;
	return (ID_x->ID - ID_y->ID);
}

int inventory_ID_Desc(const void* x, const void* y) {
	INV* ID_x = (INV*)x;
	INV* ID_y = (INV*)y;
	return (ID_y->ID - ID_x->ID);
}

int inventory_Type_Asc(const void* a, const void* b) {
	INV* typeA = (INV*)a;
	INV* typeB = (INV*)b;
	return -(strcmp(typeB->type, typeA->type));
}

int inventory_Type_Desc(const void* a, const void* b) {
	INV* typeA = (INV*)a;
	INV* typeB = (INV*)b;
	return strcmp(typeB->type, typeA->type);
}

int inventory_Name_Asc(const void* a, const void* b) {
	INV* nameA = (INV*)a;
	INV* nameB = (INV*)b;
	return -(strcmp(nameB->name, nameA->name));
}

int inventory_Name_Desc(const void* a, const void* b) {
	INV* nameA = (INV*)a;
	INV* nameB = (INV*)b;
	return strcmp(nameB->name, nameA->name);
}