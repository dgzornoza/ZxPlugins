#include "MainMenuLayer.h"

using namespace cocos2d;

// Namespace anonimo para crear objetos SOLO en el ambito de este archivo cpp
namespace
{
	/** Estructura para crear la lista de acciones del menu */
	typedef struct st_testList
	{
		/** Nombre de la accion */
		std::string name;
		/** Puntero a la funcion con la escena que implementa la accion */
		std::function<Scene*()> callback;

	} TestList;

	/** Estructura para crear la lista de acciones del menu */
	std::vector<TestList> g_testList;


	/** Numero de elementos de la lista de acciones */
	static int g_testListCount;
}

/** Constructor por defecto de la clase */
MainMenuLayer::MainMenuLayer(void)
{
	// inicializar lista de acciones
	//g_testList.push_back({ "Prueba", [](){ return Scenes::Circuit::CircuitScene::create(); } });
	

	// guardar el numero de elementos
	g_testListCount = g_testList.size();
}

/** Destructor por defecto de la clase */
MainMenuLayer::~MainMenuLayer(void)
{
}

/** 
* Metodo sobreescrito que sera invocado para inicializar la instancia de la clase
* @return True si se puede ha inicializado correctamente, false en caso contrario
*/
bool MainMenuLayer::init()
{
	// Inicializar la clase base
	if ( !Layer::init() ) return false;

	// obtener dimensiones de diseño
	Size screenSize = Director::getInstance()->getWinSize();

	// cachear los spriteframes del menu
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MainMenu/gui.plist", "MainMenu/gui.png");
	    
	// crear un layout principal para los controles UI
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(screenSize);
	this->addChild(layout);

	// crear el menu con las acciones
	this->_createMenu(layout);
	// crear el boton para cerrar la aplicacion
	this->_createCloseButton(layout);

	// inicializacion correcta
	return true;
}	

/** Funcion para la creacion del menu principal */
void MainMenuLayer::_createMenu(ui::Layout* _layout)
{
	// crear el list view
	ui::ListView* lv = ui::ListView::create();
    lv->setItemsMargin(10);
	lv->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
	lv->setContentSize(Size(Director::getInstance()->getWinSize().width, 250.0f));	

	// añadir toddas las acciones al list view
	for (int i = 0; i < g_testListCount; ++i)
    {
		ui::Text* text = ui::Text::create(g_testList[i].name, "fonts/AveriaSansLibre-Bold.ttf", 30);
		text->setColor(Color3B(159, 168, 176));
		text->setTouchEnabled(true);
		lv->pushBackCustomItem(text);
    }
	
	// eventos de seleccion de items
	lv->addEventListener((ui::ListView::ccListViewCallback)[](Ref* _sender, ui::ListView::EventType _type)		
	{
		// evaluar el tipo de evento generado
		switch (_type)
		{

		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:

			// obtener el listview
			ui::ListView* lv = static_cast<ui::ListView*>(_sender);
			// obtener el indice del elemento seleccionado y el item seleccionado
			ssize_t selectedIndex = lv->getCurSelectedIndex();
			ui::Widget* selectedItem = lv->getItem(selectedIndex);
			
			// crear acciones para dar efecto al item seleccionado y cambiar a la escena que impelemnta la accion cuando finalicen
			//selectedItem->runAction(TintTo::create(1.0f, 0x0, 0xFF, 0x0));
			//selectedItem->runAction(Sequence::create(DelayTime::create(.3f), ScaleTo::create(.7f, 1.0f, .0f), nullptr));
			//selectedItem->runAction(Sequence::create(				
			//	Sequence::create(MoveBy::create(.3f, Vec2(-20.0f, .0f)), MoveBy::create(.7f, Vec2(500.0f, .0f)), nullptr),
			//	CallFunc::create([selectedIndex]()
			//	{
			//		// eliminar todos los datos de la cache de esta capa
			//		Director::getInstance()->purgeCachedData();

			//		// crear la escena con el ejemplo seleccionado por el indice del listview
			//		Scene* scene = g_testList[selectedIndex].callback();

			//		// cambiar a la escena con la accion
			//		Director::getInstance()->replaceScene(scene);
			//	}),
			//	nullptr));
			
			// eliminar todos los datos de la cache de esta capa
			Director::getInstance()->purgeCachedData();
			// crear la escena con el ejemplo seleccionado por el indice del listview
			Scene* scene = g_testList[selectedIndex].callback();
			// cambiar a la escena con la accion
			Director::getInstance()->pushScene(scene);

			break;
		}
	});


	// añadir el listview al layout
    _layout->addChild(lv);
}

/** Funcion para crear el boton para cerrar la aplicacion */
void MainMenuLayer::_createCloseButton(ui::Layout* _layout)
{
	// Crear el boton para cerrar la aplicacion
    ui::Button* closeBtn = ui::Button::create("btn_close_normal.png",	"btn_close_selected.png", "", ui::Widget::TextureResType::PLIST);
	closeBtn->setPosition(Director::getInstance()->getWinSize() - closeBtn->getContentSize());

	// eventos
	closeBtn->addTouchEventListener([](Ref* _sender, ui::Widget::TouchEventType _evtType)
	{			
		// evaluar el tipo de evento generado
		switch (_evtType)
		{

		case ui::Widget::TouchEventType::ENDED :

				// Finalizar la aplicacion
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
				return;
#endif
				Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
#endif
				break;

		}
	});

    _layout->addChild(closeBtn);
}
