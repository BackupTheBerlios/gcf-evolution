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

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <fstream>
#include <signal.h>

// Maximal markierbare/l�schbare Files
   #define MAX_FILES  512
// Delay zwischen Markieren und L�schen in s
   #define DEL_DELAY  300

using namespace std;

char path[60];
DIR *dir;
struct dirent *pdir;

void *display(void *d)
{

     signal(SIGHUP, SIG_IGN);

	 int len = strlen(path);
     int l,m;
     l = 0;

	 while (true)
	 {

       char dateien[MAX_FILES][80];
       for(int i=0; i<MAX_FILES; i++)
	   {
               for (int k=0; k<=len; k++) dateien[i][k] = path[k];
       }
       dir = opendir(path);
       //Neue zum L�schen Markieren
       while ((pdir=readdir(dir)) != NULL)
       {
         l++;
       	 for (int k=0; k < 20; k++) dateien[l-1][len+k]=(*pdir).d_name[k];
         if(l==MAX_FILES - 1) break;
       }
 	   sleep(DEL_DELAY); //Delay vorm L�schen
       //Vorher markierte l�schen
       for(m = 0; (strlen(dateien[m]) > len); m++)
       {
           if (strlen(dateien[m]) > len+2)
           {
              unlink(dateien[m]);

           }
           if (m==MAX_FILES - 1) break;
       }
       //Restl�schung
       char rmc[90] = "rm -rf ";
       for(int k=7; k<=len+6; k++)
       {
          rmc[k] = path[k-7];
       }
       for(int k=len+7; k<=len+27; k++)
       {
          rmc[k] = char(63);
       }
       rmc[len+28] = char(42);
       rmc[len+29] = char(0);
       system(rmc);

       cout<<"[eww] Es wurden "<<l-2<<" alte Dateien gel�scht...\n";
       m = 0;
       l = 0;

    }

	pthread_exit(NULL);

}

int main(int argc, char *argv[])
{
        signal(SIGHUP, SIG_IGN);

        string c;
        pthread_t tdisplayer;

        //Wurm-Pfad in globale Variable einf�gen
        for (int u=0; u<61; u++) path[u]=argv[1][u];

        //Sicherheitsabfrage
        if(strlen(argv[1])<3)
        {
            cout<<"Sie haben keinen oder einen zu kleinen Pfad angegeben\n";
            return 0;
        }else{
            cout<<"Sind Sie sich sicher, den Pfad "<<path<<" zu verwenden?"<<
                  " (ja/nein)"<<endl;
            cout<<"In diesem Pfad werden alle Dateien und Unter"<<
                  "verzeichnisse regelm��ig gel�scht!"<<endl;
            cin>>c;
            if(c!="ja") return 0;
        }

        pthread_create(&tdisplayer, NULL, display, NULL);

       	c = "";
        while(c!="q")
        {
                cout<<"Zum Beenden q [Enter]\n";
                cin>>c;
        }

        return 0;
}
