LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ext_chipmunk
LOCAL_MODULE_FILENAME := chipmunk
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libchipmunk.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)
