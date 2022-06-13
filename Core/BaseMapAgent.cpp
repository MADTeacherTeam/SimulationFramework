#include "BaseMapAgent.h"


BaseMapAgent::BaseMapAgent(MapGeoObject* ptr) : _pMapObject(ptr)
{

}

void BaseMapAgent::RedrawMObject()
{
    emit _pMapObject->redrawRequested();
}

void BaseMapAgent::SetMObjectPos(QPointF pos)
{
    _pMapObject->setPos(pos);
}

MapGeoObject *BaseMapAgent::getGeoObject()
{
    return _pMapObject;
}
