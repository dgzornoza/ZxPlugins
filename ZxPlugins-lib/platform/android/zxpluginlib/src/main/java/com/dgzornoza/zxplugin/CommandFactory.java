package com.dgzornoza.zxplugin;

import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 Provides functionality to create plugin command by name.
*/
public class CommandFactory
{
    /**
     Namespace base for all commands
    */
    private static final String BaseCommandNamespacePrefix = "com.dgzornoza.zxplugin.";

    /**
     Cache instantiated commands in a map.
    */
    private static Map<String, BaseCommand> commandMap = new HashMap<>();

    /**
     Creates command using command class name. Returns null for unknown commands.
     @param _service Command class name, for example Device or Notification
     @return Command class instance or null
     @remarks alias can be used as a namespace which is resolved + service
     or it can be the fully qualified classname
     or the classname in the current assembly
    */
    public static BaseCommand CreateByServiceName(String _service)
    {
        if (null == _service || _service.trim().length() == 0)
        {
            throw new IllegalArgumentException("service to create can't be null");
        }

        if (!commandMap.containsKey(_service))
        {
            Class classDefinition;

            try
            {
                classDefinition = Class.forName(BaseCommandNamespacePrefix + _service);
            }
            catch (ClassNotFoundException e)
            {
                Logger.getLogger("CommandFactory").log(Level.WARNING, "Unable to locate command :: " + _service);
                e.printStackTrace();
                return null;
            }

            try
            {
                commandMap.put(_service, (BaseCommand)classDefinition.newInstance());
            }
            catch (InstantiationException e)
            {
                e.printStackTrace();
            }
            catch (IllegalAccessException e)
            {
                e.printStackTrace();
            }
        }

        return commandMap.get(_service);
    }

    /**
     Function for reset all commands cached
    */
    public static void ResetAllCommands()
    {
        for (BaseCommand bc : commandMap.values())
        {
            bc.OnReset();
        }
    }
}