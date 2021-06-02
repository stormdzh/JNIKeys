package com.pinery.jni;

import android.content.Context;

/**
 * @Description: 描述
 * @Author: dzh
 * @CreateDate: 2021/6/2 1:50 PM
 */
class KeyStore {

    static {
        System.loadLibrary("native-lib");
    }

    public native String getSignKey(Context context,boolean debug);

}
