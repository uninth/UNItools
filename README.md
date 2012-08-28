
[![Documentation][logo]][documentation]
[logo]: UNItools.png
[documentation]: src/GaIA/pkgs/documentation/UNItools.pdf

# UNItools - Readme

UNItools is a collection of command line utilities which I have found helpful
in managing Check Point firewalls. They are/where all freely available on the
Internet, and have been compiled for
[GAiA](https://www.checkpoint.com/press/2012/check-point-introduces-gaia-unified-secure-operating-system-with-its-latest-r75-40-software-blade-release/)
on a fedora6 (zod) core.
The old version was selected as the package original also was compiled for
[SPLAT](https://en.wikipedia.org/wiki/Check_Point_VPN-1).

I believe most tools may have been outdated by now or been superseded by
something more fancy.

The package  _UNItools_ is required by the other packages _UNIfw1doc_,
_UNIfw1lr_, _UNIha_, _UNIlog_, _UNItools_ and  _UNIzab_.

### Security

As none of the programs are exposed to the outside, there should be few if any
security risks using them on a ad-hoc basis, and you may not be able to execute
the files when compiled on an newer system.

## Deployment - GaIA

The RPM and the installation instruction is found [in RPM](RPM).

The package installs a backup and configuration migration, see
`/var/opt/UNItools/fwbu/`. The backup runs on a daily basis from cron - see
`/etc/cron.d/UNItools_backup`. All other files are store below
`/var/opt/UNItools`.

## Deployment - SPLAT

The archive `UNItools.SPLAT.1.0.tgz` is for Secure Platform - the predecessor
of GAiA. It installs in /var/opt/UNItools and must be configured with
`/var/opt/UNItools/bin/setup.sh`.  Do examen the script before executing it.

## Documentation

The package is documented as one pdf file. Once installed the documentation is
in `/var/opt/UNItools/docs/UNItools.pdf`.
[A copy of the documentation is here](src/GaIA/pkgs/documentation/UNItools.pdf)

## Development - GAiA

You can re-compile everything add and modify packages. The source is in `src`:

    UNItools
            `-- src
                `-- GaIA
                    |-- UNItools-coverpage.graffle
                    |-- UNItools_buildroot
                    |-- hpacucli
                    `-- pkgs ...


The source for each component is below `pkgs` together with a file
named `setup.sh` which must be executed.  The documentation is below
`pkgs/documentation`.

A number of small scripts for testing etc. is in `pkg_tools.tgz`; unpack
and place somewhere in your `$PATH`.

Build all programs this way (you may have to change paths in the
scripts first):

	pkg_do_it_all_for_all_known_packages
	cd UNItools/src/GaIA
	make

New packages may be added and a directory with source and compile instructions
made with the command `pkg_setup` _URL version local-package-name_. See an existing
package for further information.

Executing `setup.sh` also produces a test script, which may be used to test each
package on a Check Point firewall. It installs the package and tests if all required
shared libraries are available.

### Compile host

You will need a compile machine, `fedora6` will do as it resembles
GAiA enough. [Fedora6 ISO images are here](http://archive.fedoraproject.org/pub/archive/fedora/linux/core/6/x86_64/iso/),
you may download them with

    for f in FC-6-x86_64-DVD.iso FC-6-x86_64-disc1.iso FC-6-x86_64-disc2.iso FC-6-x86_64-disc3.iso FC-6-x86_64-disc4.iso FC-6-x86_64-disc5.iso FC-6-x86_64-disc6.iso FC-6-x86_64-rescuecd.iso README-BURNING-ISOS-en_US.txt SHA1SUM
    do
        wget http://archive.fedoraproject.org/pub/archive/fedora/linux/core/6/x86_64/iso/$f
    done

The documentation requires `poppler-utils` which may be downloaded and installed 
from [freedesktop.org](https://poppler.freedesktop.org/poppler-0.19.0.tar.gz)

	cd /usr/local/src
	wget --no-check-certificate https://poppler.freedesktop.org/poppler-0.19.0.tar.gz
	poppler-0.19.0
	./configure
	make install

The coverpage is made using OmniGraffe on a Mac; if you want create your own
feel free to do so - any PDF will do.

## License

This is a collection of software which each has a different license. The different
licences is located together with the source code below `src/GaIA/pkgs/`.

Everything I've made is released under a
[modified BSD License](https://opensource.org/licenses/BSD-3-Clause).


