#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

void login_Menu(void) {

	FILE* admin_File = NULL;
	admin_File = fopen("admini.bin", "rb");
	if (!admin_File) {
		// ako ne postoji file, nema ni admina ide se na admin_Input();
		system("cls");
		printf("\n\tTrenutno nema admina.\n\tNastavite na unos...\n");
		c = _getch();
		admin_Input();
	}
	else {
		int admin_Str_Number, i, flag = 0;
		fread(&admin_Str_Number, sizeof(int), 1, admin_File);
		ADMIN* admin_Str = NULL;
		admin_Str = allocate_Admin(admin_Str, admin_Str_Number);
		char* username, *password;
		username = calloc(15, sizeof(char));
		if (!username) {
			exit(EXIT_FAILURE);
		}
		password = calloc(30, sizeof(char));
		if (!password) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\t--- Morate se ulogirati da biste nastavili ---\n\nKorisnicko ime: ");
		if (fgets(username, 14, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Lozinka: ");
		for (i = 0; *(password + i - 1) != '\r'; i++) {
			*(password + i) = _getch();
			printf("*");
		}
		*(password + i - 1) = '\n';
		fread(admin_Str, sizeof(ADMIN), admin_Str_Number, admin_File);
		for (i = 0; i < admin_Str_Number; i++) {
			if (strcmp((admin_Str + i)->username, username) == 0) {
				if (strcmp((admin_Str + i)->password, password) == 0) {
					flag = 2;
					break;
				}
				else {
					flag = 1;
					break;
				}
			}
			else {
				flag = 0;
			}
		}
		if (flag == 2) {
			int temp_Num = 0;
			while (*(username + temp_Num) != '\n') {
				temp_Num++;
			}
			prepare_Logged(username, temp_Num);
			free(username);
			free(password);
			free(admin_Str);
			if (fclose(admin_File) != 0) { // za sve ove provjere možeš pročitat online da ti ne prepisujem
				// sve sa interneta :D uglavnom, vidiš da ako ne vraća 0 da je failala, znači ako vrati 0, onda je true, tj prošla je
				exit(EXIT_FAILURE);
			}
			main_Menu();
		}
		else if (flag == 1) {
			free(username);
			free(password);
			free(admin_Str);
			if (fclose(admin_File) != 0) {
				exit(EXIT_FAILURE);
			}
			printf("\n\tPogresna lozinka!\n");
			c = _getch();
			return;
		}
		else if (flag == 0) {
			free(username);
			free(password);
			free(admin_Str);
			if (fclose(admin_File) != 0) {
				exit(EXIT_FAILURE);
			}
			printf("\n\tAdmin ne postoji!\n");
			c = _getch();
			return;
		}
	}
}

void main_Menu(void) {

	int izbor;

	while (true) {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Pocetni izbornik\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Admini\n<2> Skladiste\n<3> Izlaz\n\nIzbor: ");
			// ove printf si možeš izmijenit kako tebi odgovoara
			if (scanf("%d", &izbor) <= 0) {
				/* On success, the function returns the number of items of the argument
				list successfully read. If a reading error happens or the end-of-file is
				reached while reading, the proper indicator is set (feof or ferror) and,
				if either happens before any data could be successfully read, EOF is returned.
				vraća ti broj pročitanih itema, ako vrati 0 ili manje znači da je failalo */
				exit(EXIT_FAILURE);
			}
		} while (izbor < 1 || izbor > 3);
		switch (izbor) {
		case 1: {
			admin_Menu();
			break;
		}
		case 2: {
			inventory_Menu();
			break;
		}
		case 3: {
			if (logged_Admin != NULL) {
				free(logged_Admin);
			}
			exit(EXIT_SUCCESS);
			/* da ti ne pišem svugdje
			exit(EXIT_SUCCESS) je isto što i exit(0)
			exit(EXIT_FAILURE) je isto što i exit(1) ili bilo koji drugi broj
			npr. exit(3) i tako */
		}
		}
	}
}

void admin_Menu(void) {

	int choice;

	while (true) {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izbornik admina\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Dodaj admina\n<2> Obrisi admina\n<3> Trazi admina\n<4> Izlistaj admine\n<5> Povratak\n\nIzbor: ");
			if (scanf("%d", &choice) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (choice < 1 || choice > 5);
		switch (choice) {
		case 1: {
			admin_Input();
			break;
		}
		case 2: {
			admin_Delete();
			break;
		}
		case 3: {
			admin_Search();
			break;
		}
		case 4: {
			admin_List();
			break;
		}
		case 5: {
			return;
		}
		}
	}
}

void inventory_Menu(void) {

	int choice;

	while (1) {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izbornik inventara\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Dodaj inventar\n<2> Obrisi inventar\n<3> Trazi inventar\n<4> Izlistaj inventar\n<5> Povratak\n\nIzbor: ");
			if (scanf("%d", &choice) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (choice < 1 || choice > 5);
		switch (choice) {
		case 1: {
			inventory_Input();
			break;
		}
		case 2: {
			inventory_Delete();
			break;
		}
		case 3: {
			inventory_Search();
			break;
		}
		case 4: {
			inventory_List();
			break;
		}
		case 5: {
			return;
		}
		}
	}
}