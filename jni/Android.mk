LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := android_ptrace
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := \
				android_ptrace.c\
				common.c
LOCAL_LDLIBS    := -llog 

include $(BUILD_SHARED_LIBRARY)

#for compiling the client, need to add the library as a dependency?
include $(CLEAR_VARS)
LOCAL_MODULE := ptrace_client
LOCAL_SRC_FILES := \
				ptrace_client.c\
				common.c

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
include $(BUILD_EXECUTABLE)

#for compiling the example
include $(CLEAR_VARS)
LOCAL_MODULE := ptrace
LOCAL_SRC_FILES := \
				ptrace.c

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
include $(BUILD_EXECUTABLE)

