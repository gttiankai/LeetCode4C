//
// Created by tiankai on 19-5-5.
//

#include <jni.h>
#include <cstddef>


#include "asset_hook.h"
#include "libxhook/xhook.h"
#include "debug.h"


typedef size_t(*readType)(void* thiz, void* buf, size_t count);
readType readFunction = NULL;

size_t readFake(void* thiz, void* buf, size_t count) {
    EGIS_DEBUG("invoke read");
    if (readFunction != NULL) {
        EGIS_DEBUG("the buf: %p, and the count: %zu", buf, count);
        return (*readFunction)(thiz, buf, count);
    } else {
        return 0;
    }
}



typedef void* (*getBufferType)(void * thiz,bool wordAligned);
getBufferType  getBuffer = NULL;

void* getBufferFake( void* thiz,bool wordAligned) {
    EGIS_DEBUG("invoke getBuffer");
    if (getBuffer != NULL) {
        return getBuffer(thiz, wordAligned);
    } else{
        EGIS_ERROR("getBuffer pointer failed");
        return NULL;
    }
}


void hookAsset() {

    xhook_register("/system/lib/libandroidfw.so",
                   "_ZN7android16_CompressedAsset4readEPvj",
                   (void *) readFake,
                   (void **) &readFunction);

    xhook_register("/system/lib/libandroidfw.so",
                   "_ZN7android16_CompressedAsset9getBufferEb",
                   (void *) getBufferFake,
                   (void **) &getBuffer);


}
