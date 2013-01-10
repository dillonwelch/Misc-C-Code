#include <iostream>
using namespace std;

int main()
{
    int i = 88;
    int j = 88888;
    int k = 0;

    if (i == 0 || j == 0)
    {
        cout << "No." << endl;
        return 0;
    }
    while(i != j)
    {
        if(i < j)
        {
            k = i;
            i = j;
            j = k;
        }
        //if(i > j)
        //{
            if(i % j != 0)
            {
                i = i % j;
                //cout << i << endl;
            }
            else
            {
                cout << "GCD: " << j << endl;
                return 0;
                //i = i - j;
                //j = j % i;
            }
        //}
        /*else
        {
            if(j % i != 0)
            {
                j = j % i;
            }
            else
            {
                //j = j - i;
                i = i % j;
            }
        }*/
    }
    cout << "GCD: " << j << endl;
    //cout << i << " " << j << endl;
}
