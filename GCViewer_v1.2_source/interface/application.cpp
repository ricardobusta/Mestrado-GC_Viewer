#include "application.h"

#include <QTime>

#include "mainwindow.h"
#include "rendering/scene.h"
#include "ric.h"

Application::Application(int &argc, char **argv)
  : QApplication(argc,argv)
{
  Ric::seeded=false;
  Ric::init();
  scene_ = new Scene(this);
  main_window_ = new MainWindow(scene_);
  main_window_->show();
}

Application::~Application()
{
  if( NULL != scene_ ){
    delete scene_;
  }
}
