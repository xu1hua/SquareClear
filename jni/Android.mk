LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/BackgroundLayer.cpp \
				   ../../../Classes/GamePlayLayer.cpp \
				   ../../../Classes/GamePlayScene.cpp \
				   ../../../Classes/MainMenuLayer.cpp \
				   ../../../Classes/MainMenuScene.cpp \
				   ../../../Classes/MapMakerScene.cpp \
				   ../../../Classes/Square.cpp \
				   ../../../Classes/SquareBaseplateLayer.cpp \
				   ../../../Classes/SquareGroup.cpp \
				   ../../../Classes/Sqlite3Database/CppSQLite3.cpp \
				   ../../../Classes/Sqlite3Database/CppSQLite3Table.cpp \
				   ../../../Classes/Sqlite3Database/CppSQLite3Query.cpp \
				   ../../../Classes/Sqlite3Database/CppSQLite3Statement.cpp \
				   ../../../Classes/Sqlite3Database/CppSQLite3DB.cpp \
				   ../../../Classes/Library/sqlite/sqlite3.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../cocos2d/cocos/storage/local-storage
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/Sqlite3Database
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/Library/sqlite

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_localstorage_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,storage/local-storage)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
