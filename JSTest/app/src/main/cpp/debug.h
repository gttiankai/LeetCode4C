#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <android/log.h>

#define PAYEGIS_LOG_TAG "HookJNILog"

#define EGIS_INFO(fmt, args...)  do{ __android_log_print(ANDROID_LOG_ERROR, PAYEGIS_LOG_TAG, fmt, ##args); }while(0)

//#ifdef ENABLE_DEBUG
#define EGIS_DEBUG(fmt, args...)  do{ __android_log_print(ANDROID_LOG_DEBUG, PAYEGIS_LOG_TAG, fmt, ##args); }while(0)
#define EGIS_WARN(fmt, args...)  do{ __android_log_print(ANDROID_LOG_WARN, PAYEGIS_LOG_TAG, fmt, ##args); \
        __android_log_print(ANDROID_LOG_WARN, PAYEGIS_LOG_TAG, "at %s : %d", __FILE__ ,__LINE__);}while(0)
#define EGIS_ERROR(fmt, args...)  do{ __android_log_print(ANDROID_LOG_ERROR, PAYEGIS_LOG_TAG, fmt, ##args); \
        __android_log_print(ANDROID_LOG_ERROR, PAYEGIS_LOG_TAG, "at %s : %d", __FILE__ ,__LINE__);}while(0)
//#else
//#define EGIS_DEBUG(fmt, args...)  do{}while(0)
//#define EGIS_WARN(fmt, args...)  do{}while(0)
//#define EGIS_ERROR(fmt, args...)  do{}while(0)
//
//#endif

#endif /* end _DEBUG_H_*/
