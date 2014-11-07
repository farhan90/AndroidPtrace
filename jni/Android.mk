LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := android_ptrace
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := android_ptrace.c
LOCAL_LDLIBS    := -llog 

include $(BUILD_SHARED_LIBRARY)