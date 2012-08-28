# $Id: pktstat.spec.in 1198 2008-02-29 16:03:44Z d $
Name: pktstat
Version: @PACKAGE_VERSION@
Source0: http://www.adaptive-enterprises.com.au/~d/software/pktstat/%{name}-%{version}.tar.gz
Release: 1
Summary: Displays a live list of active connections and what files are being transferred.
Group: Applications/Internet
License: BSD
Vendor: David Leonard
URL: http://www.adaptive-enterprises.com.au/~d/software/pktstat/
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot
BuildPreReq: libpcap-devel, ncurses-devel

%description
Display a real-time list of active connections seen on a network
interface, and how much bandwidth is being used by what. Partially decodes
HTTP and FTP protocols to show what filename is being transferred. X11
application names are also shown. Entries hang around on the screen for
a few seconds so you can see what just happened. Also accepts filter
expressions á la tcpdump.

%prep
%setup

%build
%configure
make

%install
make install DESTDIR="$RPM_BUILD_ROOT"

%files
%defattr(-,root,root)
%attr(0755,root,root) %{_bindir}/pktstat
%attr(0644,root,root) %{_mandir}/man1/pktstat.*
%doc COPYING ChangeLog NEWS README TODO

