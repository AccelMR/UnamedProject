#include "InventorySlot.h"
#include "Item.h"
#include <godot_cpp/classes/style_box_texture.hpp>
#include <godot_cpp/classes/texture2d.hpp>

using namespace godot;

void InventorySlot::populate(const Ref<Item>& storedItem)
{
  if (storedItem.is_null()) return;

  m_storedItem = storedItem;
  m_currentNumberOfStackedItems = 1;

  Ref<StyleBox> style = get_theme_stylebox("Panel", "Panel");
  if (!style.is_valid()) return;

  Ref<StyleBoxTexture> sbt = style;
  if (!sbt.is_valid()) return;

  Ref<Texture2D>& tex = sbt->get_texture();
  if (!tex.is_valid()) return;
  tex = storedItem->getItemIcon();
}

bool InventorySlot::tryAddToStack()
{
  if (m_currentNumberOfStackedItems >= m_maxNumberOfStackedItems)
  {
    return false;
  }

  m_currentNumberOfStackedItems++;
  return true;
}

void InventorySlot::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("populate", "storedItem"), &InventorySlot::populate);
  ClassDB::bind_method(D_METHOD("addToStack"), &InventorySlot::tryAddToStack);

  ClassDB::bind_method(D_METHOD("getMaxNumberOfStackedItems"), &InventorySlot::getMaxNumberOfStackedItems);
  ClassDB::bind_method(D_METHOD("setMaxNumberOfStackedItems", "maxNumberOfItems"), &InventorySlot::setMaxNumberOfStackedItems);

  ClassDB::bind_method(D_METHOD("getCurrentStoredItem"), &InventorySlot::getCurrentStoredItem);

  ADD_PROPERTY(
    PropertyInfo(
      Variant::INT,                    // stored type
      "MaxNumberOfStackedItems",       // name
      PropertyHint::PROPERTY_HINT_ENUM,// tell editor to show dropdown
      "MaxStackedItems"                // options
    ),
    "setMaxNumberOfStackedItems",
    "getMaxNumberOfStackedItems"
  );
}