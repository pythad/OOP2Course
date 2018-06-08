package kdk.android.notes;

import java.util.List;

public interface DataViewer
{
    public List<ItemDesc> getItemData();
    public List<ListDesc> getListData();
    public void setSelectedList(ListDesc selectedList);
    public ListDesc getSelectedList();
    public void fetchLists();
    public ListDesc fetchList(int listId);
    public void fetchItems(int listId);
    public void updateItemActiveness(ItemDesc item, boolean active);
    public void updateItemStarness(ItemDesc item, boolean star);
    public void updateItemLabel(ItemDesc item, String newLabel);
    public void updateListLabel(int listId, String newLabel);
    public void moveItem(ItemDesc item, int toListId);
    public void createList(String label);
    public void createItem(String label);
    
    /**
     * Deletes inactive items from the current list. 
     */
    public void deleteInactive();
    
    public void deleteList(int listId);
    public void deleteItem(ItemDesc item);
    public void flush();
    public void invalidateCache();
    public void close();
}
