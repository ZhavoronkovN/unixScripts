import argparse
import os
import sys
import time
import shutil
from stat import *

parser = argparse.ArgumentParser(description="1) Prints files where changed last hour \n 2) Prints 10 the oldest files and calculates sum of their sizes \n 3) Copies 10 the freshest files into directory \"backup\"")
parser.add_argument("DIRECTORY",help="Working directory")
args = parser.parse_args()

escape = "/"

files = list()

def findFiles(directory):
	global files
	for file in os.listdir(directory):
		full_path = os.path.join(directory,file)
		mode = os.stat(full_path).st_mode
		if S_ISDIR(mode):
			findFiles(full_path)
		elif S_ISREG(mode):
			files.append(full_path)

def modifiedLast(minutes):
	global files
	for file in files:
		stat = os.stat(file)
		if time.time() - stat.st_mtime < minutes*60:
			print(file)

def oldest():
	global files
	files.sort(key = lambda x : os.stat(x).st_ctime)
	size = 0
	cnt = 0
	for file in files[::-1]:
		print(file)
		cnt+=1
		size+=os.stat(file).st_size
		if cnt == 10:
			break
	return size

def copyFreshest(directory):
	global files
	cnt = 0
	backup = os.path.join(directory,"backup")
	os.mkdir(backup)
	for file in files:
		shutil.copy(file,os.path.join(backup,file.split(escape)[-1]))

findFiles(args.DIRECTORY)
print("Files were changed last hour : ")
modifiedLast(60)
print("The oldest files : ")
print("Their size "+str(oldest()))
copyFreshest(args.DIRECTORY)