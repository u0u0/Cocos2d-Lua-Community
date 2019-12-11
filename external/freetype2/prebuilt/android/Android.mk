LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ext_freetype2
LOCAL_MODULE_FILENAME := freetype2
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libfreetype.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android \
                         $(LOCAL_PATH)/../../include/android/freetype2
include $(PREBUILT_STATIC_LIBRARY)
