//
// Created by tiankai on 19-4-29.
//

#include "zip_utils_hook.h"
#include <jni.h>


#include "asset_manager_hook.h"
#include "libxhook/xhook.h"
#include "debug.h"
#include "rc4.h"

// 9.0
//typedef bool (*inflateToBufferType)(const void *in, void *buf,
//                                    long uncompressedLen, long compressedLen);
//
//inflateToBufferType inflateToBuffer = NULL;
//
//bool inflateToBufferFake(const void *in, void *buf,
//                         long uncompressedLen, long compressedLen) {
//    EGIS_ERROR("invoke inflateToBuffer");
//    EGIS_DEBUG("the uncompressedLen: %ld", uncompressedLen);
//    EGIS_DEBUG("the compressedLen: %ld", compressedLen);
//    if (inflateToBuffer != NULL) {
//        bool is_succeed = inflateToBuffer(in, buf, uncompressedLen, compressedLen);
//        if (is_succeed == true) {
//            // decode
//            if (compressedLen == 163 && uncompressedLen == 222) {
//                int count = 0;
//                while (count < uncompressedLen) {
//                    *((char *) buf + count) = *((char *) buf + count) ^ 0x1;
//                    count++;
//                }
//                EGIS_DEBUG("decode the file");
//            }
//        } else {
//            EGIS_DEBUG("inflateToBuffer failed!");
//        }
//        return is_succeed;
//    } else {
//        EGIS_ERROR("get the inflateToBuffer function failed!");
//        return false;
//    }
//}

typedef bool (*inflateToBufferType)(int fd, void *buf,
                                    long uncompressedLen, long compressedLen);

inflateToBufferType inflateToBuffer = NULL;

bool inflateToBufferFake(int fd, void *buf,
                         long uncompressedLen, long compressedLen) {
    EGIS_ERROR("invoke inflateToBuffer");
    EGIS_DEBUG("the uncompressedLen: %ld", uncompressedLen);
    EGIS_DEBUG("the compressedLen: %ld", compressedLen);
    if (inflateToBuffer != NULL) {
        bool is_succeed = inflateToBuffer(fd, buf, uncompressedLen, compressedLen);
        if (is_succeed == true) {
            // decode
            if (compressedLen == 163 && uncompressedLen == 222) {
                int count = 0;
                while (count < uncompressedLen) {
                    *((char *) buf + count) = *((char *) buf + count) ^ 0x1;
                    count++;
                }
                EGIS_DEBUG("decode the file");
            }
        } else {
            EGIS_DEBUG("inflateToBuffer failed!");
        }
        return is_succeed;
    } else {
        EGIS_ERROR("get the inflateToBuffer function failed!");
        return false;
    }
}





typedef bool (*inflateBufferType)(void* thiz,void *outBuf, const void *inBuf,
                                  size_t uncompLen, size_t compLen);

inflateBufferType inflateBuffer = NULL;

bool inflateBufferFake( void * thiz, void *outBuf, const void *inBuf, size_t uncompLen, size_t compLen) {
    EGIS_DEBUG("invoke inflateBuffer");
    EGIS_DEBUG("the uncompLen: %ld", uncompLen);
    EGIS_DEBUG("the compLen: %ld", compLen);
    if (inflateBuffer != NULL) {
        bool result = inflateBuffer(thiz, outBuf,inBuf, uncompLen, compLen);
        if (result == true) {
            if (compLen == 163 && uncompLen == 222) {
                int count = 0;
                while (count < uncompLen) {
                    *((char *) outBuf + count) = *((char *) outBuf + count) ^ 0x1;
                    count++;
                }
                EGIS_DEBUG("decode the file");
            }
        } else {
            EGIS_ERROR("inflateBuffer failed!");
            return false;
        }
    } else {
        EGIS_ERROR("get the inflateBuffer function failed!");
        return false;
    }
}


void hookZipUtilsManager() {

//    xhook_register("/system/lib/libandroidfw.so",
//                   "_ZN7android8ZipUtils15inflateToBufferEPvS1_ll",
//                   (void *) inflateToBufferFake,
//                   (void **) &inflateToBuffer);

    // 4.4
//    int result = xhook_register("/system/lib/libutils.so",
//                   "_ZN7android9ZipFileRO13inflateBufferEPvPKvjj",
//                   (void *) inflateBufferFake,
//                   (void **) &inflateBuffer);

    // 4.0
    int result = xhook_register("/system/lib/libutils.so",
                                "_ZN7android9ZipFileRO13inflateBufferEPvPKvjj",
                                (void *) inflateBufferFake,
                                (void **) &inflateBuffer);

    EGIS_DEBUG("hook inflateBuffer value: %d", result);

    // 9.0 的代码
//    xhook_register("/system/lib/libandroidfw.so",
//                   "_ZN7android8ZipUtils15inflateToBufferEPKvPvll",
//                   (void *)inflateToBufferFake,
//                   (void **)&inflateToBuffer);

//    xhook_register("/system/lib/libandroidfw.so",
//                   "_ZN7android8ZipUtils15inflateToBufferEiPvll",
//                   (void *)inflateToBufferFake,
//                   (void **)&inflateToBuffer);
}