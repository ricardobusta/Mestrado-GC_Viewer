#ifndef OBJECTCONTROLWIDGET_H
#define OBJECTCONTROLWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ObjectControlWidget;
}

class SceneObject;

class ObjectControlWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ObjectControlWidget(SceneObject *object_, QWidget *parent = 0);
  ~ObjectControlWidget();

  SceneObject *object_;
private:
  Ui::ObjectControlWidget *ui_;

private slots:
  void ToggleVisible(bool value);
  void DeleteObject();
  void SelectColor();
signals:
  void VisibilityChanged();
  void ObjectDeleted();
};

#endif // OBJECTCONTROLWIDGET_H
