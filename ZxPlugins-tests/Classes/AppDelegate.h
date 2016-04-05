#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"


/**
@brief La aplicacion cocos2dx.

La razon para implementar como herencia privada es ocultar algunas interfaces invocadas por el director
*/
class  AppDelegate : private cocos2d::Application
{
public:
	
	/** Constructor por defecto de la clase */
    AppDelegate();
	/** Destructor por defecto de la clase */
    virtual ~AppDelegate();

	/*
	 @brief Funcion para inicializar los atributos del contexto OpenGL
	 @remarks is se quiere un contexto diferente puede modificarse el valor de glContextAttrs, esto tendra efecto en todas las plataformas
	 */
    virtual void initGLContextAttrs();

    /**
    @brief  Funcion con el codigo de inicio de la escena y el director
    @return true    Inicializacion correcta, continuar con la aplicacion.
    @return false   Inicializacion incorrecta, terminar la aplicacon
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Funcion que sera invocada cuando la aplicacion entre en segundo plano
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Funcion que sera invocada cuando la aplicacion entre en primer plano
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

