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
© 2003-2005 das evolution-Team - www.gcf.de/evolution                    \/

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

© 2003-2005 das evolution-Team. Alle Rechte vorbehalten.
Nicht gestattet sind unerlaubte Vervielfältigung, Verleih, Verkauf,
Weitergabe, Veröffentlichung oder Nutzung innerhalb anderen Projekten.
Das evolution-Team behält sich vor, bestimmte Übereinkünfte zur Nutzung
dieses Software-Paketes jederzeit zu ändern oder zu widerrufen.

*/

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
// #include <pthread.h>
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

int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid);
int setresuid(uid_t ruid, uid_t euid, uid_t suid);

string path;
int evouser_uid;
int bashpid;
int my_bash_pid;

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
			
			// Neue Dateien zum Löschen markieren
			while ((pdir = readdir(dir)) != NULL) {
				if (pdir->d_name==string(".") || pdir->d_name==string("..")) {
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
			
			// Neue Prozesse zum töten markieren
			while ((pdir = readdir(dir)) != NULL) {
				struct stat statbuf;
				
				if (pdir->d_name==string(".")
				||  pdir->d_name==string("..")
				||  pdir->d_name==string("self")) {
					continue;
				}
				if (!stat((string(PROC_PATH) + "/" + pdir->d_name).c_str(),&statbuf)
				&&   statbuf.st_uid == evouser_uid
				&&   (pid=atoi(pdir->d_name)) != bashpid
				&&   (pid                   ) != my_bash_pid) {
//					cout << "Prozess nummer " << pid << " (d_name=\"" << pdir->d_name << "\" hat Wert " << prozess[pid] << "." << endl;
					if (prozess[pid]++ == EWW_ITERATIONS_TO_KILL) {
//						cout << "kill " << pid << endl;
						if (kill(pid,SIGKILL)) {
							cerr << "[eww]| kill " << pid << ": " << strerror(errno) << endl;
						}
						prozess.erase(pid);
						++num_killed;
					}
				}
			}
			
			closedir(dir);
		}
		
		cout << "[eww] " << num_deleted << " Dateien gelöscht, " << num_killed  << " Prozesse getötet ..." << endl;
		
		delay=EWW_ITERATION_DELAY;
		
		do {
			sleep(1);
		} while (--delay);
	}
}

void printresuid() {
	uid_t r,e,s;

	if (getresuid(&r,&e,&s)) {
		fprintf(stderr,"getresuid: %s\n",strerror(errno));
		return;
	}

	printf("[eww]| uid{r=%u,e=%u,s=%u}\n",(unsigned)r,(unsigned)e,(unsigned)s);
}
	
int main(int argc, char *argv[]) {
	printresuid();
	setresuid(geteuid(),getuid(),geteuid());
	printresuid();
	
	// Kein evouser als saved uid, sonst darf uns der Wurm trotzdem noch killen.
/*
	setreuid(geteuid(),geteuid());
*/
	
	my_bash_pid=getppid();
	
	signal(SIGHUP, SIG_IGN);
	setsid();
	
	string c;
//	pthread_t tdisplayer;
	
	{
		struct passwd * evouser_passwd;
		
		evouser_passwd = getpwnam(EVOUSER);
		
		if (!evouser_passwd) {
			cerr << "Konnte Benutzer " << EVOUSER << " nicht in der Datei /etc/passwd finden!" << endl;
			return 6;
		}
		
		evouser_uid = evouser_passwd->pw_uid;
	}
	
	{
		FILE * bash_pid_file=fopen(BASH_PID_FILE,"r");
		
		if (!bash_pid_file) {
			cerr << "eww: FATAL: " << BASH_PID_FILE << " doesn't exist!" << std::endl;
			return 4;
		}
		
		if (fscanf(bash_pid_file,"%i",&bashpid) != 1) {
			cerr << "eww: FATAL: " << BASH_PID_FILE << " doesn't contain a number!" << std::endl;
			return 5;
		}
		
		fclose(bash_pid_file);
	}
	
	// Wurm-Pfad in globale Variable einfügen
	if (argc == 2 && strlen(argv[1]) < 3) {
		cout << "Sie haben einen zu kleinen Pfad angegeben." << endl;
		return 2;
	}
	
	if (argc > 2) {
		cout << "Sie haben zu viele Argumente übergeben." << endl;
		return 7;
	}
	
	if (argc == 1) {
		path=WORMCIVDIR;
		cout << "Benutze Standardpfad " << path << "." << endl;
	} else {
		path=argv[1];
		
		// Sicherheitsabfrage
		cout << "Sind Sie sich sicher, den Pfad " << path << " zu verwenden?" << " (ja/nein)" << endl;
		cout << "In diesem Pfad werden alle Dateien und Unterverzeichnisse regelmässig gelöscht!" << endl;
		cin >> c;
		if (c != "ja")
			return 0;
	}
	
	display(NULL);
	
/*
	pthread_create(&tdisplayer, NULL, display, NULL);
	
	c = "";
	while (c != "q") {
		cout << "Zum Beenden q [Enter]\n";
		cin >> c;
	}
*/

	return 0;
}
