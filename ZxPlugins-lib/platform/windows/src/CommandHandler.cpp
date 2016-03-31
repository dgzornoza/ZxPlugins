#include "CommandHandler.h"

using namespace CocosAppWinRT::ZxPlugin;
	
// define static map for platform command handler
Platform::Collections::Map<Platform::String^, IPlatformCommandHandler^> CommandHandler::s_platformCommandsHandlers;

void CommandHandler::addPlatformCommandHandler(Platform::String^ _pluginName, IPlatformCommandHandler^ _platformCommandHandler)
{
	// verify command handler and add
	if (s_platformCommandsHandlers.HasKey(_pluginName)) return;
	s_platformCommandsHandlers.Insert(_pluginName, _platformCommandHandler);
}

void CommandHandler::removePlatformCommandHandler(Platform::String^ _pluginName)
{
	// verify command handler and remove
	if (!s_platformCommandsHandlers.HasKey(_pluginName)) return;
	s_platformCommandsHandlers.Remove(_pluginName);
}

void CommandHandler::execPlatformCommand(CompletedFunc^ _successCallback, CompletedFunc^ _errorCallback, Platform::String^ _pluginName, Platform::String^ _className, Platform::String^ _funcName, Platform::String^ _params)
{

	// verify command handler
	if (!s_platformCommandsHandlers.HasKey(_pluginName)) return;
		
	// invoke command handler in native platform using the input parameters
	s_platformCommandsHandlers.Lookup(_pluginName)->exec(_successCallback, _errorCallback, _className, _funcName, _params);
}



