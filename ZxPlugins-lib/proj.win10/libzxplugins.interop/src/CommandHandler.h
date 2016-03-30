#ifndef __ZXPLUGIN_COMMAND_HANDLER_H__
#define __ZXPLUGIN_COMMAND_HANDLER_H__


namespace libzxplugins_interop {

/**
* delegate to invoke from platform command handler on finish command
* @param _jsonResult json result formed by 'status, message' ej: "\"status\":{0},\"message\":{1}"
*/
public delegate void CompletedFunc(Platform::String^ _jsonResult);

/** 
* @brief zxplugin interface for platform command handler.
* this interface declare methods for handle comunication between platform native code and cocos2dx.
*/
[Windows::Foundation::Metadata::WebHostHidden]
public interface class IPlatformCommandHandler
{
public:

	/** virtual function for implement in platform command handler for execute platform code
	* @param _successCallback callback for success result
	* @param _errorCallback callback for error result
	* @param _className Class name in platform code with the function to execute
	* @param _funcName Function name in the class to execute
	* @param _params parameters to invoke the function, for complex objects can use json string.
	*/
	virtual void exec(CompletedFunc^ _successCallback, CompletedFunc^ _errorCallback, Platform::String^ _className, Platform::String^ _funcName, Platform::String^ _params);

};

/** 
* @brief class for interop with native code
* this class handle comunication cocos2dx -> platform native.
*/
[Windows::Foundation::Metadata::WebHostHidden]
public ref class CommandHandler sealed
{ 

public: 

	/** function for set platform command handler for interop with platform code
	* @param _platformCommandHandler Object with platform command handler
	*/
	static void setPlatformCommandHandler(IPlatformCommandHandler^ _platformCommandHandler);

	/** function for execute platform code using the input parameters
	* @param _successCallback callback for success result
	* @param _errorCallback callback for error result
	* @param _className Class name in platform code with the function to execute
	* @param _funcName Function name in the class to execute
	* @param _params parameters to invoke the function, for complex objects can use json string.
	*/
	static void execPlatformCommand(CompletedFunc^ _successCallback, CompletedFunc^ _errorCallback, Platform::String^ _className, Platform::String^ _funcName, Platform::String^ _params);

};

} // namespace libzxplugins_interop


#endif /* __ZXPLUGIN_COMMAND_HANDLER_H__ */