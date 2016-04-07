using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace CocosAppWinRT.ZxPlugin
{
    /// <summary>
    /// Provides functionality to create plugin command by name.
    /// </summary>
    public static class CommandFactory
    {
        /// <summary>
        /// Namespace base for all commands
        /// </summary>
        private static readonly string BaseCommandNamespacePrefix = "CocosAppWinRT.ZxPlugin.";

        /// <summary>
        /// Cache instantiated commands in a map.
        /// </summary>
        private static Dictionary<string, BaseCommand> commandMap = new Dictionary<string, BaseCommand>();

        /// <summary>
        /// Creates command using command class name. Returns null for unknown commands.
        /// </summary>
        /// <param name="_service">Command class name, for example Device or Notification</param>
        /// <returns>Command class instance or null</returns>
        /// alias can be used as a namespace which is resolved + service
        /// or it can be the fully qualified classname
        /// or the classname in the current assembly
        public static BaseCommand CreateByServiceName(string _service)
        {

            if (string.IsNullOrEmpty(_service))
            {
                throw new ArgumentNullException("service", "service to create can't be null");
            }

            if (!commandMap.ContainsKey(_service))
            {
                Type type = Type.GetType(BaseCommandNamespacePrefix + _service);

                // unknown command, still didn't find it
                if (type == null)
                {
                    Debug.WriteLine("Unable to locate command :: " + _service);
                    return null;
                }

                // create command instance
                commandMap[_service] = Activator.CreateInstance(type) as BaseCommand;
            }

            return commandMap[_service];
        }

        /// <summary>
        /// Function for reset all commands cached
        /// </summary>
        public static void ResetAllCommands()
        {
            foreach (BaseCommand bc in commandMap.Values)
            {
                bc.OnReset();
            }
        }
    }
}
