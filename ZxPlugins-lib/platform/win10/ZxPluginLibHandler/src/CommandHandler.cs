using System;

namespace CocosAppWinRT.ZxPlugin
{
    /// <summary>
    /// delegate to invoke from platform command handler on finish command
    /// </summary>
    /// <param name="_jsonResult"> json result formed by 'status, message' ej: "\"status\":{0},\"message\":{1}"</param>
    public delegate void CommandCallback(string _jsonResult);


    /// <summary>
    /// zxplugin interface for platform command handler.
    /// this interface declare methods for handle comunication between platform native code and cocos2dx.
    /// </summary>
    public interface ICommandHandler
    {

        /// <summary>
        /// virtual function for implement in platform command handler for execute platform code
        /// </summary>
        /// <param name="_successCallback">callback for success result</param>
        /// <param name="_errorCallback">callback for error result</param>
        /// <param name="_className">Class name in platform code with the function to execute</param>
        /// <param name="_funcName">Function name in the class to execute</param>
        /// <param name="_params">parameters to invoke the function, for complex objects can use json string.</param>
        void exec(CommandCallback _successCallback, CommandCallback _errorCallback, string _className, string _funcName, string _params);

    };

    /// <summary>
    /// Class for manage native platform command handler for call from ZxPlugins
    /// </summary>
    public sealed class CommandHandler : ICommandHandler
    {
        /// <summary>
        /// Function for execute platform code
        /// </summary>
        /// <param name="_successCallback"> callback for success result</param>
        /// <param name="_errorCallback">callback for error result</param>
        /// <param name="_className">Class name in platform code with the function to execute</param>
        /// <param name="_funcName">Function name in the class to execute</param>
        /// <param name="_params">parameters to invoke the function, for complex objects can use json string.</param>
        public void exec(CommandCallback _successCallback, CommandCallback _errorCallback, string _className, string _funcName, string _params)
        {
            // verify params
            if (_successCallback == null || _errorCallback == null || string.IsNullOrWhiteSpace(_className) || string.IsNullOrWhiteSpace(_funcName) || string.IsNullOrWhiteSpace(_params))
            {
                throw new ArgumentNullException("CommandHandler::exec()");
            }

            // create callbackID
            string callbackId = Guid.NewGuid().ToString();

            try
            {
                // create service
                BaseCommand service = CommandFactory.CreateByServiceName(_className);
                if (service == null)
                {
                    _errorCallback.Invoke(new CommandResult(CommandResult.Status.CLASS_NOT_FOUND_EXCEPTION, $"ERROR: Class not found :: {_className}:{_funcName}").ToJSONString());
                    return;
                }

                // create command result handler
                EventHandler<CommandResult> OnCommandResultHandler = delegate (object _sender, CommandResult _result)
                {
                    // verify callback id
                    if (_result.CallbackId == null || _result.CallbackId == callbackId)
                    {
                        CommandCallback resultHandler = _result.Result != CommandResult.Status.OK ? _errorCallback : _successCallback;
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
                        _errorCallback.Invoke(new CommandResult(CommandResult.Status.INVALID_ACTION, $"ERROR: Exception in ProcessCommand  :: {_funcName} on Object :: {_className} :: {ex.Message}").ToJSONString());
                        return;
                    }
                });

            }
            catch (Exception ex)
            {
                // ERROR
                _errorCallback.Invoke(new CommandResult(CommandResult.Status.ERROR, $"ERROR: Unable to execute command :: {_className}:{_funcName}:{ex.Message}").ToJSONString());
                return;
            }

        }
    }
}
