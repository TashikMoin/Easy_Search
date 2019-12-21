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