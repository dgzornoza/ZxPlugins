using System;
using System.Collections.Generic;
using System.Text;

namespace CocosAppWinRT.ZxPlugin
{
    /// <summary>
    /// delegate to invoke from platform command handler on finish command
    /// </summary>
    /// <param name="_jsonResult"> json result formed by 'status, message' ej: "\"status\":{0},\"message\":{1}"</param>
    public delegate void CompletedFunc(string _jsonResult);

    /// <summary>
    /// zxplugin interface for platform command handler.
    /// this interface declare methods for handle comunication between platform native code and cocos2dx.
    /// </summary>
    public interface IPlatformCommandHandler
    {

        /// <summary>
        /// virtual function for implement in platform command handler for execute platform code
        /// </summary>
        /// <param name="_successCallback">callback for success result</param>
        /// <param name="_errorCallback">callback for error result</param>
        /// <param name="_className">Class name in platform code with the function to execute</param>
        /// <param name="_funcName">Function name in the class to execute</param>
        /// <param name="_params">parameters to invoke the function, for complex objects can use json string.</param>
        void exec(CompletedFunc _successCallback, CompletedFunc _errorCallback, string _className, string _funcName, string _params);

    };

    /// <summary>
    /// ZxPlugin command handler for interop with platform code
    /// </summary>
    public sealed class CommandHandler
    {

        /// <summary>
        /// (Internal use only). Function for add platform command handler for interop with platform code.
        /// </summary>
        /// <param name="_pluginName">unique name for plugin identity (shoud be unique on all plugins)</param>
        /// <param name="_platformCommandHandler">Object with platform command handler</param>
        /// <remarks>This function should be invoked for factory code for set 'PlatformCommandHandler' on load plugin</remarks>
        public static void addPlatformCommandHandler(string _pluginName, IPlatformCommandHandler _platformCommandHandler)
        {
            // verify command handler and add
            if (s_platformCommandsHandlers.ContainsKey(_pluginName)) return;
            s_platformCommandsHandlers.Add(_pluginName, _platformCommandHandler);
        }

        /// <summary>
        /// (Internal use only). Function for remove platform command handler for interop with platform code.
        /// </summary>
        /// <param name="_pluginName">unique name for plugin identity to remove from platform command handler (shoud be unique on all plugins)</param>
        /// <remarks>This function should be invoked for factory code for remove 'PlatformCommandHandler' on unload plugin</remarks>
        public static void removePlatformCommandHandler(string _pluginName)
        {
            // verify command handler and remove
            if (!s_platformCommandsHandlers.ContainsKey(_pluginName)) return;
            s_platformCommandsHandlers.Remove(_pluginName);
        }

        /// <summary>
        /// function for execute platform code using the input parameters
        /// </summary>
        /// <param name="_successCallback">callback for success result</param>
        /// <param name="_errorCallback">callback for error result</param>
        /// <param name="_pluginName">unique name for plugin identity (shoud be unique on all plugins)</param>
        /// <param name="_className">Class name in platform code with the function to execute</param>
        /// <param name="_funcName">Function name in the class to execute</param>
        /// <param name="_params">parameters to invoke the function, for complex objects can use json string.</param>
        public static void execPlatformCommand(CompletedFunc _successCallback, CompletedFunc _errorCallback, string _pluginName, string _className, string _funcName, string _params)
        {
            // verify command handler
            if (!s_platformCommandsHandlers.ContainsKey(_pluginName)) return;

            // invoke command handler in native platform using the input parameters
            s_platformCommandsHandlers[_pluginName].exec(_successCallback, _errorCallback, _className, _funcName, _params);
        }

        /// <summary>
        /// map for maintain the platform commands handlers
        /// </summary>
        private static Dictionary<string, IPlatformCommandHandler> s_platformCommandsHandlers = new Dictionary<string, IPlatformCommandHandler>();

    }
}
