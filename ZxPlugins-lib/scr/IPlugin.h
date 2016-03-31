#ifndef __ZXPLUGIN_IPLUGIN_H__
#define __ZXPLUGIN_IPLUGIN_H__

#include <memory>
#include <functional>
#include "PlatformHelpers.h"

namespace cocos2d { 
	namespace zxplugin {

		/**
		@brief Plugin properties model	
		*/
		struct PluginPropertiesModel
		{
			/** Get flag telling if wrap cordova plugin = true, false if not wrap cordova plugin
			* @return ZxPlugin author
			* @remarks This ZxPlugin author
			*/
			bool WrapCordovaPlugin;

			/** Get plugin name
			* @return unique name for plugin identity (shoud be unique on all plugins)
			* @remarks If wrap cordova plugin, the plugin name must be obtained from original plugin file "plugin.xml" or "package.json"
			*/
			const char* Name;

			/** Get plugin version
			* @return plugin version
			* @remarks If wrap cordova plugin, the plugin version must be obtained from original plugin file "plugin.xml" or "package.json"
			*/
			const char* Version;

			/** Get plugin description
			* @return plugin description
			* @remarks If wrap cordova plugin, the plugin description must be obtained from original plugin file "plugin.xml" or "package.json"
			*/
			const char* Description;

			/** Get cordova plugin licebnse
			* @return cordova plugin license
			* @remarks If wrap cordova plugin, the cordova plugin license must be obtained from original plugin file "plugin.xml" or "package.json". 
			* License for this ZxPlugin must be compatible with de cordova plugin license
			*/
			const char* License;

			/** Get cordova plugin author (Only for wrap cordova plugin)
			* @return cordova plugin author
			* @remarks If wrap cordova plugin, the cordova plugin author must be obtained from original plugin file "plugin.xml" or "package.json"
			*/
			const char* CordovaAuthor;

			/** Get ZxPlugin author
			* @return ZxPlugin author
			* @remarks This ZxPlugin author
			*/
			const char* ZxPluginAuthor;
		};


		/**
		 * Interface for create cocos2dx zxplugins
		*/
		class IPlugin
		{


		public:

			/** Default constructor */
			IPlugin() {}

			/** Default destructor */
			virtual ~IPlugin(void) {}

			/** 
			@brief Get plugin properties
			@return plugin properties
			*/
			const PluginPropertiesModel* getPluginProperties() { return this->m_pluginPropertiesModel.get(); }


		protected:

			/**
			@brief Set plugin properties
			@param _pluginProperties plugin properties
			@remarks This function must be invoked for inherited classes for set plugin properties
			*/
			void setPluginProperties(PluginPropertiesModel& _pluginProperties) { this->m_pluginPropertiesModel = std::make_shared<PluginPropertiesModel>(_pluginProperties); }

			/**
			 * Method for invoke platform native code
			 * @param _successCallback callback for success result
			 * @param _errorCallback callback for error result
			 * @param _className class namespace and name
			 * @param _funcName function name to execute
			 * @param _params function parameters
			 */
			void exec(std::function<void(const std::string&)> _successCallback, std::function<void(const std::string&)> _errorCallback, const char* _className, const char* _funcName, std::string _params)
			{			
				// invoke platform handler command code								
				CocosAppWinRT::ZxPlugin::CommandHandler::execPlatformCommand(
					wrapPlatformCallback(_successCallback),
					wrapPlatformCallback(_errorCallback),
					convertToPlatformString(this->m_pluginPropertiesModel->Name),
					convertToPlatformString(_className),
					convertToPlatformString(_funcName),
					convertToPlatformString(_params));
			};
	


		private:

			/** Plugin properties model */
			std::shared_ptr<PluginPropertiesModel> m_pluginPropertiesModel;



		};


	} // namespace cocos2d 
} // namespace zxplugin

#endif /* __ZXPLUGIN_IPLUGIN_H__ */
