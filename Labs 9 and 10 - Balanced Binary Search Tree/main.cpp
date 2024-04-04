#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// word class allows us to add a word item to the tree
class Word {
public:
  string word;
  int count;
  // constructor
  Word(string w) {
    word = w;
    count = 1;
  }
  // overloaded > operator
  bool operator>(Word &other) { return word > other.word; }
  // overloaded < operator
  bool operator<(Word &other) { return word < other.word; }
  // overloaded = operator
  bool operator==(Word &other) { return word == other.word; }
};

template <typename T>
// builds the nodes of the tree
class node {
public:
  T data;
  node *right;
  node *left;
  int height;
  // Constructor
  node(T value) : data(value), right(nullptr), left(nullptr), height(1) {}
  // Destructor
  ~node() {
    delete left;
    delete right;
  }
};

template <typename T>
// Binary Tree implementation
class tree {
public:
  node<T> *root;
  // Constructor
  tree() { root = NULL; }
  // Destructor
  ~tree() { delete root; }

  // gets the height of a subtree
  int height(node<T> *leaf) {
    if (leaf == NULL) {
      return 0;
    }
    return leaf->height;
  }

  // Get Balance factor of node N
  int getBalance(node<T> *N) {
    if (N == NULL) {
      return 0;
    }
    return height(N->left) - height(N->right);
  }

  // gets the max of two inputs
  int max(int a, int b) { return (a > b) ? a : b; }

  // gets the smallest node - bottom left
  node<T> *minValueNode(node<T> *root) {
    node<T> *current = root;
    // find the leftmost leaf
    while (current->left != NULL) {
      current = current->left;
    }
    return current;
  }

  bool isEmpty() { return (root == NULL); }

  node<T> *insert(node<T> *root, T data) {
    // accepts a value, creates a node, and inserts the node into the tree in
    // the appropriate location. This should rebalance the tree as necessary, so
    // the tree remains balanced at all times. If the value already exists in
    // the tree, this should throw an error.
    if (root == NULL) {
      root = new node<T>(data);
      return root;
    } else if (data < root->data) {
      root->left = insert(root->left, data);
    } else if (data.word > root->data.word) {
      root->right = insert(root->right, data);
    } else {
      // if a word that already exists is encountered
      return root;
    }
    // update the height of the ancestor node
    root->height = 1 + max(height(root->left), height(root->right));

    // get the balance factor of this ancestor node to check if unbalanced
    int balance = getBalance(root);

    // if unbalanced:
    // left left case
    if (balance > 1 && data < root->left->data) {
      return rightRotate(root);
    }
    // right right case
    if (balance < -1 && data > root->right->data) {
      return leftRotate(root);
    }
    // right left case
    if (balance > 1 && data > root->left->data) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
    // left right case
    if (balance < -1 && data < root->right->data) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
    return root;
  }

  node<T> *removeNode(node<T> *root, T val) {
  //removes a node from the tree while keeping it balanced 
    if (root == NULL)
      return root;

    // If the vlaue to be deleted is smaller, go left 
    if (val < root->data){
      root->left = removeNode(root->left, val);
    }
    // If  value to be deleted is greater, go right
    else if (val > root->data)
      root->right = removeNode(root->right, val);

    // if value is the same, this is the node to be deleted
    else {
      // node with only one child or no child
      if ((root->left == NULL) || (root->right == NULL)) {
        node<T> *temp = root->left ? root->left : root->right;

        // No child case
        if (temp == NULL) {
          temp = root;
          root = NULL;
        } else           
          // One child case
          *root = *temp; 
        free(temp);
      } else {
        // node with two children
        node<T> *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
      }
    }
    //if theres nothing to remove, return 
    if (root == NULL)
      return root;

    //update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    //get balance factor of this ancestor node to check if unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
      return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
      return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
    return root;
  }

  node<T> *find(node<T> *root, T val) {
    // accepts a value, locates the value in the tree and returns a pointer to
    // the node. If the value isn’t in the tree, it will return a null pointer
    if (isEmpty()) {
      return NULL;
    }
    if (root == nullptr || root->data == val) {
      return root;
    }
    if (val < root->data) {
      return find(root->left, val);
    } else {
      return find(root->right, val);
    }
  }

  int size() {
    // Size – returns the number of elements in the tree as an integer.
    if (root == nullptr) {
      return 0;
    } else {
      return 1 + size(root->left) + size(root->right);
    }
  }

  void getAllAscending(node<T> *node, std::vector<T> &result) {
    // returns an array with each node stored in order from smallest
    //  to largest (based on the sorting value, not the other data in the node)
    if (node == nullptr) {
      return;
    }
    getAllAscending(node->left, result);
    result.push_back(node->data);
    getAllAscending(node->right, result);
  }
  std::vector<T> getAllAscending() {
    std::vector<T> result;
    getAllAscending(root, result);
    return result;
  }

  void getAllDescending(node<T> *node, std::vector<T> &result) {
    // returns an array with each node stored in order from largest to smallest
    // (based on the sorting value, not the other data in the node)
    if (node == nullptr) {
      return;
    }
    getAllDescending(node->right, result);
    result.push_back(node->data);
    getAllDescending(node->left, result);
  }
  std::vector<T> getAllDescending() {
    std::vector<T> result;
    getAllDescending(root, result);
    return result;
  }

  void emptyTree(node<T> *temp) {
    // EmptyTree – removes all nodes in the tree in a way to avoid memory leaks
    if (temp == nullptr) {
      return;
    }
    emptyTree(temp->left);
    emptyTree(temp->right);
    temp = nullptr;
  }

  // function to rotate the tree right
  node<T> *rightRotate(node<T> *y) {
    node<T> *x = y->left;
    node<T> *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
  }

  // A utility function to left
  // rotate subtree rooted with x
  // See the diagram given above.
  node<T> *leftRotate(node<T> *x) {
    node<T> *y = x->right;
    node<T> *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
  }
};

int main() {
  // instantiates tree
  tree<Word> myTree;
  // User inputs filename, file opens
  string FileName;
  std::cout << "Input Name of File <FileName>.txt\n";
  std::cin >> FileName;
  ifstream cardcatalog(FileName, ios::in);

  // reads title and author and contents lines
  string title;
  string author;
  string contentsline;
  getline(cardcatalog, title);
  getline(cardcatalog, author);
  getline(cardcatalog, contentsline);

  // reads file line by line
  string line;
  while (getline(cardcatalog, line)) {
    // splits line into words
    string word;
    stringstream ss(line);
    while (ss >> word) {
      // make the word lower case
      for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
      }
      // inserts words into tree
      Word newWord{word};
      node<Word> *exists = myTree.find(myTree.root, newWord);
      if (exists) {
        exists->data.count++;
      } else {
        myTree.root = myTree.insert(myTree.root, newWord);
      }
    }
  }

  // file has been processed - user mode
  bool ifContinue = true;
  while (ifContinue) {
    cout << "_______________________________________________\n";

    int choice;
    cout
        << "Would you like to...\n1. Search for a word in the file\n2. Display "
           "the words in the file in ascending order\n3. Display the words in "
           "the file in descending order\n4. View the number of words in the "
           "file\n5. Remove a word from the file\n6. Empty the tree\n7. Exit\n";
    cin >> choice;
    switch (choice) {
    case (1): {
      // search for a word in the file
      cout << "What word would you like to search for?\n";
      string searchWord;
      cin >> searchWord;
      Word searchWordObj{searchWord};
      node<Word> *searchResult = myTree.find(myTree.root, searchWordObj);
      if (searchResult) {
        cout << "The word " << searchWord << " was found "
             << searchResult->data.count << " times in the file\n";
      } else {
        cout << "The word " << searchWord << " was not found\n";
      }
      break;
    }
    case (2): {
      // display the words in the file in ascending order
      std::vector<Word> words = myTree.getAllAscending();
      cout << "**********************************\n\n";
      cout << "Word           |Count| BF  |Height\n";
      cout << "---------------------------------\n";
      for (const auto &word : words) {
        cout << word.word;
        for (int i = 0; i < (15 - word.word.length()); i++) {
          cout << " ";
        }
        node<Word> *currentNode = myTree.find(myTree.root, word);
        cout << "|    " << word.count;

        if (myTree.getBalance(currentNode) >= 0) {
          cout << "|    " << myTree.getBalance(currentNode) << "|   "
               << myTree.height(currentNode) << endl;
        } else {
          cout << "|   " << myTree.getBalance(currentNode) << "|   "
               << myTree.height(currentNode) << endl;
        }
      }
      cout << "**********************************\n";
      break;
    }
    case (3): {
      // display the words in the file in decending order
      std::vector<Word> words = myTree.getAllDescending();
      cout << "**********************************\n\n";
      cout << "Word           |Count| BF  |Height\n";
      cout << "---------------------------------\n";
      for (const auto &word : words) {
        cout << word.word;
        for (int i = 0; i < (15 - word.word.length()); i++) {
          cout << " ";
        }
        node<Word> *currentNode = myTree.find(myTree.root, word);
        cout << "|    " << word.count;

        if (myTree.getBalance(currentNode) >= 0) {
          cout << "|    " << myTree.getBalance(currentNode) << "|   "
               << myTree.height(currentNode) << endl;
        } else {
          cout << "|   " << myTree.getBalance(currentNode) << "|   "
               << myTree.height(currentNode) << endl;
        }
      }
      cout << "**********************************\n";
      break;
    }
    case (4): {
      // View the number of words in the file
      // iterate through each word in the tree and add its count to total
      std::vector<Word> words = myTree.getAllAscending();
      int total = 0;
      for (const auto &word : words) {
        total += word.count;
      }
      cout << "The total number of words in the file is " << total << endl;
      break;
    }
    case (5): {
      // remove a word from the file
      cout << "What word would you like to remove?\n";
      string removeWord;
      cin >> removeWord;
      Word removeWordObj{removeWord};
      node<Word> *removeResult = myTree.find(myTree.root, removeWordObj);
      if (removeResult) {
        myTree.root = myTree.removeNode(myTree.root, removeWordObj);
        cout << "The word " << removeWord << " was removed from the file\n";
      } else {
        cout << "The word " << removeWord << " was not found\n";
      }
      break;
    }
    case (6): {
      // empty the tree
      myTree.emptyTree(myTree.root);
      myTree.root =  nullptr;
      cout << "The tree has been emptied!\n";
      break;
    }
    case (7): {
      cout << "Thanks! Goodbye!\n";
      ifContinue = false;
      break;
    }
    }
  }
}