package com.example.androidptrace;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

public class MySimpleAdapter extends ArrayAdapter {

	private final Context context;
    private HashMap<String,ActiveProcess>processMap;
    private ArrayList<ActiveProcess>processList;
	
	@SuppressWarnings("unchecked")
	public MySimpleAdapter(Context context, int resource, List objects, HashMap<String,ActiveProcess>processMap) {
		super(context, resource, objects);
		// TODO Auto-generated constructor stub
		this.context=context;
		this.processMap=processMap;
		this.processList=(ArrayList<ActiveProcess>) objects;
	}
	
	@SuppressWarnings("null")
	@SuppressLint("InflateParams")
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
	    View row = convertView;
	    
	    if (row  == null) {
	        LayoutInflater vi = 
	                (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	        row = vi.inflate(R.layout.simplerow, null);
	        Holder holder= new Holder();
	        holder.text = (TextView) row.findViewById(R.id.rowTextView);
	        
	        row.setTag(holder);
	    }
	    Holder holder= (Holder)row.getTag();
	    final ActiveProcess ap = processList.get(position);
	    holder.text.setText(ap.getName());
	    holder.text.setOnClickListener(new OnClickListener() {

            public void onClick(View v) {
            	Log.d(ap.getName(), ""+ap.getPid());
        		Intent intent= new Intent(context,DisplayActiveProcess.class);
        		intent.putExtra("AppID", ap.getPid());
        	    context.startActivity(intent);
            }
        });
	    return row;
	}
	
	static class Holder{
		public TextView text;
	}

}
