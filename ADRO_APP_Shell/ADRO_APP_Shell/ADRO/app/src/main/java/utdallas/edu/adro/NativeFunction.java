package utdallas.edu.adro;

public class NativeFunction {
    static {
        System.loadLibrary("ADRO");
    }
    public static native void NativeInit(int samplerate, int buffersize);
    public static native void NativePlayerInit(int samplerate, int buffersize);

    public static native void OpenFile(String path);
    public static native void setPreset(float[] presetarray);
    public static native float[] getAudiogram();
    public static native float[] getComfortTarget();

    public static native float[] getHighPercentile();

    public static native float[] getMidPercentile();
    public static native float[] getMOL();
    public static native float[] EuDistance();
    public static native float[] ADROGain();
    public static native void onForeground();
    public static native void onBackground();
    public static native void Cleanup();
    public static native void EnableADRO(int onoff);
    public static native void EnableDataStore(int onoff);
    public static native boolean getEnableData();
    public static native boolean isplaying();

    public static native void setDataName(String filename);
    public static native String getDataName();
    public static native float getframetime();
}
