//
// Created by tiankai on 19-4-26.
//

#include <jni.h>
#include <string>


#include "asset_manager_hook.h"
#include "libxhook/xhook.h"
#include "debug.h"


typedef void *(*openAssetFromZipLockedType)(void *thiz,
                                            void *pZipFile,
                                            void *entry,
                                            AccessMode mode,
                                            void *entryName);

openAssetFromZipLockedType openAssetFromZipLocked = NULL;

void *openAssetFromZipLockedFake(void *thiz,
                                 void *pZipFile,
                                 void *entry,
                                 AccessMode mode,
                                 void *entryName) {
    EGIS_DEBUG("invoke openAssetFromZipLocked ");
    EGIS_DEBUG("the entry name: %s", (const char *) entryName);
    if (openAssetFromZipLocked != NULL) {
        return (*openAssetFromZipLocked)(thiz, pZipFile, entry, mode, entryName);
    } else {
        EGIS_ERROR("can not get openAssetFromZipLocked");
        return NULL;
    }
}


typedef void *(*openNonAssetInPathLockedType)(
                                              const char *fileName,
                                              AccessMode mode,
                                              void *ap);

openNonAssetInPathLockedType openNonAssetInPathLocked = NULL;

void* openNonAssetInPathLockedFake( const char *fileName, AccessMode mode, void *ap) {
    EGIS_DEBUG("invoke openNonAssetInPathLocked");
    EGIS_DEBUG("the fileName %s", fileName);
    if (openNonAssetInPathLocked != NULL) {
        return (*openNonAssetInPathLocked)(fileName, mode, ap);
    } else {
        EGIS_ERROR("can not get openNonAssetInPathLocked");
        return NULL;
    }
}

void hookAssetManager() {

//    xhook_register("/system/lib/libandroidfw.so",
//                   "_ZN7android12AssetManager22openAssetFromZipLockedEPKNS_9ZipFileROEPvNS_5Asset10AccessModeERKNS_7String8E",
//                   (void *) openAssetFromZipLockedFake,
//                   (void **) &openAssetFromZipLocked);

    xhook_register("/system/lib/libandroidfw.so",
                   "_ZN7android12AssetManager24openNonAssetInPathLockedEPKcNS_5Asset10AccessModeERKNS0_10asset_pathE",
                   (void *) openNonAssetInPathLockedFake,
                   (void **) &openNonAssetInPathLocked);

}
