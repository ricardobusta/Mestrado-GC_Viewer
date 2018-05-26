#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Scene;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(Scene *scene, QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui_;
  Scene *scene_;

  void SetObjectListSize(int size);
private slots:
  void SceneChanged();
  void LoadFile();
  void BackgroundChanged();
};

#endif // MAINWINDOW_H
