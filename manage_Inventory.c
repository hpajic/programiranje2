#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void inventory_Input(void) {

	INV* inventoryS = NULL;
	inventoryS = allocate_Inventory(inventoryS, 1);
	FILE* inventory_File = NULL;
	inventory_File = fopen("inventar.bin", "r+b");
	if (!inventory_File) {
		inventory_File = fopen("inventar.bin", "wb");
		if (!inventory_File) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tUnos 1. inventara.\n\nUnesite ID: ");
		if (scanf("%d", &inventoryS->ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite tip: ");
		c = getchar();
		if (fgets(inventoryS->type, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite naziv: ");
		if (fgets(inventoryS->name, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite opis: ");
		if (fgets(inventoryS->description, 99, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite kolicinu: ");
		do {
			if (scanf("%d", &inventoryS->quantity) <= 0) {
				exit(EXIT_FAILURE);
			}
			if (inventoryS->quantity <= 0) {
				printf("Ne moze biti manje od 1. Ponovite unos: ");
			}
		} while (inventoryS->quantity <= 0);
		int inventory_Number = 1;
		fwrite(&inventory_Number, sizeof(int), 1, inventory_File);
		fwrite(inventoryS, sizeof(INV), 1, inventory_File);
		free(inventoryS);
		if(fclose(inventory_File) != 0) {
			exit(EXIT_FAILURE);
		}
		return;
	}
	else {
		int inventory_Number;
		fread(&inventory_Number, sizeof(int), 1, inventory_File);
		INV* check_Inv = NULL;
		check_Inv = allocate_Inventory(check_Inv, inventory_Number);
		fread(check_Inv, sizeof(INV), inventory_Number, inventory_File);
		inventory_Number++;
		system("cls");
		printf("\n\tUnos %d. inventara.\n\nUnesite ID: ", inventory_Number);
		if (scanf("%d", &inventoryS->ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < (inventory_Number - 1); i++) {
			if ((check_Inv + i)->ID == inventoryS->ID) {
				printf("\n\tInventar sa tim ID-om postoji!\n");
				c = _getch();
				free(inventoryS);
				free(check_Inv);
				if(fclose(inventory_File) != 0) {
					exit(EXIT_FAILURE);
				}
				return;
			}
		}
		printf("Unesite tip: ");
		c = getchar();
		if (fgets(inventoryS->type, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite naziv: ");
		if (fgets(inventoryS->name, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite opis: ");
		if (fgets(inventoryS->description, 99, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite kolicinu: ");
		do {
			if (scanf("%d", &inventoryS->quantity) <= 0) {
				exit(EXIT_FAILURE);
			}
			if (inventoryS->quantity <= 0) {
				printf("Ne moze biti manje od 1. Ponovite unos: ");
			}
		} while (inventoryS->quantity <= 0);
		rewind(inventory_File);
		fwrite(&inventory_Number, sizeof(int), 1, inventory_File);
		if(fseek(inventory_File, sizeof(int) + ((inventory_Number - 1) * sizeof(INV)), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fwrite(inventoryS, sizeof(INV), 1, inventory_File);
		free(inventoryS);
		free(check_Inv);
		if(fclose(inventory_File) != 0) {
			exit(EXIT_FAILURE);
		}
		return;
	}
}

void inventory_Delete(void) {

	FILE* inventory_File = NULL;
	inventory_File = fopen("inventar.bin", "rb");
	if (!inventory_File) {
		system("cls");
		printf("\n\t\tPogreska!\n\tInventar prazan!\n");
		c = _getch();
		return;
	}

	int choice, inventory_Number, delete_ID, temp_Var, i;

	do {
		system("cls");
		printf("\n\tGradjevinska firma - Obrisi inventar\n\tLogiran admin: [%s]\n\n", logged_Admin);
		printf("<1> Obrisi po ID\n<2> Obrisi po nazivu\n<3> Povratak\n\nIzbor: ");
		if (scanf("%d", &choice) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (choice < 1 || choice > 3);

	FILE* temp_F = NULL;
	temp_F = fopen("tmp.bin", "wb");
	if (!temp_F) {
		exit(EXIT_FAILURE);
	}
	fread(&inventory_Number, sizeof(int), 1, inventory_File);
	INV* deleteS = NULL;
	deleteS = allocate_Inventory(deleteS, inventory_Number);

	switch (choice) {
	case 1: {
		int found_Var = 0;
		printf("\nUnesite ID za brisanje: ");
		if (scanf("%d", &delete_ID) <= 0) {
			exit(EXIT_FAILURE);
		}

		temp_Var = inventory_Number - 1;
		fwrite(&temp_Var, sizeof(int), 1, temp_F);

		for (i = 0; i < inventory_Number; i++) {
			fread(deleteS, sizeof(INV), 1, inventory_File);
			if (deleteS->ID == delete_ID) {
				found_Var = 1;
			}
			else {
				fwrite(deleteS, sizeof(INV), 1, temp_F);
			}
		}

		if (found_Var != 1) {
			system("cls");
			printf("\n\tInventar sa ID [%d] nije pronadjen!\n", delete_ID);
			if(fclose(inventory_File) != 0) {
				exit(EXIT_FAILURE);
			}
			if(fclose(temp_F) != 0) {
				exit(EXIT_FAILURE);
			}
			free(deleteS);
			c = _getch();
		}
		else {
			system("cls");
			printf("\n\tInventar sa ID [%d] je uklonjen.\n", delete_ID);
			c = _getch();
			if (temp_Var == 0) {
				if(fclose(inventory_File) != 0) {
					exit(EXIT_FAILURE);
				}
				if(fclose(temp_F) != 0) {
					exit(EXIT_FAILURE);
				}
				free(deleteS);
				if (remove("inventar.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (remove("tmp.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				printf("\n\tInventar prazan.\n");
				c = _getch();
				return;
			}
			else {
				if(fclose(inventory_File) != 0) {
					exit(EXIT_FAILURE);
				}
				if(fclose(temp_F) != 0) {
					exit(EXIT_FAILURE);
				}
				free(deleteS);
				if (remove("inventar.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (rename("tmp.bin", "inventar.bin") != 0) {
					exit(EXIT_FAILURE);
				}
			}
		}
		return;
	}
	case 2: {
		char* del_Name;
		int found_Var = 0;
		del_Name = (char*)calloc(30, sizeof(char));
		if (!del_Name) {
			exit(EXIT_FAILURE);
		}
		c = getchar();
		printf("\nUnesite naziv inventara za brisanje: ");
		if (fgets(del_Name, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		temp_Var = inventory_Number - 1;
		fwrite(&temp_Var, sizeof(int), 1, temp_F);
		for (i = 0; i < inventory_Number; i++) {
			fread(deleteS, sizeof(INV), 1, inventory_File);
			if (strcmp(deleteS->name, del_Name) == 0) {
				found_Var = 1;
			}
			else {
				fwrite(deleteS, sizeof(INV), 1, temp_F);
			}
		}

		if (found_Var != 1) {
			system("cls");
			*(del_Name + (strlen(del_Name) - 1)) = 0;
			printf("\n\tInventar naziva [%s] nije pronadjen.\n", del_Name);
			if(fclose(inventory_File) != 0) {
				exit(EXIT_FAILURE);
			}
			if(fclose(temp_F) != 0) {
				exit(EXIT_FAILURE);
			}
			free(deleteS);
			free(del_Name);
			c = _getch();
		}
		else {
			system("cls");
			*(del_Name + (strlen(del_Name) - 1)) = 0;
			printf("\n\tInventar naziva [%s] je uklonjen.\n", del_Name);
			c = _getch();
			if(fclose(inventory_File) != 0) {
				exit(EXIT_FAILURE);
			}
			if(fclose(temp_F) != 0) {
				exit(EXIT_FAILURE);
			}
			free(deleteS);
			free(del_Name);
			if (temp_Var == 0) {
				if (remove("inventar.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (remove("tmp.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				printf("\n\tInventar prazan.\n");
				c = _getch();
				return;
			}
			else {
				if (remove("inventar.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (rename("tmp.bin", "inventar.bin") != 0) {
					exit(EXIT_FAILURE);
				}
			}
		}
		return;
	}
	case 3: {
		if(fclose(inventory_File) != 0) {
			exit(EXIT_FAILURE);
		}
		if(fclose(temp_F) != 0) {
			exit(EXIT_FAILURE);
		}
		free(deleteS);
		return;
	}
	}
}

void inventory_Search(void) {

	FILE* search_F = NULL;
	search_F = fopen("inventar.bin", "rb");
	if (!search_F) {
		system("cls");
		printf("\n\t\tPogreska!\n\tInventar prazan!\n");
		c = _getch();
		return;
	}

	int choice, i, inventory_Number, search_ID, flag = 0;

	do {
		system("cls");
		printf("\n\tGradjevinska firma - Trazi inventar\n\tLogiran admin: [%s]\n\n", logged_Admin);
		printf("<1> ID\n<2> Naziv\n<3> Povratak\n\nIzbor: ");
		if (scanf("%d", &choice) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (choice < 1 || choice > 3);

	INV* search_S = NULL;
	fread(&inventory_Number, sizeof(int), 1, search_F);
	search_S = allocate_Inventory(search_S, inventory_Number);

	switch (choice) {
	case 1: {
		system("cls");
		printf("\nUnesite ID: ");
		if (scanf("%d", &search_ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < inventory_Number; i++) {
			fread(search_S, sizeof(INV), 1, search_F);
			if (search_S->ID == search_ID) {
				fprintf(stdout, "\n[%d] ID: %d\n", i + 1, search_S->ID);
				fprintf(stdout, "[%d] Tip: %s", i + 1, search_S->type);
				fprintf(stdout, "[%d] Naziv: %s", i + 1, search_S->name);
				fprintf(stdout, "[%d] Opis: %s", i + 1, search_S->description);
				fprintf(stdout, "[%d] Kolicina: %d\n", i + 1, search_S->quantity);
				flag = 1;
				c = _getch();
				break;
			}
		}
		if (flag == 0) {
			printf("\nNe postoji inventar sa ID: [%d].\n", search_ID);
			c = _getch();
		}
		free(search_S);
		if(fclose(search_F) != 0) {
			exit(EXIT_FAILURE);
		}
		return;
	}
	case 2: {
		char* search_Name = (char*)calloc(30, sizeof(char));
		if (!search_Name) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		c = getchar();
		printf("\nUnesite naziv: ");
		if (fgets(search_Name, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < inventory_Number; i++) {
			fread(search_S, sizeof(INV), 1, search_F);
			if (strcmp(search_S->name, search_Name) == 0) {
				fprintf(stdout, "\n[%d] ID: %d\n", i + 1, search_S->ID);
				fprintf(stdout, "[%d] Tip: %s", i + 1, search_S->type);
				fprintf(stdout, "[%d] Naziv: %s", i + 1, search_S->name);
				fprintf(stdout, "[%d] Opis: %s", i + 1, search_S->description);
				fprintf(stdout, "[%d] Kolicina: %d\n", i + 1, search_S->quantity);
				flag = 1;
				c = _getch();
				break;
			}
		}
		if (flag == 0) {
			*(search_Name + (strlen(search_Name) - 1)) = 0;
			printf("\nNe postoji inventar naziva: [%s].\n", search_Name);
			c = _getch();
		}
		free(search_S);
		free(search_Name);
		if(fclose(search_F) != 0) {
			exit(EXIT_FAILURE);
		}
		return;
	}
	case 3: {
		free(search_S);
		if(fclose(search_F) != 0) {
			exit(EXIT_FAILURE);
		}
		return;
	}
	}
}

void inventory_List(void) {

	FILE* inventory_File = NULL;
	inventory_File = fopen("inventar.bin", "rb");
	if (!inventory_File) {
		system("cls");
		printf("\n\t\tPogreska!\n\tInventar prazan!\n");
		c = _getch();
		return;
	}

	int choice, inventory_Number, i, asc_Desc = 0;

	do {
		system("cls");
		printf("\n\tGradjevinska firma - Izlistaj inventar\n\tLogiran admin: [%s]\n\n", logged_Admin);
		printf("<1> ID\n<2> Tip\n<3> Naziv\n<4> Povratak\n\nIzbor: ");
		if (scanf("%d", &choice) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (choice < 1 || choice > 4);

	INV* list_S = NULL;
	fread(&inventory_Number, sizeof(int), 1, inventory_File);
	list_S = allocate_Inventory(list_S, inventory_Number);

	switch (choice) {
	case 1: {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izlistaj inventar -> ID\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Uzlazno\n<2> Silazno\n\nIzbor: ");
			if (scanf("%d", &asc_Desc) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (asc_Desc < 1 || asc_Desc > 2);
		if(fseek(inventory_File, sizeof(int), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fread(list_S, sizeof(INV), inventory_Number, inventory_File);
		if (asc_Desc == 1) {
			qsort(list_S, inventory_Number, sizeof(INV), inventory_ID_Asc);
		}
		else {
			qsort(list_S, inventory_Number, sizeof(INV), inventory_ID_Desc);
		}

		system("cls");
		printf("\n\tStanje inventara: %d\n\n", inventory_Number);
		for (i = 0; i < inventory_Number; i++) {
			fprintf(stdout, "[%d] ID: %d\n", i + 1, (list_S + i)->ID);
			fprintf(stdout, "[%d] Tip: %s", i + 1, (list_S + i)->type);
			fprintf(stdout, "[%d] Naziv: %s", i + 1, (list_S + i)->name);
			fprintf(stdout, "[%d] Opis: %s", i + 1, (list_S + i)->description);
			fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, (list_S + i)->quantity);
		}
		fprintf(stdout, "\nKraj liste.\n");
		c = _getch();
		if(fclose(inventory_File) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	case 2: {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izlistaj inventar -> Tip\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Uzlazno\n<2> Silazno\n\nIzbor: ");
			if (scanf("%d", &asc_Desc) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (asc_Desc < 1 || asc_Desc > 2);

		if(fseek(inventory_File, sizeof(int), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fread(list_S, sizeof(INV), inventory_Number, inventory_File);
		if (asc_Desc == 1) {
			qsort(list_S, inventory_Number, sizeof(INV), inventory_Type_Asc);
		}
		else {
			qsort(list_S, inventory_Number, sizeof(INV), inventory_Type_Desc);
		}

		system("cls");
		printf("\n\tStanje inventara: %d\n\n", inventory_Number);
		for (i = 0; i < inventory_Number; i++) {
			fprintf(stdout, "[%d] ID: %d\n", i + 1, (list_S + i)->ID);
			fprintf(stdout, "[%d] Tip: %s", i + 1, (list_S + i)->type);
			fprintf(stdout, "[%d] Naziv: %s", i + 1, (list_S + i)->name);
			fprintf(stdout, "[%d] Opis: %s", i + 1, (list_S + i)->description);
			fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, (list_S + i)->quantity);
		}
		fprintf(stdout, "\nKraj liste.\n");
		c = _getch();
		if(fclose(inventory_File) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	case 3: {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izlistaj admine -> Naziv\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Uzlazno\n<2> Silazno\n\nIzbor: ");
			if (scanf("%d", &asc_Desc) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (asc_Desc < 1 || asc_Desc > 2);

		if(fseek(inventory_File, sizeof(int), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fread(list_S, sizeof(INV), inventory_Number, inventory_File);
		if (asc_Desc == 1) {
			qsort(list_S, inventory_Number, sizeof(INV), inventory_Name_Asc);
		}
		else {
			qsort(list_S, inventory_Number, sizeof(INV), inventory_Name_Desc);
		}

		system("cls");
		printf("\n\tStanje inventara: %d\n\n", inventory_Number);
		for (i = 0; i < inventory_Number; i++) {
			fprintf(stdout, "[%d] ID: %d\n", i + 1, (list_S + i)->ID);
			fprintf(stdout, "[%d] Tip: %s", i + 1, (list_S + i)->type);
			fprintf(stdout, "[%d] Naziv: %s", i + 1, (list_S + i)->name);
			fprintf(stdout, "[%d] Opis: %s", i + 1, (list_S + i)->description);
			fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, (list_S + i)->quantity);
		}
		fprintf(stdout, "\nKraj liste.\n");
		c = _getch();
		if(fclose(inventory_File) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	case 4: {
		if(fclose(inventory_File) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	}
}