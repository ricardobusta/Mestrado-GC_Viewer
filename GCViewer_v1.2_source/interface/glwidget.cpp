#include "glwidget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>

#include "rendering/scene.h"

const float kAxisWidth = 0.025;
const float kAxisSize = 0.9;
const float kArrowWidth = 2*kAxisWidth;
const float kArrowSize = kAxisSize+0.1;

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent),
  scene_(NULL)
{
  connect(&auto_paint_timer_,SIGNAL(timeout()),this,SLOT(AutoPaint()));

  auto_paint_timer_.start(1000/60);
}

void GLWidget::SetScene(Scene *scene)
{
  scene_ = scene;
}

void GLWidget::UpdateBGColor()
{
  QColor bg = palette().background().color();
  glClearColor(bg.redF(),bg.greenF(),bg.blueF(),1);
}

void GLWidget::initializeGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  UpdateBGColor();

  QImage text_font_ = QImage("://font.png");
  bindTexture(text_font_,GL_TEXTURE_2D);
}

void GLWidget::resizeGL(int w, int h)
{
  int size = qMax(w,h);
  glViewport((w-size)/2.0,(h-size)/2.0,size,size);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  glOrtho(-1,1,-1,1,-50,50);
  glFrustum(-.1,.1,-.1,.1,0.1,1000);
  glTranslatef(0,0,-1);

  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL()
{
  glClear(  GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
  glLoadIdentity();

  if(NULL == scene_) return;

  ApplyRot();

  glScalef( scene_->zoom_, scene_->zoom_, scene_->zoom_ );

  DrawAxis();

  scene_->draw();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  if( NULL == scene_ ) return;

  auto_delta_ = QPoint(0,0);
  last_click_ = event->pos();
  event->accept();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if( NULL == scene_ ) return;

  if(delta_.manhattanLength() > 5){
    auto_delta_ = delta_/5;
//    auto_paint_timer_.start(1000/60);
  }else{
    auto_delta_ = QPoint(0,0);
//    auto_paint_timer_.stop();
  }
  event->accept();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
  if( NULL == scene_ ) return;

  float newzoom = scene_->zoom_ + float(event->delta())/5000.0f;
  if(newzoom > 0 && newzoom < 2){
    scene_->zoom_ = newzoom;
  }

  TryRepaint();
  event->accept();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  if( NULL == scene_ ) return;

  delta_ = event->pos()-last_click_;
  last_click_ = event->pos();
  if(event->buttons() & Qt::LeftButton){
    scene_->rot_x_ += delta_.y();
    scene_->rot_y_ += delta_.x();
  }
  TryRepaint();
  event->accept();
}

void GLWidget::ApplyRot()
{
  if( NULL == scene_ ) return;
  glRotatef(scene_->rot_x_,1,0,0);
  glRotatef(scene_->rot_y_,0,1,0);
  glRotatef(scene_->rot_z_,0,0,1);
}

void GLWidget::DrawOneAxis()
{
  glBegin(GL_TRIANGLES);
  glVertex3f(0,0,0);
  glVertex3f(kAxisSize,kAxisWidth,kAxisWidth);
  glVertex3f(kAxisSize,kAxisWidth,-kAxisWidth);

  glVertex3f(0,0,0);
  glVertex3f(kAxisSize,-kAxisWidth,kAxisWidth);
  glVertex3f(kAxisSize,kAxisWidth,kAxisWidth);

  glVertex3f(0,0,0);
  glVertex3f(kAxisSize,kAxisWidth,-kAxisWidth);
  glVertex3f(kAxisSize,-kAxisWidth,-kAxisWidth);

  glVertex3f(0,0,0);
  glVertex3f(kAxisSize,-kAxisWidth,-kAxisWidth);
  glVertex3f(kAxisSize,-kAxisWidth,kAxisWidth);


  glVertex3f(kAxisSize,kArrowWidth,-kArrowWidth);
  glVertex3f(kAxisSize,kArrowWidth,kArrowWidth);
  glVertex3f(kArrowSize,0,0);

  glVertex3f(kAxisSize,kArrowWidth,kArrowWidth);
  glVertex3f(kAxisSize,-kArrowWidth,kArrowWidth);
  glVertex3f(kArrowSize,0,0);


  glVertex3f(kAxisSize,-kArrowWidth,-kArrowWidth);
  glVertex3f(kAxisSize,kArrowWidth,-kArrowWidth);
  glVertex3f(kArrowSize,0,0);

  glVertex3f(kAxisSize,-kArrowWidth,kArrowWidth);
  glVertex3f(kAxisSize,-kArrowWidth,-kArrowWidth);
  glVertex3f(kArrowSize,0,0);

  glEnd();
}

void GLWidget::DrawAxis()
{
  glPushAttrib( GL_ALL_ATTRIB_BITS );
  glDisable(GL_LIGHTING);

  glLineWidth(3);


  glColor3f(1,0,0);
  DrawOneAxis();

  glPushMatrix();
  glRotatef(90,0,0,1);
  glColor3f(0,1,0);
  DrawOneAxis();
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90,0,1,0);
  glColor3f(0,0,1);
  DrawOneAxis();
  glPopMatrix();

  glEnd();

  glPopAttrib();
}

void GLWidget::AutoPaint()
{
  if( NULL == scene_ ) return;
  scene_->rot_x_ += auto_delta_.y();
  scene_->rot_y_ += auto_delta_.x();
  repaint();
}

void GLWidget::TryRepaint()
{
  if(!auto_paint_timer_.isActive()){
    repaint();
  }
}
