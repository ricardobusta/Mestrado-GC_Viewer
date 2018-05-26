#include "rendering/scene.h"

#include <QTime>

#include "rendering/sceneobject.h"
#include "rendering/scenepointcloud.h"
#include "rendering/sceneconvexhull.h"
#include "rendering/scenetetrahedrons.h"
#include "rendering/scenetext.h"

const QString kInputString = "INPUT";
const QString kHullString = "HULL";
const QString kTetraString = "TETRA";
const QString k3DString = "3D";
const QString k2DString = "2D";

QString ReadValidLine(QTextStream &ts){
  QString line = "#";
  while(line.startsWith("#") && !ts.atEnd()){
    line = ts.readLine ();
  }
  return line;
}

int Interval(const int value, const int lower, const int upper){
  return qMax(qMin(value,upper),lower);
}

Scene::Scene(QObject *parent):
  QObject(parent),
  rot_x_(0),
  rot_y_(0),
  rot_z_(0),
  zoom_(0.3),
  shrink_(0),
  spread_(0),
  wireframe_(false),
  user_color_(true),
  current_frame_(0),
  frame_delay_count_(0),
  frame_delay_(0)
{
}

Scene::~Scene()
{
  while(!objects_.isEmpty()){
    SceneObject *object = objects_.first();
    objects_.pop_front();
    if(object != NULL){
      delete object;
    }
  }
}

void Scene::draw()
{
  if(wireframe_){
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  }else{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  }

  foreach(SceneObject *object,objects_){
    if(object!=NULL){
      if( -1 != frame_delay_){
        frame_delay_count_ ++;
        if(frame_delay_count_ > frame_delay_){
          current_frame_ ++;
          frame_delay_count_ = 0;
        }
      }
      object->Draw(spread_,shrink_,user_color_,current_frame_);
    }
  }
}

int Scene::ObjectNumber() const
{
  return objects_.size();
}

void Scene::LoadFile(const QString &filename)
{
  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    qDebug() << "Failed to open file!";
    return;
  }

  QTextStream in(&file);

  QString line = ReadValidLine(in);

  if( line.startsWith(kInputString) ){
    LoadInput(in,line.endsWith(k3DString));
  }else if( line.startsWith(kHullString) ){
    LoadHull(in,line.endsWith(k3DString));
  }else if( line.startsWith(kTetraString) ){
    LoadTetra(in,line.endsWith(k3DString));
  }else{
    qDebug() << "Invalid File Format!";
    return;
  }
}

void Scene::LoadInput(QTextStream &in, const bool is3d)
{
  // Read File Header
  bool problem = false;
  QString object_owner = ReadValidLine(in);
  int object_frame_count = ReadValidLine(in).toInt();
  int object_count = ReadValidLine(in).toInt();
  QVector<SceneObject*> objects;
  objects.resize(object_count);
  // End File Header

  for(int i=0;i<object_count;i++){
    // Read Object Header
    QString object_name = ReadValidLine(in);
    QString object_color = ReadValidLine(in);
    double object_spread = ReadValidLine(in).toDouble();
    int object_vertex_count = ReadValidLine(in).toInt();
    // End Object Header

    ScenePointCloud *spc = new ScenePointCloud(object_name,object_owner,object_spread,object_color);
    objects[i] = spc;

    // For Each Frame Block
    spc->points_.resize(object_frame_count);
    for(int f=0;f<object_frame_count;f++){
      spc->points_[f].resize(object_vertex_count);

      // Read Vertex Block
      for(int v=0;v<object_vertex_count;v++){
        double x,y,z;
        x = ReadValidLine(in).toDouble();
        y = ReadValidLine(in).toDouble();
        if(is3d){
          z = ReadValidLine(in).toDouble();
        }else{
          z = 0.0;
        }
        spc->points_[f][v] = QVector3D(x,y,z);
      }
      // End Vertex Block
    }
    // End Frame Block
    spc->Colorize();
  }
  if(!problem){
    objects_ += (objects);
  }else{
    while(!objects.empty()){
      SceneObject *object = objects.first();
      objects.pop_front();
      delete object;
    }
  }
}

void Scene::LoadHull(QTextStream &in, const bool is3d)
{
  // Read Header
  bool problem = false;
  QString object_owner = ReadValidLine(in);
  int object_frame_count = ReadValidLine(in).toInt();
  int object_count = ReadValidLine(in).toInt();
  QVector<SceneObject*> objects;
  objects.resize(object_count);
  // End Read Header

  for(int i=0;i<object_count;i++){
    // Read Object Header
    QString object_name = ReadValidLine(in);
    QString object_color = ReadValidLine(in);
    double object_spread = ReadValidLine(in).toDouble();
    int object_vertex_count = ReadValidLine(in).toInt();
    // End Object Header
    SceneConvexHull *sch = new SceneConvexHull(object_name,object_owner, object_spread,object_color);
    objects[i] = sch;

    // For Each Frame Block
    sch->faces_.resize(object_frame_count);
    for(int f=0;f<object_frame_count;f++){
      // Read Point Block
      QVector<QVector3D> points;
      points.resize(object_vertex_count);
      for(int p=0;p<object_vertex_count;p++){
        double x,y,z;
        x = ReadValidLine(in).toDouble();
        qDebug()<< "x" << p << x;
        y = ReadValidLine(in).toDouble();
        qDebug()<< "y" << p << y;
        if(is3d){
          z = ReadValidLine(in).toDouble();
          qDebug()<< "z" << p << z;
        }else{
          z = 0;
        }
        points[p] = QVector3D(x,y,z);
      }
      // End Point Block

      // Read Face Block
      int object_face_count = ReadValidLine(in).toInt();
      qDebug() << "object_face_count" << object_face_count;
      for(int t=0;t<object_face_count;t++){
        int face_vertex_count = ReadValidLine(in).toInt();
        qDebug() << "face_vertex_count" << face_vertex_count;
        QVector<QVector3D> vert_list;
        for(int v=0;v<face_vertex_count;v++){
          qDebug() << vert_list;
          vert_list.push_back( points[Interval(ReadValidLine(in).toInt(),0,object_vertex_count-1)] );
        }
        sch->faces_[f].push_back(new Face(vert_list,object_color));
      }
      // End Face Block
    }
    //End Frame Block
    sch->Colorize();
  }
  if(!problem){
    objects_ += (objects);
  }else{
    while(!objects.empty()){
      SceneObject *object = objects.first();
      objects.pop_front();
      delete object;
    }
  }
}

void Scene::LoadTetra(QTextStream &in, const bool is3d)
{
  // Read Header
  bool problem = false;
  QString object_owner = ReadValidLine(in);
  int object_frame_count = ReadValidLine(in).toInt();
  int object_count = ReadValidLine(in).toInt();
  QVector<SceneObject*> objects;
  objects.resize(object_count);
  // End Read Header

  for(int i=0;i<object_count;i++){
    // Read Object Header
    QString object_name = ReadValidLine(in);
    QString object_color = ReadValidLine(in);
    double object_spread = ReadValidLine(in).toDouble();
    int object_vertex_count = ReadValidLine(in).toInt();
    // End Object Header

    SceneTetrahedrons *sth = new SceneTetrahedrons(object_name,object_owner,object_spread,object_color);
    objects[i] = sth;

    sth->tetrahedrons_.resize(object_frame_count);
    for(int f=0;f<object_frame_count;f++){
      // Read Point Block
      QVector<QVector3D> points;
      points.resize(object_vertex_count);
      for(int p=0;p<object_vertex_count;p++){
        double x,y,z;
        x = ReadValidLine(in).toDouble();
        y = ReadValidLine(in).toDouble();
        if(is3d){
          z = ReadValidLine(in).toDouble();
        }else{
          z = 0;
        }
        points[p] = QVector3D(x,y,z);
      }
      // End Point Block

      // Read Tetra Block
      int object_tetrahedrons_count = ReadValidLine(in).toInt();
      for(int t=0;t<object_tetrahedrons_count;t++){
        int v1_index = Interval(ReadValidLine(in).toInt(),0,object_vertex_count-1);
        int v2_index = Interval(ReadValidLine(in).toInt(),0,object_vertex_count-1);
        int v3_index = Interval(ReadValidLine(in).toInt(),0,object_vertex_count-1);
        if(is3d){
          int v4_index = Interval(ReadValidLine(in).toInt(),0,object_vertex_count-1);
          sth->tetrahedrons_[f].push_back(new Tetrahedron(points[v1_index],points[v2_index],points[v3_index],points[v4_index]));
        }else{
          sth->tetrahedrons_[f].push_back(new Tetrahedron(points[v1_index],points[v2_index],points[v3_index]));
        }
      }
      // End Tetra Block
    }
    //End Frame Block
    sth->Colorize();
  }
  if(!problem){
    objects_ += (objects);
  }else{
    while(!objects.empty()){
      SceneObject *object = objects.first();
      objects.pop_front();
      delete object;
    }
  }
}

void Scene::SetShrink(const int &shrink)
{
  shrink_ = float(shrink)/100.0f;
  emit Repaint();
}

void Scene::SetSpread(const int &spread)
{
  spread_ = 2.0*float(spread)/100.0f;
  emit Repaint();
}

void Scene::SetWireframe(const bool &wireframe)
{
  wireframe_ = wireframe;
  emit Repaint();
}

void Scene::SetUserColor(const bool &user_color)
{
  user_color_=user_color;
  emit Repaint();
}

void Scene::SetFrameDelay(const int &fps)
{
  if(0 == fps){
    frame_delay_ = -1;
  }else{
    frame_delay_ = (float(60.0)/float(fps));
  }
}

void Scene::Colorize()
{
  foreach(SceneObject *object,objects_){
    if(object!=NULL){
      object->Colorize();
    }
  }
  emit Repaint();
}
