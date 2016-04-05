#include "cordova_plugin_device_test.h"

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

bool cordova_plugin_device_test::execute()
{

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