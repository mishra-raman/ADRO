package utdallas.edu.adro;

import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.widget.CompoundButton;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.google.android.material.switchmaterial.SwitchMaterial;

import java.io.File;
import java.io.FileOutputStream;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class LineGraphActivity extends AppCompatActivity {

    private LineChart mChart;

    float[] HP;
    float[] MP;

    LineDataSet set1, set2, set3;
    private FileOutputStream data_Writer;

    SwitchMaterial ADROswitch, Datasave;

    TextView Distance1, Distance2,Frametime;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_linegraph);
        ADROswitch = (SwitchMaterial) findViewById(R.id.enableADRO);
        ADROswitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    NativeFunction.EnableADRO(0);
                }else{
                    NativeFunction.EnableADRO(1);
                }
            }
        });


        mChart = (LineChart) findViewById(R.id.line_chart);

        mChart.setTouchEnabled(true);
        mChart.setDragEnabled(true);
        mChart.setScaleEnabled(true);
        mChart.setPinchZoom(true);

        float[] AG = NativeFunction.getAudiogram();
        float[] CT = NativeFunction.getComfortTarget();
        float[] MOL = NativeFunction.getMOL();

        ArrayList<Entry> AGVals = new ArrayList<>();
        ArrayList<Entry> CTVals = new ArrayList<>();
        ArrayList<Entry> MOLVals = new ArrayList<>();

        for (int i=0; i<10; i++) {
            AGVals.add(new Entry(i, AG[i]));
            CTVals.add(new Entry(i, CT[i]));
            MOLVals.add(new Entry(i, MOL[i]));
        }



        set1 = new LineDataSet(AGVals, "Audiogram");
        set2 = new LineDataSet(CTVals, "Comfort Target");
        set3 = new LineDataSet(MOLVals, "MOL");

        set1.setColor(Color.rgb(157,204,83));
        set2.setColor(Color.rgb(239,225,229));


        LineData data = new LineData(set1, set2, set3);
        mChart.setData(data);
        mChart.invalidate();


        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                addEntry();
                handler.postDelayed(this, 30);
            }
        };
        handler = new Handler();
        handler.postDelayed(runnable, 30);

        Runnable runnable1 = new Runnable() {
            @Override
            public void run() {
                DistanceUpdate();
                handler1.postDelayed(this, 500);
            }
        };
        handler1 = new Handler();
        handler1.postDelayed(runnable1, 500);



    }


    private void addEntry() {
        HP = NativeFunction.getHighPercentile();
        MP = NativeFunction.getMidPercentile();
        ArrayList<Entry> HighP = new ArrayList<>();
        ArrayList<Entry> MidP = new ArrayList<>();
        for (int i=0; i<10; i++) {
            HighP.add(new Entry(i, HP[i]));
            MidP.add(new Entry(i, MP[i]));
        }
        LineDataSet setHP, setMP;
        setHP = new LineDataSet(HighP, "HighPercentile");
        setMP = new LineDataSet(MidP, "MidPercentile");

        setHP.setColor(Color.rgb(193,2,4));
        setMP.setColor(Color.rgb(116,166,168));

        setHP.setLineWidth(2);
        setMP.setLineWidth(2);

        LineData data = new LineData(set1, set2, set3, setHP, setMP);
        //LineChart newChart = (LineChart)  findViewById(R.id.line_chart);
        mChart.setData(data);
        mChart.notifyDataSetChanged();
        mChart.invalidate();
    }

    public void DistanceUpdate() {
        float[] Distance = NativeFunction.EuDistance();
        float frameprocessingtime = NativeFunction.getframetime()*1000;
        float q = (float) ((Math.ceil(frameprocessingtime*10000))/10000);

        Distance1 = findViewById(R.id.EuD1);
        Distance2 = findViewById(R.id.EuD2);
        Frametime = findViewById(R.id.frametime);

        Distance1.setText("Distance1: " + Float.toString(Distance[0]));
        Distance2.setText("Distance2: " + Float.toString(Distance[1]));
        Frametime.setText("Frame Processing time: " + Float.toString(q)+ "ms");

        float[] bandGain = NativeFunction.ADROGain();

        if(NativeFunction.getEnableData()&& NativeFunction.isplaying()){
            String DataFileName = NativeFunction.getDataName();
            File datafile = MainActivity.getFile(DataFileName);
            String OnOff;
            if(ADROswitch.isChecked()){
                OnOff = "On";
            }else{
                OnOff = "off";
            }
            String newLine = OnOff + " | " +Float.toString(Distance[0])+ " | " +Float.toString(Distance[1])+" | " +new SimpleDateFormat("mm:ss.SSS").format(new Date()) + " | "+Float.toString(bandGain[0]) +" | "+Float.toString(bandGain[1]) +" | "+Float.toString(bandGain[2]) +" | "+Float.toString(bandGain[3]) +" | "+Float.toString(bandGain[4]) +" | "+Float.toString(bandGain[5]) +" | "+Float.toString(bandGain[6]) +" | "+Float.toString(bandGain[7]) +" | "+Float.toString(bandGain[8]) +" | "+Float.toString(bandGain[9]) +" | "+Float.toString(bandGain[10]) +" | "+Float.toString(bandGain[11]) +" | "+Float.toString(bandGain[12]) +" | "+Float.toString(bandGain[13]) +" | "+Float.toString(bandGain[14]) +" | "+Float.toString(bandGain[15]) +" | "+Float.toString(bandGain[16]) +" | "+Float.toString(bandGain[17]) +" | "+Float.toString(bandGain[18]) +" | "+Float.toString(bandGain[19]) +" | "+Float.toString(bandGain[20]) +" | "+Float.toString(bandGain[21]) +" | "+Float.toString(bandGain[22]) +" | "+Float.toString(bandGain[23]) +" | "+Float.toString(bandGain[24]) +" | "+Float.toString(bandGain[25]) +" | "+Float.toString(bandGain[26]) +" | "+Float.toString(bandGain[27]) +" | "+Float.toString(bandGain[28]) +" | "+Float.toString(bandGain[29]) +" | "+Float.toString(bandGain[30]) +" | "+Float.toString(bandGain[31]) +"\n";
            try {
                data_Writer = new FileOutputStream(datafile,true);
            } catch (Exception e) {}
            try {
                data_Writer.write((newLine.getBytes()));
            } catch (Exception e) {}
        }
    }
    protected void onDestroy() {
        super.onDestroy();
        NativeFunction.Cleanup();
    }
    private Handler handler,handler1;
}
