//DLLs.cpp


#include "ApplicationKit.h"
#include "DLLsApplication.h"
#include "UndoRedoStack.h"
#include "MainWindow.h"



using namespace VCF;



int main(int argc, char *argv[])
{
	DLLsApplication app;

	Application::appMain( argc, argv );
	
	return 0;
}

