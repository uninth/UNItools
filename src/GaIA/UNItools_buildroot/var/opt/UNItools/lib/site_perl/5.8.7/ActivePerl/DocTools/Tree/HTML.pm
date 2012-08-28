package ActivePerl::DocTools::Tree::HTML;

use strict;
use warnings;

use Config qw(%Config);
use Cwd qw(cwd);
use File::Basename qw(dirname);
use File::Path qw(mkpath);
use Pod::Find qw(pod_find);
use Pod::Html qw(pod2html);

sub _relative_path {
    my($path, $prefix) = @_;
    $path =~ s,\\,/,g if $^O eq "MSWin32";
    $path =~ s,/\z,, unless $path =~ m,^([A-Za-z]:)?/\z,;

    if (defined $prefix && length $prefix) {
	$prefix =~ s,\\,/,g if $^O eq "MSWin32";
        $prefix =~ s,/\z,, unless $prefix =~ m,^([A-Za-z]:)?/\z,;

	my @path_parts   = split('/', $path);
	my @prefix_parts = split('/', $prefix);
	return $path if @path_parts < @prefix_parts;

	while (@prefix_parts) {
	    my $path_part   = shift(@path_parts);
	    my $prefix_part = shift(@prefix_parts);
	    if ($^O eq "MSWin32") {
		$_ = lc for $path_part, $prefix_part;
	    }
	    return $path unless $path_part eq $prefix_part;
	}

	$path = join('/', @path_parts) || ".";
    }
    return $path;
}

sub Update {
    my %args = @_;

    my $prefix  = $args{prefix}  || $Config{installprefix};
    my $htmldir = $args{htmldir} || $Config{installhtmldir} || "$prefix/html";
    my $podpath = $args{podpath} || [@Config{qw(privlib sitelib scriptdir)}];

    my $starting_cwd = cwd();
    unless (chdir($prefix)) {
	warn "Can't chdir to root of Perl installation: $!\n";
	return;
    }

    print "Building HTML tree at $htmldir, cwd is $prefix\n" if $args{verbose};

    my %pods = pod_find(@$podpath);
    $podpath = join ":", map { s/:/|/g; $_ } map { _relative_path($_, $prefix) } @$podpath;

    foreach my $key (sort keys %pods) {
	my $in_file = _relative_path($key, $prefix);
	my $out_file = "$htmldir/$in_file";
	$out_file =~ s/\.[a-z]+\z|\z/.html/i;

	unless (-e $out_file && (stat $in_file)[9] <= (stat $out_file)[9]) {
	    print "Making $out_file from $in_file => $pods{$key}\n"
		if $args{verbose};

	    unlink($out_file) if -e $out_file;
	    my $out_dir = dirname($out_file);
	    mkpath($out_dir);

	    my $depth = $in_file =~ tr,/,,;
	    _translate($in_file, $out_file, $out_dir, $depth, ".", $podpath, 1);
	}
	else {
	    print "Skipping $out_file\n" if $args{verbose};
	}
    }

    # remove pod2html cache files; 5.6 uses ".x~~" and 5.8 uses ".tmp" extensions
    unlink("pod2htmd.$_", "pod2htmi.$_") for qw(x~~ tmp);

    chdir($starting_cwd) or die "Can't chdir back to '$starting_cwd': $!";
}

sub Pod2HTML {
    my %args  = @_;

    my $prefix      = $args{prefix}      || $Config{installprefix};
    my $htmldir     = $args{htmldir}     || $Config{installhtmldir} || "$prefix/html";

    my $installdirs = $args{installdirs} || 'site';
    my $instprefix  = { perl   => 'lib/',
                        site   => 'site/lib/',
                        vendor => 'site/lib/',
                      }->{$installdirs};

    my $starting_cwd = cwd();
    my $blib = File::Spec->catfile($starting_cwd, 'blib');

    my $podpath = $args{podpath} || [$blib, @Config{qw(privlib sitelib scriptdir)}];

    print "Building HTML in $blib\n" if $args{verbose};

    unless (chdir($prefix)) {
	warn "Can't chdir to root of Perl installation: $!\n";
	return;
    }

    my %pods = pod_find($blib);
    $podpath = join ":", map { s/:/|/g; $_ } map { _relative_path($_, $prefix) } @$podpath;

    foreach my $key (sort keys %pods) {
        my $in_file = $key;
        my $out_file = _relative_path($key, $blib);
        $out_file =~ s/\.[a-z]+\z|\z/.html/i;

        #Correct differences between blib/ layout and final layout
        $out_file =~ s[^script/][bin/];
        $out_file =~ s[^lib/][$instprefix];
        my $depth = $out_file =~ tr,/,,;

        $out_file = File::Spec->catfile($blib, 'html', $out_file);
        my $out_dir = dirname($out_file);
        mkpath($out_dir);

        print  "Making $out_file from $in_file => $pods{$key}\n"
            if $args{verbose};

        my @args = (
            $in_file,
            $out_file,
            $out_dir,
            $depth,
            '.',
            $podpath,
            1
        );
        _translate(@args);

        #We now fix links that point to our blib/html, since that's only
        #a temporary location
        open (HTMLFILE, "<$out_file") or die "Couldn't open $out_file: $!";
        open (TMPFILE, ">$out_file.tmp") or die "Couldn't open $out_file.tmp: $!";

        my $bhtml = File::Spec->catfile($blib, 'html', '');
        while (my $line = <HTMLFILE>) {
            $line =~ s/\Q$bhtml//g;
            print TMPFILE $line;
        }

        close (TMPFILE) || die;
        close (HTMLFILE);
        rename("$out_file.tmp", $out_file) || die;
    }

    # remove pod2html cache files; 5.6 uses ".x~~" and 5.8 uses ".tmp" extensions
    unlink("pod2htmd.$_", "pod2htmi.$_") for qw(x~~ tmp);
    chdir($starting_cwd) or die "Can't chdir back to '$starting_cwd': $!";
}

my($basename,%expand); # XXX
my $scineplex = eval { require ActiveState::Scineplex };

# This function is also called by ActivePerl-Docs/install.pl
# to convert the changelogs and release notes.
sub _translate {
    my($in_file,$out_file,$out_dir,$depth,$podroot,$podpath,$index) = @_;
    unlink($out_file);

    my $html_root = substr("../" x $depth || "./", 0, -1);
    $index = $index ? "index" : "noindex";

    pod2html("--quiet",
	     "--$index",
	     "--htmldir=$out_dir",
	     "--htmlroot=$html_root",
	     "--podroot=$podroot",
	     "--podpath=$podpath",
	     "--libpods=perlfunc:perlguts:perlvar:perlrun:perlopt",
	     "--infile=$in_file",
	     "--outfile=$out_file",
	     "--css=${html_root}/Active.css",
	 );

    open (HTMLFILE, "<$out_file") or die "Couldn't open $out_file: $!";
    open (TMPFILE, ">$out_file.tmp") or die "Couldn't open $out_file.tmp: $!";
    my $first_header = 1;
    my $title;
    while (my $content = <HTMLFILE> ) {
	# Despite what Pod::Html says, this is not XHTML.
	# IE6 doesn't display things correctly with the wrong DOCTYPE.
	$content =~ s#^<!DOCTYPE .*?>#<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">#i;
	$content =~ s#<html xmlns="http://www.w3.org/1999/xhtml">#<html>#i;

	if ($content =~ s/^(\s*)<HEAD>\s*//i) {
	    print TMPFILE <<EOT;
$1<head>
$1<!-- saved from url=(0017)http://localhost/ -->
$1<script language="JavaScript" src="$html_root/displayToc.js"></script>
$1<script language="JavaScript" src="$html_root/tocParas.js"></script>
$1<script language="JavaScript" src="$html_root/tocTab.js"></script>
EOT
	    if ($scineplex) {
	        print TMPFILE qq($1<link rel="stylesheet" type="text/css" href="$html_root/scineplex.css">\n);
	    }
	}

	# Join split TITLE lines
	if ($content =~ /<TITLE>/i) {
	    until ($content =~ /<\/TITLE>/i) {
		chomp $content;
		$content .= " " . <HTMLFILE>;
	    }
	}

	if ($content =~ /<TITLE>(.*?)<\/TITLE>/i) {
	    $title = $1;
	}

	if ($index eq "index" && $content =~ /^<p><a name="__index__"><\/a><\/p>$/i) {
	    if ($title) {
		$content = <<EOT;
<script>writelinks('__top__',$depth);</script>
<h1><a>$title</a></h1>
$content
EOT
	    }
	    else {
		warn "DocTools: $out_file has no TITLE\n";
	    }
	}

	# Don't duplicate the title if we don't have an index.
	# Instead put the TOC buttons on the first header in the document.
	# This is being used for release notes and changelogs.
	if ($first_header && $index eq "noindex" && $content =~ /^<H\d>/i) {
	    $first_header = 0;
		$content = <<EOT;
<script>writelinks('__top__',$depth);</script>
$content
EOT
	}

	if (1) {
	    # XXX Skip the rest of the PDK doc tweaking for now...
	    print TMPFILE $content;
	    next;
	}

	if ($content =~ /^(.*<H1><A NAME=".*?_top">).*?(<\/A><\/H1>.*)$/i) {
	    # XXX die unless $title; ???
	    # substitute "NAME" with actual title
	    $content = "$1$title$2";
	}
	elsif ($content =~ /^(.*)<H(\d)><A NAME="(.*)">(.*)<\/A><\/H\2>(.*)$/i) {
	    my($prefix,$level,$name,$header,$suffix) = ($1,$2,$3,$4,$5);
	    if ($first_header && $header eq $title) {
		# skip redundant header
		$content = "$prefix<!-- $header -->$suffix";
	    }
	    else {
		# push all other heading one level down
		++$level;
		my $toc = "";
		my $expand = defined $expand{$basename} ? $expand{$basename} : 3;
		if (2 <= $level && $level <= $expand) {
		    $toc = "<script>writelinks('$name');</script>\n";
		}
		$content = "$prefix$toc<h$level><a name=\"$name\">$header</a></h$level>$suffix\n";
	    }
	    $first_header = undef;
	}
	elsif ($content =~ m,^(.*)<A HREF="(http://.*?)">(.*?)</A>(.*)$,i) {
	    # Add open external links in new browser and add xlink image after link text
	    my($prefix,$href,$text,$suffix) = ($1,$2,$3,$4);
	    # XXX treat .activestate.com URL differently?
	    $text .= qq( <img src="images/xlink.gif" border="0">) unless $href eq $text;
	    $content = qq($prefix<a target="_blank" href="$href">$text</a>$suffix\n);
	}

	print TMPFILE $content;
    }
    close (TMPFILE) || die;
    close (HTMLFILE);
    rename("$out_file.tmp", $out_file) || die;
}

1;
