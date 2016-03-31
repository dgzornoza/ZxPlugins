using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CocosAppWinRT.ZxPlugin;

namespace org.apache.cordova.device
{
    /// <summary>
    /// Class for implement native platform command handler for call from ZxPlugins
    /// </summary>
    public class PlatformCommandHandler : CocosAppWinRT.ZxPlugin.IPlatformCommandHandler
    {
        /// <summary>
        /// Function for implement in platform command handler for execute platform code
        /// </summary>
        /// <param name="_successCallback"> callback for success result</param>
        /// <param name="_errorCallback">callback for error result</param>
        /// <param name="_className">Class name in platform code with the function to execute</param>
        /// <param name="_funcName">Function name in the class to execute</param>
        /// <param name="_params">parameters to invoke the function, for complex objects can use json string.</param>
        public void exec(CompletedFunc _successCallback, CompletedFunc _errorCallback, string _className, string _funcName, string _params)
        {
            
        }
    }
}
