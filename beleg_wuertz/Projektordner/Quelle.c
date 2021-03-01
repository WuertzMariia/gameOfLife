

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //for rand, WIndows inclus windows.h
#include <time.h> // for srand
#include <conio.h>
#define red 1 //Farbe am Start und danach bei 3 und mehr Nachbarnzehllen
#define green 2 //Farbe bei 2 Nachbarnzellen
#define dead 0
#define live_cell "*"
#define dead_cell ' '
#define width 25
#define height 25
#pragma warning (disable: 4996) 


//GOTOXY
void gotoXY(int x, int y) {
	HANDLE hConsoleOutput;
	COORD koords;
	koords.X = x;
	koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}


//HEAD
void head() {
	printf("\t----------------GAME OF LIFE-------------------\n\n");
}


//SPIELFELD INITIALISIERUNG
void init_board(int board[height][width]) {
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			board[i][j] = dead;
}


//SPIELFELD DARSTELLEN
void print_arr(int arr[height][width]) {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (arr[i][j] == green) { //grüne Zellen
				printf("\033[1;32m%s\033[0m", live_cell);
			}
			else if (arr[i][j] == red) { //lila Zellen
				printf("\033[1;35m%s\033[0m", live_cell);
			}
			else printf("%c", dead_cell);
		} printf("\n"); //wichtig
	}
}


//LEBENDE ZELLEN BERECHNEN
int activ_count(int board[height][width]) {
	int anz, i, j;
	anz = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (board[i][j] == red || board[i][j] == green) {
				anz++;
			}
		}
	}return anz;
};


//REDRAW SPIELFELD
void redraw(int board[height][width], int gen, int aktive_zellen, char* prompt) {
	head();
	printf("\t%d Generation; %d Live Cells; %dx%d Spielfeld\n\n", gen, aktive_zellen, width, height);
	printf("\033[6;2H");//animation ohne Blinken
	printf(prompt);
	print_arr(board);
}

//NACHBARNZELLEN BERECHNEN
int count_neigbours(int board[height][width], int x, int y) {
	int i, j, count = 0;
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (!(i == 0 && j == 0) &&
				(x + i >= 0 && x + i < height) &&
				(y + j >= 0 && y + j < width) &&
				(board[x + i][y + j] == red || board[x + i][y + j] == green))
				count++;
		}
	}   return count;
}

//ZELLENZUSTAND ERMITTELN
void new_state(int board[height][width], int new_s[height][width], int x, int y) {
	int current = board[x][y];

	int anz_neighbours = count_neigbours(board, x, y);
	if (current == dead && anz_neighbours == 3) {
		new_s[x][y] = red;
	}
	else if (current == red && anz_neighbours > 3 || current == green && anz_neighbours > 3) {
		new_s[x][y] = dead;
	}
	else if (current == red && anz_neighbours < 2 || current == green && anz_neighbours < 2) {
		new_s[x][y] = dead;
	}
	else if (current == red && anz_neighbours == 2 || current == green && anz_neighbours == 2) {
		new_s[x][y] = green;
	}
	else if (current == red && anz_neighbours == 3 || current == green && anz_neighbours == 3) {
		new_s[x][y] = red;
	}
	else new_s[x][y] = dead;
}

//KOPIE VOM SPIELFELD ERSTELLEN
void copy_playingboard(int new_board[height][width], int board[height][width]) {
	int i, j;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			board[i][j] = new_board[i][j];
}


//NÄCHSTE GENERATION ins SPIELFELD packen
void next_gen(int board[height][width]) {
	int i, j;
	int new_board[height][width];
	init_board(new_board);
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			new_state(board, new_board, i, j);
		}
	}copy_playingboard(new_board, board);
}


//Abarbeitung Abfrage


//ANIMATION
void abarbeitung_animation(int board[height][width], int gen_anz, int aktive_zellen) {
	while (1) {
		system("CLS");
		redraw(board, gen_anz, aktive_zellen, "Neues Spiel: beliebige Taste druecken\n");
		next_gen(board);
		aktive_zellen = activ_count(board);
		gen_anz++;
		Sleep(500);
		if (_kbhit()) {
			char c = getch();
			break;
		}
	}
	umleitung_nach_falscheingabe();
}


//SCHRITTWEISE ABARBEITUNG
void abarbeitung_schrittweise(int board[height][width], int gen_anz, int aktive_zellen) {
	redraw(board, gen_anz, aktive_zellen, "ENTER druecken, um die naechste Generation zu generieren. Neues Spiel - beliebige Taste.\n");
	next_gen(board);
	aktive_zellen = activ_count(board);
	while (1) {

		int c;
		if ((c = _getch()) != 13) {
			umleitung_nach_falscheingabe();
		}
		system("CLS");
		redraw(board, gen_anz, aktive_zellen, "ENTER druecken, um die naechste Generation zu generieren. Neues Spiel - beliebige Taste.\n");
		next_gen(board);
		aktive_zellen = activ_count(board);
		gen_anz++;
	}
}

//MENÜ TEIL ZWEI
//Schrittweise oder Animation?
void menu2(int board[height][width], int aktive_zellen) {
	system("CLS");
	int x = 2, y = 5;
	gotoXY(2, 0);
	int gen_anz = 0;
	system("CLS");
	head();
	gotoXY(2, 5);
	printf("\033[1;32m[>]\033[0m     Schrittweise Abarbeitung\n"); printf("");
	gotoXY(2, 7);
	printf("[>]     Fliessende Animation \n");
	gotoXY(2, 5);
	while (1) {
		while (!_kbhit());
		gotoXY(x, y);
		printf("[ ]");
		switch (_getch()) {

		case 72: y = 5; break; // hoch

		case 80: y = 7; break; // runter
		case 13:
			system("CLS");
			if (y == 7) {
				abarbeitung_animation(board, gen_anz, aktive_zellen);
			}
			else { abarbeitung_schrittweise(board, gen_anz, aktive_zellen); }
			break;
		case 27:
			umleitung_nach_falscheingabe(); break;
		}gotoXY(x, y);
		printf("\033[1;32m"); printf("[>]"); printf("\033[0m");
	}
}

//Speicherzustand ermitteln. Speicher voll - keine weitere Dateien speichern
int zeilen() {
	FILE* save;
	int count = 0;
	char temp[1024];
	if ((save = fopen("client_files.txt", "r+t")) != 0) {
		while (fgets(temp, 1024, save) != 0) {
			count++;
		}
	}
	else { umleitung_nach_falscheingabe(); }
	fcloseall();
	return count;
}

//Dateinname vom Nutzer speichern und prüfen DAU
void DAUEingabe() {

	int tolerance = 2;
	printf("Geben Sie den Dateinamen ein:\n");
	char line[1024];
	fgets(line, 1024, stdin);
	//check, ob der Dateiname nicht leer ist
	while(tolerance>0) {
	
		tolerance--;
	if (line[0] == '\n') {
		printf("Sie haben keinen Dateinamen eingegeben! \n");
		printf("Geben Sie den Dateinamen ein:\n");
		fgets(line, 1024, stdin);
	}
	if (line[0] != '\n') {
		printf("Die Datei wurde erfolgreich speichert: \nDateiname: %sNeustart in wenigen Sekunden", line);
		break;
	}
	if (tolerance == 0) {
		char noname[15] = "NoName Datei";
		sprintf(line, "%s\n", noname);
		printf("Sie haben keinen gueltigen Dateinamen eingegeben. Die Datei wurde unter dem Namen \"NoName Datei\" gespeichert.");

	}
	
}
	
	//Dateiname speichern
	FILE* save;
	if ((save = fopen("client_files.txt", "a+t")) != 0) { //Dateiname speichern
		fputs(line, save);
	}fcloseall();
};

//Datei erstellen
int create_file(int board[height][width])
{
	int count = zeilen();
	if (count == 10) {  //Speicherprüfung
		system("CLS");
		printf("\tDer Speicher ist ausgeschoepft. Sie koennen keine weiteren Zustaende speichern. Neustart in wenigen Sekunden");
		Sleep(3000);
		umleitung_nach_falscheingabe();
	}
	gotoXY(0, height + 3);
	char filename[1024];
	
	//Dateiname DAUEingabeprüfung und Speicherung
	DAUEingabe();

	//Dateipfad und Datei erstellen
	int counter = zeilen();
	FILE* stream;
	char te[50] = ".txt";
	sprintf(filename, "%d%s", counter, te);   
	if ((stream = fopen(filename, "w+t")) == 0) {
		printf("ERROR");
	}

	int i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {

			if (board[i][j] == red) {
				char num[1024];
				sprintf(num, "%d,%d\n", j, i);
				fputs(num, stream);

			}
		}
	}


	fcloseall();
	Sleep(2000);
	system("CLS");
	neustart();
	return;
}

//EDIT -ja
int edit_yes(int board[height][width]) {
	int x = 0; int y = 0;
	system("CLS");
	print_arr(board);
	gotoXY(0, height + 1);
	printf("Editieren:SPACE; Navigation: Pfeile; Zustand speichern: ENTER; Neustart vom Spiel: ESCAPE \n");
	gotoXY(0, 5);
	while (1) {
		while (!kbhit());
		gotoXY(x, y);
		switch (getch()) {
		case 75: x = (--x + width) % width; break; // links
		case 72: y = (--y + height) % height; break; // hoch
		case 77: x = (++x + width) % width; break; // rechts
		case 80: y = (++y + height) % height; break; // runter
		case 32:
			if (board[y][x] == red) {
				board[y][x] = dead;
				printf(" ");
			}
			else if (board[x][y] == dead) {
				printf("*");
				board[y][x] = red;

			}
			break;
		case 27:  umleitung_nach_falscheingabe(); break;
		case 13:
			create_file(board);
			break;

		}
		gotoXY(x, y);

	}
}

//EDIT -nein
void edit_no(int board[height][width], int aktive_zellen) {
	menu2(board, aktive_zellen);
}

//EDITIEREN Abfrage im Menü
void edit(int board[height][width]) {
	system("CLS");
	int x = 0, y = 4;
	int gen_anz = 0;
	int aktive_zellen;
	aktive_zellen = activ_count(board);
	head();
	printf("\tWollen Sie den geladenen Startzustand editieren?\n");
	gotoXY(0, 4);
	printf("\033[1;32m[>]\033[0m     Editieren\n");
	gotoXY(0, 6);
	printf("[ ]     Editieren ueberspringen\n");
	gotoXY(x, y);
	while (1) {
		while (!_kbhit());
		gotoXY(x, y);
		printf("[ ]");
		switch (getch()) {
		case 72: y = 4; break;
		case 80: y = 6;  break;
		case 13:
			if (y == 4) {
				edit_yes(board);    //EDITIEREN
			}
			else if (y == 6) {
				edit_no(board, aktive_zellen); //NICHT EDITIEREN
			}
			break;
		case 27: umleitung_nach_falscheingabe(); break;
		}
		gotoXY(x, y);
		printf("\033[1;32m"); printf("[>]"); printf("\033[0m");
	}
}

//STARTZUSTAND AUS EINER editierten oder default DATEI EINLESEN
int readFromFile(int board[height][width], char* prompt) {
	int x = 0;
	int y = 0;
	FILE* fp;
	if ((fp = fopen(prompt, "r+t")) == NULL) {
		system("CLS");
		printf("Fehler beim Oeffnen von %s \n", prompt);
		umleitung_nach_falscheingabe();
	}
	else {
		while (fscanf(fp, "%d,%d\n", &y, &x) != EOF) {
			board[x][y] = red;
		}
		fclose(fp);
	}

	edit(board);
	return 1;
}


// ZUFALLSZAHLENGENERATOR
void zzgenerator(int board[height][width], int proz) {
	if (proz > 100 || proz < 0) {
		proz = 0;
	}
	int x = 0;
	int y = 0;
	srand(time(NULL));
	for (x = 0; x < height; x++) {
		for (y = 0; y < width; y++) {

			board[x][y] = rand() % 100 + 1 < proz ? red : dead;
		}
	}

	edit(board);
}


//PROZENTANGABE für ZZ-Generator
void prozentangabe(int board[height][width]) {
	system("CLS");
	int proz = 10;
	head();
	gotoXY(2, 4);
	printf("Zu wie viel Prozent soll das Spielfeld mit lebenden Zellen gefuellt werden? Mit Pfeilen hoch/runter die Prozentzahl anpassen. \n ");
	gotoXY(2, 7);
	printf("%3d Prozent", proz);
	while (1) {
		int num = 0;
		gotoXY(2, 7);
		switch (getch()) {

		case 72: proz += 10; if (proz > 100) {
			proz = 100;
		}
			   else if (proz < 0) {
			proz = 0;
		}
			   printf("%3d Prozent", proz);
			   break; // hoch

		case 80:  proz -= 10; if (proz > 100) {
			proz = 100;
		}
			   else if (proz < 0) {
			proz = 0;
		}
			   printf("%3d Prozent", proz);
			   break;  // runter
		case 13:
			zzgenerator(board, proz); break;
		case 27:
			umleitung_nach_falscheingabe(); break;
		}

	}
}


//Gespeicherte Dateien Laden Menü
int saved_files(int board[height][width], char* prompt) {
	system("CLS");
	head();
	int x = 0;
	int y = 4;
	printf(prompt);
	FILE* fp;
	char path1[30] = "Speicher leer";
	char path2[30] = "Speicher leer";
	char path3[30] = "Speicher leer";
	char path4[30] = "Speicher leer";
	char path5[30] = "Speicher leer";
	char path6[30] = "Speicher leer";
	char path7[30] = "Speicher leer";
	char path8[30] = "Speicher leer";
	char path9[30] = "Speicher leer";
	char path10[30] = "Speicher leer";
	if ((fp = fopen("client_files.txt", "r+t")) == NULL) {
		printf("ERROR. Dateien vom Kunden konnten nicht geladen werden.\n");
		umleitung_nach_falscheingabe();
	}

	fgets(path1, 30, fp);
	fgets(path2, 30, fp);
	fgets(path3, 30, fp);
	fgets(path4, 30, fp);
	fgets(path5, 30, fp);
	fgets(path6, 30, fp);
	fgets(path7, 30, fp);
	fgets(path8, 30, fp);
	fgets(path9, 30, fp);
	fgets(path10, 30, fp);
	gotoXY(0, 4);
	printf("\033[1;32m[>]\033[0m     %s\n", path1);
	gotoXY(0, 5);
	printf("[ ]     %s\n", path2);
	gotoXY(0, 6);
	printf("[ ]     %s\n", path3);
	gotoXY(0, 7);
	printf("[ ]     %s\n", path4);
	gotoXY(0, 8);
	printf("[ ]     %s\n", path5);
	gotoXY(0, 9);
	printf("[ ]     %s\n", path6);
	gotoXY(0, 10);
	printf("[ ]     %s\n", path7);
	gotoXY(0, 11);
	printf("[ ]     %s\n", path8);
	gotoXY(0, 12);
	printf("[ ]     %s\n", path9);
	gotoXY(0, 13);
	printf("[ ]     %s\n", path10);
	gotoXY(x, y);
	while (1) {
		while (!_kbhit());
		gotoXY(x, y);
		printf("[ ]");
		switch (getch()) {
		case 72: if (y != 4) {
			y = (--y + 25) % 25;
		}
			   else y = 4;
			break;
		case 80: if (y != 13) { y = (++y + 25) % 25; }
			   else y = 13;  break;
		case 13:
			switch (y) {
			case 4: readFromFile(board, "1.txt");  break;
			case 5: readFromFile(board, "2.txt");  break;
			case 6: readFromFile(board, "3.txt"); break;
			case 7: readFromFile(board, "4.txt"); break;
			case 8: readFromFile(board, "5.txt"); break;
			case 9: readFromFile(board, "6.txt");  break;
			case 10: readFromFile(board, "7.txt");  break;
			case 11: readFromFile(board, "8.txt"); break;
			case 12: readFromFile(board, "9.txt"); break;
			case 13: readFromFile(board, "10.txt"); break;
			}
			break;
		case 27: umleitung_nach_falscheingabe(); break;
		}
		gotoXY(x, y);
		printf("\033[1;32m"); printf("[>]"); printf("\033[0m");

	}

}


//Menüschritt Startzustand laden
void menu1(int board[height][width], int y) {
	int num = 1;
	switch (y) {
	case 5:readFromFile(board, "gosper_glider_gun.txt"); break;
	case 6:readFromFile(board, "Pulsar.txt"); ; break;
	case 7:readFromFile(board, "state.txt"); break;
	case 8: prozentangabe(board);
		break;
	case 9:
		saved_files(board, "Waehlen Sie die Datei zum Einlesen aus:\n", num);
		break;
	}
}


//HAUPTMENÜ
void menu(int board[height][width]) {
	head();
	int x = 2;
	int y = 5;
	gotoXY(2, 5);
	printf("\033[1;32m[>]\033[0m    Den Startzustand \"Spaceship\" laden\n ");
	gotoXY(2, 6);
	printf("[ ]    Den Startzustand \"Pulsar laden\" \n");
	gotoXY(2, 7);
	printf("[ ]    Den Startzustand \"Glider laden\"\n");
	gotoXY(2, 8);
	printf("[ ]    Den Startzustand per Zufallszahlengenerator generieren \n");
	gotoXY(2, 9);
	printf("[ ]    Den von Ihnen gespeicherten Zustand laden\n");
	gotoXY(x, y);


	while (1) {
		while (!_kbhit());
		gotoXY(x, y);
		printf("[ ]");
		switch (getch()) {
		case 72: if (y != 5) {
			y = (--y + 25) % 25;
		}
			   else y = 5;
			break;
		case 80: if (y != 9) { y = (++y + 25) % 25; }
			   else y = 9;  break;
		case 13: menu1(board, y);
			break;

		case 27:
			umleitung_nach_falscheingabe(); break;
		}
		gotoXY(x, y);
		printf("\033[1;32m"); printf("[>]"); printf("\033[0m");
	}
}


//SPIELNEUSTART 
int neustart() {

	int board[height][width];
	init_board(board);
	menu(board);
	return;
}


//SPIEL NEUANFANG INFOLGE FALSCHER TASTENEINGABE
//ODER NEUES SPIEL
int umleitung_nach_falscheingabe() {
	system("CLS");
	printf("\033[1;31m");
	printf("\n\tEXIT.\n\tNEUSTART IN WENIGEN SEKUNDEN. \n");
	printf("\033[0m");
	Sleep(500);
	system("CLS");
	neustart();
	return;
}
//Main Function
int main() {
	system("CLS");  //ohne fehlerhafte Anzeige von Farben im 1. Menüschritt
	neustart();
	return 0;
}