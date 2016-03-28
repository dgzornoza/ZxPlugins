#include "ZPluginsSampleLayer.h"

#include "ZxPlugins-lib/proj.win10/src/PluginFactory.h"

using namespace cocos2d;

/** Constructor por defecto de la clase */
ZPluginsSampleLayer::ZPluginsSampleLayer(void)
{

}

/** Destructor por defecto de la clase */
ZPluginsSampleLayer::~ZPluginsSampleLayer(void)
{
}

/** 
* Metodo sobreescrito que sera invocado para inicializar la instancia de la clase
* @return True si se puede ha inicializado correctamente, false en caso contrario
*/
bool ZPluginsSampleLayer::init()
{
	// Inicializar el padre primero
	if ( !Layer::init() ) return false;

	// Inicializar clase

	// .......

	// prueba, crear un listview con las imagenes


	// obtener dimensiones de diseño
	Size screenSize = Director::getInstance()->getWinSize();

	// crear un layout principal para los controles UI
	ui::Layout* layout = ui::Layout::create();
	layout->setSize(screenSize);
	this->addChild(layout);

	// crear el list view
	ui::ListView* lv = ui::ListView::create();
	lv->setItemsMargin(10);
	lv->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
	lv->setSize(Size(Director::getInstance()->getWinSize().width, 250.0f));

	layout->addChild(lv);

	zplugin::zmedia::ZMedia* zmediaPlugin = zplugin::PluginFactory::getInstance()->loadPlugin<zplugin::zmedia::ZMedia>("zmedia");


	zmediaPlugin->GetAlbumItems(
		[lv](const std::string& _result)
		{
			rapidjson::Document json;
			json.Parse<0>(_result.data());

			if (json.HasParseError())
			{
				CCLOG("Error al parsear el resultado del plugin zmedia, funcion 'GetAlbumItems'");
				return;
			};

			const rapidjson::Value& jsonMessage = json["message"];

			// recorrer todos los items
			for (rapidjson::SizeType i = 0; i < jsonMessage.Size(); i++)
			{
				//// imagenes
				//const rapidjson::Value& image = jsonMessage[i]["Image"];

				//ssize_t size = image.Size();
				//unsigned char* data = new unsigned char[size];
				//for (ssize_t k = 0; k < size; k++)
				//{
				//	data[k] = (unsigned char)image[k].GetInt();
				//}
				//
				//Image* img = new Image();
				//img->initWithImageData(data, size);
				//Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(img, jsonMessage[i]["Name"].GetString());
				//Sprite* sprite = Sprite::createWithTexture(texture);
				//
				//auto* a = ui::Widget::create();
				//a->addChild(sprite);
				//lv->pushBackCustomItem(a);

				//delete img;
				//delete data;
				

				
				// Texto
				const rapidjson::Value& name = jsonMessage[i]["Name"]; 
				ui::Text* text = ui::Text::create(name.GetString(), "fonts/AveriaSansLibre-Bold.ttf", 30);
				text->setColor(Color3B(159, 168, 176));
				text->setTouchEnabled(true);
				lv->pushBackCustomItem(text);

			};




		},
			[](const std::string& _error){
			CCLOG("Error al invocar la funcion 'GetAlbumItems' del plugin zmedia");
			return;
		});

		_createTestButton(layout);

	// inicializacion correcta
	return true;
}	


/** Funcion para crear el boton para cerrar la aplicacion */
void ZPluginsSampleLayer::_createTestButton(ui::Layout* _layout)
{
	// cachear los spriteframes
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MainMenu/gui.plist", "MainMenu/gui.png");


	// Crear el boton para cerrar la aplicacion
	ui::Button* closeBtn = ui::Button::create("btn_close_normal.png", "btn_close_selected.png", "", ui::Widget::TextureResType::PLIST);
	closeBtn->setPosition(Director::getInstance()->getWinSize() - closeBtn->getSize());

	// eventos
	closeBtn->addTouchEventListener([](Ref* _sender, ui::Widget::TouchEventType _evtType)
	{
		// evaluar el tipo de evento generado
		switch (_evtType)
		{

		case ui::Widget::TouchEventType::ENDED:

			zplugin::zmedia::ZMedia* zmediaPlugin = zplugin::PluginFactory::getInstance()->loadPlugin<zplugin::zmedia::ZMedia>("zmedia");
			zmediaPlugin->GetAlbumItems(
				[](const std::string& _result)
			{
				rapidjson::Document json;
				json.Parse<0>(_result.data());

				if (json.HasParseError())
				{
					CCLOG("Error al parsear el resultado del plugin zmedia, funcion 'GetAlbumItems'");
					return;
				};

				const rapidjson::Value& jsonMessage = json["message"];

				// recorrer todos los items
				for (rapidjson::SizeType i = 0; i < jsonMessage.Size(); i++)
				{
					//const rapidjson::Value& image = jsonMessage[i]["Image"];
					const rapidjson::Value& name = jsonMessage[i]["Name"];

				};




			},
				[](const std::string& _error){
				CCLOG("Error al invocar la funcion 'GetAlbumItems' del plugin zmedia");
				return;
			});

			break;

		}
	});

	_layout->addChild(closeBtn);
}