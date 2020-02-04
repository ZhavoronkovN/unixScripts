#!/usr/bin/perl

use strict;
use File::Find;
use File::stat;
use File::Spec::Functions 'catfile';
use File::Basename;
use File::Copy;

sub too_few_arguments
{
	print "Too few arguments. Type -h or --help for help\n";
	exit 1;
}

my @files;

sub add_files_to_array
{
	if(not -d $_)
	{
		if(time() - stat($_)->mtime<3600)
		{
	    	print "$File::Find::name\n";
		}
		push @files, $File::Find::name;
	}
}

sub print_help
{
	print "Task 3\nUsage : ./task3.pl DIRECTORY\n1) Prints files were changed last hour\n2) Prints 10 the oldest files\n3) Copies 10 the freshest into directory \"backup\"\n";
}

my $first_argument = shift();

my $second_argument = shift();


if($first_argument eq "-h" or $first_argument eq "--help")
{
	print_help();
	exit 0;
}

if(not defined $first_argument)
{
	print "Too few arguments. Type -h or --help for help\n";
	exit 1;
}

if(defined $second_argument)
{
	print "Too much arguments. Type -h or --help for help\n";
	exit 2;
}

if(not -d $first_argument)
{
	print "First argument must be a directory\n";
	exit 3;
}
print "Files was changed last hour : \n";
find(\&add_files_to_array, $first_argument);
my $files_length = scalar @files;
my @sorted_files = sort {
        stat($a)->ctime <=> stat($b)->ctime;
    }  @files;
my $size = 0;
print "Ten oldest files : \n"; 
for (my $i = 0; $i < 10; $i++)
{
	last if ($files_length == $i);
	print "@sorted_files[$i]\n";
	$size += stat(@sorted_files[$i])->size;
}
print "Their size : \n";
print "$size\n";

my $backupDir = catfile($first_argument,"backup"); 
mkdir $backupDir;

@sorted_files = reverse(@sorted_files);

for (my $i = 0; $i < 10; $i++)
{
	last if ($files_length == $i);
	copy(@sorted_files[$i],catfile($backupDir,basename(@sorted_files[$i])));
}
