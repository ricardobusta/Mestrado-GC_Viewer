#include "ric.h"

#include <QtGlobal>
#include <QTime>

namespace Ric{
int rand(int a)
{
  if(!seeded){
    init();
  }

  return qrand()%a;
}


int rand(int a, int b)
{
  if(!seeded){
    init();
  }

  return ((qrand()%(b-a))+a);
}

void init()
{
  seeded = true;
  qsrand(QTime::currentTime().second());
}
}
