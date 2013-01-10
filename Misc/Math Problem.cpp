#include <iostream>
using namespace std;



int* dpArray;
int start = 1;
int end = 1994;
int maxVal = 0;
int maxN = 0;

int STORAGE_AMOUNT = end * 2 + 1;

int function(int num)
{
    dpArray[2 * num] = dpArray[num];
    if(dpArray[2 * num] > maxVal)
    {
        maxVal = dpArray[2 * num];
        maxN = num;
    }
    dpArray[2 * num + 1] = dpArray[2 * num] + 1;
    if(dpArray[2 * num + 1] > maxVal)
    {
        maxVal = dpArray[2 * num + 1];
        maxN = num;
    }
}

int main()
{
    int num = 0;

    /*while(num < start || num > end)
    {
        cout << "Enter in a number between " << start << " and " << end << "." << endl;
        cin >> num;
    }
    cout << num << endl;*/
    dpArray = new int[STORAGE_AMOUNT + 1];
    for(int i = 0; i <= STORAGE_AMOUNT; i++)
    {
        dpArray[i] = 0;
    }
    dpArray[1] = 1;

    for(int i = start; i <= end; i++)
    {
        function(i);
        cout << dpArray[i] << endl;
    }

    cout << maxVal << " " << maxN << endl;

}
