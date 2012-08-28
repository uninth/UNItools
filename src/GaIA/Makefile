#
# $Header$
#

# This has to be updated in unitools.spec too:
VERSION		= 1.0
RELEASE		= 26

# working catalog. Notice that RPM WD is below /usr/src/redhat/RPMS/i386/

RPMS		= /usr/src/redhat/RPMS/i386/
DIR			= /lan/ssi/shared/software/internal/UNItools/src/GaIA
# RPMDIR		= /lan/ssi/shared/software/internal/RPM
RPMDIR		= ../../RPM

specfile	= unitools.spec
spectmpl	= $(specfile).template

src			= pkgs

NAME		= UNItools
ARCH        = i386
package		= UNItools-$(VERSION)-$(RELEASE).i386.rpm
TARGET      = $(NAME)-$(VERSION)-$(RELEASE).$(ARCH).rpm
INSTALL		= INSTALL-$(NAME)-$(VERSION)-$(RELEASE).md
INST_HTML   = INSTALL-$(NAME)-$(VERSION)-$(RELEASE).html

default: $(RPMDIR)/$(TARGET)
	ls -l $(RPMDIR)/$(TARGET)

$(specfile): $(DIR)/$(spectmpl) Makefile
	sed "s/__VERSION__/$(VERSION)/g; s/__RELEASE__/$(RELEASE)/g" < $(spectmpl)  > $(specfile)

$(INSTALL): INSTALL.md
	@sed "									\
		s/__VERSION__/$(VERSION)/g;			\
		s/__RELEASE__/$(RELEASE)/g;			\
		s%__TARGET__%$(TARGET)%g;			\
		" < INSTALL.md > $(INSTALL)

spec: $(specfile) Makefile
	echo new $(specfile)

$(RPMS)/$(TARGET):	$(specfile)
	/bin/rm -f /usr/src/redhat/SPECS/UNItools*
	rpmbuild -bb --buildroot=/tmp/UNItools_buildroot $(specfile)

$(RPMDIR)/$(TARGET): $(RPMS)/$(TARGET) $(INSTALL)
	@/bin/mv $(RPMS)/$(TARGET) $(RPMDIR)
	@/bin/mv $(INSTALL) $(RPMDIR)

documentation:

recompile:
	echo this will take a long time and you should run it from a screen - sleeping 5 seconds .....
	sleep 5
	pkg_do_it_all_for_all_known_packages

clean:
	@rm -f $(specfile)
