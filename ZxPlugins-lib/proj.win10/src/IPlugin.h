#ifndef __ZXPLUGIN_IPLUGIN_H__
#define __ZXPLUGIN_IPLUGIN_H__

#include "CommandHandler.h"
#include <functional>
#include <codecvt>

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
