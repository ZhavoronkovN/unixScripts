#!/usr/bin/perl

use strict;
use File::Find;

sub too_few_arguments
{
	print "Too few arguments. Type -h or --help for help\n";
	exit 1;
}

sub print_help
{
	print "Task 1\nUsage : ./task1.pl DIRECTORY FILE_TYPE\nRemoves files of specific FILE_TYPE in subdirectories of DIRECTORY\nExample : ./task1.pl /home .cpp (removes all .cpp files from /home subfolders)\n";
}

my $first_argument = shift();

my $second_argument = shift();

my $third_argument = shift();


sub remove_specific_files
{
	my ($ext) = $_ =~ /(\.[^.]+)$/;
	if($ext eq $second_argument)
	{
    	unlink $_;
	}
}

if($first_argument eq "-h" or $first_argument eq "--help" or $second_argument eq "-h" or $second_argument eq "--help")
{
	print_help();
	exit 0;
}

if(not defined $first_argument or not defined $second_argument)
{
	too_few_arguments();
}

if(defined $third_argument)
{
	print "Too much arguments. Type -h or --help for help\n";
	exit 2;
}

if(not -d $first_argument)
{
	print "First argument must be a directory\n";
	exit 3;
}

find(\&remove_specific_files, $first_argument);