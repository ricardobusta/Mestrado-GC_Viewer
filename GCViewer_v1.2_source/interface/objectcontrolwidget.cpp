#include "objectcontrolwidget.h"
#include "ui_objectcontrolwidget.h"

#include "rendering/sceneobject.h"

const QString kStringColorButtonStyle = "QPushButton{\n	background-color: %1;\n  border: 1px solid #999;\n	font: bold;\n color: %2;}\n\nQPushButton::hover{\n	border: 1px solid white;\n}";

ObjectControlWidget::ObjectControlWidget(SceneObject *object, QWidget *parent)
  : QWidget(parent),
    ui_(new Ui::ObjectControlWidget),
    object_(object)
{
  ui_->setupUi(this);

  if( NULL != object ){
    ui_->name_label->setText(object_->name_);
    QColor c2 = object_->color_.lightnessF()>0.5?QColor(0,0,0):QColor(255,255,255);
    ui_->color_button->setStyleSheet(kStringColorButtonStyle.arg(object_->color_.name()).arg(c2.name()));
  }
  connect(ui_->visible_check,SIGNAL(toggled(bool)),this,SLOT(ToggleVisible(bool)));
  connect(ui_->delete_button,SIGNAL(clicked()),this,SLOT(DeleteObject()));
  connect(ui_->color_button,SIGNAL(clicked()),this,SLOT(SelectColor()));
}

ObjectControlWidget::~ObjectControlWidget()
{
  delete ui_;
}

void ObjectControlWidget::ToggleVisible(bool value)
{
  if( NULL != object_ ){
    object_->visible_ = value;
  }
  emit VisibilityChanged();
}

void ObjectControlWidget::DeleteObject()
{
  object_->Delete();
  emit ObjectDeleted();
}

void ObjectControlWidget::SelectColor()
{
  QColor c = QColorDialog::getColor(object_->color_,NULL,"Select "+object_->name_+" Color");
  if(c.isValid()){
    object_->color_ = c;
    QColor c2 = c.lightnessF()>0.5?QColor(0,0,0):QColor(255,255,255);
    ui_->color_button->setStyleSheet(kStringColorButtonStyle.arg(object_->color_.name()).arg(c2.name()));
    emit VisibilityChanged();
  }
}
