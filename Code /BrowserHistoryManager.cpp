#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

//! First we need to make the stack data structure
class Stack
{
    struct Node
    {
        string data;
        Node *next;
        // Parameterized constructor
        Node(const string &value)
        {
            this->data = value;
            this->next = nullptr;
        }
    };

    // The top of the stack
    Node *top;

public:
    // Constructor to initialize the stack
    Stack()
    {
        top = nullptr;
    }

    // Copy constructor
    Stack(const Stack &other)
    {
        // Initialize empty stack if other is empty
        if (other.isEmpty())
        {
            top = nullptr;
            return;
        }

        // Copy first node
        Node *otherCurrent = other.top;
        this->top = new Node(otherCurrent->data);

        // Keep track of last node in new stack
        Node *current = this->top;
        otherCurrent = otherCurrent->next;

        // Copy remaining nodes
        while (otherCurrent != nullptr)
        {
            current->next = new Node(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

    // function to push an element onto the stack
    void push(const string &item)
    {
        Node *newElement = new Node(item);
        if (top == nullptr)
        {
            top = newElement;
            return;
        }
        newElement->next = top;
        top = newElement;
    }

    // function to pop an element from the stack
    string pop()
    {
        if (top == nullptr)
        {
            return "";
        }
        string item = top->data; // Get the data from top node
        Node *temp = top;        // Store the top node to delete it
        top = top->next;         // Move top to next node
        delete temp;             // Free the memory
        return item;
    }

    // function to check if the stack is empty
    bool isEmpty() const
    {
        return (top == nullptr);
    }
    // Destructor to free the memory
    ~Stack()
    {
        while (top != nullptr)
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }
};
// Now the BrowserHistory class
class BrowserHistory
{
    // Two stacks to keep track of the back and forward history
    // The back stack stores the URLs visited before the current URL
    // The forward stack stores the URLs visited after the current URL

    Stack backStack;
    Stack forwardStack;
    string currentUrl;

    // function to print the stack
    static void printStack(const Stack &stack)
    {

        Stack temp(stack);
        cout << "[";
        while (true)
        {

            string url = temp.pop();
            if (url.empty())
                break;
            cout << "\" " << url << "\",";
        }
        cout << "]" << endl;
    }

public:
    // Constructor to initialize the browser history
    BrowserHistory()
    {
        currentUrl = "";
    }

    // The visit function takes a URL as an argument and pushes the current URL onto the back stack
    // and clears the forward stack
    void visit(const string &url)
    {

        currentUrl = url;
        backStack.push(currentUrl);

        // empty the forward stack
        while (!forwardStack.isEmpty())
        {
            forwardStack.pop();
        }
    }

    // The goBack function pops the top URL from the back stack and pushes the current URL onto the forward stack
    // The function returns the previous URL if available, otherwise it returns the current URL
    string goBack()
    {
        if (backStack.isEmpty())
        {
            cout << "No previous URL to go back " << endl
                 << endl;
            return "";
        }
        if (currentUrl.empty())
        {
            cout << "No current URL" << endl;
            return "";
        }

        string previousUrl = backStack.pop();
        forwardStack.push(previousUrl);

        currentUrl = backStack.pop();
        backStack.push(currentUrl);

        return currentUrl;
    }

    // The goForward function pops the top URL from the forward stack and pushes the current URL onto the back stack
    // The function returns the next URL if available, otherwise it returns the current URL
    string goForward()
    {
        if (forwardStack.isEmpty())
        {
            cout << "No forward URL to go forward" << endl
                 << endl;
            return "";
        }
        if (currentUrl.empty())
        {
            cout << "No current URL" << endl;
            return "";
        }

        string nextUrl = forwardStack.pop();
        backStack.push(nextUrl);
        currentUrl = nextUrl;
        return currentUrl;
    }

    // The printHistory function prints the back and forward stacks
    // and the current URL
    // The function uses the printStack function of the Stack class to print the stacks
    void printHistory()
    {
        cout << "Back Stack: ";
        printStack(backStack);
        cout << "Forward Stack: ";
        printStack(forwardStack);
        cout << "Current URL: " << currentUrl << endl
             << endl;
    }
};
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
            ifstream fileInput(fileName);
            if (!fileInput.is_open())
            {
                throw R"(Error: Could not open the file.)";
            }
            BrowserHistory browser;
            string line;
            while (getline(fileInput, line))
            {
                if (line.empty())
                    continue;
                istringstream iss(line);
                int choice;
                if (!(iss >> choice))
                    continue;
                switch (choice)
                {
                case 1:
                {
                    string url;
                    if (!(iss >> url))
                        continue;
                    browser.visit(url);
                    cout << "Visited: " << url << endl
                         << endl;
                    break;
                }
                case 2:
                {
                    string url = browser.goBack();
                    if (!url.empty())
                        cout << "Went back to: " << url << endl
                             << endl;
                    break;
                }
                case 3:
                {
                    string url = browser.goForward();
                    if (!url.empty())
                        cout << "Went forward to: " << url << endl
                             << endl;
                    break;
                }
                case 4:
                {
                    browser.printHistory();
                    break;
                }
                default:
                    cout << "Invalid choice found in the file " << endl
                         << endl;
                    break;
                }
            }

            fileInput.close();
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

            // The user choose to stop
            if (continueOption == 2)
            {
                cout << "Exiting..." << endl;
                return 0;
            }
            // getting another file input
            cout << "\n--- Restarting with another file ---\n\n";
        }
        catch (const char *error)
        {
            cout << error << endl;
            cout << "Retrying...\n\n";
        }
    }

    return 0;
}
