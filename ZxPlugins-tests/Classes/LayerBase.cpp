#include "LayerBase.h"


using namespace cocos2d;

/** Constructor por defecto de la clase */
LayerBase::LayerBase(void)
{
}

/** Destructor por defecto de la clase */
LayerBase::~LayerBase(void)
{
}

/** 
* Metodo sobreescrito que sera invocado para inicializar la instancia de la clase
* @return True si se puede ha inicializado correctamente, false en caso contrario
*/
bool LayerBase::init()
{
	// 1.- Inicializar el padre primero
	if ( !Layer::init() ) return false;

	// 2.- Inicializar clase

    ////add the menu item for back to main menu
    //TTFConfig ttfConfig("fonts/arial.ttf", 20);
    //auto label = Label::createWithTTF(ttfConfig,"MainMenu");

    //auto menuItem = MenuItemLabel::create(label, testScene_callback );
    //auto menu = Menu::create(menuItem, NULL);

    //menu->setPosition( Vec2::ZERO );
    //menuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    //addChild(menu, 1);

	// inicializacion correcta
	return true;
}	

/** Funcion callback para volver al menu principal 	*/
void LayerBase::_mainMenuCallback(cocos2d::Ref* _sender)
{
	//Scene* scene = Scene::create();

 //   auto layer = new TestController();
 //   scene->addChild(layer);
 //   layer->release();

 //   Director::getInstance()->replaceScene(scene);
}