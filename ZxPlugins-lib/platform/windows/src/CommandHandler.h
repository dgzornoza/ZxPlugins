#ifndef __ZXPLUGIN_COMMAND_HANDLER_H__
#define __ZXPLUGIN_COMMAND_HANDLER_H__

#include <collection.h>

// NOTE: this namespace is required for interop with WinRT from cocos2dx (currently, cocos2dx use this namespace in winrt project)
namespace CocosAppWinRT	{
	namespace ZxPlugin {

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

			/** (Internal use only). Function for add platform command handler for interop with platform code.
			@param _pluginName unique name for plugin identity (shoud be unique on all plugins)
			@param _platformCommandHandler Object with platform command handler
			@remarks This function should be invoked for factory code for set 'PlatformCommandHandler' on load plugin
			*/
			static void addPlatformCommandHandler(Platform::String^ _pluginName, IPlatformCommandHandler^ _platformCommandHandler);

			/** (Internal use only). Function for remove platform command handler for interop with platform code.
			@param _pluginName unique name for plugin identity to remove from platform command handler (shoud be unique on all plugins)
			@remarks This function should be invoked for factory code for remove 'PlatformCommandHandler' on unload plugin
			*/
			static void removePlatformCommandHandler(Platform::String^ _pluginName);

			/** function for execute platform code using the input parameters
			* @param _successCallback callback for success result
			* @param _errorCallback callback for error result
			* @param _pluginName unique name for plugin identity (shoud be unique on all plugins)
			* @param _className Class name in platform code with the function to execute
			* @param _funcName Function name in the class to execute
			* @param _params parameters to invoke the function, for complex objects can use json string.
			*/
			static void execPlatformCommand(CompletedFunc^ _successCallback, CompletedFunc^ _errorCallback, Platform::String^ _pluginName, Platform::String^ _className, Platform::String^ _funcName, Platform::String^ _params);

		private:

			/** map for maintain the platform commands handlers */
			static Platform::Collections::Map<Platform::String^, IPlatformCommandHandler^> s_platformCommandsHandlers;

		};

	} // namespace ZxPlugin
} // namespace CocosAppWinRT


#endif /* __ZXPLUGIN_COMMAND_HANDLER_H__ */