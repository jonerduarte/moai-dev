// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef DISABLE_FACEBOOK

#include "pch.h"

#include <jni.h>

#include <moaiext-android/moaiext-jni.h>
#include <moaiext-android/MOAIFacebook.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
cc8* MOAIFacebook::_luaParseTable ( lua_State* L, int idx ) {

	switch ( lua_type ( L, idx )) {

		case LUA_TSTRING: {

			cc8* str = lua_tostring ( L, idx );
			return str;
		}
	}

	return NULL;
}

//----------------------------------------------------------------//
int MOAIFacebook::_getToken ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	JNI_GET_ENV ( jvm, env );
	
	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {
	
		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {
	
    	jmethodID getToken = env->GetStaticMethodID ( facebook, "getToken", "()Ljava/lang/String;" );
   		if ( getToken == NULL ) {
	
			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "getToken" );
		} else {
	
			jstring jtoken = ( jstring )env->CallStaticObjectMethod ( facebook, getToken );
			
			JNI_GET_CSTRING ( jtoken, token );

			lua_pushstring ( state, token );
			
			JNI_RELEASE_CSTRING ( jtoken, token );
			
			return 1;
		}
	}
	
	lua_pushnil ( state );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFacebook::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* identifier = lua_tostring ( state, 1 );
	
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( identifier, jidentifier );
	
	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {
	
		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {
	
    	jmethodID init = env->GetStaticMethodID ( facebook, "init", "(Ljava/lang/String;)V" );
   		if ( init == NULL ) {
	
			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "init" );
		} else {
	
			env->CallStaticVoidMethod ( facebook, init, jidentifier );		
		}
	}
	
	return 0;
}
		
//----------------------------------------------------------------//
int MOAIFacebook::_login ( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	JNI_GET_ENV ( jvm, env );
	
	jobjectArray jpermissions = NULL;
	
	if ( state.IsType ( 1, LUA_TTABLE )) {
	
		int numEntries = 0;
		for ( int key = 1; ; ++key ) {
	
			state.GetField ( 1, key );
			cc8* value = _luaParseTable ( state, -1 );
			lua_pop ( state, 1 );
	
			if ( !value ) {
				
				numEntries = key - 1;
				break;
			}
		}
	
		jpermissions = env->NewObjectArray ( numEntries, env->FindClass( "java/lang/String" ), 0 );
		for ( int key = 1; ; ++key ) {
	
			state.GetField ( 1, key );
			cc8* value = _luaParseTable ( state, -1 );
			lua_pop ( state, 1 );
	
			if ( value ) {
				
				JNI_GET_JSTRING ( value, jvalue );
				env->SetObjectArrayElement ( jpermissions, key - 1, jvalue );
			}
			else {
				
				break;
			}	
		}
	}
	
	if ( jpermissions == NULL ) {
		
		jpermissions = env->NewObjectArray ( 0, env->FindClass( "java/lang/String" ), 0 );
	}
	
	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {

		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {

    	jmethodID login = env->GetStaticMethodID ( facebook, "login", "([Ljava/lang/String;)V" );
    	if ( login == NULL ) {

			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "login" );
    	} else {

			env->CallStaticVoidMethod ( facebook, login, jpermissions );				
		}
	}
		
	return 0;
}

//----------------------------------------------------------------//
int MOAIFacebook::_logout ( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	JNI_GET_ENV ( jvm, env );
	
	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {
	
		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {
	
    	jmethodID logout = env->GetStaticMethodID ( facebook, "logout", "()V" );
   		if ( logout == NULL ) {
	
			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "logout" );
		} else {
	
			env->CallStaticVoidMethod ( facebook, logout );		
		}
	}

	return 0;
}

//----------------------------------------------------------------//
int MOAIFacebook::_postToFeed ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* link = lua_tostring ( state, 1 );
	cc8* picture = lua_tostring ( state, 2 );
	cc8* name = lua_tostring ( state, 3 );
	cc8* caption = lua_tostring ( state, 4 );
	cc8* description = lua_tostring ( state, 5 );
	cc8* message = lua_tostring ( state, 6 );
	
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( link, jlink );
	JNI_GET_JSTRING ( picture, jpicture );
	JNI_GET_JSTRING ( name, jname );
	JNI_GET_JSTRING ( caption, jcaption );
	JNI_GET_JSTRING ( description, jdescription );
	JNI_GET_JSTRING ( message, jmessage );
	
	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {
	
		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {
	
    	jmethodID postToFeed = env->GetStaticMethodID ( facebook, "postToFeed", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
   		if ( postToFeed == NULL ) {
	
			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "postToFeed" );
		} else {
	
			env->CallStaticVoidMethod ( facebook, postToFeed, jlink, jpicture, jname, jcaption, jdescription, jmessage );	
		}
	}
		
	return 0;
}

//----------------------------------------------------------------//
int MOAIFacebook::_sendRequest ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* message = lua_tostring ( state, 1 );
	
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( message, jmessage );
	
	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {
	
		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {
	
    	jmethodID sendRequest = env->GetStaticMethodID ( facebook, "sendRequest", "(Ljava/lang/String;)V" );
   		if ( sendRequest == NULL ) {
	
			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "sendRequest" );
		} else {
	
			env->CallStaticVoidMethod ( facebook, sendRequest, jmessage );		
		}
	}
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIFacebook::_sessionValid ( lua_State* L ) {

	MOAILuaState state ( L );

	JNI_GET_ENV ( jvm, env );

	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {

		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {

    	jmethodID isSessionValid = env->GetStaticMethodID ( facebook, "isSessionValid", "()Z" );
    	if ( isSessionValid == NULL ) {

			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "isSessionValid" );
    	} else {

			jboolean jvalid = ( jboolean )env->CallStaticBooleanMethod ( facebook, isSessionValid );	

			lua_pushboolean ( state, jvalid );

			return 1;
		}
	}

	lua_pushboolean ( state, false );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFacebook::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );

	if ( idx < TOTAL ) {
		
		MOAIFacebook::Get ().mListeners [ idx ].SetStrongRef ( state, 2 );
	}
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIFacebook::_setToken ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* token = lua_tostring ( state, 1 );
	
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( token, jtoken );
	
	jclass facebook = env->FindClass ( "com/ziplinegames/moai/MoaiFacebook" );
    if ( facebook == NULL ) {
	
		USLog::Print ( "MOAIFacebook: Unable to find java class %s", "com/ziplinegames/moai/MoaiFacebook" );
    } else {
	
    	jmethodID setToken = env->GetStaticMethodID ( facebook, "setToken", "(Ljava/lang/String;)V" );
   		if ( setToken == NULL ) {
	
			USLog::Print ( "MOAIFacebook: Unable to find static java method %s", "setToken" );
		} else {
	
			env->CallStaticVoidMethod ( facebook, setToken, jtoken );		
		}
	}
	
	return 0;
}

//================================================================//
// MOAIFacebook
//================================================================//

//----------------------------------------------------------------//
MOAIFacebook::MOAIFacebook () {

	RTTI_SINGLE ( MOAILuaObject )	
}

//----------------------------------------------------------------//
MOAIFacebook::~MOAIFacebook () {

}

//----------------------------------------------------------------//
void MOAIFacebook::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "DIALOG_DID_COMPLETE",		( u32 ) DIALOG_DID_COMPLETE );
	state.SetField ( -1, "DIALOG_DID_NOT_COMPLETE",	( u32 ) DIALOG_DID_NOT_COMPLETE );
	state.SetField ( -1, "SESSION_DID_LOGIN",		( u32 ) SESSION_DID_LOGIN );
	state.SetField ( -1, "SESSION_DID_NOT_LOGIN",	( u32 ) SESSION_DID_NOT_LOGIN );
	
	luaL_Reg regTable [] = {
		{ "getToken",		_getToken },
		{ "init",			_init },
		{ "login",			_login },
		{ "logout",			_logout },
		{ "postToFeed",		_postToFeed },
		{ "sendRequest",	_sendRequest },
		{ "sessionValid",	_sessionValid },
		{ "setListener",	_setListener },
		{ "setToken",		_setToken },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFacebook::NotifyLoginComplete ( int code ) {

	MOAILuaRef& callback = this->mListeners [ SESSION_DID_NOT_LOGIN ];
	if ( code == DIALOG_RESULT_SUCCESS ) {
		
		callback = this->mListeners [ SESSION_DID_LOGIN ];
	}

	if ( callback ) {
	
		MOAILuaStateHandle state = callback.GetSelf ();
	
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebook::NotifyDialogComplete ( int code ) {
	
	MOAILuaRef& callback = this->mListeners [ DIALOG_DID_NOT_COMPLETE ];
	if ( code == DIALOG_RESULT_SUCCESS ) {
		
		callback = this->mListeners [ DIALOG_DID_COMPLETE ];
	}

	if ( callback ) {
	
		MOAILuaStateHandle state = callback.GetSelf ();
	
		state.DebugCall ( 0, 0 );
	}
}

//================================================================//
// Facebook JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiFacebook_AKUNotifyFacebookLoginComplete ( JNIEnv* env, jclass obj, jint code ) {

	MOAIFacebook::Get ().NotifyLoginComplete ( code );
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiFacebook_AKUNotifyFacebookDialogComplete ( JNIEnv* env, jclass obj, jint code ) {

	MOAIFacebook::Get ().NotifyDialogComplete ( code );
}

#endif