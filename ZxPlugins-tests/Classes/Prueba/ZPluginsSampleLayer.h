#ifndef __ZPLUGIN_SAMPLE_LAYER_H__
#define __ZPLUGIN_SAMPLE_LAYER_H__

#include "cocos2d.h"
#include "cocos\ui\CocosGUI.h"
#include "LayerBase.h"

/** 
*@brief Clase con la capa para el ejemplo del articulo dedicado a los plugins para acceder a codigo nativo de las plataformas
* http://discuss.cocos2d-x.org/t/wp8-cocos2dx-and-xaml/4886/6
* http://www.cocos2d-x.org/wiki/How_to_integrate_third_SDK
* http://stackoverflow.com/questions/17304386/how-does-one-make-function-calls-or-trigger-events-from-a-native-component-into
* http://discuss.cocos2d-x.org/t/share-iap-for-windows-phone-8/12701/10
* http://discuss.cocos2d-x.org/t/wp8-c-call-c-function-with-param/11302/2
*/
class ZPluginsSampleLayer : public LayerBase
{

public:

	/** Destructor por defecto de la clase */
	virtual ~ZPluginsSampleLayer(void);

	/** 
	* Macro que sera desplegada en un metodo estatico 'create' para crear e inicializar la instancia de la clase.
	* La instancia de la clase debe ser creada invocando el metodo 'ZPluginsSampleLayer::create()'
	*/
	CREATE_FUNC(ZPluginsSampleLayer);


	// se hace uso de la macro de cocos2dx para definir el acceso de metodos heredados
	// con la finalidad de no violar el principio de sustitucion de Liskov y usar el mismo modificador de las clases base)
CC_CONSTRUCTOR_ACCESS:

	/** 
	* Metodo sobreescrito que sera invocado para inicializar la instancia de la clase.
	* @return True si se puede ha inicializado correctamente, false en caso contrario
	*/
	virtual bool init() override;

protected:

	/** Constructor por defecto de la clase (protegido para evitar que se creen instancias desde fuera de la clase, deben crearse mediante el metodo 'ZPluginsSampleLayer::create()')*/
	ZPluginsSampleLayer(void);


	void _createTestButton(cocos2d::ui::Layout* _layout);
};


#endif // __ZPLUGIN_SAMPLE_LAYER_H__

