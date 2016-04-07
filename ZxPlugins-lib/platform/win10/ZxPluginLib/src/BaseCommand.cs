using System;
using System.Reflection;
using System.Diagnostics;
using System.Collections.Generic;

namespace CocosAppWinRT.ZxPlugin
{
    /// <summary>
    /// Command base for create windows platform plugins
    /// </summary>
    /// <remarks>All platform plugins must extend BaseCommand</remarks>
    public class BaseCommand : IDisposable
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
        /// <param name="callbackId">Callback id</param>
        /// <param name="handler">handler</param>
        public void AddResultHandler(string callbackId, EventHandler<CommandResult> handler)
        {
            ResultHandlers.Add(callbackId, handler);
        }
        /// <summary>
        /// Method for remove result handler
        /// </summary>
        /// <param name="callbackId">Callback id</param>
        /// <returns>True if can remove.</returns>
        public bool RemoveResultHandler(string callbackId)
        {
            return ResultHandlers.Remove(callbackId);
        }

        /// <summary>
        /// Method for invoke plugin command method.
        /// InvokeMethodNamed will call the named method of a BaseCommand subclass if it exists and pass the variable arguments list along.
        /// </summary>
        /// <param name="callbackId">Callback id</param>
        /// <param name="methodName">plugin method name to invoke</param>
        /// <param name="args">method arguments</param>
        /// <returns>Invoked oject result</returns>
        public object InvokeMethodNamed(string callbackId, string methodName, params object[] args)
        {
            //Debug.WriteLine(string.Format("InvokeMethodNamed:{0} callbackId:{1}",methodName,callbackId));
            this.CurrentCommandCallbackId = callbackId;
            return InvokeMethodNamed(methodName, args);
        }

        /// <summary>
        /// Method for invoke plugin command method.
        /// InvokeMethodNamed will call the named method of a BaseCommand subclass if it exists and pass the variable arguments list along.
        /// </summary>
        /// <param name="methodName">plugin method name to invoke</param>
        /// <param name="args">method arguments</param>
        /// <returns>Invoked oject result</returns>
        public object InvokeMethodNamed(string methodName, params object[] args)
        {
            MethodInfo mInfo = this.GetType().GetMethod(methodName);

            if (mInfo != null)
            {
                // every function handles DispatchCommandResult by itself
                return mInfo.Invoke(this, args);
            }

            // actually methodName could refer to a property
            if (args == null || args.Length == 0 ||
               (args.Length == 1 && "undefined".Equals(args[0])))
            {
                PropertyInfo pInfo = this.GetType().GetProperty(methodName);
                if (pInfo != null)
                {
                    object res = pInfo.GetValue(this, null);

                    DispatchCommandResult(new CommandResult(CommandResult.Status.OK, res));

                    return res;
                }
            }

            throw new MissingMethodException(methodName);

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
                this.Dispose();
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
        /// Occurs when the application is being made active after previously being put
        /// into a dormant state or tombstoned.
        /// </summary>        
        public virtual void OnActivated(object sender, Windows.UI.Core.WindowActivatedEventArgs e) { }

        /// <summary>
        /// Dispose command
        /// </summary>
        public void Dispose()
        {
            //Window.Current.Activated -= this.OnActivated;
            this.OnCommandResult = null;
        }

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

}
