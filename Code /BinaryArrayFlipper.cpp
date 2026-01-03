#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

int main()
{
    while (true)
    {
        string fileName;
        cout << "Please enter the file name (without extension): ";
        cin >> fileName;
        fileName += ".txt";
        try
        {
            ifstream infile(fileName);
            if (!infile.is_open())
            {
                throw runtime_error("Error opening input File");
            }
            string line1;
            getline(infile, line1); // only first line

            stringstream ss(line1);
            int capacity = 4;
            int size = 0;
            int *arr = new int[capacity];

            int x;
            while (ss >> x)
            {
                if (size == capacity)
                {
                    capacity *= 2;
                    int *newArr = new int[capacity];

                    for (int i = 0; i < size; ++i)
                    {
                        newArr[i] = arr[i];
                    }

                    delete[] arr;
                    arr = newArr;
                }

                arr[size++] = x;
            }
            int k;
            infile >> k;
            infile.close();

            //    int cntToK = 0;
            int cntOfSub = 0;
            bool done = true;
            //    bool inArow = false;    //subarr begins
            for (int i = 0; i < size; ++i)
            {
                if (arr[i] == 0)
                {
                    for (int j = 0; j < k; ++j)
                    {
                        if (i + j >= size)
                        {
                            done = false;
                            break;
                        }
                        arr[i + j] = !arr[i + j];
                    }
                    cntOfSub++;
                }
                else continue;
            }

            if (!done)
            {
                cout << "-1" << endl;
            }
            else
            {
                cout << cntOfSub << endl;
            }
             int continueOption;
            // validate the input choice & if not valid throw exception
            while (true)
            {
                
                // Ask the user if they want to continue with another file
                cout << "Do you want to test another file? (1) Yes / (2) No: ";
                if (!(cin >> continueOption))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Invalid input." << endl;
                    continue;
                }
                break;
            }
            delete[] arr;

            // The user choose to stop
            if (continueOption == 2)
            {
                cout << "Exiting..." << endl;
                return 0;
            }
            // getting another file input
            cout << "\n--- Restarting with another file ---\n\n";
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    
}
