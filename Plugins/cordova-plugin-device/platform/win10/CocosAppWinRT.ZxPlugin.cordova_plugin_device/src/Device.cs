using System;
using Windows.ApplicationModel.Resources;
using Windows.System.Profile;

namespace CocosAppWinRT.ZxPlugin.cordova_plugin_device
{
    /// <summary>
    /// Class for define device info cordova plugin
    /// </summary>
    class Device : BaseCommand
    {


        #region [Inicialization]

        /// <summary>
        /// Default constructor
        /// </summary>
        public Device()
        {
        }

        #endregion [Inicialization]



        #region [Public methods]

        /// <summary>
        /// Function for get device info
        /// </summary>
        /// <param name="_params">not used</param>
        public void getDeviceInfo(string _params)
        {
            // not used currently
            // ResourceLoader resources = ResourceLoader.GetForViewIndependentUse("CocosAppWinRT.ZxPlugin.cordova_plugin_device/Resources");

            // ---------------------------
            // Platform
            string devicePlatform = AnalyticsInfo.VersionInfo.DeviceFamily;

            // ---------------------------
            // Uuid
            // deviceId aka uuid, stored in Windows.Storage.ApplicationData.current.localSettings.values.deviceId
            string deviceId;
            // get deviceId, or create and store one
            var localSettings = Windows.Storage.ApplicationData.Current.LocalSettings;
            if (localSettings.Values.ContainsKey("deviceId"))
            {
                deviceId = localSettings.Values["deviceId"].ToString();
            }
            else
            {
                // App-specific hardware id could be used as uuid, but it changes if the hardware changes...
                try
                {
                    var ASHWID = Windows.System.Profile.HardwareIdentification.GetPackageSpecificToken(null).Id;
                    deviceId = Windows.Storage.Streams.DataReader.FromBuffer(ASHWID).ReadGuid().ToString();
                }
                catch
                {
                    // Couldn't get the hardware UUID
                    deviceId = string.Empty;
                }
                //...so cache it per-install
                localSettings.Values["deviceId"] = deviceId;
            }

            // ---------------------------
            // Version
            string sv = AnalyticsInfo.VersionInfo.DeviceFamilyVersion;
            ulong v = ulong.Parse(sv);
            ulong v1 = (v & 0xFFFF000000000000L) >> 48;
            ulong v2 = (v & 0x0000FFFF00000000L) >> 32;
            ulong v3 = (v & 0x00000000FFFF0000L) >> 16;
            ulong v4 = (v & 0x000000000000FFFFL);
            string systemVersion = $"{v1}.{v2}.{v3}.{v4}";

            // ---------------------------
            // Model
            var deviceInfo = new Windows.Security.ExchangeActiveSyncProvisioning.EasClientDeviceInformation();
            string model = deviceInfo.SystemProductName;

            // ---------------------------
            // Manufacturer
            string manufacturer = deviceInfo.SystemManufacturer;

            // ---------------------------
            // IsVirtual
            // Running in the Windows Simulator is a remote session.
            // Running in the Windows Phone Emulator has the systemProductName set to "Virtual"
            string isVirtual = (Windows.System.RemoteDesktop.InteractiveSession.IsRemote || deviceInfo.SystemProductName == "Virtual") ? "true" : "false";

            // Format result
            string result = $"\"platform\":\"{devicePlatform}\"," +
                $"\"uuid\":\"{deviceId}\"," +
                $"\"version\":\"{systemVersion}\"," +
                $"\"model\":\"{model}\"," +
                $"\"manufacturer\":\"{manufacturer}\"," +
                $"\"isVirtual\":{isVirtual}";

            // dispatch cordova plugin result
            DispatchCommandResult(new CommandResult(CommandResult.Status.OK, "{" + result + "}"));


        }

        #endregion [Public methods]


    }
}
