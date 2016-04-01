using System;
using System.Reflection;
using CocosAppWinRT.ZxPlugin.Cordova;
using System.Diagnostics;

namespace CocosAppWinRT.ZxPlugin.cordova_plugin_device
{
    /// <summary>
    /// Class for implement native platform command handler for call from ZxPlugins
    /// </summary>
    public sealed class PlatformCommandHandler : IPlatformCommandHandler
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        //public PlatformCommandHandler() { }

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
            // verify params
            if (_successCallback == null || _errorCallback == null || string.IsNullOrWhiteSpace(_className) || string.IsNullOrWhiteSpace(_funcName) || string.IsNullOrWhiteSpace(_params))
            {
                throw new ArgumentNullException("PlatformCommandHandler::exec()");
            }

            // create callbackID
            string callbackId = Guid.NewGuid().ToString();

            try
            {
                // create service
                BaseCommand service = CommandFactory.CreateByServiceName("cordova_plugin_device." + _className);
                if (service == null)
                {
                    _errorCallback.Invoke(new PluginResult(PluginResult.Status.CLASS_NOT_FOUND_EXCEPTION, $"ERROR: Class not found :: {_className}:{_funcName}").ToJSONString());
                    return;
                }

                // create command result handler
                EventHandler<PluginResult> OnCommandResultHandler = delegate (object _sender, PluginResult _result)
                {
                    // verify callback id
                    if (_result.CallbackId == null || _result.CallbackId == callbackId)
                    {
                        CompletedFunc resultHandler = _result.Result != PluginResult.Status.OK ? _errorCallback : _successCallback;
                        resultHandler.Invoke(_result.ToJSONString());

                        // remove current command result handler
                        if (!_result.KeepCallback) service.RemoveResultHandler(callbackId);
                    }
                };
                // add command result handler
                service.AddResultHandler(callbackId, OnCommandResultHandler);

                // create new task for invoque service method
                var task = Windows.System.Threading.ThreadPool.RunAsync((_workItem) =>
                {
                    try
                    {
                        service.InvokeMethodNamed(callbackId, _funcName, _params);
                        // commands.Add(service); ??? No tiene sentido
                    }
                    catch (Exception ex)
                    {
                        // remove current command result handler and invoke error
                        service.RemoveResultHandler(callbackId);
                        _errorCallback.Invoke(new PluginResult(PluginResult.Status.INVALID_ACTION, $"ERROR: Exception in ProcessCommand  :: {_funcName} on Object :: {_className} :: {ex.Message}").ToJSONString());
                        return;
                    }
                });

            }
            catch (Exception ex)
            {
                // ERROR
                _errorCallback.Invoke(new PluginResult(PluginResult.Status.ERROR, $"ERROR: Unable to execute command :: {_className}:{_funcName}:{ex.Message}").ToJSONString());
                return;
            }

        }
    }
}
