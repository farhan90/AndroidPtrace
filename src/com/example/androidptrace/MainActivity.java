package com.example.androidptrace;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	private ArrayAdapter processAdapter;
	private ListView mainListView;
	ArrayList<ActiveProcess> activeProcessList;
	HashMap<String,ActiveProcess> processMap;
	
	public final static String EXTRA_ACTIVITY= "com.example.androidptrace.activeprocess";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		ActivityManager am = (ActivityManager)this.getSystemService(Context.ACTIVITY_SERVICE);
		List<ActivityManager.RunningAppProcessInfo> runningApps=am.getRunningAppProcesses();
		
		activeProcessList=new ArrayList<ActiveProcess>();
		processMap= new HashMap<String,ActiveProcess>();
		for(int i=0;i<runningApps.size();i++){
			int pid= runningApps.get(i).pid;
			String name=runningApps.get(i).processName;
			ActiveProcess ap= new ActiveProcess(pid,name);
			activeProcessList.add(ap);
			processMap.put(name, ap);
		}
		
		mainListView = (ListView) findViewById( R.id.mainListView );
		processAdapter = new MySimpleAdapter(this, R.layout.simplerow, activeProcessList,processMap);
		mainListView.setAdapter(processAdapter);
		
		
		
//		Context context = getApplicationContext();
//		CharSequence text = stringTest();
//		int duration = Toast.LENGTH_SHORT;
//
//		Toast toast = Toast.makeText(context, text, duration);
//		toast.show();
	}
	
//	public native String  stringTest();
//
//    /* this is used to load the 'hello-jni' library on application
//     * startup. The library has already been unpacked into
//     * /data/data/com.example.hellojni/lib/libhello-jni.so at
//     * installation time by the package manager.
//     */
//    static {
//        System.loadLibrary("");
//    }
//	
	
	public void onShellButtonClicked(View v){
		Log.v("AndroidPtrace", "Clicked the shell button");
		Intent intent = new Intent(this, ShellActivity.class);
	    startActivity(intent);
		
	}
	
	
	
}
