void Generate_Pi_Table( string &Pattern , int Pi_Table[] ) 
{ 
    int Counter = 0; 
    Pi_Table[0] = 0; 
    int j = 1; 
    while ( j < Pattern.length() ) 
    { 
        if (Pattern[j] == Pattern[Counter]) 
        { 
            Counter++; 
            Pi_Table[j] = Counter; 
            j++; 
        } 
        else 
        { 
            if (Counter != 0) 
            { 
                Counter = Pi_Table[Counter - 1];
            } 
            else 
            { 
                Pi_Table[j] = 0; 
                j++; 
            } 
        } 
    } 
} 



void Knuth_Morris_Algorithm( string &Pattern, string &Data , int Pi_Table[] ) 
{ 
    Generate_Pi_Table(Pattern, Pi_Table); 
    int i = 0; 
    int j = 0; 
    while ( i < Data.length() ) 
    { 
        if (Pattern[j] == Data [i]) 
        { 
            j++; 
            i++; 
        } 
  
        if (j == Pattern.length() ) 
        { 
            cout<<"String Found At Index : "<< i-j ;
            j = Pi_Table[j - 1]; 
        } 
        else if (i < Data.length() && Pattern[j] != Data [i]) 
        { 
            if (j != 0)
            {
                j = Pi_Table[j - 1] ;
            } 
            else
            {
                ++i ; 
            }
        } 
    } 
} 
  