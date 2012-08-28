#!/var/opt/UNItools/bin/perl -w
#
# $Header: /var/opt/UNItools/src/scripts/RCS/fmog.pl,v 1.7 2003/02/20 09:17:40 root Exp $
#

#
# Requirements
#
use English;
use FileHandle;
use Getopt::Long;
use sigtrap qw(die normal-signals);
#
# Global vars
#
my $today = `date`;
chop $today;
my $fix = 0;
my $check = 0;
my $dir;
my $files = 0;
my $wrong_uid = 0;
my $wrong_gid = 0;
my $wrong_mode = 0;

my $dev = $ino = $mode = $nlink = $uid = $gid = $rdev = $size = 
		$atime = $mtime = $ctime = $blksize = $blocks = "";

my $usage = "

	$0 [-b | -f | -c ] [ dir ]
	Either $0 --build|b directory 
	or     $0 --fix < list
	or     $0 --check  < list

";

################################################################################
# MAIN
################################################################################
#
# Parse and process options
#
if (!GetOptions('build|b=s'	=> \$dir,
		'fix|f'		=> \$fix,
		'check|c'	=> \$check
	)) {
	die "$usage";
}
#
# Check options and args
#
die "$dir $usage" if (defined($dir) && ($fix || $check));
die "$dir $usage" if (! defined($dir) && ! $fix && ! $check);
die "$dir $usage" if ($fix && $check);

if ( $dir ) {
	#
	# Print a list to STDOUT with UID GID MODE FILENAME
	#
	open ( FIND, "/usr/bin/find $dir |") ||
		die "/usr/bin/find: $!";

	while (<FIND>) {

		chop $_;
		$filename = $_;

		#
		# Handle symbolic links correct
		#
		if ( -l "$filename") {
			($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, 
				$atime, $mtime, $ctime, $blksize, $blocks)
					= lstat($filename);
		} else {
			($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, 
				$atime, $mtime, $ctime, $blksize, $blocks)
					= stat($filename);
		}

		#
		# Seen this meny files till now
		#
		$files ++ ;
		#
		# OWNER GROUP MODE FILENAME
		#
		printf ("%-8s %-8s %-4o %-s\n", $uid, $gid, $mode & 07777, $filename);

	}
} else {
	my ($read_filename, $read_uid, $read_gid, $read_mode);
	loop: while (<>) {
		chomp;

		#
		# All chars are btw legal in a filename, also whitespace so split
		# cannot be used here
		#
		/(\d*)\s+(\d*)\s+(\d*)\s+(.*)$/	&& do {
			$read_uid	= "$1";
			$read_gid	= "$2";
			$read_mode	= "$3";
			$read_filename	= "$4";
		};

		if ( ! -e "$read_filename") {
			print "$read_filename file not found\n";
			next loop;
		}

		if ( -l $read_filename) {
			($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, 
				$atime, $mtime, $ctime, $blksize, $blocks)
					= lstat($read_filename);
		} else {
			($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, 
				$atime, $mtime, $ctime, $blksize, $blocks)
					= stat($read_filename);
		}
		#
		# convert mode to octal for readability
		#
		$mode = sprintf "%lo", $mode & 07777;
		$files = $files + 1;

		#
		# Lookup user and group name for readability and
		# use uid and gid if not found.
		#
		if ($read_uid ne $uid) {
			$wrong_uid ++;
			$owner = getpwuid($read_uid);
			$owner = $owner ? $owner : $uid;
			print "owner was $owner\[$read_uid\] is ";

			$owner = getpwuid($uid);
			$owner = $owner ? $owner : $uid;
			print "$owner\[$uid\] $read_filename";
			if ( $fix ) {
				print " fixing ... ";
				chown ($read_uid, $read_gid, $read_filename) || warn "chown failled: $!";
				print "done\n";
			} else { print "\n"; }
		}

		if ($read_gid ne $gid) {
			$wrong_gid ++;
			$group = getpwuid($read_gid);
			$group = $group ? $group : $gid;
			print "group was $group\[$read_gid\] is ";
			$group = getpwuid($gid);
			$group = $group ? $group : $gid;
			print "$group\[$gid\] $read_filename";
			if ( $fix ) {
				print " fixing ... ";
				chown ($read_uid, $read_gid, $read_filename) || warn "chown failled: $!";
				print "done\n";
			} else { print "\n"; }
		}

		if ($read_mode ne $mode) {
			$wrong_mode ++;
			printf("mode was %s is %s %s",  $read_mode, $mode, $read_filename);
			if ( $fix ) {
				print " fixing ... ";
				chmod (oct($read_mode), $read_filename) || warn "chmod failled: $!";
				print "done\n";
			} else { print "\n"; }
		}

	}
} 

printf("Files total: %s\n", $files);
printf("Wrong  UID:  %s\n", $wrong_uid);
printf("Wrong  GID:  %s\n", $wrong_uid);
printf("Wrong mode:  %s\n", $wrong_mode);

exit 0;

################################################################################
#
# Documentation and  standard disclaimar
#
# Copyright (C) ECMWF
# http://www.ecmwf.int/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# F M O G -
#                fix/reset or check mode owner and group for files
#
# This is *not* a security tool: the aim is to be able to re-set
# file permisions owner and group after a messy software instal­
# lation.

#
#++
# NAME
#	fmog.pl 1
# SUMMARY
#	fix/reset or check mode owner and group for files
# PACKAGE
#	UNItools
# SYNOPSIS
#	fmog.pl \fC[-b | -f | -c ] [ \fIdir\fC ]\fR
# DESCRIPTION
#	\fBfmog.pl\fR is not a security utility; the tool is aimed for
#	checking and resetting permissions and ownership for files to a
#	known state, eg. after a buggy software installation or
#	change of configuration files with a wrong umask.
#	
#	The utility is a filter; it reads it's input from stdin and writes
#	to stdout.
#
#	The utility has tree modes: \fBbuild\fR, \fBcheck\fR and \fBfix\fR.
# OPTIONS
# .TP
#	\fCfmog.pl --build\fR\ \fIdirectory\fR \fC>\fR \fIfile\fR
#	Find all files below \fIdir\fR and print \fCuid\fR, \fCgid\fR,
#	\fCmode\fR, and \fCfile name\fR to stdout. The information is
#	intented to be saved in a file.
# .TP
#	\fCfmog.pl --check < \fIfile\fR
#	Read from stdin a list with \fCuid\fR, \fCgid\fR, \fCmode\fR, and
#	\fCfile name\fR and certify the files in the list has the mode
#	and permission mentioned there. Complain if that is not the case.
# 
# .TP
#	\fCfmog.pl --fix < \fIfile\fR
#	Identical to \fCcheck\fR, but files with other mode or permission
#	than the one in the list is beeing reset to what is in the list.
# COMMANDS
#	perl(1)
# DIAGNOSTICS
#	None.
# BUGS
#	The script uses the \fCperl\fR \fCfind\fR package and may produce
#	wery large lists.
#
#	It continues as best as it can and warns when chmod/chown faills.
# WISHLIST
#	Extension of the script to also check for change in file contents,
#	and the ability to detect added files.
# VERSION
#      $Date: 2003/02/20 09:17:40 $
# .br
#      $Revision: 1.7 $
# .br
#      $Source: /var/opt/UNItools/src/scripts/RCS/fmog.pl,v $
# .br
#      $State: Exp $
# HISTORY
#	See \fCrlog fmog.pl\fR.
# AUTHOR(S)
#	Niels Thomas Haugaard
# .br
#	E-mail: thomas@haugaard.net
# .br
#	ECMWF
# .br
#	Shinfield Park
# .br
#	Reading, Berks.
# .br
#	RG2 9AX  England
#--
