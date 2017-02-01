package com.example.admin.testjni;

import android.graphics.Point;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView textView;

    // these fields will be accessed from jni
    private int i = 0;
    private static String s = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initNativeLib();

        textView = (TextView) this.findViewById(R.id.text);

        passObjectArrayToJNI();
    }

    public void initNativeLib()
    {
        System.loadLibrary("native-lib");
        NativeLib.init();
    }

    public void passObjectToJNI()
    {
        NativeLib.passObjectToJNI(new Point2D(1, 2));
    }

    public void getPointFromJNI()
    {
        Point2D point = (Point2D)NativeLib.returnObjectToJava();
        Log.i("", "x value = " + point.x);
        Log.i("", "y value = " + point.y);
    }

    public void passObjectArrayToJNI()
    {
        Point2D [] points = {
                new Point2D(1, 2),
                new Point2D(3, 4),
                new Point2D(5, 6),
                new Point2D(7, 8)
        };

        NativeLib.passObjectArrayToJNI(points);
    }
}
