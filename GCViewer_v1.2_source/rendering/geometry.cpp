#include "rendering/geometry.h"

#include <QtOpenGL>

Face::Face(const QVector<QVector3D> &v)
  : valid_(true)
{
  if(v.size()<3){
    valid_ = false;
    return;
  }
  v_ = v;
  QVector3D center;
  for(int i=0;i<v_.size();i++){
    center += v_[i];
  }
  center_ = center/v_.size();
  color_ = QColor(0xffffffff);
  QVector3D a = (v[1]-v[0]), b = (v[2]-v[0]);
  n_ = QVector3D::crossProduct(a,b);
}

Face::Face(const QVector<QVector3D> &v, const QColor &color)
  : valid_(true)
{
  if(v.size()<3){
    valid_ = false;
    return;
  }
  v_ = v;
  QVector3D center;
  for(int i=0;i<v_.size();i++){
    center += v_[i];
  }
  center_ = center/v_.size();
  color_ = color;
  QVector3D a = (v[1]-v[0]), b = (v[2]-v[0]);
  n_ = QVector3D::crossProduct(a,b);
}

Face::Face(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2)
  : valid_(true)
{
  v_.resize(3);
  v_[0] = v0;
  v_[1] = v1;
  v_[2] = v2;
  center_ = (v0 + v1 + v2)/3;
  color_ = QColor(0xffffffff);
  QVector3D a = (v1-v0), b = (v2-v0);
  n_ = QVector3D::crossProduct(a,b);
}

Face::Face(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QColor &color)
  : valid_(true)
{
  v_.resize(3);
  v_[0] = v0;
  v_[1] = v1;
  v_[2] = v2;
  center_ = (v0 + v1 + v2)/3;
  color_ = color;
  QVector3D a = (v1-v0), b = (v2-v0);
  n_ = QVector3D::crossProduct(a,b);
}

void Face::Draw(const float &spread, const float &shrink, const bool user_color) const
{
  glPushMatrix();

  if(shrink>0){
    glTranslatef(center_.x(),center_.y(),center_.z());
    glScalef(1-shrink,1-shrink,1-shrink);
    glTranslatef(-center_.x(),-center_.y(),-center_.z());
  }

  if(spread>0){
    QVector3D s = center_*(spread);
    glTranslatef(s.x(),s.y(),s.z());
  }

  if(!user_color){
    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  }
  GLenum type = v_.size()>3?GL_POLYGON:GL_TRIANGLES;
  glBegin(type);
  glNormal3f(n_.x(),n_.y(),n_.z());
  for(int i=0;i<v_.size();i++){
    glVertex3f(v_[i].x(),v_[i].y(),v_[i].z());
  }
  glEnd();

  glBegin(type);
  glNormal3f(-n_.x(),-n_.y(),-n_.z());
  for(int i=v_.size()-1;i>=0;i--){
    glVertex3f(v_[i].x(),v_[i].y(),v_[i].z());
  }
  glEnd();

  glPopMatrix();
}

void Face::DrawTetraFace(const float &spread, const float &shrink, const bool user_color) const
{
  glBegin(GL_TRIANGLES);
  if(!user_color){
    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  }
  glNormal3f(n_.x(),n_.y(),n_.z());
  glVertex3f(v_[0].x(),v_[0].y(),v_[0].z());
  glVertex3f(v_[1].x(),v_[1].y(),v_[1].z());
  glVertex3f(v_[2].x(),v_[2].y(),v_[2].z());
  glEnd();
}

void Face::SetColor(const QColor &color)
{
  color_ = color;
}

//2D
Tetrahedron::Tetrahedron(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2)
{
  f[0] = new Face(v0,v1,v2);
  f[1] = new Face(v0,v2,v1);

  qDebug() << "v0" << v0;
  qDebug() << "v1" << v1;
  qDebug() << "v2" << v2;

  face_count_ = 2;
  center_ = (v0 + v1 + v2)/3;
}

//3D
Tetrahedron::Tetrahedron(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QVector3D &v3)
{
  f[0] = new Face(v0,v1,v2);
  f[1] = new Face(v1,v3,v2);
  f[2] = new Face(v3,v1,v0);
  f[3] = new Face(v2,v3,v0);

  face_count_ = 4;
  center_ = (v0 + v1 + v2 + v3)/4;
}

Tetrahedron::~Tetrahedron(){
  for(int i=0;i<4;i++){
    if(f[i]!=NULL){
      delete f[i];
    }
  }
}

void Tetrahedron::Draw(const float &spread, const float &shrink, const bool user_color) const
{
  glPushMatrix();

  if(shrink>0){
    glTranslatef(center_.x(),center_.y(),center_.z());
    glScalef(1-shrink,1-shrink,1-shrink);
    glTranslatef(-center_.x(),-center_.y(),-center_.z());
  }

  if(spread>0){
    QVector3D s = center_*(spread);
    glTranslatef(s.x(),s.y(),s.z());
  }

  for(int i=0;i<face_count_;i++){
    if(f[i]!=NULL){
      f[i]->DrawTetraFace(spread,shrink,user_color);
    }
  }

  glPopMatrix();
}

void Tetrahedron::SetColor(const QColor &color)
{
  for(int i=0;i<face_count_;i++){
    if(f[i]!=NULL){
      f[i]->SetColor(color);
    }
  }
}
