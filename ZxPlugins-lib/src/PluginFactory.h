#ifndef __ZXPLUGIN_PLUGINFACTORY_H__
#define __ZXPLUGIN_PLUGINFACTORY_H__

#include "IPlugin.h"

#include <assert.h>
#include <map>
#include <string>
#include <type_traits> 

namespace cocos2d { namespace zxplugin {

/**
 * class for manage cocos2dx zxplugins
*/
class PluginFactory
{

public:

	/** Default destructor */
	virtual ~PluginFactory();

	/** @brief Constructor copia, es eliminado para no poder copiar el objeto */
	PluginFactory(const PluginFactory &obj) = delete;
	/** @brief Operador de asignacion, es eliminado para no poder asignar el objeto */
	PluginFactory &operator=(const PluginFactory &obj) = delete;

	/** Get singleton of PluginFactory 
	 * @return Unique instance of PluginFactory
	 */
    static PluginFactory* getInstance();

	/** load plugin by name
	 * @param _pluginName unique name for plugin identity
	 * @return plugin loaded
	 */
	template<class TPlugin>
	TPlugin* loadPlugin(const char* _pluginName)
	{
		// verify IPlugin inheritance
		static_assert(std::is_base_of<IPlugin, TPlugin>::value, "PluginFactory::loadPlugin() => TPlugin don´t inherit from IPlugin"); 

		// verify plugin name
		assert((_pluginName != nullptr && strlen(_pluginName) != 0) && "PluginFactory::loadPlugin() => Plugin name is required");

		// result
		TPlugin* plugin = nullptr;

		// find plugin name in plugins map
		std::map<const char*, IPlugin*>::iterator it = m_pluginsMap.find(_pluginName);
		// found
		if (it != m_pluginsMap.end())
		{
			// verify plugin pointer, create if not found and insert in plugins map
			if (it->second == nullptr) it->second = new TPlugin();
			assert((plugin != (TPlugin*)it->second) && "PluginFactory::loadPlugin() => Already plugin loaded with other type.");
		}
		// not found. create plugin and insert in plugin map
		else
		{
        	plugin = new TPlugin();
        	m_pluginsMap[_pluginName] = plugin;
		}
		
		// return loaded plugin
		return plugin;
	}

    /** unload the plugin by name 
	* @param _pluginName plugin name for unload
	*/
    void unloadPlugin(const char* _pluginName);

private:

	/** Default constructor  */
	PluginFactory();     

	/** Map of loaded plugins */
    std::map<const char*, IPlugin*> m_pluginsMap;

	/** singleton instance */
	static PluginFactory* s_pluginFactory;
};


}} //namespace cocos2d { namespace zxplugin {

#endif /* __ZXPLUGIN_PLUGINFACTORY_H__ */
