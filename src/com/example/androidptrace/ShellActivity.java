package com.example.androidptrace;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class ShellActivity extends ActionBarActivity {

	EditText input;
	Button btn;
	TextView out;
	//This array length is the number of commands to execute
	String[] command = new String[1];
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_shell);
		input = (EditText)findViewById(R.id.txt);
		btn = (Button)findViewById(R.id.btn);
		out = (TextView)findViewById(R.id.out);
		btn.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				//Get the entered command
				command[0] = input.getText().toString();
				String outp = executeCommands(command);
				out.setText(outp);
				Log.d("Output", outp);
			}
		});
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

	public String executeCommands(String[] commands) {
		StringBuffer output = new StringBuffer();
		Process p;
		try {
			p = Runtime.getRuntime().exec("sh");
			DataOutputStream os = new DataOutputStream(p.getOutputStream()); 
			for (String tmpCmd : commands) {
				os.writeBytes(tmpCmd+"\n");
			}           
	        os.writeBytes("exit\n");  
	        os.flush();
	        String line = "";
			BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
			while ((line = reader.readLine())!= null) {
				output.append(line + "\n");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		String response = output.toString();
		return response;
	}
	
}
