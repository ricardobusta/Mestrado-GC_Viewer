#include "rendering/sceneconvexhull.h"

#include "sceneobject.h"
#include "geometry.h"
#include "ric.h"

SceneConvexHull::SceneConvexHull(const QString &name, const QString &owner, const double &spread, const QString &color)
  : SceneObject(name,owner,spread,color)
{
}

SceneConvexHull::~SceneConvexHull()
{
  ClearFaces();
}

void SceneConvexHull::DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const
{
  if(user_color){
    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  }
  int cf = current_frame%faces_.size();
  foreach(Face *face, faces_[cf]){
    if(face!=NULL){
      face->Draw(spread,shrink,user_color);
    }
  }
}

void SceneConvexHull::ClearFaces()
{
  while(!faces_.isEmpty()){
    while(!faces_.first().isEmpty()){
      Face *f = faces_.first().first();
      faces_.first().pop_front();
      if(f!=NULL){
        delete f;
      }
    }
    faces_.pop_front();
  }
}

void SceneConvexHull::Colorize()
{
  foreach(QVector<Face*> faces, faces_){
    foreach(Face *face, faces){
      int r,g,b;
      r = Ric::rand(256);
      g = Ric::rand(256);
      b = Ric::rand(256);
      face->SetColor(QColor(r,g,b));
    }
  }
}

void SceneConvexHull::Delete()
{
  deleted_ = true;
  ClearFaces();
}
