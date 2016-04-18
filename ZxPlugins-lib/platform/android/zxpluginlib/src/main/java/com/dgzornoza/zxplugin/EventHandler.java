package com.dgzornoza.zxplugin;

/** Interface for manage events handlers */
public interface EventHandler<TEventArgs>
{
    void Invoke(Object sender, TEventArgs e);
}
