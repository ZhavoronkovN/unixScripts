import argparse
import os
import sys
from stat import *

parser = argparse.ArgumentParser(description="Removes all files with the same name in DIRECTORY except that have type FILETYPE")
parser.add_argument("DIRECTORY",help="Directory where files will be deleted")
parser.add_argument("FILETYPE",help="Type of files which WONT be deleted")
args = parser.parse_args()

def removeFilesFromDirectory(directory, fileType):
	filesToDelete = list()
	for file in os.listdir(directory):
		full_path = os.path.join(directory,file)
		mode = os.stat(full_path).st_mode
		if S_ISREG(mode):
			repeating = False
			for file2 in os.listdir(directory):
				full_path2 = os.path.join(directory,file2)
				mode2 = os.stat(full_path2).st_mode
				if S_ISREG(mode2):
					if file != file2 and file.split(".")[0] == file2.split(".")[0]:
						repeating = True
						if file2.split(".")[-1] != fileType and full_path2 not in filesToDelete:
							filesToDelete.append(full_path2)
			if repeating and file.split(".")[-1] != fileType and full_path not in filesToDelete:
				filesToDelete.append(full_path)	
	for file in filesToDelete:
		os.remove(file)

removeFilesFromDirectory(args.DIRECTORY,args.FILETYPE)