//
// Created by tiankai on 19-4-18.
//
#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>

#include "libxhook/xhook.h"
#include "debug.h"
#include "asset_manager_hook.h"
#include "zip_utils_hook.h"
#include "asset_hook.h"
#include "libutils_hook.h"

static const char *mainClass = "payegis/com/jstest/MainActivity"; // path of Java file

#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))




int openFake(const char *pathname, int flags, mode_t mode) {
    EGIS_DEBUG("open pathname: %s", pathname);
    return open(pathname, flags, mode);
}


JNIEXPORT jstring JNICALL get_hello(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("hello from jni");
}


JNIEXPORT void JNICALL hookFunction(JNIEnv *env, jclass clazz) {
    (void) env;
    (void) clazz;

    xhook_enable_debug(1);
    xhook_enable_sigsegv_protection(0);

    hookLibUtils();
//    hookAssetManager();
//    hookAsset();

//    hookZipUtilsManager();

//    hookCompressedAssetManager();

    xhook_refresh(0);

}

static JNINativeMethod g_methods[] = {
        {"getHello",     "()Ljava/lang/String;", (void *) get_hello},
        {"hookFunction", "()V",                  (void *) hookFunction}
};


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = JNI_FALSE;

    //获取env指针
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    if (env == NULL) {
        return result;
    }
    //获取类引用，写类的全路径（包名+类名）。FindClass等JNI函数将在后面讲解
    jclass clazz = env->FindClass(mainClass);
    if (clazz == NULL) {
        return result;
    }
    //注册方法
    if (env->RegisterNatives(clazz, g_methods, NELEM(g_methods)) < 0) {
        return result;
    }
    //成功
    result = JNI_VERSION_1_6;
    return result;
}



