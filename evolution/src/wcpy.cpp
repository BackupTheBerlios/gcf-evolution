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

#include <unistd.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>

// Maximaler Delay vor dem Kopieren in us (1s = 1.000.000us)
   #define MAX_SLEEP  20000000
// Mutationsfaktoren (je kleiner, desto größere Mutation)
   #define BYTE_DROP     30000
   #define BYTE_ADD      30000
   #define BYTE_CHG      20000

using namespace std;

int aktpid;

extern void kopieren(char* ,char*);
extern char randomizebyte(char cont);
extern char bitchange(char cont);
extern int exp(int Basis, int Exponent);

int main(int argc, char *argv[])
{
        aktpid = getpid();
        srand((unsigned)time(NULL) * aktpid);
        usleep(rand()%MAX_SLEEP);
        cout<<aktpid<<"| Neuer Kopiervorgang..."<<endl;
        kopieren(argv[2], argv[1]);
}


void kopieren(char* dest,char* src)
{
        std::ifstream von(src);
        std::ofstream nach(dest);
        char byte;
        while(von.get(byte))
        {
                byte = randomizebyte(byte);
                   if(!(rand()%BYTE_ADD))
                   {
                     nach.put(char(rand()%256));
                     cout<<aktpid<<"| Byte eingefügt"<<endl;
                   }
                   if(rand()%BYTE_DROP)
                   {
                     nach.put(byte);
                   }else{
                     cout<<aktpid<<"| Byte ausgelassen"<<endl;
                   }
        }
}



char randomizebyte(char cont)
{
     if(rand()%BYTE_CHG)
     {
      return cont;
     }else{
      cout<<aktpid<<"| Werde ein Byte verändern"<<endl;
      return bitchange(cont);
     }
}

char bitchange(char cont)
{
     int icont;
     bool bcont[8];
     icont = int(cont);
     //Zerlegen in 8Bit-Bool Array
     for(int b=7; b>=0; b--)
         {
             if(icont >= exp(2,b))
             {
                   bcont[b] = true;
                   icont -= exp(2,b);
             }else{
                   bcont[b] = false;
             }
         }
     //Zufällige Veränderungen
     for(int b=7; b>=0; b--)
         {
             if(!(rand()%4))
             {
                   cout<<aktpid<<"| Ein Bit geändert"<<endl;
                   if (bcont[b]==false)
                   {
                       bcont[b]=true;
                   }else{
                       bcont[b]=false;
                   }
             }
         }
     //8Bit-Bool Array zu 1-Byte-Int
     icont = 0;
     for(int b=7; b>=0; b--)
         {
             if(bcont[b]==true) icont += exp(2,b);
         }
     //Rückgabe des 8-Bit-Ints als Char
     return char(icont);
}

int exp(int Basis, int Exponent)
{
     //Funktion zur Berechnung von Potenzen
     int m_iResult;
     m_iResult = Basis;
     for(int x=2; x<=Exponent ; x++)
     {
     m_iResult = m_iResult * Basis;
     }
     return m_iResult;
}
