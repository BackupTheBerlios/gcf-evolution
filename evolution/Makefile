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
	chown $(WORMUSER):$(WORMGROUP) $(wormhome) $(wormcivdir)
	
	echo "MAKE_INSTALL_CREATED_USER = true" >> Makefile.Config
endif
endif
	
ifdef UPDATE_BASHRC
ifndef UPDATED_BASHRC
	echo 'export PATH=$$PATH:$(exeprefix)' >> $(wormhome)/.bashrc
	echo "UPDATED_BASHRC = true" >> Makefile.Config
endif
endif
	$(MAKE) -C src install

clean:
	$(MAKE) -C src clean

distclean:
	$(MAKE) -C src distclean
	rm -f Makefile.Config
