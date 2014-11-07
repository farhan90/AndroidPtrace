package com.example.androidptrace;

public class PtraceLib {

	static{
		System.loadLibrary("android_ptrace");
	}
	
	public native int syscall_trace(int pid);
}
