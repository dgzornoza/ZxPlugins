#include "CommandHandler.h"

using namespace CocosAppWinRT::ZxPlugin;
	
// define static map for platform command handler
Platform::Collections::Map<Platform::String^, IPlatformCommandHandler^> CommandHandler::s_platformCommandsHandlers;

/** function for set native command handler for interop with native code */
void CommandHandler::setPlatformCommandHandler(Platform::String^ _pluginName, IPlatformCommandHandler^ _platformCommandHandler)
{
	s_platformCommandsHandlers.Insert(_pluginName, _platformCommandHandler);
}

/** function for execute platform code using the input parameters */
void CommandHandler::execPlatformCommand(CompletedFunc^ _successCallback, CompletedFunc^ _errorCallback, Platform::String^ _pluginName, Platform::String^ _className, Platform::String^ _funcName, Platform::String^ _params)
{
	// verify command handler
	if (!s_platformCommandsHandlers.HasKey(_pluginName)) return;
		
	// invoke command handler in native platform using the input parameters
	s_platformCommandsHandlers.Lookup(_pluginName)->exec(_successCallback, _errorCallback, _className, _funcName, _params);
}



