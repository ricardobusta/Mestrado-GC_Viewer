#include "rendering/scenetetrahedrons.h"

#include "ric.h"

SceneTetrahedrons::SceneTetrahedrons(const QString &name, const QString &owner, const double &spread, const QString &color)
  : SceneObject(name,owner,spread,color)
{

}

SceneTetrahedrons::~SceneTetrahedrons()
{
  ClearTetrahedrons();
}

void SceneTetrahedrons::DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const
{
  if(user_color){
    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  }
  int cf = current_frame%tetrahedrons_.size();
  foreach(Tetrahedron *tetrahedron, tetrahedrons_[cf]){
    if(tetrahedron!=NULL){
      tetrahedron->Draw(spread,shrink,user_color);
    }
  }
}

void SceneTetrahedrons::ClearTetrahedrons()
{
  while(!tetrahedrons_.isEmpty()){
    while(!tetrahedrons_.first().isEmpty()){
      Tetrahedron* tetrahedron = tetrahedrons_.first().first();
      tetrahedrons_.first().pop_front();
      if(tetrahedron!=NULL){
        delete tetrahedron;
      }
    }
    tetrahedrons_.pop_front();
  }
}

void SceneTetrahedrons::Colorize()
{
  foreach(QVector<Tetrahedron*> tetrahedrons, tetrahedrons_){
    foreach(Tetrahedron *tetrahedron, tetrahedrons){
      int r,g,b;
      r = Ric::rand(256);
      g = Ric::rand(256);
      b = Ric::rand(256);
      tetrahedron->SetColor(QColor(r,g,b));
    }
  }
}

void SceneTetrahedrons::Delete()
{
  deleted_ = true;
  ClearTetrahedrons();
}
