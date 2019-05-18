//
// Created by tiankai on 19-4-18.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <jni.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include "libxhook/xhook.h"
#include "debug.h"

static const char *mainClass = "payegis/com/jstest/MainActivity"; // path of Java file

#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

typedef void *(*MMAP_FUNCTION_POINTER)(void *addr, size_t length, int prot, int flags,
                                       int fd, off_t offset);

MMAP_FUNCTION_POINTER mmap_function_pointer = NULL;


typedef bool (*CREATE_FUNCTION)(void *this,
                                const char *origFileName,
                                int fd,
                                off64_t offset,
                                size_t length,
                                bool readOnly);

CREATE_FUNCTION create_function = NULL;

bool createFake(void *this,
                const char *origFileName,
                int fd,
                off64_t offset,
                size_t length,
                bool readOnly) {
    EGIS_DEBUG("invoke create function");
    if (create_function != NULL) {
        EGIS_DEBUG("invoke fake create function");
        EGIS_DEBUG("the create funciton: %p", create_function);
        EGIS_DEBUG("the create fake function: %p", createFake);
        EGIS_DEBUG("the origFileName: %s" , origFileName);
        return (*create_function)(this, origFileName, fd, offset, length, readOnly);
    } else {
        EGIS_ERROR("get the create function failed!");
        return false;
    }
};


JNIEXPORT jstring JNICALL get_hello(JNIEnv *env, jclass clazz) {
    return (*env)->NewStringUTF(env, "hello from jni");
}

int openFake(const char *pathname, int flags, mode_t mode) {
    EGIS_DEBUG("open pathname: %s", pathname);
    return open(pathname, flags, mode);
}

void getFileName(int fd, char *file_path) {
    char buf[1024] = {'\0'};
    snprintf(buf, sizeof(buf), "/proc/self/fd/%d", fd);
    readlink(buf, file_path, 1023);
}

/**
 * 可以先使用fd和offset，进行过滤，来判断，是否需要解密，其中如果offset是固定的话，可以直接存储起来。减少运行时间。
 * */
void *mmapFake(void *addr, size_t length, int prot, int flags,
               int fd, off_t offset) {
    char *file_path = (char *) calloc(1024, sizeof(char));
    if (NULL == file_path) {
        EGIS_ERROR("calloc memory failed");
        return mmap(addr, length, prot, flags, fd, offset);
    }
    getFileName(fd, file_path);
    EGIS_DEBUG("mmap the file : %s", file_path);
    EGIS_DEBUG("mmap: offset %d and length %zu", offset, length);
    if (mmap_function_pointer != NULL) {
        if (length == 747 && offset == 126976) {
            EGIS_DEBUG("Get the need file to decrypt");
            return (*mmap_function_pointer)(addr, length, prot | PROT_WRITE, MAP_PRIVATE, fd,
                                            offset);
        } else {
            return (*mmap_function_pointer)(addr, length, prot, flags, fd, offset);
        }
    } else {
        EGIS_ERROR("the mmap function pointer is NULL!");
        if (length == 747 && offset == 126976) {
            EGIS_DEBUG("Get the need file to decrypt");
            return mmap(addr, length, prot | PROT_WRITE, MAP_PRIVATE, fd, offset);
        } else {
            return mmap(addr, length, prot, flags, fd, offset);
        }
    }

}


JNIEXPORT void JNICALL hookFunction(JNIEnv *env, jclass clazz) {
    (void) env;
    (void) clazz;

    xhook_enable_debug(1);
    //xhook_register("/system/lib/libutils.so", "mmap", mmapFake, &mmap_function_pointer);
    xhook_register("/system/lib/libandroidfw.so", "_ZN7android7FileMap6createEPKcixjb",
                   createFake, &create_function);
    xhook_refresh(0);
    EGIS_DEBUG("xhook_register values succeed!");
    // int result = xhook_register("^/system/.*\\.so$", "mmap", mmapFake, NULL);
    //xhook_register("^/vendor/.*\\.so$",  "__android_log_print", my_system_log_print,  NULL);
    //xhook_register(".*/libtest\\.so$", "__android_log_print", my_libtest_log_print, NULL);

    //just for testing
//    xhook_ignore(".*/liblog\\.so$",
//                 "__android_log_print"); //ignore __android_log_print in liblog.so
//    xhook_ignore(".*/libjavacore\\.so$", NULL); //ignore all hooks in libjavacore.so

}

static JNINativeMethod g_methods[] = {
        {"getHello",     "()Ljava/lang/String;", (void *) get_hello},
        {"hookFunction", "()V",                  (void *) hookFunction}
};

static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,

                                 int numMethods) {
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_ERR;
    }

    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_ERR;
    }

    return JNI_TRUE;
}


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    assert(env != NULL);

    if (!registerNativeMethods(env, mainClass, g_methods, NELEM(g_methods))) {
        return JNI_ERR;
    }
    result = JNI_VERSION_1_6;

    return result;
}


