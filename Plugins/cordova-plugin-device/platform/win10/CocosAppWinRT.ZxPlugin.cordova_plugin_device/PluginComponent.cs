
namespace CocosAppWinRT.ZxPlugin.cordova_plugin_device
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class PluginComponent : ICommandHandler
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="_successCallback"></param>
        /// <param name="_errorCallback"></param>
        /// <param name="_className"></param>
        /// <param name="_funcName"></param>
        /// <param name="_params"></param>
        public void exec(CommandCallback _successCallback, CommandCallback _errorCallback, string _className, string _funcName, string _params)
        {
            new CommandHandler().exec(_successCallback, _errorCallback, _className, _funcName, _params);
        }
    }
}
