
#include <limits.h>
#include <stdlib.h>
int main(int argc, char **argv) {
	int i;
	for (i = 1; i < argc; i++) {
		char rp[PATH_MAX];
		if (!realpath(argv[i], rp)) {
			perror(argv[i]);
		return 1;
		} else {
			printf("%s\n", rp);
		}
	}
	return 0;
}

static char	*author   = "@(#)Author     : Niels Thomas Haugaard";
static char	*checked  = "@(#)Checked by : - ";
static char	*approved = "@(#)Approved by: - ";
static char	*version  = "@(#)Version    : $Id$";

/*
/*  Copyright (C) 2001 Niels Thomas Haugård
/*  UNI-C
/*  http://www.uni-c.dk/
/*
/*  This program is free software; you can redistribute it and/or modify
/*  it under the terms of the GNU General Public License as published by
/*  the Free Software Foundation; either version 2 of the License, or
/*  (at your option) any later version.
/*
/*  This program is distributed in the hope that it will be useful,
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
/*  GNU General Public License for more details.
/*
/*  You should have received a copy of the GNU General Public License 
/*  along with this program; if not, write to the Free Software
/*  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
/*++
/* NAME
/*	realpath 1
/* SUMMARY
/*	Return the real path of a link
/* SYNOPSIS
/*	\fBrealpath\fR \fIpath\fR \fIpath\fR \fIpath\fR ...
/* PACKAGE
/*	UNItools
/* DESCRIPTION
/*	\fBrealpath\fR program returns the real path to something
/*	pointed to, by a symbolic link. E.g.:
/* .nf \fC
/*	ln -s /etc/passwd /tmp/passwd
/*	ln -s /tmp/passwd /tmp/passwd-link-level2
/*	realpath /tmp/passwd-link-level2
/*	\fB/etc/passwd
/* .fi \fR
/* OPTIONS
/* .IP \fIpath\fR
/*	One or more pathname(s).
/* DIAGNOSTICS
/*	Missing file, no permissions, etc. goes to STDOUT.
/* ENVIRONMENT
/* SEE ALSO
/*	\fCrealpath(3c)\fR
/* VERSION
/*	$Date: 2003/10/24 12:59:21 $
/*	$Revision: 1.1 $
/*	$Source: /lan/ssi/projects/UNItools/Linux/src/realpath/RCS/realpath.c,v $
/*	$State: Exp $
/* HISTORY
/*	See \fCrlog realpath.c\fR.
/* BUGS
/*	Probably. Please report them to the call-desk or the author.
/* AUTHOR(S)
/*	Niels Thomas Haugård
/* .br
/*	E-mail: thomas@haugaard.net
/*	UNI\(buC
/* .br
/*	DTU, Building 304
/* .br
/*	DK-2800 Kgs. Lyngby
/* .br
/*	Denmark
/*--*/
