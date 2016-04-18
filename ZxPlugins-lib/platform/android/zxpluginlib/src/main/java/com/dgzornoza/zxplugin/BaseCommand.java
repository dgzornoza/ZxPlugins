package com.dgzornoza.zxplugin;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 Command base for create windows platform plugins
 @remarks All platform plugins must extend BaseCommand
 */
public class BaseCommand
{
    private String m_currentCommandCallbackId;

    /**
    Dictionary for store result handlers for commands with callback id
    */
    protected Map<String, EventHandler<CommandResult>> ResultHandlers;

    /**
     Eventhandler for custom Command result
    */
    public EventHandler<CommandResult> OnCommandResult;

    public String getCurrentCommandCallbackId() { return this.m_currentCommandCallbackId; }
    public void setCurrentCommandCallbackId(String _callbackId) { this.m_currentCommandCallbackId = _callbackId; }

    /**
     default constructor
    */
    public BaseCommand()
    {
        ResultHandlers = new HashMap<String, EventHandler<CommandResult>>();
    }


    /**
    Method for add result handler
    @param _callbackId Callback id
    @param _handler handler
     */
    public void AddResultHandler(String _callbackId, EventHandler<CommandResult> _handler)
    {
        ResultHandlers.put(_callbackId, _handler);
    }
    /**
     Method for remove result handler
     @param _callbackId Callback id
     @return True if can remove.
     */
    public boolean RemoveResultHandler(String _callbackId)
    {
        boolean result = false;
        if(ResultHandlers.containsKey(_callbackId))
        {
            ResultHandlers.remove(_callbackId);
            result = true;
        }

        return result;
    }

    /**
    Method for invoke plugin command method.
    InvokeMethodNamed will call the named method of a BaseCommand subclass if it exists and pass the variable arguments list along.
    @param _callbackId Callback id
    @param _methodName plugin method name to invoke
    @param _args method arguments
    @return Invoked object result
    */
    public Object InvokeMethodNamed(String _callbackId, String _methodName, Object[] _args) throws NoSuchMethodException, IllegalAccessException, InvocationTargetException
    {
        //Logger.getLogger(getClass().getName()).log(Level.INFO, "InvokeMethodNamed:" + _methodName + " callbackId: " + _callbackId);
        this.m_currentCommandCallbackId = _callbackId;
        return InvokeMethodNamed(_methodName, _args);
    }

    /**
     Method for invoke plugin command method.
     InvokeMethodNamed will call the named method of a BaseCommand subclass if it exists and pass the variable arguments list along.
     @param_ methodName plugin method name to invoke
     @param _args method arguments
     @return Invoked oject result
     */
    public Object InvokeMethodNamed(String _methodName, Object[] _args) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {

        Method mInfo = this.getClass().getMethod(_methodName);
        return mInfo.invoke(this, _args);
    }

    /**
     Method for dispatch command result
     */
    public void DispatchCommandResult()
    {
        this.DispatchCommandResult(new CommandResult(CommandResult.Status.NO_RESULT));
    }

    /**
     Method for dispatch command result with values
     @param _result command result
     */
    public void DispatchCommandResult(CommandResult _result)
    {
        this.DispatchCommandResult(_result, "");
    }

    /**
     Method for dispatch command result with values
     @param _result command result
     @param _callbackId Callback id for command
     */
    public void DispatchCommandResult(CommandResult _result, String _callbackId)
    {
        if (null != _callbackId && _callbackId.trim().length() > 0)
        {
            _result.setCallbackId(_callbackId);
        }
        else
        {
            _result.setCallbackId(this.m_currentCommandCallbackId);
        }

        if (ResultHandlers.containsKey(_result.getCallbackId()))
        {
            ResultHandlers.get(_result.getCallbackId()).Invoke(this, _result);
        }
        else if (this.OnCommandResult != null)
        {
            OnCommandResult.Invoke(this, _result);
        }
        else
        {
            Logger.getLogger(getClass().getName()).log(Level.WARNING, "Failed to locate callback for id : " + _result.getCallbackId());
        }

        if (!_result.getIsKeepCallback())
        {
            this.OnCommandResult = null;
        }

    }


    /**
     Occurs when the application is being deactivated.
    */
    public void OnReset() {}

    /**
     Occurs when the application is being loaded, and the config.xml has an autoload entry
    */
    public void OnInit() {}

    /**
     Detach all command handlers
    */
    public void DetachHandlers()
    {
        this.OnCommandResult = null;

        Set<String> keys = new HashSet<>(ResultHandlers.keySet());
        for (String callbackId : keys )
        {
            RemoveResultHandler(callbackId);
        }
    }

}
