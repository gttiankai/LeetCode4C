//
// Created by tiankai on 19-5-5.
//

#include "libutils_hook.h"
#include "libxhook/xhook.h"
#include "debug.h"
#include "rc4.h"

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
    EGIS_DEBUG("length : %zu", length);
    EGIS_DEBUG("offset : %zu", offset);
    free(file_path);
    if (length == 4129 && offset == 16384) {
        int a = 2;
        int b = 2;
        int c = a /(2-2);
    }
    return mmap(addr, length, prot, flags, fd, offset);



//    EGIS_DEBUG("invoke mmap: offset %zu and length %zu", offset, length);
//    if (offset == 1019904 && length == 2694 && addr == NULL) {
//        EGIS_DEBUG("decrpt the file");
//        void *ptr = mmap(addr, length, prot | PROT_WRITE, MAP_PRIVATE, fd, offset);
//        EGIS_DEBUG("the baseptr: %p, ",(char*)ptr + 2472);
//        crypt((const u_char *) ((char*)ptr + 2472), (u_char *) ((char*)ptr + 2472), 222);
//        return ptr;
//    } else {
//        return mmap(addr, length, prot, flags, fd, offset);
//    }
}

typedef bool (*createType)(void *thiz,
                           const char *origFileName,
                           int fd,
                           off64_t offset,
                           size_t length,
                           bool readOnly);

createType create_function = NULL;

bool createFake(void *thiz,
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
        EGIS_DEBUG("the origFileName: %s", origFileName);
        EGIS_DEBUG("the offset: %lld", offset);
        EGIS_DEBUG("the length: %zu", length);
        return (*create_function)(thiz, origFileName, fd, offset, length, readOnly);
    } else {
        EGIS_ERROR("get the create function failed!");
        return false;
    }
}

void hookLibUtils() {

//    xhook_register("/system/lib/libutils.so",
//                   "mmap",
//                   (void *) mmapFake,
//                   NULL);
    // 4.2
    xhook_register("^/system/.*$",
                   "_ZN7android7FileMap6createEPKcixjb",
                   (void *) createFake,
                   (void **) &create_function);
}
