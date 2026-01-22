#ifndef ITEM_H
#define ITEM_H

#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/texture2d.hpp>

using namespace godot;

class Item : public Resource
{
  GDCLASS(Item, Resource);
  
 public:
  Item()=default;
  ~Item()=default;

 public:
  enum ItemRarity
  {
    RARITY_NONE=-1,
    RARITY_COMMON,
    RARITY_RARE
  };
  
  enum ItemType
  {
    TYPE_NONE=-1,
    TYPE_EQUIPABLE,
    TYPE_CONSUMABLE
  };

 public:
   ItemRarity getItemRarity() { return m_rarity; }
   void setItemRarity(const int& rarity) { m_rarity = (ItemRarity)rarity; }

   ItemType getItemType() { return m_type; }
   void setItemType(const int& type) { m_type = (ItemType)type; }

   bool getIsStackable() { return m_isStackable; }
   void setIsStackable(bool stackable) { m_isStackable = stackable; }

   Ref<Texture2D> getItemIcon() { return m_icon; }
   void setItemIcon(const Ref<Texture2D>& icon) { m_icon = icon; }

  protected:
    static void _bind_methods();

 private:
    Ref<Texture2D> m_icon;

    bool m_isStackable;

    ItemRarity m_rarity = RARITY_NONE;
    ItemType m_type = TYPE_NONE;
    
    float m_pickUpRadius = 10.0f;

};

VARIANT_ENUM_CAST(Item::ItemRarity);
VARIANT_ENUM_CAST(Item::ItemType);

#endif