LOCAL_PATH:= $(call my-dir)

# Qualcomm XML Files

include $(CLEAR_VARS)
LOCAL_MODULE       := dsi_config.xml
LOCAL_MODULE_TAGS  := optional eng
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES    := data/dsi_config.xml
LOCAL_MODULE_PATH  := $(TARGET_OUT_ETC)/data
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE       := netmgr_config.xml
LOCAL_MODULE_TAGS  := optional eng
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES    := data/netmgr_config.xml
LOCAL_MODULE_PATH  := $(TARGET_OUT_ETC)/data
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE       := qmi_config.xml
LOCAL_MODULE_TAGS  := optional eng
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES    := data/qmi_config.xml
LOCAL_MODULE_PATH  := $(TARGET_OUT_ETC)/data
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE       := pp_calib_data_auo_r61322_1080p_video_mode_dsi_panel.xml
LOCAL_MODULE_TAGS  := optional eng
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES    := pp_calib_data_auo_r61322_1080p_video_mode_dsi_panel.xml
LOCAL_MODULE_PATH  := $(TARGET_OUT_ETC)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE       := pp_calib_data_tianma_r63350_1080p_video_mode_dsi_panel.xml
LOCAL_MODULE_TAGS  := optional eng
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES    := pp_calib_data_tianma_r63350_1080p_video_mode_dsi_panel.xml
LOCAL_MODULE_PATH  := $(TARGET_OUT_ETC)
include $(BUILD_PREBUILT)
