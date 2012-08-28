#!/var/opt/UNItools/bin/perl
#
# Converts FW-1 4.x/5.x/R5x/R6x connections table to readable format
#  (and perhaps more in the future)
#
# (P) & (C) 2003-2006 by Dr. Peter Bieringer <info@aerasec.de>
#   with credits to Lance Spitzner 
#
# $Id$
#
# License: GNU General Public License v2
#

my $prog_copyright = "(P) & (C) 2003-2006 by Dr. Peter Bieringer <info\@aerasec.de>";
my $prog_version   = "3.4";
my $prog_name      = "fw1-tool.pl";

my $fw1_version = "R60"; # default NG R60
my $target = "local"; # default
my $hostname = "localhost"; # default
my $user = "root"; # for SSH access

my $debuglevel = 0;

my %options;
my %opts;
$opts{'showsummary'} = 1; # Currently always on

my %counters;

use strict;
use Getopt::Long;

my @connection_table;
my @ipv6_conversion_table;
my %ipv6_conversion_hash;

# Buffer for bulk table fetch
my @buffer_tables;


#############################################################
# Change Log                                                #
#############################################################

# Some content taken from "fwtableng.pl"
#   Last change by by Dr. Peter Bieringer, <info@aerasec.de>
#   May 28, 2004
# 
# Which was based on "fwtable.pl"
#   Created by Lance Spitzner, lance@spitzner.net
#   July 3, 1999 for Check Point FW-1 4.1 (or 4.0)?
#
# PB: Dr. Peter Bieringer, <pbieringer@aerasec.de>
# WS: Wolfgang Sesin / schoeller network control / http://www.schoeller.at
#
# 20030716/PB: (2.1)
#  redesign to "fw1-tool.pl"
#  - option redesign
#  - add SSH retrieving option
#  - add some statistics
# 20030721/PB: (2.2)
#  - 4.1 code adjusted
# 20030723/PB: (2.3)
#  - add support for 32 and 37 tokens per line
#  - add support for displaying NAT lines (13 tokens)
#  - replace NAT with a more sophisticated code
# 20030724/PB:
#  - replace token matcher with regexp according to ATRG
#  - add support for nonnumeric on destination ports
# 20030725/PB: (2.4)
#  - check 4.1 data
#  - add version detection mechanism and do not display
#     unsupported NAT connection listing on 4.x
#  - make Perl 5.0 compatible
# 20040528/PB: (2.5)
#  - add support for R55
# 20050127/PB: (3.0)
#  - add support for R55W, R55WIPv6
# 20050129/PB: (3.1)
#  - add support for Microsoft Windows platforms
#  - add new option "target" for selecting other targets
#     on a remote management
# 20050923/WS: (3.2)
#  - add support for R60
# 20060331/PB: (3.3)
#  - enhance connection table parser to solve output
#     difference between module and management (,/; issue)
# 20060406/PB: (3.4)
#  - add support for IPv6 on R60 (byte order was changed in lookup table)
#  - add buffer support to fetch more than one table in one time
#     now, only one remote login is required to fetch IPv6 tables

# Connection table list tested on
#   FW-1 4.1      FP6                        fw1-tool.pl (2.4)
#   FW-1 5.0 (NG) FP2                        fwtableng.pl (1.3)
#   FW-1 5.0 (NG) FP3 HF1                    fwtableng.pl (1.3)
#   FW-1 5.0 (NG) FP3 HF2                    fw1-tool.pl (2.3)
#   FW-1 5.0 (NG) FP4                        fw1-tool.pl (2.0)
#   FW-1 5.0 (NG) FP5                        fw1-tool.pl (2.5)
#   FW-1 R55WIPv6                            fw1-tool.pl (3.0)
#   FW-1 R55 Win via SSH                     fw1-tool.pl (3.1)
#   FW-1 R55 Win native                      fw1-tool.pl (3.1) ActiveState Perl 5.6.1
#   FW-1 R55 Linux via Managment (Linux)     fw1-tool.pl (3.3)
#   FW-1 R60 IPv6Pack SPLAT via remote Linux fw1-tool.pl (3.4)
#
# Automatic NAT detection list tested on
#   FW-1 4.1      FP6     not supported
#   FW-1 5.0 (NG) FP3 HF2 not working fw1-tool.pl (2.4)
#   FW-1 5.0 (NG) FP4     working fw1-tool.pl (2.2)

#############################################################
# Definitions                                               #
#############################################################

my %FW1_setup = (
	'fallback' => {
		'FWDIR' => "$ENV{'FWDIR'}",
		'CPDIR' => "$ENV{'CPDIR'}"
		},
	'R41' => {
		'FWDIR' => "/opt/CPfw1-41",
		'CPDIR' => ""
		},
	'R50' => {
		'FWDIR' => "/opt/CPfw1-50-00",
		'CPDIR' => "/opt/CPshrd-50-00"
		},
	'R51' => {
		'FWDIR' => "/opt/CPfw1-50-01",
		'CPDIR' => "/opt/CPshrd-50-01"
		},
	'R52' => {
		'FWDIR' => "/opt/CPfw1-50-02",
		'CPDIR' => "/opt/CPshrd-50-02"
		},
	'R53' => {
		'FWDIR' => "/opt/CPfw1-50-03",
		'CPDIR' => "/opt/CPshrd-50-03"
		},
	'R54' => {
		'FWDIR' => "/opt/CPfw1-50-04",
		'CPDIR' => "/opt/CPshrd-50-04"
		},
	'R55' => {
		'FWDIR' => "/opt/CPfw1-R55",
		'CPDIR' => "/opt/CPshrd-R55"
		},
	'R55W' => {
		'FWDIR' => "/opt/CPfw1-R55W",
		'CPDIR' => "/opt/CPshrd-R55W"
		},
	'R55WIPv6' => {
		'FWDIR' => "/opt/CPfw1-R55WIPv6",
		'CPDIR' => "/opt/CPshrd-R55WIPv6"
		},
	'R60' => {
		'FWDIR' => "/opt/CPsuite-R60/fw1",
		'CPDIR' => "/opt/CPshrd-R60"
		}
);


## Options
$options{"numeric|n"} = \$opts{'numeric'};
$options{"ipv6|6"} = \$opts{'ipv6'};
$options{"windows|w"} = \$opts{'windows'};
$options{"use-ssh"} = \$opts{'usessh'};
$options{"target|t=s"} = \$opts{'target'};
$options{"ssh-user|u=s"} = \$opts{'sshuser'};
$options{"ssh-host=s"} = \$opts{'sshhost'};
$options{"show-connections|c"} = \$opts{'showconnections'};
$options{"show-nat|a"} = \$opts{'shownat'};
$options{"show-summary|s"} = \$opts{'showsummary'};
$options{"input-file|i=s"} = \$opts{'inputfile'};
$options{"output-file|o=s"} = \$opts{'outputfile'};
$options{"help|?|h"} = \$opts{'help'};
$options{"fw1-version|f=s"} = \$opts{'fw1version'};
$options{"show-summary-peraddr"} = \$opts{'peraddrdst'};
$options{"show-summary-peraddrsrc"} = \$opts{'peraddrsrc'};
$options{"show-summary-perport"} = \$opts{'perport'};
$options{"debug|d:s"} = \$opts{'debuglevel'};

## Local variables
my %list_nat_entries;
my $firewall_version;

## Help
sub show_info {
	print "$prog_name $prog_copyright\n";
	print " Version: $prog_version\n";
};

sub show_help {
	print  <<EOT;

Usage: $prog_name
	[--help|-?|-h]
		Show this help
	[--use-ssh]
		Use Secure SHell for retrieving information of
		 remote target
	[--ssh-user|-u <user name>]
		User for SSH access on remote target
		 default: root
	[--ssh-host <host name>]
		Remote host for SSH access
		 default: same as target
	[--target|-t <target>]
		Specify target for retrieving information
		 default: 'local'
		 on managment stations use e.g. a FW-1 object name
		 on others use IPv4 address or hostname
		  (option --use-ssh and proper SSH access required)
	[--fw1-version|-f <version token>]
		Specify version token of FW-1
		 default: 'R55' for SSH access
		 default: 'fallback' for local access
		 currently supported: R50, R51, R52, R53, R54, R55
                                      R55W, R55WIPv6
                                      R60
	[--ipv6|-6]
		Show IPv6 tables (instead of IPv4)
	[--windows|-w]
		Management is running on Microsoft Windows platform
		 (only required for access via SSH)
	[--numeric|-n]
		Shows some output numeric instead of text
	[--input-file|-i <file name>]
		Use input from a file instead of retrieving from
		 an active FW-1
	[--output-file|-o <file name>]
		Save raw data to output file
	[--show-connections|-c]
		Show connections
	[--show-nat|-a]
		Show NAT entries
	[--show-summary-peraddrsrc]
		Show summary per source address
	[--show-summary-peraddr]
		Show summary per destination address
	[--show-summary-perport]
		Show summary per destination port
	[--show-summary|-s]
		Show summary (currently always on)
	[--debug|-d [debug level]]
		Debugging (bitwise)
		0x0002: show match information
		0x0010: show executed commands
		0x0020: input file related debugging
		0x0040: table buffer related debugging
		0x0080: show received table
		0x0100: show skipped lines
		0x0200: show valid lines
		0x0400: show NAT lines
		0x1000: show parsed ipv6_conversion_table (IPv6)
EOT
	;
}

#############################################################
#		Get options from user  			    #
#############################################################
sub get_options() {
	my $ret = GetOptions(%options);

	if (! $ret ) {
		print "Use help to see more\n";
		exit 1;
	};

	if (defined $opts{'sshhost'}) {
		$hostname =  $opts{'sshhost'};
	} else {
		if (defined $opts{'target'}) {
			$hostname = $opts{'target'};
		};
	};

	if (defined $opts{'target'}) {
		$target =  $opts{'target'};
	};

	if (defined $opts{'sshuser'}) {
		$user = $opts{'sshuser'};
	};

	if (defined $opts{'fw1version'}) {
		if (defined $FW1_setup{$opts{'fw1version'}}) {
			$fw1_version = $opts{'fw1version'};
		} else {
			die "Specified fw1-version is currently not supported: " . $opts{'fw1version'};
		};			
	};

	if (defined $opts{'inputfile'}) {
		if (! -r $opts{'inputfile'}) {
			die "Specified input file isn't readable: " . $opts{'inputfile'};
		};			
	};

	if (defined $opts{'debuglevel'}) {
		if ($opts{'debuglevel'} =~ /^0x/) {
			# Convert hex to dec
			$opts{'debuglevel'} =~ s/^0x//;
			$debuglevel = hex($opts{'debuglevel'});		
		} else {
			$debuglevel = $opts{'debuglevel'};
		};
	};

	if (defined $opts{'help'}) {
		show_help();
		exit 5;
	};
};


#############################################################
# Global Functions / Subroutines                            #
#############################################################

# Debug logging
sub debug_log($$) {
	my $level = @_[0];
	if (! defined $level) { die "Missing log level (arg1)"; };
	my $message = @_[1] ||  die "Missing log message (arg2)";

	if ((($debuglevel & $level) != 0) || ($level == 0)) {
		print STDERR $message . "\n";
	};
};


# Execute command remote via SSH
sub exec_command_remote($) {
	my $command = @_[0] || die "Missing command (arg1)";
	my $ssh_command = "ssh -l " . $user . " " . $hostname . " '" . $command . "'";

	debug_log(0x10, "Execute SSH command: " . $ssh_command);

	my @result = `$ssh_command`;
	my $exit_value  = $? >> 8;
	my $signal_num  = $? & 127;
	my $dumped_core = $? & 128;

	if ($exit_value != 0) {
		print "Error executing command: " . $command . "\n";
		print "Note: if message is like 'cannot open shared object file', try to use option -f <version token>\n";
		print "      currently supported:";
		for my $v (sort grep !/^fallback$/, keys %FW1_setup) {
			print " " . $v;
		};
		print "\n";
		die;
	};

	return @result;
};


# Execute command local
sub exec_command_local($) {
	my $command = @_[0] || die "Missing command (arg1)";

	debug_log(0x10, "Execute local command: " . $command);

	my @result = `$command`;
	my $exit_value  = $? >> 8;
	my $signal_num  = $? & 127;
	my $dumped_core = $? & 128;

	if ($exit_value != 0) {
		die "Error executing command: $command";
	};

	return @result;
};


# Convert 8 char hex to dot separated IPv4 address
#  In : 8 char hex string
#  Out: dot separated IPv4 address
sub convert_hex_to_IPv4_address {
	my $hexstring = @_[0] || die "Missing 8 char hex string (arg 1)";

	debug_log(0x1000, "Convert hex string: " . $hexstring);
	my $dec1 = hex(substr($hexstring,0,2));
	my $dec2 = hex(substr($hexstring,2,2));
	my $dec3 = hex(substr($hexstring,4,2));
	my $dec4 = hex(substr($hexstring,6,2));

	return ("$dec1.$dec2.$dec3.$dec4");
};


#############################################################
# FW-1 related Functions / Subroutines                      #
#############################################################

# Get required FW-1 tables
sub fw1_get_tables($@) {
	my $firewall = $_[0] || die "Missing firewall host (arg 1)";

	my @result;
	my $tables;

	if (defined $opts{'inputfile'}) {
		open(FILE, "<" . $opts{'inputfile'}) || die "Can't open: $opts{'inputfile'}";

		# read input file in buffer
		@result = <FILE>;

		close(FILE);
	} else {
		# Set fw command
		my $fwbin;
		my $command;

		if (defined $opts{'ipv6'}) {
			$fwbin = "fw6";
		} else {
			$fwbin = "fw";
		};

		if (! defined $opts{'usessh'}) {
			if (defined $ENV{'OS'} && $ENV{'OS'} =~ /^Windows/) {
				$opts{'windows'} = 1;
			};
		};

		
		if (defined $opts{'windows'}) {
			# Assume, that required binary is in path
			$command = $fwbin;

		} else {
			# Set directory variables
			my $FWDIR = $FW1_setup{$fw1_version}->{'FWDIR'};
			my $CPDIR = $FW1_setup{$fw1_version}->{'CPDIR'};


			if (defined $opts{'fw1version'}) {
				$FWDIR = $FW1_setup{$fw1_version}->{'FWDIR'};
				$CPDIR = $FW1_setup{$fw1_version}->{'CPDIR'};

			} else {
				$FWDIR = $FW1_setup{'fallback'}->{'FWDIR'};
				$CPDIR = $FW1_setup{'fallback'}->{'CPDIR'};

			};

			$fwbin = $FWDIR . "/bin/" . $fwbin;

			$command = "LD_LIBRARY_PATH=$FWDIR/lib:$CPDIR/lib FWDIR=$FWDIR CPDIR=" . $CPDIR . " " . $fwbin;
		};

		# Add fw[6] command
		$command .= " tab -u";

		# Add tables
		while (defined $_[1]) {
			$command .= " -t " . $_[1];

			if (defined $tables) {
				$tables .= ",";
			};
			$tables .= $_[1];

			shift;
		};

		# Add optional firewall
		if ($firewall ne "local" ) {
			$command .= " " . $firewall;
		};


		if (defined $opts{'usessh'}) {
			debug_log(0, "Try to retrieve via SSH from remote FW-1 enforcement module: table(s)=" . $tables . " module=" . $firewall);
			@result = exec_command_remote($command);

		} elsif ($firewall eq "local" ) {
			debug_log(0, "Try to retrieve table(s) from local FW-1 enforcement module: " . $tables);
			# Execute local command
			@result = exec_command_local($command);

		} else {
			debug_log(0, "Try to retrieve via local running FW-1 management: table(s)=" . $tables . " module=" . $firewall);
			# Execute local command, try to get table via local management
			@result = exec_command_local($command);
		};
	};

	if ($debuglevel & 0x80) {
		print @result;
	};

	return @result;
};

# Get FW-1 connection table
sub fw1_get_connection_table($$) {
	my $firewall = $_[0] || die "Missing firewall host (arg 1)";
	my $table = $_[1] || die "Missing table (arg 2)";
	
	my @result;

	if (defined @buffer_tables) {
		debug_log(0x40, "Look in buffer for table: " . $table);

		my $match = "-- " . $table . " --";

		my $flag_found = 0;

		#while (@buffer_tables) {
		foreach my $line (@buffer_tables) {
			chomp $line;

			debug_log(0x40, "Line: >" . $line . "< (" . length($line) . ")");

			# Looking for start
			if ($flag_found == 0) {
				if ($line !~ /$match/) {
					# skip line
					next;
				} else {
					$flag_found = 1;
					debug_log(0x40, "Begin of table: " . $table);
				};
			} else {
				if (length($line) == 0 || $line =~ /\:$/) {
					# last line
					debug_log(0x40, "End of table: " . $table);
					last;
				};
			};

			debug_log(0x40, "Store line in array: " . $line);
			push @result, $line . "\n";

		};
	} elsif (defined $opts{'inputfile'}) {
		open(FILE, "<" . $opts{'inputfile'}) || die "Can't open: $opts{'inputfile'}";
		debug_log(0x20, "Look in inputfile for table: " . $table);

		my $match = "-- " . $table . " --";

		my $flag_found = 0;

		while (<FILE>) {
			chomp $_;

			debug_log(0x20, "Line: >" . $_ . "< (" . length($_) . ")");

			# Looking for start
			if ($flag_found == 0) {
				if ($_ !~ /$match/) {
					# skip line
					next;
				} else {
					$flag_found = 1;
					debug_log(0x20, "Begin of table: " . $table);
				};
			} else {
				if (length($_) == 0 || $_ =~ /\:$/) {
					# last line
					debug_log(0x20, "End of table: " . $table);
					last;
				};
			};

			debug_log(0x20, "Store line in array: " . $_);
			push @result, $_ . "\n";

		};
		close(FILE);
	} else {
		# Set fw command
		my $fwbin;
		my $command;

		if (defined $opts{'ipv6'}) {
			$fwbin = "fw6";
		} else {
			$fwbin = "fw";
		};

		if (! defined $opts{'usessh'}) {
			if (defined $ENV{'OS'} && $ENV{'OS'} =~ /^Windows/) {
				$opts{'windows'} = 1;
			};
		};

		
		if (defined $opts{'windows'}) {
			# Assume, that required binary is in path
			$command = $fwbin;

		} else {
			# Set directory variables
			my $FWDIR = $FW1_setup{$fw1_version}->{'FWDIR'};
			my $CPDIR = $FW1_setup{$fw1_version}->{'CPDIR'};


			if (defined $opts{'fw1version'}) {
				$FWDIR = $FW1_setup{$fw1_version}->{'FWDIR'};
				$CPDIR = $FW1_setup{$fw1_version}->{'CPDIR'};

			} else {
				$FWDIR = $FW1_setup{'fallback'}->{'FWDIR'};
				$CPDIR = $FW1_setup{'fallback'}->{'CPDIR'};

			};

			$fwbin = $FWDIR . "/bin/" . $fwbin;

			$command = "LD_LIBRARY_PATH=$FWDIR/lib:$CPDIR/lib FWDIR=$FWDIR CPDIR=" . $CPDIR . " " . $fwbin;
		};

		# Add fw[6] command
		$command .= " tab -u -t " . $table;

		# Add optional firewall
		if ($firewall ne "local" ) {
			$command .= " " . $firewall;
		};


		if (defined $opts{'usessh'}) {
			debug_log(0, "Try to retrieve via SSH from remote FW-1 enforcement module: table=" . $table . " module=" . $firewall);
			@result = exec_command_remote($command);

		} elsif ($firewall eq "local" ) {
			debug_log(0, "Try to retrieve table from local FW-1 enforcement module: " . $table);
			# Execute local command
			@result = exec_command_local($command);

		} else {
			debug_log(0, "Try to retrieve via local running FW-1 management: table=" . $table . " module=" . $firewall);
			# Execute local command, try to get table via local management
			@result = exec_command_local($command);
		};
	};

	if ($debuglevel & 0x80) {
		print @result;
	};

	return @result;
};

# Get FW-1 connection table version and limit
sub fw1_get_header_info($) {
	my $p_table = @_[0] || die "Missing pointer to table (arg 1)";

	foreach my $line (@$p_table) {
		# Check for line with "limit"
		if ($line =~ / limit (\d+),?/) {
			if (! defined $counters{'connections'}->{'all'}->{'max'}) {
				$counters{'connections'}->{'all'}->{'max'} = $1;
			};

			if (! defined $firewall_version) {
				if ($line =~ /^attributes: /) {
				# Let's look for version of file we have:
					$firewall_version = "4.x"
				} else {
					$firewall_version = "5.x"
				};
			};

			if ((defined  $counters{'connections'}->{'all'}->{'max'}) && (defined $firewall_version)) {
				print "\nConnection table is taken from firewall version " . $firewall_version . "\n";
				last;
			};
		};
	};
};


# Print FW-1 connection table
sub fw1_print_connection_table($) {
	my $p_table = @_[0] || die "Missing pointer to table (arg 1)";

	my $linecounter = 0;

	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time); 
	my $time = sprintf "%02d:%02d:%02d", $hour, $min, $sec;

	# Set length for formatted output
	my $length_ip = 15;

	if (defined $opts{'ipv6'}) {

		sub swap2($) {
			$_[0] =~ /^([0-9a-f]{2})([0-9a-f]{2})$/;
			return $2 . $1;
		};

		# Create hash
		foreach my $line (@ipv6_conversion_table) {
			if ($line =~ /^<([0-9a-f]{8})> -> <([0-9a-f]{4})([0-9a-f]{4}), ([0-9a-f]{4})([0-9a-f]{4}), ([0-9a-f]{4})([0-9a-f]{4}), ([0-9a-f]{4})([0-9a-f]{4})>/) {
				my $hash =  $1;
				my $ipv6;

				if ($opts{'fw1version'} eq "R55W") {
					# Hopefully R55W was the exception...

					# Example/R55W: <1ab23577> -> <fe800000, 00000000, 0a0020ff, fec7801c> (00000000)
					$ipv6 =  $2 . ":" . $3 . ":" . $4 . ":" . $5 . ":" . $6 . ":" . $7 . ":" . $8 . ":" . $9;
				} else {
					# Example/R60: <17622307> -> <000080fe, 00000000, ff760402, 347c1afe> (00000000)
					$ipv6 =  swap2($3) . ":" . swap2($2) . ":" . swap2($5) . ":" . swap2($4) . ":" . swap2($7) . ":" . swap2($6) . ":" . swap2($9) . ":" . swap2($8);
				};

				debug_log(0x1000, $line);
				debug_log(0x1000, $hash . " -> " . $ipv6);

				$ipv6_conversion_hash{$1} = $ipv6;
			};
		};

		# Set length for formatted output
		$length_ip = 39;
	};


	if (defined $opts{'showconnections'}) {
		print "\n---- FW-1 CONNECTION ENTRIES ---";
		if (defined $opts{'inputfile'}) {
			print ": " . $opts{'inputfile'} . "\n";
		} else {
			print ": ". $time ."\n";
		};

		# print "Src_IP   \tSrc_Prt\tDst_IP   \tDst_Prt\tIP_prot\tKbuf\tType\tFlags   \tTimeout\n\n"; # 4.1
		printf "CON: ";
		printf "%-" . $length_ip . "s ", "Source";	# Source IPv4 address
		printf "%-15s ", "SPort";		# Source port
		printf "%-" . $length_ip . "s ", "Dest  ";	# Destination IPv4 address
		printf "%-15s ", "DPort";		# Destination port
		printf "%-10s ", "Proto";		# Protocol
		printf "%12s ", "Timeout";
		print "\n";
	};

	my ($direction, $src, $sport, $dst, $dport, $ip_p, $timeout, $proto, $valid, $nat_flag, $s_ip, $d_ip, $type_r_ctype, $flags_r_ctype, $rulenum);

	foreach my $line (@$p_table) {
		$linecounter++;

		undef $src, $sport, $dst, $dport, $ip_p, $timeout, $proto, $valid, $nat_flag, $s_ip, $d_ip, $type_r_ctype, $flags_r_ctype, $rulenum;

		### Skip lines not containing state information
		if (! $line =~ /^</) { next; };

		# Remove trailing CR/LF
		chomp($line);
		$line =~ s/

		### Skip empty lines
		if (length($line) == 0) {
			next;
		};

		if ($line =~ / -> /) {
			# NAT entry
			debug_log(0x400, "NAT line: " . $line);

			# Use dedicated option for displaying...
			next;
		};

		$valid = 0;

		if ( ($direction, $src, $sport, $dst, $dport, $ip_p, $type_r_ctype, $flags_r_ctype, $rulenum, $timeout) = $line =~ /^<([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8})[;,] ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), .*; (\d+\/\d+)>$/) {
			# According to ATRG NG
			debug_log(0x002, "Line match according ATRG NG");
			$valid = 1;
		} elsif ( ($src, $sport, $dst, $dport, $ip_p, $timeout) = $line =~ /^<([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8});.*; (\d+\/\d+)>$/) {
			# According to ATRG FW-1 4.1
			debug_log(0x002, "Line match according ATRG 4.1");
			$valid = 1;
		};


		if ($valid != 1) {
			# Skip not recognized lines
			debug_log(0x100, "Skipped line: " . $line);
			next;
		};

		# Valid connection

		debug_log(0x200, "Valid line: " . $line);

		if (! defined $opts{'ipv6'}) {
			$s_ip = convert_hex_to_IPv4_address($src);
			$d_ip = convert_hex_to_IPv4_address($dst);
		} else {
			$s_ip = $ipv6_conversion_hash{$src};
			$d_ip = $ipv6_conversion_hash{$dst};
		};

		$ip_p = hex($ip_p);
		$sport = hex($sport);
		$dport = hex($dport);

		$counters{'connections'}->{'entries'}->{'all'}++;
		$nat_flag = 0;

		# Count all
		$counters{'connections'}->{'entries'}->{'real'}++;

		if (! defined $opts{'ipv6'}) {
			# Check for NAT
			if (defined $list_nat_entries{$src}->{$sport}->{$dst}->{$dport}->{$ip_p}) {
				$nat_flag = 1;
			} else {
				$nat_flag = 0;
			};
		};


		if ($opts{'numeric'}) {
			$proto = $ip_p;
			# Nothing to do
		} else {
			$proto = getprotobynumber($ip_p);
			if (! defined $proto) {
				$proto = $ip_p;

			} else {
				my $name = (getservbyport($dport, $proto))[0];
				if (defined $name) {
					$dport = $name;
				};
			};
		};

		# Count per protocol
		$counters{'connections'}->{'perproto'}->{$proto}++;


		if ($opts{'peraddrsrc'}) {
			$counters{'connections'}->{'peraddrsrc'}->{$s_ip}++;
		};
		if ($opts{'peraddrdst'}) {
			$counters{'connections'}->{'peraddrdst'}->{$d_ip}++;
		};

		if ($opts{'perport'}) {
			if ($ip_p == 6 || $ip_p == 17) {
				$counters{'connections'}->{'perportdst'}->{$dport}++;
			};
		};


		if (defined $opts{'showconnections'}) {
			### Print out each column, per line.
			printf "CON: ";

			printf "%-" . $length_ip . "s ", $s_ip;

			# Only show ports on UDP and TCP
			if ($ip_p == 6 || $ip_p == 17) {
				printf "%-15s ", $sport;
			} else {
				printf "%-15s ";
			};

			printf "%-" . $length_ip . "s ", $d_ip;

			if ($ip_p == 6 || $ip_p == 17) {
				printf "%-15s ", $dport;
			} else {
				printf "%-15s ";
			};

			printf "%-10s ", $proto;
			printf "%12s", $timeout;

			if (! defined $opts{'ipv6'}) {
				# Only IPv4 has NAT
				if ($nat_flag == 1) {
					print " NAT";
				};
			};

			print "\n";
		};
	};
};


# Print FW-1 NAT table
sub fw1_print_nat_table($) {
	my $p_table = @_[0] || die "Missing pointer to table (arg 1)";

	my $linecounter = 0;

	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time); 
	my $time = sprintf "%02d:%02d:%02d", $hour, $min, $sec;

	if (defined $opts{'shownat'}) {
		if ($firewall_version eq "4.x") {
			print "\n---- FW-1 NAT ENTRIES ---\n";
			print "Cannot be extracted from connection table data on versions " . $firewall_version . "\n";
			return 0;
		};
	};

	if (defined $opts{'shownat'}) {
		print "\n---- FW-1 NAT ENTRIES ---";
		if (defined $opts{'inputfile'}) {
			print ": " . $opts{'inputfile'} . "\n";
		} else {
			print ": ". $time ."\n";
		};

		# print "Src_IP   \tSrc_Prt\tDst_IP   \tDst_Prt\tIP_prot\tKbuf\tType\tFlags   \tTimeout\n\n"; # 4.1
		printf "NAT: ";
		printf "%-15s ", "Source";	# Source IPv4 address
		printf "%5s ", "SPort";		# Source port
		printf "%-15s ", "Dest  ";	# Destination IPv4 address
		printf "%5s ", "DPort";		# Destination port
		printf "%5s ", "Proto";		# Protocol
		printf "-> ";
		printf "%-15s ", "Source";	# Source IPv4 address
		printf "%5s ", "SPort";		# Source port
		printf "%-15s ", "Dest  ";	# Destination IPv4 address
		printf "%5s ", "DPort";		# Destination port
		printf "%5s ", "Proto";		# Protocol
		print "\n";
	};

	my ($dir, $src, $sport, $dst, $dport, $ip_p, $timeout, $proto, $valid, $nat_flag, $s_ip, $d_ip);
	my ($natdir, $natsrc, $natsport, $natdst, $natdport, $natip_p, $nats_ip, $natd_ip, $natproto, $type);

	foreach my $line (@$p_table) {
		$linecounter++;

		undef $dir, $src, $sport, $dst, $dport, $ip_p, $timeout, $proto, $valid, $nat_flag, $s_ip, $d_ip;
		undef $natdir, $natsrc, $natsport, $natdst, $natdport, $natip_p, $nats_ip, $natd_ip, $natproto, $type;

		### Skip lines not containing state information
		if (! $line =~ /^</) { next; };

		# Remove trailing CR/LF
		chomp($line);
		$line =~ s/

		### Skip empty lines
		if (length($line) == 0) {
			next;
		};

		if (!($line =~ / -> /)) {
			# No symbolic link line
			next;
		};


		$counters{'link'}->{'entries'}->{'all'}++;

		if ( ($dir, $src, $sport, $dst, $dport, $ip_p, $natdir, $natsrc, $natsport, $natdst, $natdport, $natip_p, $type) = $line =~ /^<([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8})> -> <([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8}), ([A-Fa-f0-9]{8})> \(([A-Fa-f0-9]{8})\)$/) {
			# According to ATRG NG
			debug_log(0x002, "Line match according ATRG NG");

			if (($src eq $natsrc) && ($dst eq $natdst) && ($sport == $natsport) && ($dport == $natdport) && ($ip_p == $natip_p)) {
				# src/dst equal linked src/dst
				$valid = 0;
				$counters{'link'}->{'entries'}->{'nonat'}++;
				next;
			};
			if (($src eq $natdst) && ($dst eq $natsrc) && ($sport == $natdport) && ($dport == $natsport) && ($ip_p == $natip_p)) {
				# src/dst equal linked dst/src
				$valid = 0;
				$counters{'link'}->{'entries'}->{'nonat'}++;
				next;
			};
		} else {
			# Skip not recognized lines
			debug_log(0x100, "Skipped line: " . $line);
			$counters{'link'}->{'entries'}->{'skipped'}++;
			next;
		};

		$counters{'link'}->{'entries'}->{'nat'}++;

		$s_ip = convert_hex_to_IPv4_address($src);
		$d_ip = convert_hex_to_IPv4_address($dst);
		$nats_ip = convert_hex_to_IPv4_address($natsrc);
		$natd_ip = convert_hex_to_IPv4_address($natdst);

		$sport = hex($sport);
		$dport = hex($dport);
		$natsport = hex($natsport);
		$natdport = hex($natdport);

		$ip_p = hex($ip_p);
		$natip_p = hex($natip_p);

		# Fill NAT hash
		$list_nat_entries{$natsrc}->{$natsport}->{$natdst}->{$natdport}->{$natip_p} = 1;

		if (defined $opts{'shownat'}) {
			if ($opts{'numeric'}) {
				$proto = $ip_p;
				$natproto = $natip_p;
				# Nothing to do
			} else {
				$natproto = getprotobynumber($natip_p);
				if (! defined $natproto) {
					$natproto = $natip_p;
				} else {
					my $name = (getservbyport($natdport, $natproto))[0];
					if (defined $name) {
						$natdport = $name;
					};
				};
				$proto = getprotobynumber($ip_p);
				if (! defined $proto) {
					$proto = $ip_p;
				} else {
					my $name = (getservbyport($dport, $proto))[0];
					if (defined $name) {
						$dport = $name;
					};
				};
			};

			### Print out each column, per line.
			printf "NAT: ";

			# Orig connection
			printf "%-15s ", $nats_ip;

			if ($natip_p == 6 || $natip_p == 17) {
				printf "%5s ", $natsport;
			} else {
				printf "%5s ";
			};
			printf "%-15s ", $natd_ip;
			if ($natip_p == 6 || $natip_p == 17) {
				#if ($opts{'numeric'}) {
					printf "%5s ", $natdport;
				#} else {
				#	printf "%5s ", getservbyport($natdport, $ip_p);
				#}
			} else {
				printf "%5s ";
			};
			printf "%5s ", $natproto;

			# NAT connection
			print "-> ";

			printf "%-15s ", $d_ip;

			# Only show ports on UDP and TCP
			if ($ip_p == 6 || $ip_p == 17) {
				#if ($opts{'numeric'}) {
					printf "%5s ", $dport;
				#} else {
				#	printf "%5s ", getservbyport($dport, $ip_p);
				#}
			} else {
				printf "%5s ";
			};
			printf "%-15s ", $s_ip;
			if ($ip_p == 6 || $ip_p == 17) {
				printf "%5s ", $sport;
			} else {
				printf "%5s ";
			};
			printf "%5s ", $proto;

			print "\n";
		};
	};
};


# Print summary
sub fw1_print_summary() {
	if (defined $opts{'showsummary'}) {
		# Print statistics
		print "\n";
		print "---- FW-1 STATISTICS ---\n";
		for my $k1 (sort keys %counters) {
			for my $k2 (sort keys %{$counters{$k1}}) {
				for my $k3 (sort keys %{$counters{$k1}->{$k2}}) {
					print "$k1.$k2.$k3 = " . $counters{$k1}->{$k2}->{$k3} . "\n";
				};
			};
		};
		print "\n";
	};
};

#############################################################
# Main                                                      #
#############################################################
my $command = 'show-active-connections';

show_info();

get_options();


if ($command eq "show-active-connections") {

	if (defined $opts{'ipv6'}) {
		## For IPv6 also the conversion table is required
		#@ipv6_conversion_table = fw1_get_connection_table($target, "ipv6_conversion_table");

		# Get tables
		@buffer_tables = fw1_get_tables($target, "ipv6_conversion_table", "connections");

		# Get conversion table
		@ipv6_conversion_table = fw1_get_connection_table($target, "ipv6_conversion_table");
	};

	# Get connection table
	@connection_table = fw1_get_connection_table($target, "connections"); 
	fw1_get_header_info(\@connection_table);

	if ($opts{'outputfile'}) {
		# Save output
		print "Save raw data to: " . $opts{'outputfile'} . "\n";

		open (FILE, ">" . $opts{'outputfile'}) || die "Can't write output file: $opts{'outputfile'}";

		if (defined $opts{'ipv6'}) {
			# For IPv6, print conversion table first
			foreach my $line (@ipv6_conversion_table) {
				print FILE $line;
			};

		};

		foreach my $line (@connection_table) {
			print FILE $line;
		};

		close (FILE);

		print "Finished!\n";

	} else {
		if (defined $opts{'ipv6'}) {
			# IPv6 has no NAT by design
		} else {
			# Look for NAT entries first (required for NAT detection on connections)
		};

		# Look for connection entries
		fw1_print_connection_table(\@connection_table);

		# Print summary
		fw1_print_summary();
	};
};




#############################################################
#			SCRIPT ENDS			    #
#############################################################