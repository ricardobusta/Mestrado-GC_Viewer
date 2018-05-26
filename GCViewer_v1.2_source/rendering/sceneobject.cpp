#include "rendering/sceneobject.h"

SceneObject::SceneObject(const QString &name, const QString &owner, const int &scale, const QString &color)
  : name_(name),
    owner_(owner),
    color_(QColor("#"+color)),
    visible_(true),
    deleted_(false),
    scale_((scale>0)?(1.0/scale):(1.0))
{
}

void SceneObject::Draw(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const
{
  if(!deleted_ && visible_){
    glPushMatrix();
    glScalef(scale_,scale_,scale_);
    DrawObject(spread,shrink,user_color,current_frame);
    glPopMatrix();
  }
}

void SceneObject::Vertex(const QVector3D &v) const
{
  glVertex3f(v.x(),v.y(),v.z());
}

void SceneObject::Color(const QColor &c) const
{
  glColor4f(c.redF(),c.greenF(),c.blueF(),c.alphaF());
}
