using System;
using System.Collections.Generic;

namespace CocosAppWinRT.ZxPlugin
{

    /// <summary>
    /// Plugin handler for interop with platform code
    /// </summary>
    public sealed class PluginHandler
    {

        /// <summary>
        /// Function for add plugin for interop with platform code.
        /// </summary>
        /// <param name="_pluginName">unique name for plugin identity (shoud be unique on all plugins)</param>
        /// <param name="_commandHandler">Object with platform command handler</param>
        /// <remarks>This function should be invoked for factory code for set 'CommandHandler' on load plugin</remarks>
        public static void addPlugin(string _pluginName, ICommandHandler _commandHandler)
        {
            // verify command handler and add
            if (s_pluginHandlers.ContainsKey(_pluginName)) return;
            s_pluginHandlers.Add(_pluginName, _commandHandler);
        }

        /// <summary>
        /// Function for remove plugin for interop with platform code.
        /// </summary>
        /// <param name="_pluginName">unique name for plugin identity to remove from handler (shoud be unique on all plugins)</param>
        /// <remarks>This function should be invoked for factory code for remove 'CommandHandler' on unload plugin</remarks>
        public static void removePlugin(string _pluginName)
        {
            // verify command handler and remove
            if (!s_pluginHandlers.ContainsKey(_pluginName)) return;
            s_pluginHandlers.Remove(_pluginName);
        }

        /// <summary>
        /// Function for execute plugin command
        /// </summary>
        /// <param name="_successCallback">callback for success result</param>
        /// <param name="_errorCallback">callback for error result</param>
        /// <param name="_pluginName">unique name for plugin identity (shoud be unique on all plugins)</param>
        /// <param name="_className">Class name in platform code with the function to execute</param>
        /// <param name="_funcName">Function name in the class to execute</param>
        /// <param name="_params">parameters to invoke the function, for complex objects can use json string.</param>
        /// <remarks>This function should be invoked for IPlugin code for execute plugin command</remarks>
        public static void execCommand(CommandCallback _successCallback, CommandCallback _errorCallback, string _pluginName, string _className, string _funcName, string _params)
        {
            // verify plugin handler
            if (!s_pluginHandlers.ContainsKey(_pluginName)) return;

            // invoke plugin command in native platform using the input parameters
            s_pluginHandlers[_pluginName].exec(_successCallback, _errorCallback, _className, _funcName, _params);
        }

        /// <summary>
        /// map for maintain the platform plugin handlers
        /// </summary>
        private static Dictionary<string, ICommandHandler> s_pluginHandlers = new Dictionary<string, ICommandHandler>();

    }
}
