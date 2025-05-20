#include <iostream>
#include <queue>
#include<string>
#include<vector>
using namespace std;
template <class Object>
//this is our change
//this is our 2 change
struct TreeNode {

	// constructors
	TreeNode()
	{
		this->object = NULL;
		this->left = this->right = NULL;
	};
	TreeNode(Object* object)
	{
		this->object = object;
		this->left = this->right = NULL;
	};

	Object* getInfo()
	{
		return this->object;
	};
	void setInfo(Object* object)
	{
		this->object = object;
	};
	TreeNode* getLeft()
	{
		return left;
	};
	void setLeft(TreeNode* left)
	{
		this->left = left;
	};

	TreeNode* getRight()
	{
		return right;
	};
	void setRight(TreeNode* right)
	{
		this->right = right;
	};
	int isLeaf()
	{
		if (this->left == NULL && this->right == NULL)
			return 1;
		return 0;
	};




	Object* object;
	TreeNode* left;
	TreeNode* right;
};
void deleteTree(TreeNode<int>* root)
{
	if (root == nullptr) return;
	deleteTree(root->getLeft());
	deleteTree(root->getRight());
	delete root;
}
void insert(TreeNode<int>* root, int* info)
{
	TreeNode<int>* node = new TreeNode<int>(info);
	TreeNode<int>* p, * q;
	p = q = root;
	while (*info != *(p->getInfo()) && q != NULL)
	{
		p = q;
		if (*info < *(p->getInfo()))
			q = p->getLeft();
		else
			q = p->getRight();
	}
	if (*info == *(p->getInfo())) {
		cout << "attempt to insert duplicate: "
			<< *info << endl;
		delete node;
	}
	else if (*info < *(p->getInfo()))
		p->setLeft(node);
	else
		p->setRight(node);
}
// PREORDER Traversal: Root → Left → Right
void preorder(TreeNode<int>* root)
{
	if (root != NULL)
	{
		cout << *(root->getInfo()) << " "; // Visit root
		preorder(root->getLeft());          // Visit left
		preorder(root->getRight());         // Visit right
	}
}

// INORDER Traversal: Left → Root → Right
void inorder(TreeNode<int>* root)
{
	if (root != NULL)
	{
		inorder(root->getLeft());            // Visit left
		cout << *(root->getInfo()) << " ";    // Visit root
		inorder(root->getRight());            // Visit right
	}
}
void printInOrder(TreeNode<string>* root) {
	// Check if the current node
	// is null (base case for recursion)
	if (root == nullptr) {
		// If null, return and
		// terminate the function
		return;
	}

	// Recursively call printInOrder
	// for the left subtree
	printInOrder(root->left);

	// Print the value of the current node
	cout << root->getInfo() << " ";

	// Recursively call printInOrder
	// for the right subtree
	printInOrder(root->right);
}
// POSTORDER Traversal: Left → Right → Root
void postorder(TreeNode<int>* root)
{
	if (root != NULL)
	{
		postorder(root->getLeft());           // Visit left
		postorder(root->getRight());          // Visit right
		cout << *(root->getInfo()) << " ";     // Visit root
	}
}
TreeNode<int>* parent(TreeNode<int>* root, TreeNode<int>* p)
{
	if (root == NULL || p == NULL)
		return NULL;  // Base case: if the root or the node p is NULL, return NULL

	// If root's left or right child is p, root is the parent
	if (root->getLeft() == p || root->getRight() == p)
		return root;

	// Otherwise, search in the left subtree
	TreeNode<int>* leftSearch = parent(root->getLeft(), p);
	if (leftSearch != NULL)
		return leftSearch;

	// Otherwise, search in the right subtree
	return parent(root->getRight(), p);
}
TreeNode<int>* brother(TreeNode<int>* root, TreeNode<int>* p)
{
	if (root == NULL || p == NULL)
		return NULL;  // If root or node p is NULL, no brother exists

	TreeNode<int>* par = parent(root, p); // Find the parent of p
	if (par == NULL)
		return NULL; // If the parent doesn't exist (p is root or not found), no brother

	// Check which side p is and return the other child
	if (par->getLeft() == p)
		return par->getRight(); // If p is left child, return right child
	else
		return par->getLeft();  // If p is right child, return left child
}
bool find(TreeNode<int>* root, int x)
{
	// If the root is NULL, the tree is empty, so x is not found
	if (root == NULL) {
		return false;
	}

	// If the current node's value matches x, return true
	if (*(root->getInfo()) == x) {
		return true;
	}

	// If x is smaller than the current node's value, search the left subtree
	if (x < *(root->getInfo())) {
		return find(root->getLeft(), x);
	}

	// If x is greater than the current node's value, search the right subtree
	return find(root->getRight(), x);
}
void levelOrderTraversal(TreeNode<int>* root)
{
	if (root == NULL) {
		cout << "Tree is empty!" << endl;
		return;
	}

	// Create a queue to hold nodes for level-order traversal
	queue<TreeNode<int>*> q;

	// Start with the root node
	q.push(root);

	// Traverse the tree level by level
	while (!q.empty()) {
		// Get the front node from the queue
		TreeNode<int>* current = q.front();
		q.pop(); // Remove the front node from the queue

		// Visit the current node (print its value)
		cout << *(current->getInfo()) << " ";

		// If the current node has a left child, enqueue it
		if (current->getLeft() != NULL) {
			q.push(current->getLeft());
		}

		// If the current node has a right child, enqueue it
		if (current->getRight() != NULL) {
			q.push(current->getRight());
		}
	}
	cout << endl;  // For neatness, print a newline at the end
}
TreeNode<int>* findMin(TreeNode<int>* tree) {
	if (tree == NULL)
		return NULL;
	if (tree->getLeft() == NULL)
		return tree; // Minimum found
	return findMin(tree->getLeft());
}

TreeNode<int>* remove(TreeNode<int>* tree, int info) {
	if (tree == NULL) return NULL;  // base case

	int cmp = info - *(tree->getInfo());

	if (cmp < 0) {
		TreeNode<int>* t = remove(tree->getLeft(), info);
		tree->setLeft(t);
	}
	else if (cmp > 0) {
		TreeNode<int>* t = remove(tree->getRight(), info);
		tree->setRight(t);
	}
	else {  // Node to delete found
		// Case 3: Two children
		if (tree->getLeft() != NULL && tree->getRight() != NULL) {
			TreeNode<int>* minNode = findMin(tree->getRight());
			tree->setInfo(minNode->getInfo());  // Replace current node's value
			TreeNode<int>* t = remove(tree->getRight(), *(minNode->getInfo()));
			tree->setRight(t);
		}
		else {  // Case 1 and Case 2: 0 or 1 child
			TreeNode<int>* nodeToDelete = tree;
			if (tree->getLeft() == NULL)
				tree = tree->getRight();
			else if (tree->getRight() == NULL)
				tree = tree->getLeft();
			else
				tree = NULL;

			delete nodeToDelete;
		}
	}
	return tree;
}
void insertstr(TreeNode<string>* root, string* info)
{
	TreeNode<string>* node = new TreeNode<string>(info);
	TreeNode<string>* p, * q;
	p = q = root;
	while (*info != *(p->getInfo()) && q != NULL)
	{
		p = q;
		if (*info < *(p->getInfo()))
			q = p->getLeft();
		else
			q = p->getRight();
	}
	if (*info == *(p->getInfo())) {
		cout << "attempt to insert duplicate: "
			<< *info << endl;
		delete node;
	}
	else if (*info < *(p->getInfo()))
		p->setLeft(node);
	else
		p->setRight(node);
}
TreeNode<string>* wordsToBST(vector<string>& words)
{
	TreeNode<string>* root = new TreeNode<string>();
	root->setInfo(&words[0]);
	for (int i = 0;i<words.size(); i++)
	{
		insertstr(root, &words[i]);
	}
	return root;
}
vector<string>   autoComplete(TreeNode<string>* root, const string& prefix)
{ 
	vector<string> answer;
	halap(root, prefix, answer);
	return answer;
	
}
vector<string>   halap(TreeNode<string>* root, const string& prefix, vector<string> &answer)
{ 
	if (!root) return;
	if (*(root->getInfo()) == prefix)
	{
		answer.push_back(*(root->getInfo()));
	}
	halap(root->getRight(), prefix, answer);
	halap(root->getleft(), prefix, answer);
}

void reverseInorder(TreeNode<int>* node, int& counter, int k, int& Largest) {
	if (!node || counter >= k) return;

	
	reverseInorder(node->right, counter, k, Largest);

	
	counter++;

	
	if (counter == k) {
		Largest = *(node->getInfo());
		return;
	}

	
	reverseInorder(node->left, counter, k, Largest);
}
int   kthMostViewedPost(TreeNode<int>* root, int k)
{
	int counter = 0;
	int largest = INT_MAX;
	reverseInorder(root, counter, k, largest);
	return largest;
}

int halper(TreeNode<int>* root, int targetSum, int& sum)
{
	if (!root && targetSum!=sum) return false;
	int sum = sum+*(root->getInfo());
	halper(root->getRight(), targetSum,sum);
	if (sum == targetSum)
	{
		return true;
	}
	halper(root->getRight(), targetSum,sum);
	
}

bool    hasPathSum(TreeNode<int>* root, int targetSum)
{  
		int sum = 0;
		return halper(root,targetSum, sum);

}
int main(int argc, char* argv[])
{
	vector <string> words;
	 words=[ apple , appetizer, banana, ball, bat, battle", "cat"," "];
	

	/* << "Inorder Traversal: ";
	inorder(wordsToBST(words));
	cout << endl;*/
	 printInOrder(wordsToBST(words));


	

	deleteTree(root);


}
