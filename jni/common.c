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
		struct syscall_info *info=malloc(sizeof(struct syscall_info));
		char *token;
		int i=0;
		while((token=strsep(&line,","))!=NULL){
					if(i==0)
						info->num_args=atoi(token);

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


void get_syscall_args(int argnum,struct user_regs_struct *u_in){
	switch (argnum){
		case 0:
			printf("The value of first argument %08lx\n",u_in->ebx);
			break;
		case 1:
			printf("The value of second argument %08lx\n",u_in->ecx);
			break;
		case 2:
			printf("The value of third argument %08lx\n",u_in->edx);
			break;
		case 3:
			printf("The value of fourth argument %08lx\n",u_in->esi);
			break;
		case 4:
			printf("The value of fifth argument %08lx\n",u_in->edi);
			break;
		case 5:
			printf("The value of sixth argument %08lx\n",u_in->ebp);
			break;


	}
}

void print_syscall(int pid){
	struct user_regs_struct u_in;
	int syscall;
	int i=0;
	if(ptrace(PTRACE_GETREGS,pid,NULL,&u_in)<0){
		printf("Ptrace get regs in function print syscall failed\n");
		__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Ptrace get regs in function print syscall failed\n");
		return;
	}
	syscall=u_in.orig_eax;
	struct syscall_info *info=syscall_table[syscall];
	printf("The syscall name is %s and number is %ld \n",info->name,u_in.orig_eax);
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The syscall name is %s and number is %ld\n",info->name,u_in.orig_eax);

	for(i=0;i<info->num_args;i++){
		get_syscall_args(i,&u_in);
	}


}

void get_return_value(int pid){
	struct user_regs_struct u_in;

	if(ptrace(PTRACE_GETREGS,pid,NULL,&u_in)<0){
			printf("Ptrace get regs in function get return value failed\n");
			__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Ptrace get regs in function get return value failed\n");
			return;
		}

	printf("The return value is %ld\n\n",u_in.eax);
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The return value is %ld\n",u_in.orig_eax);
}

int trace_syscall(int pid){
	int stat;
	int killed;

	ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
	wait(&stat);
	killed = kill(pid, 0);

	if (killed != 0) {
		printf("Process exit (or something else)");
		return 1;
	}
	else{
		return 0;
	}

}
