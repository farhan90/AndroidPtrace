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
		if (WIFEXITED(stat))
		       return 1;
	}

}

JNIEXPORT jint JNICALL Java_com_example_androidptrace_PtraceLib_syscall_1trace
  (JNIEnv *env, jobject obj, jint pid){

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
		if(wait_for_syscall(pid)!=0)
			break;
		syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*ORIG_EAX);
		if(syscall<0){
			__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The errno is %d\n",errno);
			break;

		}
		__android_log_print(ANDROID_LOG_INFO,LOG_TAG,"The process made a system call %ld\n",syscall);
	}

	return 0;
}



