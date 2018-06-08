package kdk.android.notes;

import java.io.Serializable;

public class ListDesc implements Serializable
{
    private static final long serialVersionUID = 1L;
    
    
    private int id;
	private String label;
	private int activeItems;
	private int totalItems;
	
    public ListDesc()
    {
        // Do nothing
    }
    
    
	public ListDesc(int id, String label, int activeItems, int totalItems)
	{
		this.id = id;
		this.label = label;
		this.activeItems = activeItems;
		this.totalItems = totalItems;
	}

	public int getId()
	{
		return id;
	}

	public void setId(int id)
	{
		this.id = id;
	}

	public String getLabel()
	{
		return label;
	}

	public void setLabel(String label)
	{
		this.label = label;
	}
	
	public int getActiveItems()
	{
		return activeItems;
	}

	public void setActiveItems(int inactiveItems)
	{
		this.activeItems = inactiveItems;
	}

	public int getTotalItems()
	{
		return totalItems;
	}

	public void setTotalItems(int totalItems)
	{
		this.totalItems = totalItems;
	}
	
	
	
}
