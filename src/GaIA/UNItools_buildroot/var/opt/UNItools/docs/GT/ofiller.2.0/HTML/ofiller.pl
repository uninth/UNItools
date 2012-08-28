#!c:/perl/bin/perl
#
# OFiller and ODumper WEB GUI
#
# by Pedro Paixao 
#
use strict;
use CGI;

my $debug =0;

# Global variables
my $PATH_TO_EXEC = "c:\\ofiller\\";            # path to program executables
my $OFILLER_EXE = "ofiller.exe";               # name of the Object Filler Executable
                                               # on Linux, use ofiller.lin or equivalent
my $ODUMPER_EXE = "odumper.exe";               # name of the Object Dumper Executable

# This is the directory where the uploaded files will be placed. It should not be the same
# dir as the web server CGI directory. The directory MUST exist before you can use the script
my $UPLOAD_DIR = "c:\\ofiller\\upload\\";


# ############################################################################################
# No need for modifications from here and below...
# ############################################################################################

my $q = new CGI;                        	# create new CGI object

print $q->header('text/html'),			# create the HTTP header
      $q->start_html('Web Interface for Check Point Object Filler and Object Dumper - by Pedro Paixao');	# start the HTML

 
$q->import_names('R');
if( $debug ) {
	print "<h3>Running offiler with the following options:</h3>";
	print " Type = $R::type<br> First IP = $R::firstIP<br> Last IP = $R::lastIP<br>";
	print " Netmask = $R::netmask<br> Color = $R::color <br> NAT = $R::natIP<br>";
	print " Hide Object = $R::hideObj<br>";
}

my $cmd;
print "What: $R::what_to_do<br>" if( $debug);

if( $R::what_to_do eq "generate" ) {
        print $q->h1('Object Filler v2.0 Results');     # level 1 header

	# validate input
	validate_generate();
	
	$cmd  = $OFILLER_EXE;
	$cmd .= " -t $R::type" 		if( $R::type );
	$cmd .= " -s $R::firstIP" 	if( $R::firstIP );
	$cmd .= " -d $R::lastIP" 	if( $R::lastIP );
	$cmd .= " -m $R::netmask" 	if( $R::netmask );
	$cmd .= " -c $R::color" 	if( $R::color);
	$cmd .= " -n $R::natIP" 	if( $R::natIP);
	$cmd .= " -b $R::hideObj" 	if( $R::hideObj);
	$cmd .= " -cgi";


} elsif(  $R::what_to_do eq "import" ) {

        print $q->h1('Object Filler v2.0 Results');     # level 1 header

	# validate input
	validate_import();
	
	# upload configuration file
	upload();	
	
	# ofiller.exe -f sample_pix.txt -i pix -o pix.out -cgi
	$cmd  = $OFILLER_EXE;
	$cmd .= " -f $UPLOAD_DIR$R::file" 	if( $R::file );
	$cmd .= " -i $R::type" 				if( $R::type );
	$cmd .= " -cgi";


} elsif(  $R::what_to_do eq "objects_C_import" ) {

        print $q->h1('Object Dumper v2.0 Results');     # level 1 header

	# validate input
	validate_import();
	
	# upload configuration file
	upload();	
	
	# odumper.exe -f sample_pix.txt -html -cgi
	$cmd  = $ODUMPER_EXE;
	$cmd .= " -f $UPLOAD_DIR$R::file" 	if( $R::file );
	$cmd .= " -html";
	$cmd .= " -cgi";
}

$cmd = $PATH_TO_EXEC.$cmd;

print "Command: $cmd<br>" if( $debug);
my $out=`$cmd`;

print "<pre>\n" ;
print $out;
print "</pre>\n" ;
print $q->end_html  ;    

# Upload the file. After uploading the file will stay in the webserver and 
# must be deleted by server administrator. Files with the same name will be 
# overwritten.
sub upload {
	my $upload_filehandle = $q->upload("file");
	
	# Clean the file name
	$R::file =~ s/.*[\/\\](.*)/$1/;
	
	open UPLOADFILE, ">$UPLOAD_DIR/$R::file";
 	binmode UPLOADFILE;

	while ( <$upload_filehandle> ) {
	  print UPLOADFILE;
	}	
	close UPLOADFILE;
}

# Validate if the file to upload is valid
sub validate_import {
	if( !$R::file ) {
		print<<__END_HTML__;
		Please specify the Configuration File to use.
		<br><a href="javascript:history.back()">Back</a>
__END_HTML__
		die("No configuration file specified");
	}
	
	# Check if we have a forbidden extension if so abort
	# we check this to keep the user from uploading executable content
	if( $R::file =~ /\.(exe|sh|csh|tcl|pl|pm|bat|cmd|vbs|js|class|cgi|tar|gzip|gz|zip|hqx|sit)/i ) {
		print<<__END_HTML__;
		Forbidden Content uploaded. The configuration file to import should be a text file. Do not upload executable or compressed content
		<br><a href="javascript:history.back()">Back</a>
__END_HTML__
		die ("Bad file uploaded: $R::file");
	}
}

# Very simple validation performed jut to find out if the values have been typed. It does not check
# validity of data and appropriate formats
sub validate_generate {
	my $error="";
	
	if( !$R::type ) {
		print "<br>Please specify the type of object to generate.";
		$error = "No object type specified - generate\n";
	}
	if( !$R::firstIP ) {
		print "<br>Please specify the Starting (Initial) IP address.";
		$error .="The starting IP address wasn't specified - generate";
	}
	if( !$R::lastIP ) {
		print "<br>Please specify the Last (ending) IP address.";
		$error .="The last IP address wasn't specified - generate";
	}
	if( !$R::netmask ) {
		print "<br>Please specify the netmask.";
		$error .="The netmask wasn't specified - generate";
	}
	if( !$R::color ) {
		print "<br>Please specify the color.";
		$error .="The color wasn't specified - generate";
	}
	if( $error ) { 
		print "<br><a href='javascript:history.back()'>Back</a>";
		die($error); 
	}
}
