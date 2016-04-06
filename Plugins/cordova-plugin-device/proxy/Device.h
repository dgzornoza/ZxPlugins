#ifndef __ZXPLUGIN_DEVICE_H__
#define __ZXPLUGIN_DEVICE_H__

#include "ZxPlugins-lib\scr\IPlugin.h"

/**
* @addtogroup ZxPlugin
* @{
*/

namespace cocos2d { namespace zxplugin { namespace cordova_plugin_device {

	/** 
	@brief Device info model
	*/
	struct DeviceInfo
	{
		/** Device's operating system name. */
		const char* Platform;
		/** Operating system version. */
		const char* Version;
		/** Get the device's Universally Unique Identifier (UUID). */
		const char* Uuid;
		/** Name of the device's model or product. The value is set by the device manufacturer and may be different across versions of the same product. */
		const char* Model;
		/** Device's manufacturer. */
		const char* Manufacturer;
		/** Whether the device is running on a simulator. */
		const char* IsVirtual;
		/** Device hardware serial number (Only for Android/IOS). */
		const char* Serial;
	};

	/**
	 @brief Proxy class for access "cordova plugin device" plugin. This plugin access to device info.
	 @remarks this plugin is base on oficial cordova plugin : https://github.com/apache/cordova-plugin-device
	*/
	class Device : public IPlugin
	{

	public:


		/** Default constructor */
		Device() 
		{
			this->setPluginProperties(PluginPropertiesModel({ true,
				"cordova-plugin-device",
				"1.1.2-dev",
				"Cordova Device Plugin",
				"Apache-2.0",
				"Apache Software Foundation",
				"David González Zornoza" }));
		}

		/** Default destructor */
		virtual ~Device() {}


		/// @{
		/// @name Plugin functions


		/**
		@brief 
		*
		* @param _successCallback: callback function for success.
		* @param _errorCallback: callback function for error.
		*/
		void getInfo(std::function<void(const std::string&)> _successCallback, std::function<void(const std::string&)> _errorCallback)
		{
			// invoke native code
			this->exec(_successCallback, _errorCallback, "Device", "getDeviceInfo", "[]");
																
		};

		/// @} End Properties setter/getters


	};


	}}} //namespace cocos2d { namespace zplugin { namespace cordova_plugin_device {

	// end of ZxPlugin group
	/// @}

#endif /* __ZXPLUGIN_DEVICE_H__ */
