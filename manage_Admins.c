#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void admin_Input(void) {

	ADMIN* adminF = NULL;
	adminF = allocate_Admin(adminF, 1);
	FILE* admin_File = NULL;
	admin_File = fopen("admini.bin", "r+b");
	if (!admin_File) {
		admin_File = fopen("admini.bin", "wb");
		if (!admin_File) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tUnos 1. admina.\n\nUnesite ID: ");
		if (scanf("%d", &adminF->ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite korisnicko ime: ");
		c = getchar();
		if (fgets(adminF->username, 14, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite lozinku: ");
		if (fgets(adminF->password, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite ime: ");
		if (fgets(adminF->first_Name, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite prezime: ");
		if (fgets(adminF->last_Name, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite kontakt: ");
		if (fgets(adminF->contact, 39, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		int admins_Number = 1;
		fwrite(&admins_Number, sizeof(int), 1, admin_File);
		fwrite(adminF, sizeof(ADMIN), 1, admin_File);
		free(adminF);
		if(fclose(admin_File) != 0) {
			exit(EXIT_FAILURE);
		}
		login_Menu();
	}
	else {
		int admins_Number;
		fread(&admins_Number, sizeof(int), 1, admin_File);
		ADMIN* check_Admin = NULL;
		check_Admin = allocate_Admin(check_Admin, admins_Number);
		fread(check_Admin, sizeof(ADMIN), admins_Number, admin_File);
		admins_Number++;
		system("cls");
		printf("\n\tUnos %d. admina.\n\nUnesite ID: ", admins_Number);
		if (scanf("%d", &adminF->ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < (admins_Number - 1); i++) {
			if ((check_Admin + i)->ID == adminF->ID) {
				printf("\n\tAdmin sa tim ID-om postoji!\n");
				c = _getch();
				free(adminF);
				free(check_Admin);
				if(fclose(admin_File) != 0) {
					exit(EXIT_FAILURE);
				}
				return;
			}
		}
		printf("Unesite korisnicko ime: ");
		c = getchar();
		if (fgets(adminF->username, 14, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < (admins_Number - 1); i++) {
			if (strcmp((check_Admin + i)->username, adminF->username) == 0) {
				printf("\n\tAdmin sa tim korisnickim imenom postoji!\n");
				c = _getch();
				free(adminF);
				free(check_Admin);
				if(fclose(admin_File) != 0) {
					exit(EXIT_FAILURE);
				}
				return;
			}
		}
		printf("Unesite lozinku: ");
		if (fgets(adminF->password, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite ime: ");
		if (fgets(adminF->first_Name, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite prezime: ");
		if (fgets(adminF->last_Name, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite kontakt: ");
		if (fgets(adminF->contact, 39, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		rewind(admin_File);
		fwrite(&admins_Number, sizeof(int), 1, admin_File);
		if(fseek(admin_File, sizeof(int) + ((admins_Number - 1) * sizeof(ADMIN)), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fwrite(adminF, sizeof(ADMIN), 1, admin_File);
		free(adminF);
		free(check_Admin);
		if(fclose(admin_File) != 0) {
			exit(EXIT_FAILURE);
		}
		return;
	}
}

void admin_Delete(void) {

	FILE* adminF = NULL;
	adminF = fopen("admini.bin", "rb");
	if (!adminF) {
		system("cls");
		printf("\n\t\tPogreska!\n\tNema admina!\n");
		c = _getch();
		return;
	}

	int choice, admins_Number, delete_ID, temp_Var, i;

	do {
		system("cls");
		printf("\n\tGradjevinska firma - Obrisi admine\n\tLogiran admin: [%s]\n\n", logged_Admin);
		printf("<1> Obrisi po ID\n<2> Obrisi po korisnickom imenu\n<3> Povratak\n\nIzbor: ");
		if (scanf("%d", &choice) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (choice < 1 || choice > 3);

	FILE* temp_F = NULL;
	temp_F = fopen("tmp.bin", "wb");
	if (!temp_F) {
		exit(EXIT_FAILURE);
	}
	fread(&admins_Number, sizeof(int), 1, adminF);
	ADMIN* deleteS = NULL;
	deleteS = allocate_Admin(deleteS, admins_Number);

	switch (choice) {
	case 1: {
		int found_Var = 0;
		printf("\nUnesite ID za brisanje: ");
		if (scanf("%d", &delete_ID) <= 0) {
			exit(EXIT_FAILURE);
		}

		temp_Var = admins_Number - 1;
		fwrite(&temp_Var, sizeof(int), 1, temp_F);

		for (i = 0; i < admins_Number; i++) {
			fread(deleteS, sizeof(ADMIN), 1, adminF);
			if (deleteS->ID == delete_ID) {
				found_Var = 1;
			}
			else {
				fwrite(deleteS, sizeof(ADMIN), 1, temp_F);
			}
		}

		if (found_Var != 1) {
			system("cls");
			printf("\n\tAdmin sa ID [%d] nije pronadjen!\n", delete_ID);
			if(fclose(adminF) != 0) {
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
			printf("\n\tAdmin sa ID [%d] je uklonjen.\n", delete_ID);
			c = _getch();
			if (temp_Var == 0) {
				if(fclose(adminF) != 0) {
					exit(EXIT_FAILURE);
				}
				if(fclose(temp_F) != 0) {
					exit(EXIT_FAILURE);
				}
				free(deleteS);
				if (remove("admini.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (remove("tmp.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				printf("\n\tNema admina! Izlazak iz programa...\n");
				c = _getch();
				exit(EXIT_SUCCESS);
			}
			else {
				if(fclose(adminF) != 0) {
					exit(EXIT_FAILURE);
				}
				if(fclose(temp_F) != 0) {
					exit(EXIT_FAILURE);
				}
				free(deleteS);
				if (remove("admini.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (rename("tmp.bin", "admini.bin") != 0) {
					exit(EXIT_FAILURE);
				}
			}
		}
		return;
	}
	case 2: {
		char* del_Username;
		int found_Var = 0;
		del_Username = (char*)calloc(20, sizeof(char));
		if (!del_Username) {
			exit(EXIT_FAILURE);
		}
		c = getchar();
		printf("\nUnesite korisnicko ime za brisanje: ");
		if (fgets(del_Username, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		temp_Var = admins_Number - 1;
		fwrite(&temp_Var, sizeof(int), 1, temp_F);
		for (i = 0; i < admins_Number; i++) {
			fread(deleteS, sizeof(ADMIN), 1, adminF);
			if (strcmp(deleteS->username, del_Username) == 0) {
				found_Var = 1;
			}
			else {
				fwrite(deleteS, sizeof(ADMIN), 1, temp_F);
			}
		}

		if (found_Var != 1) {
			system("cls");
			*(del_Username + (strlen(del_Username) - 1)) = 0;
			printf("\n\tAdmin sa korisnickim imenom [%s] nije pronadjen.\n", del_Username);
			if(fclose(adminF) != 0) {
				exit(EXIT_FAILURE);
			}
			if(fclose(temp_F) != 0) {
				exit(EXIT_FAILURE);
			}
			free(deleteS);
			free(del_Username);
			c = _getch();
		}
		else {
			system("cls");
			*(del_Username + (strlen(del_Username) - 1)) = 0;
			printf("\n\tAdmin sa korisnickim imenom [%s] je uklonjen.\n", del_Username);
			c = _getch();
			if(fclose(adminF) != 0) {
				exit(EXIT_FAILURE);
			}
			if(fclose(temp_F) != 0) {
				exit(EXIT_FAILURE);
			}
			free(deleteS);
			free(del_Username);
			if (temp_Var == 0) {
				if (remove("admini.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (remove("tmp.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				printf("\n\tNema admina! Izlazak iz programa...\n");
				c = _getch();
				exit(EXIT_SUCCESS);
			}
			else {
				if (remove("admini.bin") != 0) {
					exit(EXIT_FAILURE);
				}
				if (rename("tmp.bin", "admini.bin") != 0) {
					exit(EXIT_FAILURE);
				}
			}
		}
		return;
	}
	case 3: {
		if(fclose(adminF) != 0) {
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

void admin_Search(void) {

	FILE* search_F = NULL;
	search_F = fopen("admini.bin", "rb");
	if (!search_F) {
		system("cls");
		printf("\n\t\tPogreska!\n\tNema admina!\n");
		c = _getch();
		return;
	}

	int choice, i, admins_Number, search_ID, flag = 0;

	do {
		system("cls");
		printf("\n\tGradjevinska firma - Trazi admine\n\tLogiran admin: [%s]\n\n", logged_Admin);
		printf("<1> ID\n<2> Korisnicko ime\n<3> Povratak\n\nIzbor: ");
		if (scanf("%d", &choice) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (choice < 1 || choice > 3);

	ADMIN* search_S = NULL;
	fread(&admins_Number, sizeof(int), 1, search_F);
	search_S = allocate_Admin(search_S, admins_Number);

	switch (choice) {
	case 1: {
		system("cls");
		printf("\nUnesite ID: ");
		if (scanf("%d", &search_ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < admins_Number; i++) {
			fread(search_S, sizeof(ADMIN), 1, search_F);
			if (search_S->ID == search_ID) {
				fprintf(stdout, "\n[%d] ID: %d\n", i + 1, search_S->ID);
				fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, search_S->username);
				fprintf(stdout, "[%d] Lozinka: %s", i + 1, search_S->password);
				fprintf(stdout, "[%d] Ime: %s", i + 1, search_S->first_Name);
				fprintf(stdout, "[%d] Prezime: %s", i + 1, search_S->last_Name);
				fprintf(stdout, "[%d] Kontakt: %s", i + 1, search_S->contact);
				flag = 1;
				c = _getch();
				break;
			}
		}
		if (flag == 0) {
			printf("\nNe postji admin sa ID: [%d].\n", search_ID);
			c = _getch();
		}
		free(search_S);
		if(fclose(search_F) != 0) {
			exit(EXIT_FAILURE);
		}
		return;
	}
	case 2: {
		char* search_FKIme = (char*)calloc(20, sizeof(char));
		if (!search_FKIme) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		c = getchar();
		printf("\nUnesite korisnicko ime: ");
		if (fgets(search_FKIme, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < admins_Number; i++) {
			fread(search_S, sizeof(ADMIN), 1, search_F);
			if (strcmp(search_S->username, search_FKIme) == 0) {
				fprintf(stdout, "\n[%d] ID: %d\n", i + 1, search_S->ID);
				fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, search_S->username);
				fprintf(stdout, "[%d] Lozinka: %s", i + 1, search_S->password);
				fprintf(stdout, "[%d] Ime: %s", i + 1, search_S->first_Name);
				fprintf(stdout, "[%d] Prezime: %s", i + 1, search_S->last_Name);
				fprintf(stdout, "[%d] Kontakt: %s", i + 1, search_S->contact);
				flag = 1;
				c = _getch();
				break;
			}
		}
		if (flag == 0) {
			*(search_FKIme + (strlen(search_FKIme) - 1)) = 0;
			printf("\nNe postoji admin sa korisnickim imenom: [%s].\n", search_FKIme);
			c = _getch();
		}
		free(search_S);
		free(search_FKIme);
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

void admin_List(void) {

	FILE* list_F = NULL;
	list_F = fopen("admini.bin", "rb");
	if (!list_F) {
		system("cls");
		printf("\n\t\tPogreska!\n\tNema admina!\n");
		c = _getch();
		return;
	}

	int choice, admins_Number, i, asc_Desc = 0;

	do {
		system("cls");
		printf("\n\tGradjevinska firma - Izlistaj admine\n\tLogiran admin: [%s]\n\n", logged_Admin);
		printf("<1> ID\n<2> Korisnicko ime\n<3> Ime\n<4> Povratak\n\nIzbor: ");
		if (scanf("%d", &choice) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (choice < 1 || choice > 4);

	ADMIN* list_S = NULL;
	fread(&admins_Number, sizeof(int), 1, list_F);
	list_S = allocate_Admin(list_S, admins_Number);

	switch (choice) {
	case 1: {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izlistaj admine -> ID\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Uzlazno\n<2> Silazno\n\nIzbor: ");
			if (scanf("%d", &asc_Desc) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (asc_Desc < 1 || asc_Desc > 2);
		if (fseek(list_F, sizeof(int), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fread(list_S, sizeof(ADMIN), admins_Number, list_F);
		if (asc_Desc == 1) {
			qsort(list_S, admins_Number, sizeof(ADMIN), admin_ID_Asc);
		}
		else {
			qsort(list_S, admins_Number, sizeof(ADMIN), admin_ID_Desc);
		}

		system("cls");
		printf("\n\tBroj admina: %d\n\n", admins_Number);
		for (i = 0; i < admins_Number; i++) {
			fprintf(stdout, "[%d] ID: %d\n", i + 1, (list_S + i)->ID);
			fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, (list_S + i)->username);
			fprintf(stdout, "[%d] Lozinka: %s", i + 1, (list_S + i)->password);
			fprintf(stdout, "[%d] Ime: %s", i + 1, (list_S + i)->first_Name);
			fprintf(stdout, "[%d] Prezime: %s", i + 1, (list_S + i)->last_Name);
			fprintf(stdout, "[%d] Kontakt: %s\n", i + 1, (list_S + i)->contact);
		}
		fprintf(stdout, "\nKraj liste.\n");
		c = _getch();
		if (fclose(list_F) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	case 2: {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izlistaj admine -> Korisnicko ime\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Uzlazno\n<2> Silazno\n\nIzbor: ");
			if (scanf("%d", &asc_Desc) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (asc_Desc < 1 || asc_Desc > 2);

		if(fseek(list_F, sizeof(int), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fread(list_S, sizeof(ADMIN), admins_Number, list_F);
		if (asc_Desc == 1) {
			qsort(list_S, admins_Number, sizeof(ADMIN), admin_Un_Asc);
		}
		else {
			qsort(list_S, admins_Number, sizeof(ADMIN), admin_Un_Desc);
		}

		system("cls");
		printf("\n\tBroj admina: %d\n\n", admins_Number);
		for (i = 0; i < admins_Number; i++) {
			fprintf(stdout, "[%d] ID: %d\n", i + 1, (list_S + i)->ID);
			fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, (list_S + i)->username);
			fprintf(stdout, "[%d] Lozinka: %s", i + 1, (list_S + i)->password);
			fprintf(stdout, "[%d] Ime: %s", i + 1, (list_S + i)->first_Name);
			fprintf(stdout, "[%d] Prezime: %s", i + 1, (list_S + i)->last_Name);
			fprintf(stdout, "[%d] Kontakt: %s\n", i + 1, (list_S + i)->contact);
		}
		fprintf(stdout, "\nKraj liste.\n");
		c = _getch();
		if(fclose(list_F) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	case 3: {
		do {
			system("cls");
			printf("\n\tGradjevinska firma - Izlistaj admine -> Ime\n\tLogiran admin: [%s]\n\n", logged_Admin);
			printf("<1> Uzlazno\n<2> Silazno\n\nIzbor: ");
			if (scanf("%d", &asc_Desc) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (asc_Desc < 1 || asc_Desc > 2);

		if(fseek(list_F, sizeof(int), SEEK_SET) != 0) {
			exit(EXIT_FAILURE);
		}
		fread(list_S, sizeof(ADMIN), admins_Number, list_F);
		if (asc_Desc == 1) {
			qsort(list_S, admins_Number, sizeof(ADMIN), admin_Fn_Asc);
		}
		else {
			qsort(list_S, admins_Number, sizeof(ADMIN), admin_Fn_Desc);
		}

		system("cls");
		printf("\n\tBroj admina: %d\n\n", admins_Number);
		for (i = 0; i < admins_Number; i++) {
			fprintf(stdout, "[%d] ID: %d\n", i + 1, (list_S + i)->ID);
			fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, (list_S + i)->username);
			fprintf(stdout, "[%d] Lozinka: %s", i + 1, (list_S + i)->password);
			fprintf(stdout, "[%d] Ime: %s", i + 1, (list_S + i)->first_Name);
			fprintf(stdout, "[%d] Prezime: %s", i + 1, (list_S + i)->last_Name);
			fprintf(stdout, "[%d] Kontakt: %s\n", i + 1, (list_S + i)->contact);
		}
		fprintf(stdout, "\nKraj liste.\n");
		c = _getch();
		if(fclose(list_F) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	case 4: {
		if(fclose(list_F) != 0) {
			exit(EXIT_FAILURE);
		}
		free(list_S);
		return;
	}
	}
}