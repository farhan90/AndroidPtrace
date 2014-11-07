#include <jni.h>
#include "PtraceLibJNI.h"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/reg.h>
#include <android/log.h>
#include <errno.h>
#define LOG_TAG "AndroidPtrace"

/**
 * This is code for our adb client that can utilize the ptrace commands as well.
 */

int wait_for_syscall(int pid){
	int stat;
	int err;

	while(1){
		err=ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
		if(err<0){
			__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The errno for syscall trace is %d\n",errno);
			return -1;
		}

		waitpid(pid,&stat,0);

		//If stopped due to a sig trap signal
		if (WIFSTOPPED(stat) && WSTOPSIG(stat) & 0x80)
		       return 0;

		//If the process exited from the syscall
		if (WIFEXITED(stat)) {
			printf("Process exit.");
		       return 1;
		}
	}

}

int main(int argc, char **argv)
{
	int pid;
	int killed;
	int i = 1;
	i+=2;

	pid = atoi(argv[1]);

	printf("Hello, world (i=%d)!\n", pid);


	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"inside the JNI");
	jint stat=0;
	jint res=0;
	struct user_regs_struct u_in;
	long syscall;
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Attaching to process %d\n",pid);

	if ((ptrace(PTRACE_ATTACH, pid, NULL, NULL)) != 0) {;
	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Errno for Attaching to process %d\n",errno);
	}

	res = waitpid(pid, &stat, WUNTRACED);

	__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"Status of the traced process %d\n",stat);


	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);

	while(1){
		ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
		wait(&stat);
		ptrace(PTRACE_GETREGS,pid,NULL,&u_in);
		//syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*ORIG_EAX);
		printf("The syscall is %ld\n",u_in.orig_eax);

		killed = kill(pid, 0);

		if (killed != 0) {
			printf("Process exit (or something else.");
			return 1;
		}
	}



//	while(1){
//		if(wait_for_syscall(pid)!=0)
//			break;
//		syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*ORIG_EAX);
//		if(syscall<0){
//			__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The errno is %d\n",errno);
//			break;
//
//		}
//		__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The process made a system call %ld\n",syscall);
//	}


	return 0;
	exit(0);
}

