#include<iostream>
#include<math.h>
#include<string>

using namespace std ;

long long unsigned int Hashcode( string Pattern )
{
    long long unsigned int Hash_Code = 0 ;
    int i = Pattern.length() - 1 ; 
    int k = 0 ; 
    while( i > -1 )
    {
        Hash_Code += Pattern[i] * pow( 256 , k ) ;
        k++ ;
        i-- ;
    }
    return Hash_Code % (long long unsigned int ) pow( 2 , 61 ) ;
}
