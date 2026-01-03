#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
using namespace std;

struct Info
{
    string name;
    string phone;
    string email;
    // default constructor
    Info()
    {
        this->name = this->phone = this->email = "";
    }
    Info(string const &name, string const &phone, string const &email)
    {
        this->name = name;
        this->phone = phone;
        this->email = email;
    }
};
// Making the Node struct
struct Node
{
    int id;
    Info info;
    Node *right;
    Node *left;
    // parametrized constructor
    Node(const int &id, const Info &info)
    {
        this->id = id;
        this->info = info;
        left = right = nullptr;
    }
};

// AVLTree Class
class AVLTree
{
    // var for the root of the tree
    Node *root;
    /// the private functions that we will be recursive

    // function to get the height of node
    int getHeight(Node *node)
    {
        if (node == nullptr)
            return 0;
        int right = getHeight(node->right);
        int left = getHeight(node->left);
        return (left > right ? left + 1 : right + 1);
    }

    // function to calculate the balance factor
    int getBalanceFactor(Node *node)
    {
        if (node == nullptr)
            return 0;
        int left = getHeight(node->left);
        int right = getHeight(node->right);
        return left - right;
    }

    // function to rotate left
    Node *rotateLeft(Node *node)
    {
        // check if the node is null
        if (node == nullptr)
            return nullptr;
        // storing the values
        Node *child = node->right;
        Node *temp = child->left;
        // the rotate logic :
        child->left = node;
        node->right = temp;
        return child;
    }
    // function to rotate right
    Node *rotateRight(Node *node)
    {
        // check if the node is null
        if (node == nullptr)
            return nullptr;
        // storing the values
        Node *child = node->left;
        Node *temp = child->right;
        // the rotate logic
        child->right = node;
        node->left = temp;
        return child;
    }

    // function insert a node
    Node *insert(Node *node, const int &key, const Info &info)
    {
        // base case if we have found the right place
        if (node == nullptr)
        {
            return (new Node(key, info));
        }
        if (node->id > key)
        {
            node->left = insert(node->left, key, info);
        }
        else if (node->id < key)
        {
            node->right = insert(node->right, key, info);
        }
        else
        {
            return node;
        }
        // getting the balance factor of the node
        int factor = getBalanceFactor(node);
        // there are 4 cases of unbalance nodes
        // 1- Right - Right  case
        if (factor < -1 &&node->right && (key > node->right->id))
        {
            return rotateLeft(node);
        }
        // 2- Left-Left case
        if (factor > 1 &&  node -> left &&(key < node->left->id))
        {
            return rotateRight(node);
        }
        // 3 Left-Right case
        if (factor > 1 && node->left && (key > node->left->id))
        {
            node->left = rotateLeft(node->left);
            return (rotateRight(node));
        }
        // 4- Right - Left case
        if (factor < -1 && node -> right && (key < node->right->id))
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    // function to search a node
    Node *search(Node *root, const int &key)
    {
        // check if the node equal to null
        if (root == nullptr)
        {
            return nullptr;
        }
        // check if we have found the key
        if (root->id == key)
        {
            return root;
        }
        // then search in the left subtree
        if (root->id > key)
        {
            return search(root->left, key);
        }
        return search(root->right, key);
    }

    // function to delete all the nodes in the tree
    void deleteAllNodes(Node *r)
    {
        if (r == nullptr)
            return;
        deleteAllNodes(r->left);
        deleteAllNodes(r->right);
        delete r;
    }

    // function to print all the contacts stored in the AVL tree
    void inorderDetailed(Node *root)
    {
        if (root != nullptr)
        {
            inorderDetailed(root->left);
            cout << "ID: " << root->id
                 << ", Name: " << root->info.name
                 << ", Phone: " << root->info.phone
                 << ", Email: " << root->info.email << endl;
            inorderDetailed(root->right);
        }
    }

public:
    // the constructor
    AVLTree()
    {
        root = nullptr;
    }
    // The functions that must use the recursive functions
    // function to add new node
    void insertContact(const int &id, const string &name, const string &phone, const string &email)
    {
        if (name.empty() || phone.empty() || email.empty()) {
            cout << "Error: Name, phone, and email cannot be empty" << endl;
            return;
        }
        // first check if the id already exists
        Node* isHere = search(root, id);
        if (isHere != nullptr)
        {
            cout << "Error: Contact with ID " << id << " already exists" << endl;
            return;
        }
        // The id is unique
        Info info(name, phone, email);
        root = insert(root, id, info);
         cout << "Contact added successfully." << endl;
    }
    // function for finding  a certain node
    void searchContact(const int &id)
    {
        Node *result = search(root, id);
        if (result == nullptr)
        {
            cout << "Contact not found." << endl;
        }
        else
        {
            cout << "\nContact found:" << endl;
            cout << "ID: " << result->id << endl;
            cout << "Name: " << result->info.name << endl;
            cout << "Phone: " << result->info.phone << endl;
            cout << "Email: " << result->info.email << endl << endl;
        }
    }

    // function to List All Contacts (Sorted by ID)
    void listAllContacts()
    {
        if (root == nullptr)
        {
            cout << "Address Book is empty." << endl;
            return;
        }
        cout << "Contacts in Address Book (sorted by ID):" << endl;
        inorderDetailed(root);
        cout << endl;
    }
    //? Done 
    // function to display the tree structure
    void displayTreeStructure()
    {
        
        if(root == nullptr)
        {
            cout << "The tree is empty." << endl;
            return;
        }
        cout << "Current tree structure:" << endl;
        int height = getHeight(root);

        for (size_t i = 1; i <= height  ; i++)
        {
            cout << string(((height-i+1)*4)+1, ' ');
            printLevel(root, i);
            cout << endl;
            // print the branches only when the level is not the last one
            if (i < height) {
                cout << string(((height-i+1)*4), ' ');
                printBranches(root, i);
                cout << endl;
            }
        }
        
    }
    // function to print the tree level by level
    void printLevel(Node* root, int  level)
    {
        if (root == nullptr)
            return;
        if (level == 1)
            cout<<root->id << "   ";

        else if (level > 1)
        {
            cout<<" ";
            printLevel(root->left, level - 1);
            printLevel(root->right, level - 1);
        }
    }
    // function to print the branches of the tree 
    void printBranches(Node* root, int level)
    {
     if (root == nullptr) return ; 
     else if (level == 1) {
          // Adjust spacing to match node spacing
        if (root->left && root->right) cout << "/  \\ "; 
        else if (root->left)  cout << "/    "; 
        else if (root->right) cout << "   \\ "; 
        else  cout << "     "; 

     }
     else if (level > 1) {
         cout<<" ";
        printBranches(root->left, level - 1);
        printBranches(root->right, level - 1);
     }


    }
    // the destructor
    ~AVLTree()
    {
        // delete all the nodes using (deleteAllNodes function )
        deleteAllNodes(root);
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

            AVLTree currentTree;
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
                    int id;
                    string name, phone, email;
                    if (!(iss >> id >> name >> phone >> email))
                        continue;
                    currentTree.insertContact(id, name, phone, email);
                    break;
                }
                case 2:
                {
                    int id;
                    if (!(iss >> id))
                        continue;
                    currentTree.searchContact(id);
                    break;
                }

                case 3:
                {
                    currentTree.listAllContacts();
                    break;
                }
                case 4:
                {
                    currentTree.displayTreeStructure();
                    break;
                }
                case 5:
                {
                    cout << "Exiting the file..." << endl;
                    break;
                }
                default:
                {
                    cout << "Invalid choice found in the file." << endl;
                    break;
                }
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
}
