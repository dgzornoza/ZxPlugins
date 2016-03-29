#include "CommandHandler.h"

// WinRT (Windows 10 Universal)
#if defined(_WINRT_DLL)

namespace PhoneDirect3DXamlAppComponent {
	

// anonimous namespace for global objects in cpp file
namespace
{
	// global object for the platform command handler
	IPlatformCommandHandler^ g_platformCommandHandler = nullptr;
}

/** function for set native command handler for interop with native code */
void CommandHandler::setPlatformCommandHandler(IPlatformCommandHandler^ _nativeCommandHandler)
{
	g_platformCommandHandler = _nativeCommandHandler;
}

/** function for execute platform code using the input parameters */
void CommandHandler::execPlatformCommand(CompletedFunc^ _successCallback, CompletedFunc^ _errorCallback, Platform::String^ _className, Platform::String^ _funcName, Platform::String^ _params)
{
	// verify command handler
	if (nullptr == g_platformCommandHandler) return;
		
	// invoke command handler in native platform using the input parameters
	g_platformCommandHandler->exec(_successCallback, _errorCallback, _className, _funcName, _params);
}


} // namespace PhoneDirect3DXamlAppComponent

#endif // _WINRT_DLL


