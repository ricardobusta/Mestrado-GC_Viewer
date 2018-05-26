#include "interface/mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidgetItem>
#include <QFileDialog>

#include "rendering/scene.h"
#include "rendering/sceneobject.h"
#include "interface/objectcontrolwidget.h"

const QString version = "v1.0";

MainWindow::MainWindow(Scene *scene, QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow),
  scene_(scene)
{
  ui_->setupUi(this);

  setWindowTitle(windowTitle()+" "+version);

  ui_->glwidget->SetScene( scene );

  if( NULL == scene_ )
    close();

  connect(ui_->shrink_slider,SIGNAL(valueChanged(int)),scene_,SLOT(SetShrink(int)));
  connect(ui_->spread_slider,SIGNAL(valueChanged(int)),scene_,SLOT(SetSpread(int)));
  ui_->user_color_check->setChecked(scene_->user_color_);
  connect(ui_->user_color_check,SIGNAL(toggled(bool)),scene_,SLOT(SetUserColor(bool)));
  ui_->wireframe_checkBox->setChecked(scene_->wireframe_);
  connect(ui_->wireframe_checkBox,SIGNAL(toggled(bool)),scene_,SLOT(SetWireframe(bool)));
  connect(scene_,SIGNAL(Repaint()),ui_->glwidget,SLOT(TryRepaint()));
  connect(ui_->load_button,SIGNAL(clicked()),this,SLOT(LoadFile()));
  connect(ui_->color_button,SIGNAL(clicked()),this,SLOT(BackgroundChanged()));
  scene_->SetFrameDelay(ui_->fps_spin->value());
  connect(ui_->fps_spin,SIGNAL(valueChanged(int)),scene_,SLOT(SetFrameDelay(int)));
  SceneChanged();
}

MainWindow::~MainWindow()
{
  delete ui_;
}

void MainWindow::SceneChanged()
{
  if( NULL == scene_ ) return;
  ui_->listWidget->clear();
  ObjectControlWidget *w = qobject_cast<ObjectControlWidget*>(sender());
  if( NULL != w ){
    scene_->objects_.remove(scene_->objects_.indexOf(w->object_));
  }
  for(int i=0;i<scene_->objects_.size();i++){
    if( scene_->objects_[i]->deleted_ ) continue;
    ObjectControlWidget *widget = new ObjectControlWidget(scene_->objects_[i]);
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(widget->size());
    ui_->listWidget->addItem(item);
    ui_->listWidget->setItemWidget(item,widget);
    connect(widget,SIGNAL(VisibilityChanged()),ui_->glwidget,SLOT(TryRepaint()));
    connect(widget,SIGNAL(ObjectDeleted()),this,SLOT(SceneChanged()));
  }
  ui_->glwidget->TryRepaint();
}

void MainWindow::LoadFile()
{
  QStringList file_names = QFileDialog::getOpenFileNames(this,"Load File",".","Text File (*.txt);;Input File (*.input, *.hull, *tetra);;All Files (*.*)");

  for(int i=0;i<file_names.size();i++){
    scene_->LoadFile(file_names[i]);
  }
  if(file_names.size()>0){
    SceneChanged();
  }
}

void MainWindow::BackgroundChanged()
{
  QColor c = QColorDialog::getColor(centralWidget()->palette().background().color(),NULL,"Select Window Background Color");
  if(c.isValid()){
    QColor c2 = c.lightnessF()>0.5?QColor(0,0,0):QColor(255,255,255);
    centralWidget()->setStyleSheet("background-color: "+c.name()+"; color: "+c2.name()+";");
    ui_->glwidget->UpdateBGColor();
  }
}
