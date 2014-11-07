#include <string.h>
#include <jni.h>
#include  <stdio.h>
#include  <stdlib.h>

/**
 * This is the shared library for putting all the ptrace code needed for the Android application.
 *
 */



/**
 * This method shows how to call native code from the application, returns a string
 */
jstring
Java_com_example_androidptrace_MainActivity_stringTest( JNIEnv* env,
                                                  jobject thiz )
{
	return (*env)->NewStringUTF(env, "Hello from JNI !");
}
