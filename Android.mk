LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := libthpool
LOCAL_CFLAGS += -fblocks
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/blocksruntime 

LOCAL_SRC_FILES	 := \
	blocksruntime/BlocksRuntime/data.c \
	blocksruntime/BlocksRuntime/runtime.c \
	thpool.c 
include $(BUILD_SHARED_LIBRARY)

