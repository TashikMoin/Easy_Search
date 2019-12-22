#include<iostream>
#include<math.h>
#include<string>

using namespace std ;

long long unsigned int Calculate_Hashcode( string &Pattern )
{
    long long unsigned int Hashcode = 0 ;
    int i = Pattern.length() - 1 ; 
    int k = 0 ; 
    while( i > -1 )
    {
        Hashcode += Pattern[i] * pow( 256 , k ) ;
        k++ ;
        i-- ;
    }
    return Hashcode % (long long unsigned int ) pow( 2 , 61 ) ;
}

int Rabin_Karp_Algorithm( string &Data , string &Pattern )
{
    long long unsigned int Hashcode_Of_Pattern = Calculate_Hashcode( Pattern ) ;
    string Sliding_Window = "" ;
    int i = 0 , k = 0 ;
    while( i < Pattern.length() )
    {
        Sliding_Window += Data[i] ;
        i++ ;
    }
    long long unsigned int Hashcode_Of_Sliding_Window = Calculate_Hashcode( Sliding_Window ) ;
    while( i < Data.length() )
    {
        if( Hashcode_Of_Pattern == Hashcode_Of_Sliding_Window )
        {
            int j = k , l = 0 ;
            while( j < Sliding_Window.length() )
            {
                if( Sliding_Window[j] != Pattern[l] )
                {
                    break ;
                }
                j++;
                l++ ;
            }
            if( j == Sliding_Window.length() )
            {
                return k ;
            }
        }
        else
        {
            Hashcode_Of_Sliding_Window -= Sliding_Window[k] * pow( 256 , Pattern.length() - 1 ) ;
            k++ ;
            Hashcode_Of_Sliding_Window *= 256 ;
            Hashcode_Of_Sliding_Window += Data[i] ;
            Sliding_Window += Data[k+2] ;
        }
        i++ ;
    }
    return 0 ;
}


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
            return ; 
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
    cout<<"Not Found" ;
} 


class trieNode 
{
   private:
    trieNode* data[26];
    bool endOfQuery;

   public:
    trieNode() 
    {
        endOfQuery = false;

        for (int i = 0; i < 26; i++) 
        {
            data[i] = NULL;
        }
    }

    void insert(string __input) {
        trieNode* temp = this;

        for (int i = 0; i < __input.size(); i++) 
        {
            int index = __input[i] - 'A';
            if (temp->data[index] == NULL) 
            {
                temp->data[index] = new trieNode();
                temp = temp->data[index];
            } 
           else 
           {
                temp = temp->data[index];
           }
        }
        temp->endOfQuery = true;
    }

    bool search(string __searchQuery) 
    {
        trieNode* temp = this;

        for (int i = 0; i < __searchQuery.size(); i++) 
        {
            int index = __searchQuery[i] - 'A';
            if (temp->data[index] == NULL) 
            {
                return false;
            } 
            else 
            {
                temp = temp->data[index];
            }
        }

        return (temp != NULL && temp->endOfQuery == true);
    }

    ~trieNode() {}
   
};

class Trie 
{
   private:
    trieNode root;

   public:
    Trie() : root() {}
   
    void insert(string __key) 
    {
        for (int i = 0; i < __key.size(); i++) 
        {
            this->root.insert(__key.substr(i));
        }
    }

    void search(string __searchQuery) 
    {
        if (root.search(__searchQuery)) 
        {
            cout << __searchQuery << " is present\n";
        } 
       else 
       {
            cout << __searchQuery << " is not present\n";
        }
    }

    ~Trie() {}
   
};



int main()
{
    string Data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
    string Pattern = "GHI" ; 
    int Pi_Table[Pattern.length()] = {0} ;
    Knuth_Morris_Algorithm( Pattern , Data , Pi_Table ) ;
}

