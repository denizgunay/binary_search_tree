#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


struct node
{
    std::string key;
    struct node *left;
    struct node *right;
    node()
    {   
        this->key = "ZZZZ";
        this->left = NULL;
        this->right = NULL;
    }
};

struct node *getNewNode(std::string val)
{
    struct node *newNode = new node();
    newNode->key   = val;
    newNode->left  = NULL;
    newNode->right = NULL;

    return newNode;
}


struct node *insert(struct node *root, std::string val)
{   
    /*getline metodunu kullandığımızda bazen compiler stringin sonuna '\r' karakterini
    ekleyebiliyor. bundan kurtulmak için, aşağıdaki if koşulunu çalıştırıyoruz.*/
    if (!val.empty() && (val[val.size() - 1] == '\r'))
        val.erase(val.size() - 1);
    
    if(root == NULL)
        return getNewNode(val);
    if(root->key < val)
        root->right = insert(root->right,val);
    else if(root->key > val)
        root->left = insert(root->left,val);

    return root;
}



//sağ subtree'deki min node'u buluyor.
std::string getRightMin(struct node *root)
{
    struct node *temp = root;

    while(temp->left != NULL){ temp = temp->left;}

    return temp->key;
}

//sol subtree'deki max node'u buluyor.
std::string getLeftMax(struct node *root)
{
    struct node *temp = root;

    while(temp->right != NULL){ temp = temp->right;}

    return temp->key;
}


//Eğer removal left yapacaksak, left parametresi true olacak, 
//eğer removal right yapacaksak, left parametresi false olacak.
struct node *removeNode(struct node *root, std::string val, bool left = true)
{   
    /*
    Silmek istediğimiz node BST'de bulunmuyorsa NULL return ediyoruz.
     */
    if(root == NULL)
        return NULL;
    /*
     Eğer sileceğimiz değer mevcut node'dan daha büyükse, recursive bir şekilde 
     right child'a gidiyoruz.
     */
    if(root->key < val)
        root->right = removeNode(root->right,val);
    /*
     Eğer sileceğimiz değer mevcut node'dan daha küçükse, recursive bir şekilde 
     left child'a gidiyoruz.
     */
    else if(root->key > val)
        root->left = removeNode(root->left,val);
    /*
     Silmek istediğimiz node BST'de bulunuyorsa aşağıdaki else yapısı çalışıyor..
     */
    else
    {
        /*
         Case 1: Eğer bir leaf node ise, o nodu boşaltıp NULL return ediyoruz.
        */
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        /*
         Case 2: Node'un sadece right child'i varsa, right child ile yerdeğiştiriyoruz.
        */
        else if(root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        /*
         Case 3: Node'un sadece left childı varsa, left child ile yerdeğiştiriyoruz.
        */
        else if(root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        /*
          Case 4: Root hem left child'a, hem de right child'a sahip değilse. 
          Eğer left parametresi true ise, removal left yapıyoruz.
          Eğer left parametresi false ise, removal right yapıyoruz.
        */
        else
        {   
            if(left = true)
            {
                std::string leftMax = getLeftMax(root->left);
                root->key = leftMax;
                root->left = removeNode(root->left,leftMax, true);
            }
            else
            {
                std::string rightMin = getRightMin(root->right);
                root->key = rightMin;
                root->right = removeNode(root->right,rightMin,false);
            }

        }

    }

    return root;
}


void inorder(struct node *root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    std::cout << root->key << '\n';
    inorder(root->right);
}


struct node* strategy1(struct node* root, std::string book)
{
    return removeNode(root,book,true);
}


/*Aşağıdaki x parametresinin anlamı şu: eğer strategy 2 kullanmışsak, x parametresi 
-1 ile çarpılıyor. Dolayısıyla x parametresi, strategy 2'yi her kullandığımızda 1 ya da
-1 oluyor. Ve buna göre, removal right ya da removal left yapıyoruz.*/
int x = 1;

struct node* strategy2(struct node* root, std::string book)
{   
    if (x == 1)
    {
        x = x*(-1);
        return removeNode(root,book,false);
    }
    else
    {
       x = x*(-1);
       return removeNode(root,book,true);
    }

}

int main()
{   
    struct node *root = NULL;
    //reading from books.txt
    std::ifstream file;
    file.open("books.txt");
    if(!file.is_open())
    {
        std::cout<<"Unable to open the file.\n";
        return 0;
    }
    std::string line;
    while(getline(file, line))
    {   
       root = insert(root,line);
    }
    file.close();



    //populate the tree
    std::cout << "Initial tree:\n";
    inorder(root);
    std::cout << '\n';

    //using strategy1
    std::cout << "New BST after using strategy 1:\n";
    root = strategy1(root,"Urlasurla");
    inorder(root);
    std::cout << '\n';

    //using strategy2
    std::cout << "New BST after using strategy 2:\n";
    root = strategy2(root, "Trial, The");
    inorder(root);
    std::cout << '\n';


    return 0;
}