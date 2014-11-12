#include "common.h"

#ifdef __arm__

void print_syscall_arm(int pid){
		struct user_regs u_in;
		int syscall;
		int i=0;
		if(ptrace(PTRACE_GETREGS,pid,NULL,&u_in)<0){
			printf("Ptrace get regs in function print syscall failed\n");
			__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Ptrace get regs in function print syscall failed\n");
			return;
		}
		syscall=u_in.uregs[7];
		struct syscall_info *info=syscall_table[syscall];
		printf("The syscall number is %ld\n",u_in.uregs[7]);
		printf("The syscall name is %s and number is %ld \n",info->name,u_in.uregs[7]);
		__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The syscall name is %s and number is %ld\n",info->name,u_in.uregs[7]);
}

#else
void get_syscall_args(int argnum,struct user_regs_struct *u_in){
	switch (argnum){
		case 0:
#ifdef __i386__
			printf("The value of first argument %08lx\n",u_in->ebx);
#elif __x86_64__
			printf("The value of first argument %08lx\n",u_in->rdi);
#endif
			break;
		case 1:
#ifdef __i386__
			printf("The value of second argument %08lx\n",u_in->ecx);
#elif __x86_64__
			printf("The value of second argument %08lx\n",u_in->rsi);
#endif
			break;
		case 2:
#ifdef __i386__
			printf("The value of third argument %08lx\n",u_in->edx);
#elif __x86_64__
			printf("The value of third argument %08lx\n",u_in->rdx);
#endif
			break;
		case 3:
#ifdef __i386__
			printf("The value of fourth argument %08lx\n",u_in->esi);
#elif __x86_64__
			printf("The value of fourth argument %08lx\n",u_in->r10);
#endif
			break;
		case 4:
#ifdef __i386__
			printf("The value of fifth argument %08lx\n",u_in->edi);
#elif __x86_64__
			printf("The value of fifth argument %08lx\n",u_in->r8);
#endif
			break;
		case 5:
#ifdef __i386__
			printf("The value of sixth argument %08lx\n",u_in->ebp);
#elif __x86_64__
			printf("The value of sixth argument %08lx\n",u_in->r9);
#endif
			break;


	}
}



void get_return_value(int pid){
	struct user_regs_struct u_in;

	if(ptrace(PTRACE_GETREGS,pid,NULL,&u_in)<0){
			printf("Ptrace get regs in function get return value failed\n");
			__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Ptrace get regs in function get return value failed\n");
			return;
		}
#ifdef __i386__
	printf("The return value is %ld\n\n",u_in.eax);
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The return value is %ld\n",u_in.orig_eax);
#endif

#ifdef __x86_64__
	printf("The return value is %ld\n\n",u_in.rax);
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The return value is %ld\n",u_in.orig_rax);
#endif

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
#ifdef __i386__
	syscall=u_in.orig_eax;
	struct syscall_info *info=syscall_table[syscall];
	printf("The syscall name is %s and number is %ld \n",info->name,u_in.orig_eax);
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The syscall name is %s and number is %ld\n",info->name,u_in.orig_eax);
#endif

#ifdef __x86_64__
	syscall=u_in.orig_rax;
	struct syscall_info *info=syscall_table[syscall];
	printf("The syscall name is %s and number is %ld \n",info->name,u_in.orig_rax);
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The syscall name is %s and number is %ld\n",info->name,u_in.orig_rax);

#endif

	for(i=0;i<info->num_args;i++){
			get_syscall_args(i,&u_in);
	}

}

#endif /*Main end if*/

void cleanup_syscall_tabel(){
	int i=0;
	for (i=0;i<TOTAL_SYSCALL;i++){
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

