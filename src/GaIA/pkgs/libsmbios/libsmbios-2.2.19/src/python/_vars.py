# the purpose of this file is so we can run from the build tree.
# for installation, this is replaced with a better version.
import os

__all__ = ["__VERSION__", "GETTEXT_PACKAGE",
    "localedir", "pkgdatadir", "pythondir", "pkgconfdir", "libdir",
    "LIBSMBIOS_C_SONAME"
    ]

LIBSMBIOS_C_SONAME=""

import libsmbios_c
_modpath = os.path.realpath(libsmbios_c.__path__[0])

# the following vars are all substituted on install
__VERSION__=""
GETTEXT_PACKAGE="libsmbios-2.2-i686"
libdir=""
pythondir=""
localedir=""
pkgdatadir=""
pkgconfdir=""

# end vars

