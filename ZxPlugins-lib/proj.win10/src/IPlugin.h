#ifndef __ZXPLUGIN_IPLUGIN_H__
#define __ZXPLUGIN_IPLUGIN_H__

#include "CommandHandler.h"
#include <functional>

namespace cocos2d { namespace zxplugin {


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

	/** Get plug-in name 
	 * @return plugin name
	 */
    virtual const char* getPluginName() const = 0;
	/** Get plug-in version 
	 * @return plugin version
	 */
	virtual const char* getPluginVersion() const = 0;

protected:

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
		PhoneDirect3DXamlAppComponent::CommandHandler::execPlatformCommand(
			_wrapPlatformCallback(_successCallback), 
			_wrapPlatformCallback(_errorCallback),
			_convertToPlatformString(_className),
			_convertToPlatformString(_funcName),
			_convertToPlatformString(_params));
		
	};
	
private:



	/** function for wrap c++ std:function to platform native pointer function
	* @param _callback c++ std::function for wrap into platform native pointer function
	* @result platform native pointer function
	*/
	PhoneDirect3DXamlAppComponent::CompletedFunc^ _wrapPlatformCallback(std::function<void(const std::string&)> _callback)
	{
		return ref new PhoneDirect3DXamlAppComponent::CompletedFunc([=](Platform::String^ _param)
		{
			_callback(_convertFromPlatformString(_param));
		});
	}

	/** function for convert c++ string to platform native string 
	* @param _string c++ std:string for convert to platform string
	* @result platform string converted
	*/
	Platform::String^ _convertToPlatformString(const std::string& _string)
	{
		// get wide string size from string and initialize the wide string for conversion
		int size = MultiByteToWideChar(CP_UTF8, 0, &_string[0], (int)_string.size(), nullptr, 0);
		std::wstring wstr(size, 0);
		// convert to wide string
		MultiByteToWideChar(CP_UTF8, 0, &_string[0], (int)_string.size(), &wstr[0], size);

		// create platform string and return result
		Platform::String^ result = ref new Platform::String(wstr.c_str());
		return result;
	}

	/** function for convert platform native string to c++ string 
	* @param _string platform string for convert to c++ std:string
	* @result std::string converted
	*/
	std::string _convertFromPlatformString(Platform::String^ _string)
	{
		// get string size from wide string and initialize the string for conversion
		int size = WideCharToMultiByte(CP_UTF8, 0, _string->Data(), (int)_string->Length(), nullptr, 0, nullptr, nullptr);
		std::string str(size, 0);

		// convert to string and return
		WideCharToMultiByte(CP_UTF8, 0, _string->Data(), (int)_string->Length(), &str[0], size, nullptr, nullptr);
		return str;
	}



};


}} //namespace cocos2d { namespace zxplugin {

#endif /* __ZXPLUGIN_IPLUGIN_H__ */
