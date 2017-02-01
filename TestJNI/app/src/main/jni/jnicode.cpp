//
// Created by ADMIN on 28/01/2017.
//

#include <jni.h>
#include <android/log.h>



JavaVM *javaVM;
const char * className;

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    javaVM = vm;

    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    return JNI_VERSION_1_6;
}

//=========================================================================================
/// init
//=========================================================================================
extern "C"
JNIEXPORT void JNICALL Java_com_example_admin_testjni_NativeLib_init(JNIEnv *env, jobject obj)
{
    jclass cls = env->GetObjectClass(obj);

    jmethodID mid = env->GetMethodID(cls, "getClass", "()Ljava/lang/Class;");
    jobject clsObj = env->CallObjectMethod(obj, mid);

    cls = env->GetObjectClass(clsObj);
    mid = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
    jstring name = (jstring)env->CallObjectMethod(clsObj, mid);

    className = env->GetStringUTFChars(name, 0);
    env->ReleaseStringUTFChars(name, className);
}

//=========================================================================================
/// return class name
//=========================================================================================
extern "C"
JNIEXPORT jstring JNICALL Java_com_example_admin_testjni_NativeLib_getClassName(JNIEnv *env, jobject thiz)
{
    if(className)
        return env->NewStringUTF(className);

    return env->NewStringUTF("");
}

//=========================================================================================
/// access MainActivity fields
//=========================================================================================
extern "C"
JNIEXPORT void JNICALL Java_com_example_admin_testjni_NativeLib_accessFields(JNIEnv *env, jobject thiz, jobject activity)
{
    jclass cls = env->GetObjectClass(activity);

    jfieldID iID = env->GetFieldID(cls, "i", "I");
    int i = env->GetIntField(activity, iID);
    __android_log_print(ANDROID_LOG_DEBUG, "", "i value: %d", i);

    jfieldID sID = env->GetStaticFieldID(cls, "s", "Ljava/lang/String;");
    jstring s = (jstring)env->GetStaticObjectField(cls, sID);
    __android_log_print(ANDROID_LOG_DEBUG, "", "string: %s", env->GetStringUTFChars(s, 0));
}

extern "C"
JNIEXPORT void JNICALL Java_com_example_admin_testjni_NativeLib_passObjectToJNI(JNIEnv *env, jobject thiz, jobject jPoint)
{
    jclass cls = env->GetObjectClass(jPoint);

    jfieldID xID = env->GetFieldID(cls, "x", "I");
    jfieldID yID = env->GetFieldID(cls, "y", "I");

    int x = env->GetIntField(jPoint, xID);
    int y = env->GetIntField(jPoint, yID);

    __android_log_print(ANDROID_LOG_DEBUG, "", "x value: %d", x);
    __android_log_print(ANDROID_LOG_DEBUG, "", "x value: %d", y);
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_example_admin_testjni_NativeLib_returnObjectToJava(JNIEnv *env, jobject thiz)
{
    jobject jPoint;

    jclass cls = env->FindClass("com/example/admin/testjni/Point2D");
    jmethodID mID = env->GetMethodID(cls, "<init>", "(II)V");

    jPoint = env->NewObject(cls, mID, 3, 4);

    return jPoint;
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_example_admin_testjni_NativeLib_passObjectArrayToJNI(JNIEnv *env, jobject thiz, jobjectArray jArr)
{
    jsize arrSize = env->GetArrayLength(jArr);

    for(int i = 0; i < arrSize; i++)    {

        jobject jPoint = env->GetObjectArrayElement(jArr, i);
        jclass cls = env->GetObjectClass(jPoint);

        jfieldID xID = env->GetFieldID(cls, "x", "I");
        jfieldID yID = env->GetFieldID(cls, "y", "I");

        int x = env->GetIntField(jPoint, xID);
        int y = env->GetIntField(jPoint, yID);

        __android_log_print(ANDROID_LOG_DEBUG, "", "x value = %d", x);
        __android_log_print(ANDROID_LOG_DEBUG, "", "y value = %d", y);
        __android_log_print(ANDROID_LOG_DEBUG, "", "========================");
    }
}