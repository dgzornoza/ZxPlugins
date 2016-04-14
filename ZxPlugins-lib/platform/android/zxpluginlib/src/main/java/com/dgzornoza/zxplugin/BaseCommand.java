package com.dgzornoza.zxplugin;

import java.util.Map;

/// <summary>
/// Command base for create windows platform plugins
/// </summary>
/// <remarks>All platform plugins must extend BaseCommand</remarks>
public class BaseCommand
{
    /// <summary>
    /// Eventhandler for custom Command result
    /// </summary>
    public event EventHandler<CommandResult> OnCommandResult;

    /// <summary>
    /// Property for store current command callback id
    /// </summary>
    public string CurrentCommandCallbackId { get; set; }

    /// <summary>
    /// default constructor
    /// </summary>
    public BaseCommand()
    {
        ResultHandlers = new Dictionary<string, EventHandler<CommandResult>>();
    }

    /// <summary>
    /// Dictionary for store result handlers for commands with callback id
    /// </summary>
    protected Dictionary<string, EventHandler<CommandResult>> ResultHandlers;
    /// <summary>
    /// Method for add result handler
    /// </summary>
    /// <param name="_callbackId">Callback id</param>
    /// <param name="_handler">handler</param>
    public void AddResultHandler(string _callbackId, EventHandler<CommandResult> _handler)
    {
        ResultHandlers.Add(_callbackId, _handler);
    }
    /// <summary>
    /// Method for remove result handler
    /// </summary>
    /// <param name="_callbackId">Callback id</param>
    /// <returns>True if can remove.</returns>
    public bool RemoveResultHandler(string _callbackId)
    {
        return ResultHandlers.Remove(_callbackId);
    }

    /// <summary>
    /// Method for invoke plugin command method.
    /// InvokeMethodNamed will call the named method of a BaseCommand subclass if it exists and pass the variable arguments list along.
    /// </summary>
    /// <param name="_callbackId">Callback id</param>
    /// <param name="_methodName">plugin method name to invoke</param>
    /// <param name="_args">method arguments</param>
    /// <returns>Invoked oject result</returns>
    public object InvokeMethodNamed(string _callbackId, string _methodName, params object[] _args)
    {
        //Debug.WriteLine(string.Format("InvokeMethodNamed:{0} callbackId:{1}",methodName,callbackId));
        this.CurrentCommandCallbackId = _callbackId;
        return InvokeMethodNamed(_methodName, _args);
    }

    /// <summary>
    /// Method for invoke plugin command method.
    /// InvokeMethodNamed will call the named method of a BaseCommand subclass if it exists and pass the variable arguments list along.
    /// </summary>
    /// <param name="_methodName">plugin method name to invoke</param>
    /// <param name="_args">method arguments</param>
    /// <returns>Invoked oject result</returns>
    public object InvokeMethodNamed(string _methodName, params object[] _args)
    {
        MethodInfo mInfo = this.GetType().GetMethod(_methodName);

        if (mInfo != null)
        {
            // every function handles DispatchCommandResult by itself
            return mInfo.Invoke(this, _args);
        }

        // actually methodName could refer to a property
        if (_args == null || _args.Length == 0 ||
                (_args.Length == 1 && "undefined".Equals(_args[0])))
        {
            PropertyInfo pInfo = this.GetType().GetProperty(_methodName);
            if (pInfo != null)
            {
                object res = pInfo.GetValue(this, null);

                DispatchCommandResult(new CommandResult(CommandResult.Status.OK, res));

                return res;
            }
        }

        throw new MissingMethodException(_methodName);

    }

    /// <summary>
    /// Method for dispatch command result
    /// </summary>
    public void DispatchCommandResult()
    {
        this.DispatchCommandResult(new CommandResult(CommandResult.Status.NO_RESULT));
    }

    /// <summary>
    /// Method for dispatch command result with values
    /// </summary>
    /// <param name="_result">command result</param>
    /// <param name="_callbackId">Callback id for command</param>
    public void DispatchCommandResult(CommandResult _result, string _callbackId="")
    {
        if (!string.IsNullOrEmpty(_callbackId))
        {
            _result.CallbackId = _callbackId;
        }
        else
        {
            _result.CallbackId = this.CurrentCommandCallbackId;
        }

        if (ResultHandlers.ContainsKey(_result.CallbackId))
        {
            ResultHandlers[_result.CallbackId](this, _result);
        }
        else if (this.OnCommandResult != null)
        {
            OnCommandResult(this, _result);
        }
        else
        {
            Debug.WriteLine("Failed to locate callback for id : " + _result.CallbackId);
        }

        if (!_result.KeepCallback)
        {
            this.OnCommandResult = null;
        }

    }


    /// <summary>
    /// Occurs when the application is being deactivated.
    /// </summary>
    public virtual void OnReset() {}

    /// <summary>
    /// Occurs when the application is being loaded, and the config.xml has an autoload entry
    /// </summary>
    public virtual void OnInit() {}

    /// <summary>
    /// Detach all command handlers
    /// </summary>
    public void DetachHandlers()
    {
        this.OnCommandResult = null;
        foreach (string callbackId in new List<string>(ResultHandlers.Keys))
        {
            RemoveResultHandler(callbackId);
        }
    }

}
