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
	@echo "© 2003-2005 das evolution-Team - www.gcf.de/evolution                    \/"
	@echo ""
	@echo -en "\e[31m"
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
	@echo -en "\e[0m"
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo -en "\7"; sleep 1;
	@echo ""
	@echo "© 2003-2005 das evolution-Team. Alle Rechte vorbehalten."
	@echo "Nicht gestattet sind unerlaubte Vervielfältigung, Verleih, Verkauf,"
	@echo "Weitergabe, Veröffentlichung oder Nutzung innerhalb anderen Projekten."
	@echo "Das evolution-Team behält sich vor, bestimmte Übereinkünfte zur Nutzung"
	@echo "dieses Software-Paketes jederzeit zu ändern oder zu widerrufen."
	@echo ""
	@echo ""
	@echo "Jetzt fehlt eigentlich nur noch ein 'make' und ein 'make install' als root, "
	@echo "und dann kann's eigentlich auch schon los gehen ;-)"

configured:
	test -f ../Makefile.Config

eww: eww.o
	$(CXX) $(LDFLAGS) $< -o $@

wcpy: wcpy.o
	$(CXX) $< -o $@

worm: worm.o
	$(CXX) $< -o $@
	chmod 644 $@ # Erstmal verhindern, dass worm ausversehen gestartet wird.
ifdef WORM_STRIP
	strip $@ # Und Strippen, falls angefordert.
endif

wurmkill: wurmkill.o
	$(CXX) $< -o $@

install: configured
	$(CHOWN) $(ROOTUSER):$(ROOTGROUP) wcpy wurmkill
	$(CHMOD) 755 wcpy wurmkill
	
	# eww darf nur von der Wurmgruppe gestartet werden. Auf diese weise wird 
	# sicher gestellt, dass nicht beim start von eww ausversehen ein wichtiges 
	# Verzeichnis angegeben wird, welches dann leergeräumt wird.
	# Das neue Problem, dass eww so wieder vom Wurm gekillt werden kann, wird 
	# durch SUID umgangen, eww erhält seine eigene Benutzerkennung.
	$(CHOWN) $(WORMUSER2):$(WORMGROUP) eww
	$(CHMOD) 4050 eww
	
	# Der Wurm sollte nur vom Benutzer evouser gestartet werden können.
	# Da der evouser aber kein chmod ausführen können soll, muss die Datei
	# einem priveligisierterem Benutzer gehören (hier: root). Also muss die
	# Gruppe evogroup sein, damit der Wurm nicht ausversehen mit
	# root-Rechten gestartet wird.
	$(CHOWN) $(ROOTUSER):$(WORMGROUP) worm
	$(CHMOD) 650 worm
	
	test -d $(prefix)    || mkdir -p $(prefix)
	test -d $(exeprefix) || mkdir -p $(exeprefix)
	
	cp -pf wcpy eww wurmkill worm starter.sh killworms.sh $(exeprefix)

clean:
	rm -f $(BINARIES) $(OBJFILES)

distclean: clean
	rm -f config.h
# su -c "chown evouser:evogroup killit && chmod 4750 killit"
