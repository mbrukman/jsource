
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := tsdll
LOCAL_MODULE_FILENAME    := libtsdll

LOCAL_LDLIBS := -lc

ifeq ($(TARGET_ARCH),arm)
  ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS := -fPIC -O1 -Werror -fno-strict-aliasing -fsigned-char -DC_64=0 -DC_CD_ARMEL -mfloat-abi=softfp -mfpu=vfpv3-d16 -march=armv7-a
    LOCAL_ARM_MODE := arm
  else
    LOCAL_CFLAGS := -fPIC -O1 -Werror -fno-strict-aliasing -fsigned-char -DC_64=0 -DC_CD_ARMEL -mfloat-abi=softfp -mfpu=vfp -march=armv6
    LOCAL_ARM_MODE := arm
  endif
endif
ifeq ($(TARGET_ARCH),x86)
  LOCAL_CFLAGS := -fPIC -O1 -Werror -fno-strict-aliasing -DC_64=0 -malign-double -msse3 -mfpmath=sse
endif

LOCAL_SRC_FILES :=  tsdll.c

include $(BUILD_SHARED_LIBRARY)
