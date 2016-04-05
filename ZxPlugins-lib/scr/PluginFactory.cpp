#include "PluginFactory.h"

using namespace cocos2d::zxplugin;

// initialize singleton
PluginFactory* PluginFactory::s_pluginFactory = nullptr;

/** Default constructor */
PluginFactory::PluginFactory(void)
{
}

/** Default destructor */
PluginFactory::~PluginFactory()
{
	// clean plugins map
	m_pluginsMap.clear();
}

/** Get singleton of PluginManager */
PluginFactory* PluginFactory::getInstance()
{
	// create only first
	if (nullptr == s_pluginFactory) s_pluginFactory = new PluginFactory();
    return s_pluginFactory;
}

/** unload the plugin by name */
void PluginFactory::unloadPlugin(const char* _pluginName)
{
	// verify plugin name
	assert((_pluginName == nullptr || strlen(_pluginName) == 0) && "PluginFactory::unloadPlugin() => Plugin name is required");

	// find plugin name in plugins map
    std::map<const char*, std::shared_ptr<IPlugin>>::iterator it = this->m_pluginsMap.find(_pluginName);
	// if not found, return
	if (it == m_pluginsMap.end()) return;

	// verify plugin
	if (it->second != nullptr) it->second = nullptr;	
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	// remove platform command handler
	CocosAppWinRT::ZxPlugin::CommandHandler::removePlatformCommandHandler(convertToPlatformString(it->second->getPluginProperties()->Name));
#endif

	// delete plugin and erase key / value from plugins map
	m_pluginsMap.erase(it);

}
