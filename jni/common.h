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
#include <string.h>
#define LOG_TAG "AndroidPtrace"
#define TOTAL_SYSCALL_X86 444



struct syscall_info{
	char name[150];
	int num_args;

};

struct syscall_info *syscall_table[TOTAL_SYSCALL_X86];

//Methods

void cleanup_syscall_tabel();
void parse_system_call_name(char* filename);
void print_syscall(int pid);
int trace_syscall(int pid);
