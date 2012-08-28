# This file was created by configpm when Perl was built. Any changes
# made to this file will be lost the next time perl is built.

package Config;
use strict;
# use warnings; Pulls in Carp
# use vars pulls in Carp
@Config::EXPORT = qw(%Config);
@Config::EXPORT_OK = qw(myconfig config_sh config_vars config_re);

# Need to stub all the functions to make code such as print Config::config_sh
# keep working

sub myconfig;
sub config_sh;
sub config_vars;
sub config_re;

my %Export_Cache = map {($_ => 1)} (@Config::EXPORT, @Config::EXPORT_OK);

our %Config;

# Define our own import method to avoid pulling in the full Exporter:
sub import {
    my $pkg = shift;
    @_ = @Config::EXPORT unless @_;

    my @funcs = grep $_ ne '%Config', @_;
    my $export_Config = @funcs < @_ ? 1 : 0;

    no strict 'refs';
    my $callpkg = caller(0);
    foreach my $func (@funcs) {
	die sprintf qq{"%s" is not exported by the %s module\n},
	    $func, __PACKAGE__ unless $Export_Cache{$func};
	*{$callpkg.'::'.$func} = \&{$func};
    }

    *{"$callpkg\::Config"} = \%Config if $export_Config;
    return;
}

die "Perl lib version (v5.8.7) doesn't match executable version ($])"
    unless $^V;

$^V eq v5.8.7
    or die "Perl lib version (v5.8.7) doesn't match executable version (" .
	sprintf("v%vd",$^V) . ")";


sub FETCH {
    my($self, $key) = @_;

    # check for cached value (which may be undef so we use exists not defined)
    return $self->{$key} if exists $self->{$key};

    return $self->fetch_string($key);
}
sub TIEHASH {
    bless $_[1], $_[0];
}

sub DESTROY { }

sub AUTOLOAD {
    my $config_heavy = 'Config_dynamic.pl';
    if (defined &ActivePerl::_CONFIG_HEAVY) {
       $config_heavy = ActivePerl::_CONFIG_HEAVY();
    }
    require $config_heavy;
    goto \&launcher;
    die "&Config::AUTOLOAD failed on $Config::AUTOLOAD";
}

sub __unused {
    # XXX Keep PerlApp happy
    require 'Config_dynamic.pl';
}

tie %Config, 'Config', {
    archlibexp => '/tmp/perl---------------------------------------------please-run-the-install-script---------------------------------------------/lib/5.8.7/i686-linux-thread-multi',
    archname => 'i686-linux-thread-multi',
    d_readlink => 'define',
    d_symlink => 'define',
    dlsrc => 'dl_dlopen.xs',
    dont_use_nlink => undef,
    exe_ext => '',
    inc_version_list => '5.8.6/i686-linux-thread-multi 5.8.6 5.8.4/i686-linux-thread-multi 5.8.4 5.8.3/i686-linux-thread-multi 5.8.3 5.8.2/i686-linux-thread-multi 5.8.2 5.8.1/i686-linux-thread-multi 5.8.1 5.8.0/i686-linux-thread-multi 5.8.0',
    intsize => '4',
    ldlibpthname => 'LD_LIBRARY_PATH',
    lib_ext => '.a',
    osname => 'linux',
    osvers => '2.2.17',
    path_sep => ':',
    privlibexp => '/tmp/perl---------------------------------------------please-run-the-install-script---------------------------------------------/lib/5.8.7',
    scriptdir => '/tmp/perl---------------------------------------------please-run-the-install-script---------------------------------------------/bin',
    sitearchexp => '/tmp/perl---------------------------------------------please-run-the-install-script---------------------------------------------/lib/site_perl/5.8.7/i686-linux-thread-multi',
    sitelibexp => '/tmp/perl---------------------------------------------please-run-the-install-script---------------------------------------------/lib/site_perl/5.8.7',
    so => 'so',
    useithreads => 'define',
    usevendorprefix => undef,
    version => '5.8.7',
};

1;
