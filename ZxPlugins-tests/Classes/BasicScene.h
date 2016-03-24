#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "cocos2d.h"
#include <type_traits>



/**
@brief Clase para crear una escena basica con una capa principal especificada en la plantilla.
*/
template<typename Tlayer>
class BasicScene : public cocos2d::Scene
{

public:

	/** Destructor por defecto de la clase */
	virtual ~BasicScene(void) { };

	/**
	* Macro que sera desplegada en un metodo estatico 'create' para crear e inicializar la instancia de la clase.
	* La instancia de la clase debe ser creada invocando el metodo 'BasicScene<TLayer>::create()'
	*/
	CREATE_FUNC(BasicScene<Tlayer>);

	// se hace uso de la macro de cocos2dx para definir el acceso de metodos heredados
	// con la finalidad de no violar el principio de sustitucion de Liskov y usar el mismo modificador de las clases base)
CC_CONSTRUCTOR_ACCESS:

	/**
	* Metodo sobreescrito que sera invocado para inicializar la instancia de la clase.
	* @return True si se ha inicializado correctamente, false en caso contrario
	*/
	virtual bool init() override
	{
		// 1.- Inicializar la escena padre
		if (!Scene::init()) return false;
		
		// 2.- inicializar capas
		this->m_mainlayer = Tlayer::create();

		// 3.- añadir capas a la escena
		this->addChild(this->m_mainlayer);
		
		// inicializacion correcta
		return true;
	}

protected:

	/**
	@brief Constructor por defecto de la clase (protegido para evitar que se creen instancias desde fuera de la clase, deben crearse mediante el metodo 'BasicScene<Tlayer>::create()').
	*/
	BasicScene(void) {};

	/** Capa principal que contiene la escena */
	Tlayer* m_mainlayer;
};


#endif // __SCENE_BASE_H__

