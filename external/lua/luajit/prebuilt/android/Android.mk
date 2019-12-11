LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := ext_luajit
LOCAL_MODULE_FILENAME := libluajit
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libluajit.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)
