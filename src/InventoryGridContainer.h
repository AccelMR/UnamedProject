#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <vector>

using namespace godot;

class Item;
class InventorySlot;

class InventoryGridContainer : public GridContainer
{
  GDCLASS(InventoryGridContainer, GridContainer);
  
 public:
  InventoryGridContainer()=default;
  ~InventoryGridContainer()=default;

 public:
   void _ready() override;

   bool tryAddItem(const Ref<Item>& item);

public: //Getters and setters
   int getInventoryColumns() { return m_inventoryColumns; }
   void setInventoryColumns(const int& columns) { m_inventoryColumns = columns; }

   int getInventoryRows() { return m_inventoryRows; }
   void setInventoryRows(const int& rows) { m_inventoryRows = rows; }
   
   Ref<PackedScene> getInventorySlot() { return m_slotScene; }
   void setInventorySlot(const Ref<PackedScene>& slot) { m_slotScene = slot; }

  private:
    void populateInventorySlots();

  protected:
    static void _bind_methods();

 private:
   int m_inventoryColumns = 10;
   int m_inventoryRows = 4;

   Ref<PackedScene> m_slotScene;
   std::vector<InventorySlot*> m_inventorySlots;
};