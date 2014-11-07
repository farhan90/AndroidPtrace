package com.example.androidptrace;

import android.support.v7.app.ActionBarActivity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class DisplayActiveProcess extends ActionBarActivity {

	int pid;
	String app_name;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_display_active_process);
		Intent intent= getIntent();
		pid=intent.getIntExtra("AppID", -1);
		app_name=intent.getStringExtra("AppName");
		TextView tv= (TextView)findViewById(R.id.pidValue);
		tv.setText("Application Pid : "+pid);
		
		TextView appName=(TextView)findViewById(R.id.appName);
		appName.setText("Application Name: " +app_name);
	}

	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	
	public void onRadioButtonClicked(View v){
		
	}
	
	public void onTraceButtonClicked(View v){
		Log.v("AndroidPtrace", "Clicked the trace button");
		PtraceLib ptrace=new PtraceLib();
		
		ptrace.syscall_trace(pid);
		
		
	}
	
}
