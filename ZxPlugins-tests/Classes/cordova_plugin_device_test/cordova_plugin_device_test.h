
#ifndef __CORDOVA_PLUGIN_DEVICE_TEST_H__
#define __CORDOVA_PLUGIN_DEVICE_TEST_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Infraestructure.h"

/**
 *@brief Clase con el test 'cordova_plugin_device_test'
 */
class cordova_plugin_device_test : public ITest, public cocos2d::Layer
{

public:

	/** Destructor por defecto de la clase */
	virtual ~cordova_plugin_device_test(void);

	/**
	 * Macro que sera desplegada en un metodo estatico 'create' para crear e inicializar la instancia de la clase.
	 * La instancia de la clase debe ser creada invocando el metodo 'cordova_plugin_device_test::create()'
	 */
	CREATE_FUNC(cordova_plugin_device_test);


	/** Funcion para ejecutar el test */
	virtual bool execute();

	// se hace uso de la macro de cocos2dx para definir el acceso de metodos heredados
	// con la finalidad de no violar el principio de sustitucion de Liskov y usar el mismo modificador de las clases base)
CC_CONSTRUCTOR_ACCESS:

	/**
	* Metodo sobreescrito que sera invocado para inicializar la instancia de la clase.
	* @return True si se puede ha inicializado correctamente, false en caso contrario
	*/
	virtual bool init() override;

protected:

	/** Constructor por defecto de la clase (protegido para evitar que se creen instancias desde fuera de la clase, deben crearse mediante el metodo 'cordova_plugin_device_test::create()')*/
	cordova_plugin_device_test(void);

private:

	/** Text control for display device data */
	cocos2d::ui::Text* m_deviceDataText;
};

#endif // __CORDOVA_PLUGIN_DEVICE_TEST_H__

