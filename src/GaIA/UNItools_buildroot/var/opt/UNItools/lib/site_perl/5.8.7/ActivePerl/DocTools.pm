package ActivePerl::DocTools;

use strict;
use warnings;

use Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(UpdateHTML Pod2HTML);
our $VERSION = '1.00';

sub WriteRDF {
    require ActivePerl::DocTools::TOC::RDF;
    print ActivePerl::DocTools::TOC::RDF->new->TOC();
}

sub WriteTOC {
    my($file,$toc);
    require ActivePerl::DocTools::TOC;
    return unless -d $ActivePerl::DocTools::TOC::dirbase;

    if (0) {
	require ActivePerl::DocTools::TOC::tocTab;
	$toc = ActivePerl::DocTools::TOC::tocTab->new->TOC();
	$file = "$ActivePerl::DocTools::TOC::dirbase/tocTab.js";
    }
    else {
	require ActivePerl::DocTools::TOC::HTML;
	$toc = ActivePerl::DocTools::TOC::HTML->new->TOC();
	$file = "$ActivePerl::DocTools::TOC::dirbase/perltoc.html";
    }
    unlink($file);
    my $fh;
    unless (open($fh, '>', $file)) {
	warn "Unable to open '$file' for writing: $!\n";
	return;
    }

    print $fh $toc;
    close($fh) or die "Can't write '$file': $!";
}

sub UpdateHTML {
    # if $noisy is false, ignores errors
    # if $noisy is "wait", waits for confirmation
    # else dies if there are errors
    my $noisy = shift;

    require ActivePerl::DocTools::TOC;
    return unless -d $ActivePerl::DocTools::TOC::dirbase;

    require ActivePerl::DocTools::Tree::HTML;
    eval {
	ActivePerl::DocTools::Tree::HTML::Update();
	WriteTOC();
    };
    if ($@ && $noisy) {
	if ($noisy eq 'wait') {
	    # this is somewhat bletcherous
	    print "Error building documentation: $@\n";
	    print "Press [Enter] to continue\n";
	    <STDIN>;
	    exit 1;
	}
	die $@;
    }
}

sub Pod2HTML {
    my $noisy;
    my %args;
    if (@_ == 1) {
        $args{verbose} = shift;
    }
    else {
        %args = @_;
    }

    require ActivePerl::DocTools::Tree::HTML;
    eval {
    ActivePerl::DocTools::Tree::HTML::Pod2HTML(%args);
    };
    if ($@ && $args{verbose}) {
      die $@;
    }
}

1;
