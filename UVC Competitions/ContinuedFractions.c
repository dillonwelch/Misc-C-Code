
#include <iostream>
using namespace std;

int continuedFractions(int num; int denom)
{
        int bzero = num/denom;
        if(num % denom)
        {
                num = num - (bzero * denom);
                denom = (denom / num);
                continuedFractions(1, denom);
        }
        return bzero;
}

int main()
{
        int num;
        int denom;
        while (cin.eof() != 1)
        {
                cin>>num;
                if(cin.eof() == 1)
                {
                        return (EXIT_SUCCESS);
                }
                cin>>denom;
                continuedFractions(num, denom);
        }
        return 0;
}
