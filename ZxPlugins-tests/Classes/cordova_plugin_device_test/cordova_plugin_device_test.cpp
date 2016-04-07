#include "cordova_plugin_device_test.h"

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "ZxPlugins-lib\scr\PluginFactory.h"
#include "Plugins/cordova-plugin-device/proxy/Device.h"
#endif

using namespace cocos2d;

/** Constructor por defecto de la clase */
cordova_plugin_device_test::cordova_plugin_device_test(void)
{
}

/** Destructor por defecto de la clase */
cordova_plugin_device_test::~cordova_plugin_device_test(void)
{
}

/**
* Metodo sobreescrito que sera invocado para inicializar la instancia de la clase
* @return True si se puede ha inicializado correctamente, false en caso contrario
*/
bool cordova_plugin_device_test::init()
{
	// Inicializar el padre primero
	if (!Layer::init()) return false;

	// Inicializar clase
	this->m_deviceDataText = ui::Text::create("Get device data ...", "Arial", 15);
	this->m_deviceDataText->setColor(Color3B(159, 168, 176));
	this->m_deviceDataText->setPosition(Vec2(10.0f, Director::getInstance()->getWinSize().height - 40.0f));
	this->m_deviceDataText->setAnchorPoint(Vec2(.0f, .0f));
	
	this->addChild(this->m_deviceDataText);
	
	// .......

	// execute test
	this->execute();

	// inicializacion correcta
	return true;
}

void doTestCPP(JNIEnv* e, jobject o) 
{
	log("C++callback activated");
	jfieldID f_uid = e->GetFieldID(e->GetObjectClass(o), "uid", "I");
	if (f_uid) log("UID data member: ");// +std::string(e->GetIntField(o, f_uid)));
	else log("UID not found");
}

bool cordova_plugin_device_test::execute()
{
	// http://www.codeproject.com/Articles/993067/Calling-Java-from-Cplusplus-with-JNI
	// http://stnguyen.com/cocos2d-x/call-java-functions-from-cpp.html
	// http://www.cocos2d-x.org/wiki/User_Tutorial-Call_Java_functions_in_Cocos2d-x
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// invoke native code
	//this->exec(_successCallback, _errorCallback, "Device", "getDeviceInfo", "[]");

	auto env = cocos2d::JniHelper::getEnv();

	// try to find the class
	jclass javaClass = env->FindClass("org/cocos2dx/zxplugin/CommandHandler");  
	if (javaClass == nullptr) 
	{
		log("ERROR: class not found !");
	}
	else 
	{   
		// if class found, continue
		log("Class MyTest found");

		JNINativeMethod methods[]{ { "doTest", "()V", (void *)&doTestCPP } };  // mapping table

		if (env->RegisterNatives(javaClass, methods, 1) < 0)
		{                        // register it
			if (env->ExceptionOccurred())                                        // verify if it's ok
				log("OOOOOPS: exception when registreing naives");
			else
				log("ERROR: problem when registreing naives");
		}

	}

	// create obj
	jmethodID ctor = env->GetMethodID(javaClass, "<init>", "()V");  // FIND AN OBJECT CONSTRUCTOR
	if (ctor == nullptr) 
	{
		log("ERROR: constructor not found !");
	}
	else 
	{
		log("Object succesfully constructed !");
		jobject myo = env->NewObject(javaClass, ctor);

		// invoke method
		if (myo)
		{
			jmethodID show = env->GetMethodID(javaClass, "showId", "()V");
			if (show == nullptr) log("No showId method !!");
			else env->CallVoidMethod(myo, show);
		}

	}

	//cocos2d::JniMethodInfo methodInfo;

	//if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "alertJNI", "()Ljava/lang/String;")) {
	//	return true;
	//}
	//
	//jstring s = (jstring)methodInfo.env->CallObjectMethod(methodInfo.classID, methodInfo.methodID);
	//std::string str = JniHelper::jstring2string(s);
	//methodInfo.env->DeleteLocalRef(methodInfo.classID);
//#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

	// test plugin
	 cocos2d::zxplugin::cordova_plugin_device::Device* devicePlugin = cocos2d::zxplugin::PluginFactory::getInstance()->loadPlugin<cocos2d::zxplugin::cordova_plugin_device::Device>("cordova-plugin-device");
	 auto a = devicePlugin->getPluginProperties();


	 devicePlugin->getInfo(
	 [&](const std::string& _result)
	 {
		 this->m_deviceDataText->setString("OK");
	 },
	 [&](const std::string& _error) 
	 {
		 this->m_deviceDataText->setString(_error);
	 });

#endif

	return true;
}