using System;

namespace CocosAppWinRT.ZxPlugin
{
    /// <summary>
    /// Represents command execution result
    /// </summary>
    public class CommandResult : EventArgs
    {
        /// <summary>
        /// Predefined resultant messages
        /// </summary>
        public static string[] StatusMessages = new string[] 
		{
			"No result",
			"OK",
			"Class not found",
			"Illegal access",
			"Instantiation error",
			"Malformed url",
			"IO error",
			"Invalid action",
			"JSON error",
			"Error"
		};

        /// <summary>
        /// Possible command results status codes
        /// </summary>
        public enum Status : int
        {
            NO_RESULT = 0,
            OK,
            CLASS_NOT_FOUND_EXCEPTION,
            ILLEGAL_ACCESS_EXCEPTION,
            INSTANTIATION_EXCEPTION,
            MALFORMED_URL_EXCEPTION,
            IO_EXCEPTION,
            INVALID_ACTION,
            JSON_EXCEPTION,
            ERROR
        };

        public Status Result { get; private set; }
        public string Message { get; set; }
        public bool KeepCallback { get; set; }
        public string CallbackId { get; set; }

        /// <summary>
        /// Whether command succeded or not
        /// </summary>
        public bool IsSuccess
        {
            get
            {
                return this.Result == Status.OK || this.Result == Status.NO_RESULT;
            }
        }

        /// <summary>
        /// Creates new instance of the PluginResult class.
        /// </summary>
        /// <param name="status">Execution result</param>
        public CommandResult(Status status)
            : this(status, CommandResult.StatusMessages[(int)status])
        {
        }

        /// <summary>
        /// Creates new instance of the PluginResult class.
        /// </summary>
        /// <param name="status">Execution result</param>
        /// <param name="message">The message</param>
        public CommandResult(Status status, object message)
        {
            this.Result = status;
            this.Message = JsonHelper.Serialize(message);
        }

        /// <summary>
        /// Convert command result to json string
        /// </summary>
        /// <returns>string in json with command result</returns>
        public string ToJSONString()
        {
            string res = String.Format("\"status\":{0},\"message\":{1},\"keepCallback\":{2}",
                (int)this.Result,
                this.Message,
                this.KeepCallback.ToString().ToLower());

            res = "{" + res + "}";
            return res;

        }

        /// <summary>
        /// Redefine object.ToString() for get command result in json
        /// </summary>
        /// <returns>string in json with command result</returns>
        public override String ToString()
        {
            return this.ToJSONString();
        }

    }

}
