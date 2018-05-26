#include "interface/mainwindow.h"
#include "interface/application.h"

int main(int argc, char *argv[])
{
  Application a(argc, argv);

  return a.exec();
}
