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
© das evolution-Team, 25.05.2003 - www.gcf.de/evolution                  \/

-----------------------------------WARNUNG-----------------------------------
Der Einsatz von evolution|etwo ist mit Gefahren für Hard- und Software
verbunden und geschieht auf eigene Gefahr.
Da evolution-Würmer nur durch Zufall und völlig unkontrolliert mutieren,
können auch bösartige und destruktive Würmer entstehen, die Ihr System - sei
es die Software oder auch die Hardware - zerstören könnten. Führen Sie den
Wurm deshalb nur aus, wenn Sie in Kauf nehmen, dass so etwas passieren kann,
und wenn der Rechner, auf dem Sie es starten möchten, Ihr persönliches
Eigentum ist.
evolution|etwo wird auf vielfachen Wunsch trotz dieser nicht unbeachtlichen
Risiken, über die Sie nun aufgeklärt worden sind, zum Download (auf Request)
angeboten.
Setzen Sie evolution zu destruktiven Zwecken oder zu Sabotagezwecken ein,
drohen Ihnen strafrechtliche Konsequenzen.
Für sämtliche Schäden die durch evolution|etwo - sei es direkt oder indirekt
- entstehen, ist alleine derjenige verantwortlich, der es auf dem
betreffenden PC startete.
-----------------------------------WARNUNG-----------------------------------

© 2003 das evolution-Team. Alle Rechte vorbehalten.
Nicht gestattet sind unerlaubte Vervielfältigung, Verleih, Verkauf,
Weitergabe, Veröffentlichung oder Nutzung innerhalb anderen Projekten.
Das evolution-Team behält sich vor, bestimmte Übereinkünfte zur Nutzung
dieses Software-Paketes jederzeit zu ändern oder zu widerrufen.

*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "config.h"

int main(int argc, char *argv[]) {
	int pid = atoi(argv[1]), bashs_pid;
	
	if (!pid) {
		std::cout << "wurmkill: Process tried to kill entire civilisation!\n" << std::endl;
		return 2;
	}
	
	FILE * bash_pid_file=fopen(BASH_PID_FILE,"r");
	if (!bash_pid_file) {
		std::cerr << "wurmkill: FATAL: " << BASH_PID_FILE << " doesn't exist!\n" << std::endl;
		return 4;
	}
	if (fscanf(bash_pid_file,"%i",bashs_pid) != 1) {
		std::cerr << "wurmkill: FATAL: " << BASH_PID_FILE << " doesn't contain a number!\n" << std::endl;
		return 5;
	}
	
	if (pid == bashs_pid) {
		std::cout << "wurmkill: Process tried to kill bash!\n" << std::endl;
		return 6;
	}
	
	if (kill(pid, 9)) {
		std::cerr << "wurmkill: Failed to kill: " << strerror(errno);
		return 3;
	}
	
	return 0;
}
