#!/usr/bin/perl

use strict;
use File::Spec::Functions 'catfile';

sub too_few_arguments
{
	print "Too few arguments. Type -h or --help for help\n";
	exit 1;
}

sub print_help
{
	print "Task 2\nUsage : ./task2.pl DIRECTORY FILE_TYPE\nRemoves all files with the same name in DIRECTORY except those that have type FILE_TYPE\nExample : ./task2.pl /home .cpp (removes all files with the same name but .cpp)\n";
}

my $first_argument = shift();

my $second_argument = shift();

my $third_argument = shift();


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

opendir DIR, $first_argument or die $!;
while(my $fname = readdir DIR) {
	if(not -d $fname){
	  opendir DIR_sec, $first_argument or die $!;
	  my ($name) = $fname =~  /([^.]+\.)/;
	  while(my $fname_sec = readdir DIR_sec){
	  	if(not -d $fname_sec){
		  	if(not $fname eq $fname_sec){
		  		my ($name_sec) = $fname_sec =~ /([^.]+\.)/;
		  		if($name eq $name_sec){
		  			my ($ext) = $fname_sec =~  /(\.[^.]+)$/;
		  			if(not $ext eq $second_argument){
		  				unlink catfile($first_argument, $fname_sec) or die "Cant delete $fname_sec : $!\n";
		  			}
		  		}
		  	}
	  	}
	  }
	  closedir DIR_sec;
	}

}
closedir DIR;