package utdallas.edu.adro;

import android.os.Bundle;
import android.os.Environment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import androidx.fragment.app.Fragment;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;


import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;


import android.widget.TextView;

public class RunADROFragment extends Fragment{
    AutoCompleteTextView PresetSelect;
    AutoCompleteTextView AudioSelect;
    TextView currentPreset;
    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.runadro,container,false);
        PresetSelect = (AutoCompleteTextView) v.findViewById(R.id.PresetSelect);
        currentPreset = (TextView) v.findViewById(R.id.currentPreset);
        String path = Environment.getExternalStorageDirectory().toString()+"/ADRO/Preset";
        Log.d("Files", "Path: " + path);
        File directory = new File(path);
        File[] files = directory.listFiles();
        Log.d("Files", "Size: "+ files.length);
        if (files.length !=0) {
            String[] presetfolder = new String[files.length];
            for (int i = 0; i < files.length; i++)
            {
                presetfolder[i] = files[i].getName();
                Log.d("Files", "FileName:" + files[i].getName());
            }

            ArrayAdapter<String> presetlist = new ArrayAdapter<String>(getActivity(), android.R.layout.simple_list_item_1,presetfolder);
            PresetSelect.setAdapter(presetlist);
        }


        PresetSelect.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
                File presetfile = new File(Environment.getExternalStorageDirectory().toString() + "/ADRO/Preset/" + PresetSelect.getText());
                StringBuilder presetstring = new StringBuilder();
                try {
                    BufferedReader br = new BufferedReader(new FileReader(presetfile));
                    presetstring.append(br.readLine());
                    br.close();
                }
                catch (IOException e){
                }
                String curPreset = "Audiogram:\n"+presetstring.substring(1,(presetstring.length()/2)-1) + "\n" + "Comfot Target:\n" + presetstring.substring(presetstring.length()/2,presetstring.length()-1);
                currentPreset.setText(curPreset);
                String setpreset = presetstring.substring(1,presetstring.length()-1);
                List<String> dsllist = Arrays.asList(setpreset.split(","));
                float[] presetarray = {Float.parseFloat(dsllist.get(0)),Float.parseFloat(dsllist.get(1)),Float.parseFloat(dsllist.get(2)),Float.parseFloat(dsllist.get(3)),Float.parseFloat(dsllist.get(4)),
                        Float.parseFloat(dsllist.get(5)),Float.parseFloat(dsllist.get(6)),Float.parseFloat(dsllist.get(7)),Float.parseFloat(dsllist.get(8)),Float.parseFloat(dsllist.get(9)),
                        Float.parseFloat(dsllist.get(10)),Float.parseFloat(dsllist.get(11)),Float.parseFloat(dsllist.get(12)),Float.parseFloat(dsllist.get(13)),Float.parseFloat(dsllist.get(14)),
                        Float.parseFloat(dsllist.get(15)),Float.parseFloat(dsllist.get(16)),Float.parseFloat(dsllist.get(17))};
                NativeFunction.setPreset(presetarray);

            }
        });

        AudioSelect = (AutoCompleteTextView) v.findViewById(R.id.AudioSelect);

        String audiopath = Environment.getExternalStorageDirectory().toString()+"/ADRO/Audio";
        Log.d("Files", "Path: " + audiopath);
        File audiodirectory = new File(audiopath);
        File[] audiofiles = audiodirectory.listFiles();
        Log.d("Files", "Size: "+ audiofiles.length);
        if (audiofiles.length != 0){
            String[] audiofolder = new String[audiofiles.length+1];
            audiofolder[0] = "";
            for (int i = 1; i < audiofiles.length+1; i++)
            {
                audiofolder[i] = audiofiles[i-1].getName();
                Log.d("Files", "FileName:" + audiofiles[i-1].getName());
            }

            ArrayAdapter<String> audiolist = new ArrayAdapter<String>(getActivity(), android.R.layout.simple_list_item_1,audiofolder);
            AudioSelect.setAdapter(audiolist);
        }

        return v;
    }




}
