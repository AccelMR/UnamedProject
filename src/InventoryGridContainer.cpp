#include "InventoryGridContainer.h"
#include "Item.h"
#include "InventorySlot.h"

using namespace godot;

void InventoryGridContainer::_ready()
{
    populateInventorySlots();
}

bool InventoryGridContainer::tryAddItem(const Ref<Item>& item)
{
  if (item == nullptr)
    return false;

  //First look if there's a slot that already contains the current type and,
  //in addition to that it has enough space for the item
  for (auto& slot : m_inventorySlots)
  {
    auto& itemInSlot = slot->getCurrentStoredItem();

    if (itemInSlot != nullptr && itemInSlot->get_class() == item->get_class())
    {
      if (slot->tryAddToStack())
      {
        return true;
      }
    }
  }

  //The first thing failed so just find an empty slot and store the item inside
  for (auto& slot : m_inventorySlots)
  {
    auto& itemInSlot = slot->getCurrentStoredItem();

    if (itemInSlot == nullptr)
    {
      slot->populate(item);
      return true;
    }
  }

  //The item can't be stored:(
  return false;
}

void InventoryGridContainer::populateInventorySlots()
{
    auto numberOfSlots = m_inventoryColumns * m_inventoryRows;

    for (int i = 0; i < numberOfSlots; i++)
    {
        auto slotScene = m_slotScene->instantiate();
        auto slot = Object::cast_to<InventorySlot>(slotScene);

        if (nullptr != slot)
        {
          m_inventorySlots.push_back(slot);
          add_child(slot);
        }
    }
}

void InventoryGridContainer::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("tryAddItem", "item"), &InventoryGridContainer::tryAddItem);

  ClassDB::bind_method(D_METHOD("getInventoryColumns"), &InventoryGridContainer::getInventoryColumns);
  ClassDB::bind_method(D_METHOD("setInventoryColumns", "columns"), &InventoryGridContainer::setInventoryColumns);

  ClassDB::bind_method(D_METHOD("getInventoryRows"), &InventoryGridContainer::getInventoryRows);
  ClassDB::bind_method(D_METHOD("setInventoryRows", "rows"), &InventoryGridContainer::setInventoryRows);

  ClassDB::bind_method(D_METHOD("getInventorySlot"), &InventoryGridContainer::getInventorySlot);
  ClassDB::bind_method(D_METHOD("setInventorySlot", "slot"), &InventoryGridContainer::setInventorySlot);

    ADD_PROPERTY(
        PropertyInfo(
          Variant::INT,                    // stored type
          "InventoryColumns",              // name
          PropertyHint::PROPERTY_HINT_ENUM,// tell editor to show dropdown
          "Columns"                        // options
        ),
        "setInventoryColumns",
        "getInventoryColumns"
    );

    ADD_PROPERTY(
        PropertyInfo(
          Variant::INT,
          "InventoryRows",
          PropertyHint::PROPERTY_HINT_ENUM,
          "Rows"
        ),
        "setInventoryRows",
        "getInventoryRows"
    );

    ADD_PROPERTY(
    PropertyInfo(
        Variant::OBJECT,
        "item_scene",
        PROPERTY_HINT_RESOURCE_TYPE,
        "PackedScene"
    ),
        "setInventorySlot",
        "getInventorySlot"
    );
}