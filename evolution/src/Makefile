SOURCES  = eww.cpp wcpy.cpp worm.cpp
OBJFILES = $(SOURCES:.cpp=.o)


.cpp.o: $(SOURCES)
	g++ -c -o $@ $< 

all: $(OBJFILES)
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
	@echo "© das evolution-Team, 25.05.2003 - www.gcf.de/evolution                  \/"
	@echo ""
	@echo "-----------------------------------WARNUNG-----------------------------------"
	@echo "Der Einsatz von evolution|etwo ist mit Gefahren für Hard- und Software"
	@echo "verbunden und geschieht auf eigene Gefahr."
	@echo "Da evolution-Würmer nur durch Zufall und völlig unkontrolliert mutieren,"
	@echo "können auch bösartige und destruktive Würmer entstehen, die Ihr System - sei"
	@echo "es die Software oder auch die Hardware - zerstören könnten. Führen Sie den"
	@echo "Wurm deshalb nur aus, wenn Sie in Kauf nehmen, dass so etwas passieren kann,"
	@echo "und wenn der Rechner, auf dem Sie es starten möchten, Ihr persönliches"
	@echo "Eigentum ist."
	@echo "evolution|etwo wird auf vielfachen Wunsch trotz dieser nicht unbeachtlichen"
	@echo "Risiken, über die Sie nun aufgeklärt worden sind, zum Download (auf Request)"
	@echo "angeboten."
	@echo "Setzen Sie evolution zu destruktiven Zwecken oder zu Sabotagezwecken ein,"
	@echo "drohen Ihnen strafrechtliche Konsequenzen."
	@echo "Für sämtliche Schäden die durch evolution|etwo - sei es direkt oder indirekt"
	@echo "- entstehen, ist alleine derjenige verantwortlich, der es auf dem"
	@echo "betreffenden PC startete."
	@echo "-----------------------------------WARNUNG-----------------------------------"
	@sleep 10
	@echo ""
	@echo "© 2003 das evolution-Team. Alle Rechte vorbehalten."
	@echo "Nicht gestattet sind unerlaubte Vervielfältigung, Verleih, Verkauf,"
	@echo "Weitergabe, Veröffentlichung oder Nutzung innerhalb anderen Projekten."
	@echo "Das evolution-Team behält sich vor, bestimmte Übereinkünfte zur Nutzung"
	@echo "dieses Software-Paketes jederzeit zu ändern oder zu widerrufen."
	g++ -lpthread eww.o -o eww
	# MUST BE -pthread FOR BSD SYSTEMS
	g++ wcpy.o -o wcpy
	g++ worm.o -o initialevolutionworm
	@echo "done. Now su root and type 'make install' "
	@echo " "

install:
	mv wcpy /bin/
	mv eww /root/
	chown root /bin/wcpy
	chgrp root /bin/wcpy	
	
	@echo "installed."

clean: 
	rm *.o


