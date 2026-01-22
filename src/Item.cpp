#include "Item.h"

using namespace godot;

void Item::_bind_methods()
{
  BIND_ENUM_CONSTANT(RARITY_NONE);
  BIND_ENUM_CONSTANT(RARITY_COMMON);
  BIND_ENUM_CONSTANT(RARITY_RARE);

  BIND_ENUM_CONSTANT(TYPE_NONE);
  BIND_ENUM_CONSTANT(TYPE_EQUIPABLE);
  BIND_ENUM_CONSTANT(TYPE_CONSUMABLE);

  ClassDB::bind_method(D_METHOD("getItemRarity"), &Item::getItemRarity);
  ClassDB::bind_method(D_METHOD("setItemRarity", "rarity"), &Item::setItemRarity);

  ClassDB::bind_method(D_METHOD("getItemType"), &Item::getItemType);
  ClassDB::bind_method(D_METHOD("setItemType", "type"), &Item::setItemType);

  ClassDB::bind_method(D_METHOD("getIsStackable"), &Item::getIsStackable);
  ClassDB::bind_method(D_METHOD("setIsStackable", "stackable"), &Item::setIsStackable);

  ClassDB::bind_method(D_METHOD("getItemIcon"), &Item::getItemIcon);
  ClassDB::bind_method(D_METHOD("setItemIcon", "icon"), &Item::setItemIcon);

    ADD_PROPERTY(
        PropertyInfo(
          Variant::INT,                       // stored type
          "ItemRarity",                       // name
          PropertyHint::PROPERTY_HINT_ENUM,   // tell editor to show dropdown
          "None,Common,Rare"                  // options
        ),
        "setItemRarity",
        "getItemRarity"
    );

    ADD_PROPERTY(
        PropertyInfo(
          Variant::INT,
          "ItemType",
          PropertyHint::PROPERTY_HINT_ENUM,
          "None,Equipable,Consumable"
        ),
        "setItemType",
        "getItemType"
    );

    ADD_PROPERTY(
        PropertyInfo(
          Variant::BOOL,
          "isStackable",
          PropertyHint::PROPERTY_HINT_ENUM,
          "True,False"
        ),
        "setIsStackable",
        "getIsStackable"
    );

    ADD_PROPERTY(
    PropertyInfo(
        Variant::OBJECT,
        "icon",
        PROPERTY_HINT_RESOURCE_TYPE,
        "Texture2D"
    ),
    "setItemIcon",
    "getItemIcon"
    );
}