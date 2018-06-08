package kdk.android.notes;

import android.graphics.Paint;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageSwitcher;
import android.widget.TextView;

public class ItemPropertiesAdapter extends BaseAdapter
{
    public static final String PREF_STRIKEGREY = "strikegrey";
    public static final String PREF_STRIKE = "strike";
    public static final String PREF_GREY = "grey";
    
    private SimplyDoActivity context;
    private DataViewer dataViewer;
    private boolean grey = true;
    private boolean strike = true;
    
    public ItemPropertiesAdapter(SimplyDoActivity context, DataViewer dataViewer)
    {
        this.context = context;
        this.dataViewer = dataViewer;
    }
    
    
    @Override
    public int getCount()
    {
        //Log.v(L.TAG, "ItemPropertiesAdapter.getCount() called");
        return dataViewer.getItemData().size();
    }

    @Override
    public Object getItem(int position)
    {
        //Log.v(L.TAG, "ItemPropertiesAdapter.getItem() called");
        return dataViewer.getItemData().get(position);
    }

    @Override
    public long getItemId(int position)
    {
        //Log.v(L.TAG, "ItemPropertiesAdapter.getItemId() called");
        return position;
    }
    
    public void setInactiveDecoration(String name)
    {
    	if(name.equals(PREF_STRIKEGREY))
    	{
    		grey = true;
    		strike = true;
    	}
    	else if(name.equals(PREF_STRIKE))
    	{
    		grey = false;
    		strike = true;    	
    	}
    	else if(name.equals(PREF_GREY))
    	{
    		grey = true;
    		strike = false;    	
    	}
    	else
    	{
    		grey = true;
    		strike = true;
    	}
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent)
    {
        //Log.v(L.TAG, "ItemPropertiesAdapter.getView() called");
        
        View rv = null;
        
        try
        {
            if(convertView == null)
            {
                rv = View.inflate(context, R.layout.item_entry, null);
            }
            else
            {
                rv = convertView;
            }
            
            ItemDesc it = dataViewer.getItemData().get(position);
            TextView t1 = (TextView)rv.findViewById(R.id.ieText1);
            t1.setText(it.getLabel());
            if(grey)
            {
	            t1.setTextAppearance(context, it.isActive()?R.style.ActiveText:R.style.InactiveText);
            }
            else
            {
	            t1.setTextAppearance(context, R.style.ActiveText);
            }
            
            if(strike)
            {
	            if(it.isActive())
	            {
	                t1.setPaintFlags(t1.getPaintFlags() & ~Paint.STRIKE_THRU_TEXT_FLAG);                
	            }
	            else
	            {
	                t1.setPaintFlags(t1.getPaintFlags() | Paint.STRIKE_THRU_TEXT_FLAG);
	            }
            }
            else
            {
                t1.setPaintFlags(t1.getPaintFlags() & ~Paint.STRIKE_THRU_TEXT_FLAG);                
            }
            
            ImageSwitcher starSwitch = (ImageSwitcher)rv.findViewById(R.id.StarSwitcher);
            starSwitch.setVisibility(it.isStar()?View.VISIBLE:View.INVISIBLE);
            starSwitch.setDisplayedChild(it.isActive()?0:1);
            
            View sortedMarker = (View)rv.findViewById(R.id.SortedMarker);
            if(it.isSorted())
            {
                sortedMarker.setVisibility(View.INVISIBLE);
            }
            else
            {
                sortedMarker.setVisibility(View.VISIBLE);
            }

        }
        catch(Exception e)
        {
            Log.e(L.TAG, "Error in getView()", e);
        }

        return rv;
    }

}
