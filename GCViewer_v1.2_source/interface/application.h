#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class MainWindow;
class Scene;

class Application : public QApplication
{
  Q_OBJECT
public:
  explicit Application(int &argc, char **argv);
  virtual ~Application();

private:
  MainWindow *main_window_;
  Scene *scene_;
};

#endif // APPLICATION_H
