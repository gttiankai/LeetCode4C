//
// Created by tiankai on 19-4-26.
//

#ifndef JSTEST_ASSET_MANAGER_HOOK_H
#define JSTEST_ASSET_MANAGER_HOOK_H
typedef enum AccessMode {
    ACCESS_UNKNOWN = 0,

    /* read chunks, and seek forward and backward */
            ACCESS_RANDOM,

    /* read sequentially, with an occasional forward seek */
            ACCESS_STREAMING,

    /* caller plans to ask for a read-only buffer with all data */
            ACCESS_BUFFER,
} AccessMode;

void hookAssetManager();

#endif //JSTEST_ASSET_MANAGER_HOOK_H
