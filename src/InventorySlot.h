#include <godot_cpp/classes/panel.hpp>

using namespace godot;

class Item;

class InventorySlot : public Panel {
    GDCLASS(InventorySlot, Panel);

public:
  InventorySlot()=default;
  ~InventorySlot() = default;

public:
  void populate(const Ref<Item>& storedItem);

  bool tryAddToStack();

public: //Getters and setters
  int getMaxNumberOfStackedItems() { return m_maxNumberOfStackedItems; };
  void setMaxNumberOfStackedItems(const int& maxNumberOfItems) { m_maxNumberOfStackedItems = maxNumberOfItems; };

  Ref<Item> getCurrentStoredItem() { return m_storedItem; }

protected:
    static void _bind_methods();

private:
  int m_currentNumberOfStackedItems = 0;
  int m_maxNumberOfStackedItems = 10;
  Ref<Item> m_storedItem = nullptr;
};