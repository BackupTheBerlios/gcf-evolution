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

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <pthread.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "config.h"

using namespace std;

string path;
int evouser_uid;
int bashpid;

void *display(void *d) {
	signal(SIGHUP, SIG_IGN);
	
	int num_deleted, num_killed, delay, pid;
	map<string,int> datei;
	map<int,int> prozess;
	
	for (;;) {
		DIR * dir;
		struct dirent *pdir;
		
		{
			dir = opendir(path.c_str());
			
			num_deleted=0;
			
			// Neue zum L�schen Markieren
			while ((pdir = readdir(dir)) != NULL) {
				if (pdir==string(".") || pdir==string("..")) {
					continue;
				}
				if (datei[pdir->d_name]++ == EWW_ITERATIONS_TO_DELETE) {
//					cout << "unlink " << (path+"/"+pdir->d_name).c_str() << endl;
					unlink((path+"/"+pdir->d_name).c_str());
					datei.erase(pdir->d_name);
					++num_deleted;
				}
			}
			
			closedir(dir);
		}
		
		{
			dir = opendir(PROC_PATH);
			
			num_killed=0;
			
			// Neue zum L�schen Markieren
			while ((pdir = readdir(dir)) != NULL) {
				struct stat statbuf;
				
				if (!stat((string(PROC_PATH) + "/" + pdir->d_name).c_str(),&statbuf)
				&&   statbuf.st_uid == evouser_uid
				&&   (pid=atoi(pdir->d_name)) != bashpid) {
					if (prozess[pid]++ == EWW_ITERATIONS_TO_KILL) {
						cout << "kill " << pid << endl;
						kill(pid,SIGKILL);
						prozess.erase(pid);
						++num_killed;
					}
				}
			}
			
			closedir(dir);
		}
		
		cout << "[eww] " << num_deleted << " Dateien gel�scht, " << num_killed  << " Prozesse get�tet ...\n";
		
		delay=EWW_ITERATION_DELAY;
		
		do {
			sleep(1);
		} while (--delay);
	}
}

int main(int argc, char *argv[]) {
	signal(SIGHUP, SIG_IGN);
	
	string c;
	pthread_t tdisplayer;
	
	{
		struct passwd * evouser_passwd;
		
		evouser_passwd = getpwnam(EVOUSER);
		
		if (!evouser_passwd) {
			cerr << "Konnte Benutzer " << EVOUSER << " nicht in der Datei /etc/passwd finden!" << endl;
			return 4;
		}
		
		evouser_uid = evouser_passwd->pw_uid;
	}
	
	{
		FILE * bash_pid_file=fopen(BASH_PID_FILE,"r");
		
		if (!bash_pid_file) {
			cerr << "wurmkill: FATAL: " << BASH_PID_FILE << " doesn't exist!\n" << std::endl;
			return 4;
		}
		
		if (fscanf(bash_pid_file,"%i",&bashpid) != 1) {
			cerr << "wurmkill: FATAL: " << BASH_PID_FILE << " doesn't contain a number!\n" << std::endl;
			return 5;
		}
		
		fclose(bash_pid_file);
	}
	
	// Wurm-Pfad in globale Variable einf�gen
	path=argv[1];
	
	// Sicherheitsabfrage
	if (strlen(argv[1]) < 3) {
		cout << "Sie haben keinen oder einen zu kleinen Pfad angegeben\n";
		return 2;
	} else {
		cout << "Sind Sie sich sicher, den Pfad " << path << " zu verwenden?" << " (ja/nein)" << endl;
		cout << "In diesem Pfad werden alle Dateien und Unterverzeichnisse regelm��ig gel�scht!" << endl;
		cin >> c;
		if (c != "ja")
			return 0;
	}
	
	pthread_create(&tdisplayer, NULL, display, NULL);
	
	c = "";
	while (c != "q") {
		cout << "Zum Beenden q [Enter]\n";
		cin >> c;
	}
	
	return 0;
}
