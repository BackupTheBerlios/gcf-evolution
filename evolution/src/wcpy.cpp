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
evolution|etwo R001 - wcpy.cpp (wcpy)                           Science \  /
� 2003-2005 das evolution-Team - www.gcf.de/evolution                    \/

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

� 2003-2005 das evolution-Team. Alle Rechte vorbehalten.
Nicht gestattet sind unerlaubte Vervielf�ltigung, Verleih, Verkauf,
Weitergabe, Ver�ffentlichung oder Nutzung innerhalb anderen Projekten.
Das evolution-Team beh�lt sich vor, bestimmte �bereink�nfte zur Nutzung
dieses Software-Paketes jederzeit zu �ndern oder zu widerrufen.

*/

#include <unistd.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>

#include "config.h"

using namespace std;

int aktpid;

int exp(int Basis, int Exponent) {
	//Funktion zur Berechnung von Potenzen
	int m_iResult;
	m_iResult = Basis;
	for (int x = 2; x <= Exponent; x++) {
		m_iResult = m_iResult * Basis;
	}
	return m_iResult;
}

char bitchange(char cont) {
	int icont;
	bool bcont[8];
	icont = int (cont);
	
	//Zerlegen in 8Bit-Bool Array
	for (int b = 7; b >= 0; b--) {
		if (icont >= exp(2, b)) {
			bcont[b] = true;
			icont -= exp(2, b);
		} else {
			bcont[b] = false;
		}
	}
	
	//Zuf�llige Ver�nderungen
	for (int b = 7; b >= 0; b--) {
		if (!(rand() % 4)) {
			cout << aktpid << "| Ein Bit ge�ndert" << endl;
			if (bcont[b] == false) {
				bcont[b] = true;
			} else {
				bcont[b] = false;
			}
		}
	}
	
	//8Bit-Bool Array zu 1-Byte-Int
	icont = 0;
	for (int b = 7; b >= 0; b--) {
		if (bcont[b] == true)
			icont += exp(2, b);
	}
	
	//R�ckgabe des 8-Bit-Ints als Char
	return char (icont);
}

char randomizebyte(char cont) {
	if (rand() % WCPY_BYTE_CHG) {
		return cont;
	} else {
		cout << aktpid << "| Werde ein Byte ver�ndern" << endl;
		return bitchange(cont);
	}
}

void kopieren(char *dest, char *src) {
	try {
		std::ifstream von(src);
		std::ofstream nach(dest);
		char byte;
		while (von.get(byte)) {
			byte = randomizebyte(byte);
			if (!(rand() % WCPY_BYTE_ADD)) {
				nach.put(char (rand() % 256));
				cout << aktpid << "| Byte eingef�gt" << endl;
			}
			if (rand() % WCPY_BYTE_DROP) {
				nach.put(byte);
			} else {
				cout << aktpid << "| Byte ausgelassen" << endl;
			}
		}
	} catch (...) {
		cerr << "eww: Irgendwas ist schief gelaufen..." << endl;
	}
}

int main(int argc, char *argv[]) {
	aktpid = getpid();
	srand((unsigned) time(NULL) + 60 * aktpid);
	usleep(rand() % WCPY_MAX_SLEEP);
	cout << aktpid << "| Neuer Kopiervorgang... (Mutter = " << getppid() << ")" << endl;
	kopieren(argv[2], argv[1]);
}
