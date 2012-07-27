#include "CSPrecomp.h"

#include "CSApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CSApp app;

	app.Init();
	app.Run();
	app.Cleanup();

	return 0;
}