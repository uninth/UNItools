package ActivePerl::Config;

use strict;
my %OVERRIDE;
my %COMPILER_ENV = map { $_ => 1 } qw(
    cc
    ccflags
    cccdlflags
    gccversion
    ar
    cpp
    cppminus
    cpprun
    cppstdin
    ld
    lddlflags
    ldflags
    libc
    libs
    optimize
    perllibs
    _a
    _o
    obj_ext
);
my $compiler_env_initialized;

use ActiveState::Path qw(find_prog);

use Config ();
my $CONFIG_OBJ = tied %Config::Config;

sub override {
    return 0 if $ENV{ACTIVEPERL_CONFIG_DISABLE};

    my $key = shift;

    if (exists $ENV{"ACTIVEPERL_CONFIG_\U$key"}) {
	$_[0] = $ENV{"ACTIVEPERL_CONFIG_\U$key"};
	return 1;
    }

    if (exists $OVERRIDE{$key}) {
	$_[0] = $OVERRIDE{$key};
	return 1;
    }

    if ($key eq "cc" && $ENV{ACTIVEPERL_CONFIG_CCACHE} && find_prog("ccache")) {
	$_[0] = "ccache " . _orig_conf("cc");
	return 1;
    }

    if ($key eq "make" && $^O eq "MSWin32") {
	for (qw(nmake dmake)) {
	    if (find_prog($_)) {
		$_[0] = $OVERRIDE{$key} = $_;
		return 1;
	    }
	}
	return 0;
    }

    if ($COMPILER_ENV{$key} && !$compiler_env_initialized++) {
	if ($^O eq "MSWin32" && !find_prog(_orig_conf("cc"))) {
	    if (find_prog("gcc")) {
		# assume MinGW or similar is available
		_override("cc", "gcc");
		my($gccversion) = qx(gcc --version);
		$gccversion =~ s/^gcc(\.exe)? \(GCC\) //;
		chomp($gccversion);
		warn "Set up gcc environment - $gccversion\n";
		_override("gccversion", $gccversion);

		foreach my $key (qw(libs perllibs)) {
		    # Old: "  foo.lib oldnames.lib bar.lib"
		    # New: "-lfoo -lbar"
		    my @libs = split / +/, _orig_conf($key);
		    # Filter out empty prefix and oldnames.lib
		    @libs = grep {$_ && $_ ne "oldnames.lib"} @libs;
		    # Remove '.lib' extension and add '-l' prefix
		    s/(.*)\.lib$/-l$1/ for @libs;
		    _override($key, join(' ', @libs));
		}

		# Copy all symbol definitions from the CCFLAGS
		my @ccflags = grep /^-D/, split / +/, _orig_conf("ccflags");
		# Add GCC specific flags
		push(@ccflags, qw(-DHASATTRIBUTE -fno-strict-aliasing));
		_override("ccflags", join(" ", @ccflags));

		# more overrides assuming MinGW
		_override("cpp",       "gcc -E");
		_override("cpprun",    "gcc -E");
		_override("cppminus",  "-");
		_override("ar",        "ar");
		_override("ld",        "gcc");
		_override("_a",        ".a");
		_override("_o",        ".o");
		_override("obj_ext",   ".o");
		_override("optimize",  "-O2");
		_override("lddlflags", "-mdll");

		if (exists $OVERRIDE{$key}) {
		    $_[0] = $OVERRIDE{$key};
		    return 1;
		}
	    }
	}
    }

    return 0;
}

sub _orig_conf {
    $CONFIG_OBJ->_fetch_string($_[0]);
}

sub _override {
    my($key, $val) = @_;
    $OVERRIDE{$key} = $val unless exists $OVERRIDE{$key};
}

1;

__END__

=head1 NAME

ActivePerl::Config - Override the ActivePerl configuration

=head1 SYNOPSIS

  use Config qw(%Config);

=head1 DESCRIPTION

The standard C<Config> module provides the %Config hash containing
information about how this perl was built.  These configuration values
are used by modules and programs with the assumption that they still
apply for the system where perl is deployed.  This assumption does not
always hold.  The C<ExtUtils::MakeMaker> module will for instance
assume that it can use the compiler $Config{cc} for building new
extensions, but another compiler might be the only one available.

The C<ActivePerl::Config> module provides a solution for this.  It
overrides the values of %Config to better match the system where perl
currently runs.  For example, on Windows allows you to build extensions
with the free compiler L<gcc|gcc> (see L<http://www.mingw.org/>) even
though ActivePerl for Windows itself is built with the commercial
Microsoft Visual Studio 6 compiler.

The C<ActivePerl::Config> module is not used directly.  It is
automatically loaded by C<Config> if available and works behind the
scenes, overriding the values that are found in the %Config hash.  The
overriden values from C<ActivePerl::Config> will also show when C<perl
-V:foo> is invoked from the command line.

=head2 Window overrides

For ActivePerl on Windows the following %Config overrides are provided:

=over

=item $Config{make}

This will be C<nmake> by default, but if no F<nmake> program can be
found and other compatible make programs are found, then this value
will reflect that.  Currently F<dmake> is the only other make
implementation that is compatible enough to build perl extensions.

=item $Config{cc}, $Config{ccflags},...

The value of $Config{cc} will be C<cl> by default, but if no C<cl>
program can be found and F<gcc> is found, then this value is C<gcc>
and other values related to the compiler environment is adjusted
accordingly.

=back

=head1 ENVIRONMENT

The following environment variables can influence the operation of the
C<ActivePerl::Config> module:

=over

=item ACTIVEPERL_CONFIG_DISABLE

If set to a TRUE value (e.g. "1"), prevent C<ActivePerl::Config> from
overriding any %Config value; the only values seen in %Config would be
those determined at perl build time.  Another way to disable
C<ActivePerl::Config> permanently is to remove it using L<ppm|ppm>
(C<ppm remove ActivePerl-Config>)

=item ACTIVEPERL_CONFIG_I<FOO>

Override the $Config{I<foo>} value.  For example if the
ACTIVEPERL_CONFIG_MAKE environment variable has the value C<dmake>,
then so would $Config{make}.

If the ACTIVEPERL_CONFIG_DISABLE variable is set, all other
ACTIVEPERL_CONFIG_I<FOO> variables are ignored.

=back

=head1 SEE ALSO

L<Config>
