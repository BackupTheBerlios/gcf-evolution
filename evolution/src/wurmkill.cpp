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

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
	int pid = atoi(argv[1]);
	
	if (!pid) {
		return 2;
	}
	
	if (kill(pid, 9)) {
		return 3;
	}
	
	return 0;
}
