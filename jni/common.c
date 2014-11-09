#include "common.h"


void cleanup_syscall_tabel(){
	int i=0;
	for (i=0;i<TOTAL_SYSCALL_X86;i++){
		free(syscall_table[i]);
	}
}

void parse_system_call_name(char *filename){
	int ret=0;
	char *line=NULL;
	size_t len=0;
	FILE *fptr=fopen(filename,"r");

	if(!fptr){
		printf("Could not open the file %s\n",filename);
		__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Could not open the file %s\n",filename);
		return;
	}

	int index=0;
	while((ret=getline(&line,&len,fptr))!=-1){
		printf("in the while loop\n");
		struct syscall_info *info=malloc(sizeof(struct syscall_info));
		char *token;
		int i=0;
		while((token=strsep(&line,","))!=NULL){
			if(i==0)
				info->num_args=atoi(token);

//			if(i==1)
//				printf("The second token is %s\n",token);
//
//			if(i==2)
//				printf("The third token is %s\n",token);

			if(i==3)
				memcpy(info->name,token,150);

			i++;
		}
		syscall_table[index]=info;
		index++;
	}
	free(line);
	fclose(fptr);

}

void print_syscall(int pid){
	struct user_regs_struct u_in;
	int syscall;
	ptrace(PTRACE_GETREGS,pid,NULL,&u_in);
	syscall=u_in.orig_eax;
	struct syscall_info *info=syscall_table[syscall];
	printf("The syscall name is %s and number is %ld\n",info->name,u_in.orig_eax);

}

int trace_syscall(int pid){
	int stat;
	int killed;

	ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
	wait(&stat);
	killed = kill(pid, 0);

	if (killed != 0) {
		printf("Process exit (or something else.");
		return 1;
	}
	else{
		return 0;
	}

}
