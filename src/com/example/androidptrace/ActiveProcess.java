package com.example.androidptrace;

public class ActiveProcess {
	
	private int pid;
	private String name;
	
	public ActiveProcess(int pid,String name){
		this.pid=pid;
		this.name=name;
	}

	public int getPid() {
		return pid;
	}

	public void setPid(int pid) {
		this.pid = pid;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	
	public String toString(){
		return this.name;
	}

}
