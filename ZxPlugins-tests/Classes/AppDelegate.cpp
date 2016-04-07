#include "AppDelegate.h"
#include "BasicScene.h"
#include "MainMenuLayer.h"
#include "cordova_plugin_device_test\cordova_plugin_device_test.h"

using namespace cocos2d;

// Resoluciones de diseño y de pantalla
static cocos2d::Size s_designResolutionSize = cocos2d::Size(480, 320);		// 4 pixeles por pixel
static cocos2d::Size s_sdResolutionSize = cocos2d::Size(480, 320);		// SD
static cocos2d::Size s_hdResolutionSize = cocos2d::Size(960, 640);		// HD
//static cocos2d::Size s_mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size s_hdrResolutionSize = cocos2d::Size(1920, 1280);	// HDR
//static cocos2d::Size s_largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}


void AppDelegate::initGLContextAttrs()
{
	// establecer el contexto OpenGL, ahora puede establecerse solo 6 atributos
	// rojo, verde, azul, alfa, profundidad, plantilla
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

/** Si se quiere usar package manager para instalar mas paquetes, no debe modificarse o eliminar esta funcion */
static int register_all_packages()
{
	return 0; // flag para usar package manager
}

bool AppDelegate::applicationDidFinishLaunching() 
{
	// HACK: verificar (NO funciona)
	//std::locale::global(std::locale(""));
	
    // inicializar director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {

        glview = GLViewImpl::create("SamplesGLView"); // 3:2
		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 1280, 1024)); // 5:4
		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 1280, 720)); // 16:9
		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 1067, 600)); // 16:9

		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 960, 640)); // 3:2
		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 480, 320)); // 3:2
		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 1024, 768)); // 4:3
		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 1280, 768)); // 5:3
		//glview = GLViewImpl::createWithRect("SamplesGLView", Rect(0,0, 1280, 720)); // 16:9

		// portrait
		//glview = GLView::createWithRect("SamplesGLView", Rect(0,0, 640, 960)); // 3:2

        director->setOpenGLView(glview);
    }

    // activar depuracion FPS
    director->setDisplayStats(true);
	
	// establecer FPS. El valor por defecto es 1.0/60 si no se llama
    director->setAnimationInterval(1.0f / 60);

	// MULTIRESOLUCION -----------------------------------------

	// guardar dimensiones de pantalla y resolucion de diseño
	glview->setDesignResolutionSize(s_designResolutionSize.width, s_designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
	Size frameSize = glview->getFrameSize();

	// directorio a usar en recursos depediendo de la resolucion
	std::vector<std::string> searchPaths;
	
	// establecer el factor de escala basado en el tamaño de los recursos y las dimensiones de diseño
	// HDR
	//if (frameSize.height > s_hdResolutionSize.height)
	//{
	//	director->setContentScaleFactor(MIN(s_hdrResolutionSize.height / s_designResolutionSize.height, s_hdrResolutionSize.width / s_designResolutionSize.width));
	//	searchPaths.push_back("HDR");
	//}
	//// HD
	//else if (frameSize.height > s_sdResolutionSize.height)
	//{
	//	director->setContentScaleFactor(MIN(s_hdResolutionSize.height / s_designResolutionSize.height, s_hdResolutionSize.width / s_designResolutionSize.width));
	//	searchPaths.push_back("HD");
	//}
	//// SD
	//else
	//{
	//	director->setContentScaleFactor(MIN(s_sdResolutionSize.height / s_designResolutionSize.height, s_sdResolutionSize.width / s_designResolutionSize.width));
	//	searchPaths.push_back("SD");
	//}
	// TODO: usar HD actualmente para el desarrollo continuo
	director->setContentScaleFactor(MIN(s_hdResolutionSize.height / s_designResolutionSize.height, s_hdResolutionSize.width / s_designResolutionSize.width));
	searchPaths.push_back("HD");

	// TODO: verificar que hace
	register_all_packages();

	// establecer directorios base de los recursos
	FileUtils::getInstance()->setSearchPaths(searchPaths);

	// ----------------------------------------------------------
	
    // Crear la escena principal y ejecutarla
	Scene* scene = BasicScene<cordova_plugin_device_test>::create();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {

	// detener el bucle principal
    Director::getInstance()->stopAnimation();

	// si se usa SimpleAudioEngine, debe detenerse
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	
	// reanudar el bucle principal
    Director::getInstance()->startAnimation();

	// si se usa SimpleAudioEngine, debe resumirse
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
