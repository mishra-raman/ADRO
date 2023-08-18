package utdallas.edu.adro;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.content.Context;
import android.os.Environment;
import android.widget.AutoCompleteTextView;
import android.view.View;
import android.util.Log;
import android.os.Bundle;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;

import com.google.android.material.navigation.NavigationBarView;
import com.google.android.material.switchmaterial.SwitchMaterial;

public class MainActivity extends AppCompatActivity {
    AutoCompleteTextView AG1,AG2,AG3,AG4,AG5,AG6,AG7,AG8,AG9,CT1,CT2,CT3,CT4,CT5,CT6,CT7,CT8,CT9,AudioSelect;
    private FileOutputStream file_Writer;

    SwitchMaterial Datasave;

    int samplerate;

    int buffersize;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        NavigationBarView bottomNavigationView = findViewById(R.id.bottom_navigation);
        bottomNavigationView.setOnItemSelectedListener(navigationItemSelectedListener);
        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,new PresetFragment()).commit();
        String[] permissions = {
                android.Manifest.permission.RECORD_AUDIO, android.Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE
        };
        for (String s:permissions) {
            if (ContextCompat.checkSelfPermission(this, s) != PackageManager.PERMISSION_GRANTED) {
                // Some permissions are not granted, ask the user.
                ActivityCompat.requestPermissions(this, permissions, 0);
                return;
            }
        }
        // Get the device's sample rate and buffer size to enable
        // low-latency Android audio output, if available.
        String samplerateString = null, buffersizeString = null;
        AudioManager audioManager = (AudioManager) this.getSystemService(Context.AUDIO_SERVICE);
        if (audioManager != null) {
            samplerateString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
            buffersizeString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
        }
        if (samplerateString == null) samplerateString = "48000";
        if (buffersizeString == null) buffersizeString = "480";
        //int samplerate = Integer.parseInt(samplerateString);
        samplerate = 16000;
        //int buffersize = Integer.parseInt(buffersizeString);
        buffersize = 128;

        // Files under res/raw are not zipped, just copied into the APK.
        // Get the offset and length to know where our file is located.
        AssetFileDescriptor fd = getResources().openRawResourceFd(R.raw.track);
        int fileOffset = (int)fd.getStartOffset();
        int fileLength = (int)fd.getLength();
        try {
            fd.getParcelFileDescriptor().close();
        } catch (IOException e) {
            Log.e("ADRO", "Close error.");
        }
        String path = getPackageResourcePath();         // get path to APK package
        System.loadLibrary("ADRO");
        prepareDirectory("ADRO/Audio/");// load native library
        //NativeFuntion.NativeInit(samplerate, buffersize, getCacheDir().getAbsolutePath()); // start audio engine;



    }

    private NavigationBarView.OnItemSelectedListener navigationItemSelectedListener = item -> {

        Fragment selectedFragment=null;
        switch (item.getItemId()){
            case R.id.Preset:
                selectedFragment = new PresetFragment();
                break;
            case R.id.runADRO:
                selectedFragment = new RunADROFragment();
                break;
        }
        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,selectedFragment).commit();
        return true;
    };

    public void savePreset(View button) throws IOException {
        AG1 = (AutoCompleteTextView) findViewById(R.id.AGInputText);
        AG2 = (AutoCompleteTextView) findViewById(R.id.AGInput2Text);
        AG3 = (AutoCompleteTextView) findViewById(R.id.AGInput3Text);
        AG4 = (AutoCompleteTextView) findViewById(R.id.AGInput4Text);
        AG5 = (AutoCompleteTextView) findViewById(R.id.AGInput5Text);
        AG6 = (AutoCompleteTextView) findViewById(R.id.AGInput6Text);
        AG7 = (AutoCompleteTextView) findViewById(R.id.AGInput7Text);
        AG8 = (AutoCompleteTextView) findViewById(R.id.AGInput8Text);
        AG9 = (AutoCompleteTextView) findViewById(R.id.AGInput9Text);

        CT1 = (AutoCompleteTextView) findViewById(R.id.CTInputText);
        CT2 = (AutoCompleteTextView) findViewById(R.id.CTInput2Text);
        CT3 = (AutoCompleteTextView) findViewById(R.id.CTInput3Text);
        CT4 = (AutoCompleteTextView) findViewById(R.id.CTInput4Text);
        CT5 = (AutoCompleteTextView) findViewById(R.id.CTInput5Text);
        CT6 = (AutoCompleteTextView) findViewById(R.id.CTInput6Text);
        CT7 = (AutoCompleteTextView) findViewById(R.id.CTInput7Text);
        CT8 = (AutoCompleteTextView) findViewById(R.id.CTInput8Text);
        CT9 = (AutoCompleteTextView) findViewById(R.id.CTInput9Text);

        int AG1value = Integer.valueOf(String.valueOf(AG1.getText()));
        int AG2value = Integer.valueOf(String.valueOf(AG2.getText()));
        int AG3value = Integer.valueOf(String.valueOf(AG3.getText()));
        int AG4value = Integer.valueOf(String.valueOf(AG4.getText()));
        int AG5value = Integer.valueOf(String.valueOf(AG5.getText()));
        int AG6value = Integer.valueOf(String.valueOf(AG6.getText()));
        int AG7value = Integer.valueOf(String.valueOf(AG7.getText()));
        int AG8value = Integer.valueOf(String.valueOf(AG8.getText()));
        int AG9value = Integer.valueOf(String.valueOf(AG9.getText()));

        int CT1value = Integer.valueOf(String.valueOf(CT1.getText()));
        int CT2value = Integer.valueOf(String.valueOf(CT2.getText())) ;
        int CT3value = Integer.valueOf(String.valueOf(CT3.getText())) ;
        int CT4value = Integer.valueOf(String.valueOf(CT4.getText())) ;
        int CT5value = Integer.valueOf(String.valueOf(CT5.getText())) ;
        int CT6value = Integer.valueOf(String.valueOf(CT6.getText())) ;
        int CT7value = Integer.valueOf(String.valueOf(CT7.getText())) ;
        int CT8value = Integer.valueOf(String.valueOf(CT8.getText())) ;
        int CT9value = Integer.valueOf(String.valueOf(CT9.getText())) ;

        int[] AGCT = {AG1value,AG2value,AG3value,AG4value,AG5value,AG6value,AG7value,AG8value,AG9value,CT1value,CT2value,CT3value,CT4value,CT5value,CT6value,CT7value,CT8value,CT9value};



        prepareDirectory("ADRO/Preset/");
        File presetfile = getFile("ADRO/Preset/"+"Preset" + new SimpleDateFormat("ddHHMMSS").format(new Date())+".txt");
        try {
            file_Writer = new FileOutputStream(presetfile);
        } catch (Exception e) {}
        try {
            file_Writer.write((Arrays.toString(AGCT).getBytes()));
        } catch (Exception e) {}

        AlertDialog alertDialog = new AlertDialog.Builder(this).create();
        alertDialog.setTitle("Preset Saved");
        alertDialog.setMessage("You can start to Run ADRO");
        alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, "OK",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();

                    }
                });
        alertDialog.show();

    }

    public static File prepareDirectory(String outName){
        File outDir = new File(Environment.getExternalStorageDirectory().toString(), outName);
        //File outDir = new File(Environment.getDataDirectory().toString(), outName);
        if (outDir.isFile()) {
            if(outDir.delete()){
                outDir.mkdirs();
            }
        }
        if(!outDir.isDirectory()){
            outDir.mkdirs();
        }
        return outDir;
    }

    public static File getFile(String outName){
        File outfile = new File(Environment.getExternalStorageDirectory().toString(), outName);
        if (!outfile.exists()) {
            try {
                outfile.createNewFile();
            } catch (Exception e) {}
        }
        return outfile;
    }
    public void runADRO(View button) throws IOException {
        AudioSelect = (AutoCompleteTextView) findViewById(R.id.AudioSelect);
        Datasave = (SwitchMaterial) findViewById(R.id.enableStore);
        String test = String.valueOf(AudioSelect.getText());
        if (!String.valueOf(AudioSelect.getText()).equals("")){

            if(Datasave.isChecked()){
                NativeFunction.EnableDataStore(1);
                prepareDirectory("ADRO/Data/");
                String DataFileName = "ADRO/Data/"+AudioSelect.getText() + new SimpleDateFormat("ddHHmmss").format(new Date())+".txt";
                NativeFunction.setDataName(DataFileName);
                File presetfile = getFile(DataFileName);
                try {
                    file_Writer = new FileOutputStream(presetfile);
                } catch (Exception e) {}
                try {
                    file_Writer.write(("ADRO On/Off | D1 | D2 | Time | Band1G | Band2G | Band3G | Band4G | Band5G | Band6G | Band7G | Band8G | Band9G | Band10G | Band11G | Band12G | Band13G | Band14G | Band15G | Band16G | Band17G | Band18G | Band19G | Band20G | Band21G | Band2G | Band23G | Band24G | Band25G | Band26G | Band27G | Band28G | Band29G | Band30G | Band31G | Band32G \n".getBytes()));
                } catch (Exception e) {}
            }else{
                NativeFunction.EnableDataStore(0 );
            }



            String audiopath = Environment.getExternalStorageDirectory().toString()+"/ADRO/Audio/" +String.valueOf(AudioSelect.getText());
            NativeFunction.NativePlayerInit(samplerate, buffersize);
            NativeFunction.OpenFile(audiopath);




        }else {
            NativeFunction.NativeInit(samplerate, buffersize);
        }



        startActivity(new Intent(this, LineGraphActivity.class));

    }


}
