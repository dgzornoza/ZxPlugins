
package org.cocos2dx.zxplugin;

public class CommandHandler  {
	
	public native void doTest();  // to be supplied in C++ trhough JNI

	public void showId() {  // replace the previous version of example 5
			 
		doTest();         // <==== invoke the native method
	}
}

