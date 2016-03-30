#ifndef __ZXPLUGIN_IPLUGIN_H__
#define __ZXPLUGIN_IPLUGIN_H__

#include <memory>
#include <functional>
#include <codecvt>

namespace cocos2d { namespace zxplugin {

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
		* @return plugin name
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
			libzxplugins_interop::CommandHandler::execPlatformCommand(
				_wrapPlatformCallback(_successCallback), 
				_wrapPlatformCallback(_errorCallback),
				_convertToPlatformString(_className),
				_convertToPlatformString(_funcName),
				_convertToPlatformString(_params));
		
		};
	


	private:

		/** Plugin properties model */
		std::shared_ptr<PluginPropertiesModel> m_pluginPropertiesModel;

		/** function for wrap c++ std:function to platform native pointer function
		* @param _callback c++ std::function for wrap into platform native pointer function
		* @result platform native pointer function
		*/
		libzxplugins_interop::CompletedFunc^ _wrapPlatformCallback(std::function<void(const std::string&)> _callback)
		{		
			return ref new libzxplugins_interop::CompletedFunc([=](Platform::String^ _param)
			{
				_callback(_convertFromPlatformString(_param));
			});
		}

		/** function for convert c++ string to platform native string 
		* @param _string c++ std:string for convert to platform string
		* @result platform string converted
		* @remarks http://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		*/
		Platform::String^ _convertToPlatformString(const std::string& _string)
		{
			// create converter and convert
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wstr = converter.from_bytes(_string);

			// create platform string and return result
			Platform::String^ result = ref new Platform::String(wstr.c_str());
			return result;
		}

		/** function for convert platform native string to c++ string 
		* @param _string platform string for convert to c++ std:string
		* @result std::string converted
		* @remarks http://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		*/
		std::string _convertFromPlatformString(Platform::String^ _string)
		{
			// create converter and convert
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::string result = converter.to_bytes(_string->Data());
			return result;
		}



	};


}} //namespace cocos2d { namespace zxplugin {

#endif /* __ZXPLUGIN_IPLUGIN_H__ */
