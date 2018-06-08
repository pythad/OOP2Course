package kdk.android.notes;

import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class ListPropertiesAdapter extends BaseAdapter
{
    private SimplyDoActivity context;
    private DataViewer dataViewer;
    
    public ListPropertiesAdapter(SimplyDoActivity context, DataViewer dataViewer)
    {
        this.context = context;
        this.dataViewer = dataViewer;
    }
    
    
    @Override
    public int getCount()
    {
        return dataViewer.getListData().size();
    }

    @Override
    public Object getItem(int position)
    {
        return dataViewer.getListData().get(position);
    }

    @Override
    public long getItemId(int position)
    {
        return position;
    }

    

    @Override
    public View getView(final int position, View convertView, ViewGroup parent)
    {
        View rv = null;
        
        try
        {
            if(convertView == null)
            {
                rv = View.inflate(context, R.layout.list_entry, null);
            }
            else
            {
                rv = convertView;
            }

            TextView t1 = (TextView)rv.findViewById(R.id.text1);
            ListDesc listDesc = dataViewer.getListData().get(position);
            t1.setText(listDesc.getLabel());
            
            TextView t2 = (TextView)rv.findViewById(R.id.text2);
            t2.setText("("+ listDesc.getActiveItems() + "/" + listDesc.getTotalItems() + ")");
        }
        catch(Exception e)
        {
            Log.e(L.TAG, "Error in getView()", e);
        }

        return rv;
    }
    
}
