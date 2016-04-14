package com.dgzornoza.zxplugin;

import java.util.Objects;
import org.json.simple.JSONObject;

/// <summary>
/// Represents command execution result
/// </summary>
public class CommandResult
{

    private Status m_result;
    private String m_message;
    private boolean m_keepCallback;
    private String m_callbackId;

    public static String[] StatusMessages = new String[]
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

    public Status getResult() { return m_result; }
    public void setResult(Status _result) { this.m_result = _result; }

    public String getMessage() { return m_message; }
    public void setMessage(String _message) { this.m_message = _message; }

    public boolean isKeepCallback() { return m_keepCallback; }
    public void setKeepCallback(boolean _keepCallback) { this.m_keepCallback = _keepCallback; }

    public String getCallbackId() { return m_callbackId; }
    public void setCallbackId(String _callbackId) { this.m_callbackId = _callbackId; }

    /// <summary>
    /// Possible command results status codes
    /// </summary>
    public enum Status
    {
        NO_RESULT(0),
        OK(1),
        CLASS_NOT_FOUND_EXCEPTION(2),
        ILLEGAL_ACCESS_EXCEPTION(3),
        INSTANTIATION_EXCEPTION(4),
        MALFORMED_URL_EXCEPTION(5),
        IO_EXCEPTION(6),
        INVALID_ACTION(7),
        JSON_EXCEPTION(8),
        ERROR(9);

        private final int m_value;

        Status(final int _value) { m_value = _value; }

        public int getValue() { return m_value; }

    }
    /// <summary>
    /// Whether command succeded or not
    /// </summary>
    public boolean getIsSuccess()
    {
        return this.m_result == Status.OK || this.m_result == Status.NO_RESULT;
    }

    /// <summary>
    /// Creates new instance of the PluginResult class.
    /// </summary>
    /// <param name="_status">Execution result</param>
    public CommandResult(Status _status)
    {
        this.m_result = _status;
        this.m_message =  CommandResult.StatusMessages[_status.getValue()];
    }

    /// <summary>
    /// Creates new instance of the PluginResult class.
    /// </summary>
    /// <param name="_status">Execution result</param>
    /// <param name="_message">The message</param>
    public CommandResult(Status _status, JSONObject _message)
    {
        this.m_result = _status;
        this.m_message = _message.toString();
    }

    /// <summary>
    /// Convert command result to json String
    /// </summary>
    /// <returns>String in json with command result</returns>
    public String ToJSONString()
    {
        return "{\"status\":" + this.m_result + ",\"message\":" + this.getMessage() + ",\"keepCallback\":" + this.m_keepCallback + "}";
    }

    /// <summary>
    /// Redefine object.ToString() for get command result in json
    /// </summary>
    /// <returns>String in json with command result</returns>
    public String toString()
    {
        return this.ToJSONString();
    }
}