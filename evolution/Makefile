-include Makefile.Config

all:
	$(MAKE) -C src all

install:
ifdef MAKE_INSTALL_CREATE_GROUP
ifndef MAKE_INSTALL_CREATED_GROUP
	groupadd $(WORMGROUP)
	echo "MAKE_INSTALL_CREATED_GROUP = true" >> Makefile.Config
endif
endif
	
ifdef MAKE_INSTALL_CREATE_USER
ifndef MAKE_INSTALL_CREATED_USER
	useradd -g $(WORMGROUP) -c $(WORMDESCRIPTION) -p $(WORMPASS) $(WORMUSER)
	
	test -d $(wormhome) || mkdir -p $(wormhome)
	test -d $(wormcivdir) || mkdir -p $(wormcivdir)
	chown $(WORMUSER):$(WORMGROUP) $(wormhome)
	chmod 755 $(wormhome)
	
	echo "MAKE_INSTALL_CREATED_USER = true" >> Makefile.Config
endif
endif
	
ifdef MAKE_INSTALL_CREATE_USER2
ifndef MAKE_INSTALL_CREATED_USER2
	useradd -g $(WORMGROUP) -c $(WORMDESCRIPTION2) -p $(WORMPASS2) $(WORMUSER2)
	
	echo "MAKE_INSTALL_CREATED_USER2 = true" >> Makefile.Config
endif
endif
	
	chown $(WORMUSER2):$(WORMGROUP) $(wormcivdir)
	chmod 775 $(wormcivdir)
	
ifdef UPDATE_BASHRC
ifndef UPDATED_BASHRC
	echo '. $(wormhome)/.profile.worm' >> $(wormhome)/.profile
	echo "UPDATED_BASHRC = true" >> Makefile.Config
endif
endif
	rm -f $(wormhome)/.profile.worm
	echo 'export PATH=$$PATH:$(exeprefix)' >> $(wormhome)/.profile.worm
	$(MAKE) -C src install

clean:
	$(MAKE) -C src clean

distclean:
	$(MAKE) -C src distclean
	rm -f Makefile.Config
