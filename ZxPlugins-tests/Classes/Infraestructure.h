#ifndef __INFRAESTRUCTURE_H__
#define __INFRAESTRUCTURE_H__

/** Interface para implementar tests */
class ITest
{
	/**
	@brief Funcion para ejecutar el test 
	@return true si tiene exito, false en caso contrario
	*/
	virtual bool execute() = 0;
};


#endif // __CORDOVA_PLUGIN_DEVICE_TEST_H__