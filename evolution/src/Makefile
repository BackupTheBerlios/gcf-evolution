SOURCES  = eww.cpp wcpy.cpp worm.cpp wurmkill.cpp
OBJFILES = $(SOURCES:.cpp=.o)
BINARIES = eww wcpy worm wurmkill

-include ../Makefile.Config

.cpp.o: $(SOURCES)
	$(CXX) -c -o $@ $< 

all: configured $(BINARIES)
	@echo " "
	@echo "                        _________________ ___________"
	@echo "                       /  _____/\_   ___ \\_   _____/"
	@echo "                      /   \  ___/    \  \/ |    __)"
	@echo "                      \    \_\  \     \____|     \\"
	@echo "                       \______  /\______  /\___  /"
	@echo "                              \/        \/     \/"
	@echo "                        The German Computer Freaks"
	@echo "                         www.gcf.de    Since 1997                         /\\"
	@echo "                                                                         /  \\"
	@echo "________________________________________________________________________/ # /"
	@echo "evolution|etwo R001                                             Science \  /"
	@echo "� das evolution-Team, 25.05.2003 - www.gcf.de/evolution                  \/"
	@echo ""
	@echo -en "\e[31m"
	@echo "-----------------------------------WARNUNG-----------------------------------"
	@echo "Der Einsatz von evolution|etwo ist mit Gefahren f�r Hard- und Software"
	@echo "verbunden und geschieht auf eigene Gefahr."
	@echo "Da evolution-W�rmer nur durch Zufall und v�llig unkontrolliert mutieren,"
	@echo "k�nnen auch b�sartige und destruktive W�rmer entstehen, die Ihr System - sei"
	@echo "es die Software oder auch die Hardware - zerst�ren k�nnten. F�hren Sie den"
	@echo "Wurm deshalb nur aus, wenn Sie in Kauf nehmen, dass so etwas passieren kann,"
	@echo "und wenn der Rechner, auf dem Sie es starten m�chten, Ihr pers�nliches"
	@echo "Eigentum ist."
	@echo "evolution|etwo wird auf vielfachen Wunsch trotz dieser nicht unbeachtlichen"
	@echo "Risiken, �ber die Sie nun aufgekl�rt worden sind, zum Download (auf Request)"
	@echo "angeboten."
	@echo "Setzen Sie evolution zu destruktiven Zwecken oder zu Sabotagezwecken ein,"
	@echo "drohen Ihnen strafrechtliche Konsequenzen."
	@echo "F�r s�mtliche Sch�den die durch evolution|etwo - sei es direkt oder indirekt"
	@echo "- entstehen, ist alleine derjenige verantwortlich, der es auf dem"
	@echo "betreffenden PC startete."
	@echo "-----------------------------------WARNUNG-----------------------------------"
	@echo -en "\e[0m"
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo ""
	@echo "� 2003 das evolution-Team. Alle Rechte vorbehalten."
	@echo "Nicht gestattet sind unerlaubte Vervielf�ltigung, Verleih, Verkauf,"
	@echo "Weitergabe, Ver�ffentlichung oder Nutzung innerhalb anderen Projekten."
	@echo "Das evolution-Team beh�lt sich vor, bestimmte �bereink�nfte zur Nutzung"
	@echo "dieses Software-Paketes jederzeit zu �ndern oder zu widerrufen."
	@echo ""
	@echo ""
	@echo "Jetzt fehlt eigentlich nur noch ein 'make install' als root, und dann kann's"
	@echo "eigentlich auch schon los gehen ;-)"

configured:
	test -f ../Makefile.Config

eww: eww.o
	$(CXX) $(LDFLAGS) $< -o $@

wcpy: wcpy.o
	$(CXX) $< -o $@

worm: worm.o
	$(CXX) $< -o $@
	chmod 644 $@ # Erstmal verhindern, da� worm ausversehen gestartet wird.

wurmkill: wurmkill.o
	$(CXX) $< -o $@

install: configured
	$(CHMOD) 755 wcpy eww wurmkill
	$(CHOWN) $(ROOTUSER) $(ROOTGROUP) wcpy wurmkill eww
	
	# Der Wurm sollte nur vom Benutzer wormuser gestartet werden k�nnen.
	# Da der wormuser aber kein chmod ausf�hren k�nnen soll, mu� die Datei
	# einem priveligisierterem Benutzer geh�ren (hier: root). Also mu� die
	# Gruppe wormgroup sein, damit der Wurm nicht ausversehen mit
	# root-Rechten gestartet wird.
	$(CHMOD) 650 worm
	$(CHOWN) $(ROOTUSER) $(WORMGROUP) worm
	
	cp wcpy eww wurmkill worm $(exeprefix)

clean:
	rm -f $(BINARIES) $(OBJFILES)

distclean: clean
	rm -f config.h