import argparse
import os
import sys
from stat import *

parser = argparse.ArgumentParser(description="Removes files of specific FILETYPE in DIRECTORY and its subdirectories")
parser.add_argument("DIRECTORY",help="Directory where files will be deleted")
parser.add_argument("FILETYPE",help="Type of files for deleting")
args = parser.parse_args()

def removeFilesFromDirectory(directory, fileType):
	for file in os.listdir(directory):
		full_path = os.path.join(directory,file)
		mode = os.stat(full_path).st_mode
		if S_ISDIR(mode):
			removeFilesFromDirectory(full_path,fileType)
		elif S_ISREG(mode):
			if file.split(".")[-1] == fileType:
				os.remove(full_path)

removeFilesFromDirectory(args.DIRECTORY,args.FILETYPE)