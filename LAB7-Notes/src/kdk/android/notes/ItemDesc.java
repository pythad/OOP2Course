package kdk.android.notes;

public class ItemDesc
{
	private volatile int id;
	private String label;
	private boolean active;
    private boolean star;
    private boolean sorted = false;
	
	public ItemDesc(int id, String label, boolean active, boolean star)
	{
		this.id = id;
		this.label = label;
		this.active = active;
        this.star = star;
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

	public boolean isActive()
	{
		return active;
	}

	public void setActive(boolean active)
	{
		this.active = active;
	}

    public boolean isStar()
    {
        return star;
    }

    public void setStar(boolean star)
    {
        this.star = star;
    }
	
    public boolean isSorted()
    {
        return sorted;
    }
    
    public void setSorted(boolean sorted)
    {
        this.sorted = sorted;
    }
	
}
