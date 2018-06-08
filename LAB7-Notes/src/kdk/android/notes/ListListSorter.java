package kdk.android.notes;

import java.text.Collator;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import android.util.Log;

public class ListListSorter
{
    public static final String PREF_NONE = "none";
    public static final String PREF_ALPHA = "alphabetical";
    
    private static final int NONE = 0;
    private static final int ALPHA = 1;
    
    private int sortingMode;
    
    private Comparator<ListDesc> idCompare;
    private Comparator<ListDesc> alphaCompare;
    private Collator collator = Collator.getInstance();    
    
    public ListListSorter()
    {
        idCompare = new Comparator<ListDesc>() {
            @Override
            public int compare(ListDesc object1, ListDesc object2)
            {
                return object2.getId() - object1.getId();
            }
        };
        alphaCompare = new Comparator<ListDesc>() {
            @Override
            public int compare(ListDesc object1, ListDesc object2)
            {
            	return collator.compare(object1.getLabel(), object2.getLabel());
            }
        };
    }
    
    
    public void setSortingMode(String mode)
    {
        if(PREF_NONE.equals(mode))
        {
            sortingMode = NONE;
        }
        else if(PREF_ALPHA.equals(mode))
        {
            sortingMode = ALPHA;
        }
        else
        {
            sortingMode = NONE;
            Log.w(L.TAG, "Unknown list sorting mode " + mode);
        }
    }
    
    
    public void sort(List<ListDesc> list)
    {
        switch(sortingMode)
        {
        default:
            Log.w(L.TAG, "Unknown list sorting enum " + sortingMode);
            // fall through
        case NONE:
            // actually sorted by db id
            Collections.sort(list, idCompare);
            break;
        case ALPHA:
            Collections.sort(list, alphaCompare);
            break;
        }
    }
}
