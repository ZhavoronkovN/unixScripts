#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_SIZE 100

void print_help(void){
	printf("%s\n%s\n%s\n%s\n","Task 1",
			"Usage : task1 DIRECTORY FILE_TYPE",
			"Removes files of specific FILE_TYPE in subdirectories of DIRECTORY",
			"Example : task1 /home .cpp (removes all .cpp files from /home subfolders)");
	return;
}

char* f_type(char * file){
	char * res=malloc(MAX_SIZE * sizeof(char));
	int m=0;
	char* r = strrchr(file,'.');
	for(char * i = r ; *i != '\0' ;i++){
		res[m++] = *i;
	}
	res[m]='\0';
	return res;
}

int removeFiles(char * dir_name,char * type){
	DIR * dir = opendir(dir_name);
	if(!dir){
		printf("Cant open \"%s\"\n",dir_name);
		perror("");
		free(dir_name);
		return 1;
	}
	struct dirent *dirent_f;
	while((dirent_f=readdir(dir))!=NULL){
			if(strchr((*dirent_f).d_name,'.')!=(*dirent_f).d_name){
				char * file = malloc(MAX_SIZE*sizeof(char));
				memcpy(file,dir_name,strlen(dir_name)+1);
				strcat(strcat(file,"/"),(*dirent_f).d_name);
				struct stat f_stat;
				lstat(file,&f_stat);
				if((f_stat.st_mode&S_IFMT)==S_IFDIR){
					char * next_dir = malloc(MAX_SIZE*sizeof(char));
					memcpy(next_dir,file,strlen(file)+1);
					removeFiles(next_dir,type);
					free(next_dir);
				}
				else{
					if(strchr(file,'.')!=NULL){
							char * file_type = f_type(file);
							if(! strcmp(file_type,type)){
								if(remove(file)){
									printf("Cant delete \"%s\"\n",file);
									perror("");
								}
						}
						free(file_type);
					}
				}
				free(file);
			}
		}
	closedir(dir);
	return 0;
}


int main(int argc, char * argv[]){
	for(int i=1;i<argc;i++){
		if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help")){
			print_help();
			exit(0);
		}
	}
	if(argc<3)
	{
		printf("%s\n","Error : too few arguments \nType -h or --help for help");
		exit(1);
	}
	else if (argc>3){
		printf("%s\n","Error : too much arguments \nType -h or --help for help");
		exit(2);
	}
	if(strrchr(argv[2],'.')==NULL){
		printf("Error in \"%s\", second parametr must start with \".\" (dot)\n",argv[2]);
		exit(3);
	}
	removeFiles(argv[1],argv[2]);
	return 0;
}
