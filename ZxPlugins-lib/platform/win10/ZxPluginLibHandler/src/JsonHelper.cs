using System;
using System.Runtime.Serialization.Json;
using System.IO;
using System.Text;
using System.Diagnostics;

namespace CocosAppWinRT.ZxPlugin
{
    /// <summary>
    /// Provides JSON serialization/deserialization functionality.
    /// </summary>
    static class JsonHelper
    {
        /// <summary>
        /// Serializes object to JSON string representation
        /// </summary>
        /// <param name="_obj">object to serialize</param>
        /// <returns>JSON representation of the object. Returns 'null' string for null passed as argument</returns>
        public static string Serialize(object _obj)
        {
            // verify entry params 
            if (null == _obj) return "null";

            // serialize objet in json
            DataContractJsonSerializer ser = new DataContractJsonSerializer(_obj.GetType());
            string json = String.Empty;
            using (MemoryStream ms = new MemoryStream())
            {
                ser.WriteObject(ms, _obj);
                ms.Position = 0;
                using (StreamReader sr = new StreamReader(ms)) json = sr.ReadToEnd();
            }

            return json;
        }

        /// <summary>
        /// Parses json string to object instance
        /// </summary>
        /// <typeparam name="T">type of the object</typeparam>
        /// <param name="_json">json string representation of the object</param>
        /// <returns>Deserialized object instance</returns>
        public static T Deserialize<T>(string _json)
        {

            // deserialize object
            DataContractJsonSerializer deserializer = new DataContractJsonSerializer(typeof(T));
            object result = null;
            try
            {
                using (MemoryStream mem = new MemoryStream(Encoding.UTF8.GetBytes(_json))) result = deserializer.ReadObject(mem);
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine("Failed to deserialize " + typeof(T) + " with JSON value :: " + _json);
            }

            return (T)result;
        }
    }
}
