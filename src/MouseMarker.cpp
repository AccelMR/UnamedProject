#include "MouseMarker.h"

void MouseMarker::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("setMarkShrinkSpeed", "speed"), &MouseMarker::setMarkShrinkSpeed);
  ClassDB::bind_method(D_METHOD("getMarkShrinkSpeed"), &MouseMarker::getMarkShrinkSpeed);

  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "markShrinkSpeed"), "setMarkShrinkSpeed", "getMarkShrinkSpeed");
}

void MouseMarker::_ready() { }

void MouseMarker::_process(double delta) 
{
  Vector3 currentScale = get_scale();
  if (m_bIsMarkJustPlaced)
  {
    //Decrease size over time
    const float shrinkAmount = m_markShrinkSpeed * static_cast<float>(delta);
    currentScale -= Vector3(shrinkAmount, shrinkAmount, shrinkAmount);
    set_scale(currentScale);
  }
  if (currentScale.x <= 0.0f || currentScale.y <= 0.0f || currentScale.z <= 0.0f)
  {
    m_bIsMarkJustPlaced = false;
    set_scale(Vector3(0, 0, 0));
  }

}

void MouseMarker::updateMarkerPosition(const Vector3& position) 
{
  set_global_position(position);
  m_bIsMarkJustPlaced = true;
  // Reset scale
  set_scale(Vector3(1, 1, 1));
}