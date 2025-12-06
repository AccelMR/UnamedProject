#include "MouseMarker.h"

void MouseMarker::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("SetMarkShrinkSpeed", "speed"), &MouseMarker::SetMarkShrinkSpeed);
  ClassDB::bind_method(D_METHOD("GetMarkShrinkSpeed"), &MouseMarker::GetMarkShrinkSpeed);

  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "markShrinkSpeed"), "SetMarkShrinkSpeed", "GetMarkShrinkSpeed");
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

void MouseMarker::UpdateMarkerPosition(const Vector3& position) 
{
  set_global_position(position);
  m_bIsMarkJustPlaced = true;
  // Reset scale
  set_scale(Vector3(1, 1, 1));
}