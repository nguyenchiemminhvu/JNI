package com.example.admin.testjni;

/**
 * Created by ADMIN on 28/01/2017.
 */

public class NativeLib {

    static  {
        System.loadLibrary("native-lib");
    }

    public static native void init();
    public static native String getClassName();

    public static native void accessFields(Object activity);

    public static native void passObjectToJNI(Point2D point);
    public static native Object returnObjectToJava();
}
