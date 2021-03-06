#================================================================#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#================================================================#

	include $(CLEAR_VARS)
	
	include OptionalComponentsDefined.mk

	LOCAL_MODULE 		:= moaiext-android
	LOCAL_ARM_MODE 		:= $(MY_ARM_MODE)
	LOCAL_CFLAGS		:= $(DISABLE_TAPJOY) $(DISABLE_NOTIFICATIONS) $(DISABLE_BILLING) $(DISABLE_CRITTERCISM) $(DISABLE_ADCOLONY)
	LOCAL_CFLAGS		+= -include $(MY_MOAI_ROOT)/src/zipfs/zipfs_replace.h

	LOCAL_C_INCLUDES 	:= $(MY_HEADER_SEARCH_PATHS)	
	LOCAL_SRC_FILES 	+= $(MY_MOAI_ROOT)/src/moaiext-android/MOAIAdColony.cpp
	LOCAL_SRC_FILES 	+= $(MY_MOAI_ROOT)/src/moaiext-android/MOAIApp.cpp
	LOCAL_SRC_FILES 	+= $(MY_MOAI_ROOT)/src/moaiext-android/MOAIBilling.cpp
	LOCAL_SRC_FILES 	+= $(MY_MOAI_ROOT)/src/moaiext-android/MOAICrittercism.cpp
	LOCAL_SRC_FILES 	+= $(MY_MOAI_ROOT)/src/moaiext-android/MOAIFacebook.cpp
	LOCAL_SRC_FILES 	+= $(MY_MOAI_ROOT)/src/moaiext-android/MOAINotifications.cpp
	LOCAL_SRC_FILES 	+= $(MY_MOAI_ROOT)/src/moaiext-android/MOAITapjoy.cpp

	include $(BUILD_STATIC_LIBRARY)