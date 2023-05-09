#include <iostream>
#include <queue>
using namespace std;

class TreeNode
{
    int *keys;
    int t;
    TreeNode **C;
    int n;
    bool leaf;

public:
    TreeNode(int t1, bool leaf1)
    {
        t = t1;
        leaf = leaf1;
        keys = new int[2 * t - 1];
        C = new TreeNode *[2 * t];
        n = 0;
    }

    void insertNonFull(int k) {
        int i = n - 1;
        if (leaf == true) {
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
            n = n + 1;
        } else
        {
            while (i >= 0 && keys[i] > k) i--;
            if (C[i + 1]->n == 2 * t - 1)
            {
                splitChild(i + 1, C[i + 1]);
                if (keys[i + 1] < k) i++;
            }
            C[i + 1]->insertNonFull(k);
        }
    }

    void splitChild(int i, TreeNode *y)
    {
        TreeNode *z = new TreeNode(y->t, y->leaf);
        z->n = t - 1;
        for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
        if (y->leaf == false) for (int j = 0; j < t; j++) z->C[j] = y->C[j + t];
        y->n = t - 1;
        
        for (int j = n; j >= i + 1; j--) C[j + 1] = C[j];
        C[i + 1] = z;
        
        for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
        keys[i] = y->keys[t - 1];
        n++;
    }

    friend class BTree;
};

class BTree 
{
    TreeNode *root;
    int t;

public:
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void insert(int k) {
        if (root == NULL)
        {
            root = new TreeNode(t, true);
            root->keys[0] = k;
            root->n = 1;
        }
        else
        {
            if (root->n == 2 * t - 1)
            {
                TreeNode *s = new TreeNode(t, false);
                s->C[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < k) i++;
                s->C[i]->insertNonFull(k);
                root = s;
            }
            else root->insertNonFull(k);
        }
    }

    void printLevelOrder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty!\n";
            return;
        }
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {   
            int n = int(q.size());
            for (int i = 0; i < n; i++)
            {
                TreeNode *node = q.front();
                q.pop();

                if (!node->leaf) for (int j = 0; j < (20/n)+5; j++) cout << ' ';

                cout << "(";
                for (int j = 0; j < node->n; j++) cout << " " << node->keys[j] << " ";
                cout << ")";

                if (!node->leaf) for (int k = 0; k <= node->n; k++) q.push(node->C[k]);
            }
            cout << endl;
        }
    }
};


int main() {
    BTree t(3);
    t.insert(15);
    t.insert(50);
    t.insert(10);
    t.insert(1);
    t.insert(4);
    t.insert(5);
    t.insert(7);
    t.insert(55);
    t.insert(60);
    t.insert(63);
    t.insert(30);
    t.insert(33);
    t.insert(40);
    cout << "The B-tree is: \n"; t.printLevelOrder();
    cout << endl;

    BTree t2(3);
    for(int i=0; i<40; i++) t2.insert(i);
    cout << "The B-tree is: \n"; t2.printLevelOrder();
    cout << endl;
}