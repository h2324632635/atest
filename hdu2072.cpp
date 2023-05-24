/*

单词数
Time Limit: 1000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
Total Submission(s): 107005    Accepted Submission(s): 28304


Problem Description
lily的好朋友xiaoou333最近很空，他想了一件没有什么意义的事情，就是统计一篇文章里不同单词的总数。下面你的任务是帮助xiaoou333解决这个问题。
 

Input
有多组数据，每组一行，每组就是一篇小文章。每篇小文章都是由小写字母和空格组成，没有标点符号，遇到#时表示输入结束。
 

Output
每组只输出一个整数，其单独成行，该整数代表一篇文章里不同单词的总数。
 

Sample Input
you are my friend
#
 

Sample Output
4
 

Author
Lily
 

Source
浙江工业大学网络选拔赛

*/




#include<stdio.h>
#include<string.h>

typedef struct
{
    char str [ 25 ] ;
}arr ;

arr x [ 10000 ] ;
char a [ 10000 ] ;

int main( void )
{
    int i , j , k , len , n , sum , m , flag ;

    while( gets( a ) != NULL )
    {
        if ( strcmp( a , "#" ) == 0 )//#要用“”括起来，代表字符串，而不能使用‘’，否则产生Runtime Error(ACCESS_VIOLATION)
            break ;		//因为strcmp函数比较的是两个字符串

        j = 0 ;//数组a中的下标
        sum = 0 ;//不同的单词数
        n = 0 ; //单词总数
        k = 0 ; //结构体数组中str数组的下标
        len = strlen( a ) ;

        if ( a [ 0 ] >= 'a' && a [ 0 ] <= 'z' )//防止字符串第一个元素是空格
            sum++;
        for ( i = 0 ; i < len ; i++ )
        {
            if ( i == 0 || ( a [ i - 1 ] == ' ' && a [ i ] != ' ' ) )
            {
                j = i ;
                while( 1 )
                {
                    x [ n ].str[ k ] = a[ j ] ;//把单词存入结构体数组中
                    k++ ;   j++ ;

                    if ( a [ j ] == ' ' || j == len )
                    {
                        x [ n ].str[ k ] = '\0' ;//添加字符数组结束标志符
                        k = 0 ;
                        n++ ;
                        break ;
                    }
                }
            if ( n > 1 ) //用来判断是否有相同的单词
            {
                flag = 0 ;
                for( m = 0 ; m < n - 1 ; m++ )
                {
                    if ( strcmp( x[ n - 1 ].str , x[ m ].str ) == 0 )
                    {
                         flag = 1 ;
                         break ;
                    }
                }
                if ( flag == 0 )
                    sum++ ;
            }
        }
    }
        printf( "%d\n" , sum ) ;
    }
    return 0 ;
}

