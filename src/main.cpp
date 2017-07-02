#include "define.h"
#include "app/application.h"

using namespace APP;

int main(int argc, char ** argv)
{
	Application app(argc, argv);

	return app.exec();
}
