#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_SIZE 100

void print_help(void){
	printf("%s\n%s\n%s\n%s\n","Task 2",
			"Usage : task2 DIRECTORY FILE_TYPE",
			"Removes all files with the same name in DIRECTORY except those that have type FILE_TYPE",
			"Example : task2 /home .cpp (removes all files with the same name but .cpp)");
	return;
}
char* f_name(char * file){
	char * res=malloc(MAX_SIZE*sizeof(char));
	int m=0;
	char* r = strrchr(file,'.');
	for(char * i = file ; i != r ;i++){
		res[m++] = *i;
	}
	res[m]='\0';
	return res;
}
char* f_type(char * file){
	char * res=malloc(MAX_SIZE*sizeof(char));
	int m=0;
	char* r = strrchr(file,'.');
	for(char * i = r ; *i != '\0' ;i++){
		res[m++] = *i;
	}
	res[m]='\0';
	return res;
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
	DIR * dir = opendir(argv[1]);
	char * type = argv[2];
	if(dir){
		char ** all_files = malloc(MAX_SIZE*sizeof(char *));
		for(int i = 0;i<MAX_SIZE;i++){
			all_files[i]=malloc(MAX_SIZE*sizeof(char));
		}
		int ind=0;
		struct dirent *file1;
		struct stat file_stat;
		while((file1=readdir(dir))!=NULL){
			if(strchr((*file1).d_name,'.')!=(*file1).d_name&&strchr((*file1).d_name,'.')!=NULL){
				char * file = malloc(MAX_SIZE*sizeof(char));
				memcpy(file,argv[1],strlen(argv[1])+1);
				strcat(strcat(file,"/"),(*file1).d_name);
				lstat(file,&file_stat);
				if((file_stat.st_mode&S_IFMT)==S_IFREG){
					memcpy(all_files[ind++],file,strlen(file)+1);
				}
				free(file);
			}
		}
		char ** files_to_delete = malloc(ind*sizeof(char *));
		for(int i = 0;i<ind;i++){
			files_to_delete[i]=malloc(MAX_SIZE*sizeof(char));
		}
		int d_ind=0;
		for(int i = 0; i < ind; i++){
			int del_req = 0;
			char * file1 = all_files[i];
			char * file1_t = f_type(file1);
			char * file1_n = f_name(file1);
			for(int j = i + 1; j < ind; j++){
				char * file2 = all_files[j];
				char * file2_t = f_type(file2);
				char * file2_n = f_name(file2);
				if ( ! strcmp(file1_n, file2_n)){
					del_req=1;
					if(strcmp(type, file2_t)){
						int added = 0;
						for(int t = 0; t < d_ind ; t++){
							if(! strcmp(file2, files_to_delete[t])){
								added=1;
							}
						}
						if(! added){
							memcpy(files_to_delete[d_ind++],file2,strlen(file2)+1);
						}
					}
				}
				free(file2_t);
				free(file2_n);
			}	
			if(strcmp(file1_t, type) && del_req){
				int added = 0;
				for(int t = 0; t < d_ind ; t++){
					if(! strcmp(files_to_delete[t], file1)){
						added=1;
					}
				}
				if(! added){
					memcpy(files_to_delete[d_ind++],file1,strlen(file1)+1);
				}
			}
			free(file1_t);
			free(file1_n);
		}
		for(int i = 0; i < d_ind; i++){
			if(remove(files_to_delete[i])){
				printf("Cant delete \"%s\"\n",files_to_delete[i]);
				perror("");
			}
		}
		for(int i = d_ind-1;i>-1;i--){
			free(files_to_delete[i]);
		}
		free(files_to_delete);
		for(int i = 0;i<MAX_SIZE;i++){
			free(all_files[i]);
		}
		free(all_files);
		closedir(dir);
	}
	else{
		printf("Cant open \"%s\"\t",argv[1]);
		perror("");
		return 1;
	}
	return 0;
}