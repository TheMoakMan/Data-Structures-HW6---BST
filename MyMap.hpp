void get_identity(std::string my_id[])
{
  my_id[0] = "ebmy83";
  my_id[1] = "12422230";	
	
}
      
/*~~~MyMap Functions~~~*/
//Contructs an empty Tree
template <typename K, typename V>  
MyMap<K, V>::MyMap()
{
  root = NULL; 	
}
    
template <typename K, typename V>    
MyMap<K, V>::~MyMap()
{
  //Deletes every node in the tree	
  clear_helper(root);		
}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap<K, V> &source)
{
  if(source.root == NULL)
	root = NULL;
  else{
    //Traverse the source tree and create each node as a copy of
    //the corresponding source node.
    root = clone(source.root);
  }
}
  
template <typename K, typename V>    
MyMap<K, V> & MyMap<K, V>::operator=(const MyMap<K, V> &source)
{
  //Clear the current Map
  clear();
  
  if(source.root == NULL)
	root = NULL;
  else{
	root = clone(source.root);  
  }
  
  return *this;
}

template <typename K, typename V>  
V & MyMap<K, V>::at(const K &key)
{
  return at_helper(root, key);
}

//Needs to update and insert
template <typename K, typename V>      
V & MyMap<K, V>::operator[](const K &key)
{ 
  return at_helper(root, key);
}

template <typename K, typename V>  
bool MyMap<K, V>::empty() const
{
  return (root == NULL);
}

template <typename K, typename V>          
int MyMap<K, V>::size() const
{
  return size_helper(root);	
}

template <typename K, typename V>  
void MyMap<K, V>::clear()
{
  clear_helper(root);
  root = NULL;
}

template <typename K, typename V>  
void MyMap<K, V>::insert(const MyPair<K, V> &init_pair)
{
  insert_helper(root, init_pair);
}

template <typename K, typename V>  
void MyMap<K, V>::erase(const K &key)
{
  erase_helper(root, key);	
	
}

template <typename K, typename V>  
MyPair<K, V> * MyMap<K, V>::find(const K &key) const
{
  MyPair<K, V> *matchedPair = find_helper(root, key);
  
  if(matchedPair != NULL)
	return matchedPair;
  else
	throw std::out_of_range ("MyMap:at");
}

template <typename K, typename V>  
void MyMap<K, V>::print() const
{
  print_helper(root, " ");	
}

//Returns the number of elements with the given key
//In BST this will either be 0 or 1 since there are no duplicates.
template <typename K, typename V>
int MyMap<K, V>::count(const K &key) const
{
  return count_helper(root, key);
}

template <typename K, typename V>   
V & MyMap<K, V>::at_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
  if(key < rt->data.first)
	return at_helper(rt->left, key);
  else if(key > rt->data.first)
	return at_helper(rt->right, key);
  else if(key == rt->data.first)
	return rt->data.second;
  else
	throw std::out_of_range ("MyMap:a");
}

template <typename K, typename V>  
int MyMap<K, V>::size_helper(TreeNode<MyPair<K, V>> *rt) const
{
  static int size = 0;
  //Count the number of elements. I chose to do this as a post order traversal
  if(rt == NULL)
	return 0;
  
  size += size_helper(rt->left);
  size += size_helper(rt->right);
  
  size++;

  return size;  
}

template <typename K, typename V>  
void MyMap<K, V>::clear_helper(TreeNode<MyPair<K, V>> *&rt)
{
  //Traverse the tree and delete the nodes post order.
  if(rt == NULL)
	return;
  
  clear_helper(rt->left);
  clear_helper(rt->right);
  
  delete rt;
}

//Inserts the element into it's correct sorted position by it's key into the tree if
//there are no other elements with the same key. 
//Preconditions - Operators <, and > overloaded for whichever type K the user specifies
template <typename K, typename V>  
void MyMap<K, V>::insert_helper(TreeNode<MyPair<K, V>> *&rt, const MyPair<K, V> &init_pair)
{	
  if(rt == NULL)
    root = new TreeNode<MyPair<K, V>>(init_pair, NULL, NULL);

  //Sort the elements by key while being inserted in BST Format
  if(init_pair.first < rt->data.first)
	insert_helper(rt->left, init_pair);
  else if(init_pair.first > rt->data.first)
	insert_helper(rt->right, init_pair);
  else 
	return;
}

//Return the leftmost value in the tree if sorted properly
template <typename K, typename V>  
TreeNode<MyPair<K, V>> * MyMap<K, V>::get_min(TreeNode<MyPair<K, V>> *rt)
{
  if(rt->left == NULL)
	return rt;
  else
    return get_min(rt->left);
}

template <typename K, typename V>  
void MyMap<K, V>::erase_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
  if(rt == NULL)
	return;
  
  if(key < rt->data.first)
	erase_helper(rt->left, key);
  else if(key > rt->data.first)
	erase_helper(rt->right, key);
  else{
	TreeNode<MyPair<K, V>> *temp_1 = rt;
    if(rt->left == NULL)
      rt = rt->right;
    else if(rt->right == NULL)
      rt = rt->left;
    else{
	  TreeNode<MyPair<K, V>> *temp_2 = get_min(rt->right);
	  rt->data.first = temp_2->data.first;
	  rt->data.second = temp_2->data.second;
	  
	  //Find the minimum and keep note of it's parent node
	  TreeNode<MyPair<K, V>> *iter = rt->right;
	  while(iter->left!= NULL){
		  if(iter->left->left != NULL)
			iter = iter->left;
	  }
	 
      if(rt->right == iter)
        rt->right = iter->right; 
	  else{
		if(temp_2->right != NULL)
          iter->left = temp_2->right;			
	  }
     
      delete temp_2;
	}  
	    
	delete temp_1; 
  }
  
}

template <typename K, typename V>  
MyPair<K, V> * MyMap<K, V>::find_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
  if(rt == NULL)
    return NULL;

  if(key < rt->data.first)
	return find_helper(rt->left, key);
  else if(key > rt->data.first)
	return find_helper(rt->right, key);
  else
	return &(rt->data);

}

template <typename K, typename V>  
void MyMap<K, V>::print_helper(TreeNode<MyPair<K, V>> *rt, std::string indent) const
{

}

template <typename K, typename V>  
int MyMap<K, V>::count_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
  if(rt == NULL)
	return 0;

  if(key < rt->data.first)
	return count_helper(rt->left, key);
  else if(key > rt->data.first)
	return count_helper(rt->right, key);
  else
	return 1;
}

//Clones the source node and it's subtrees.
template <typename K, typename V>  
TreeNode<MyPair<K, V>> * MyMap<K, V>::clone(const TreeNode<MyPair<K, V>> *rt)
{
  if(rt == NULL){
	return NULL;
  }

  MyPair<K, V> tempPair(rt->data.first, rt->data.second);
  TreeNode<MyPair<K, V>> * thisNode = new TreeNode<MyPair<K, V>>(tempPair, clone(rt->left), clone(rt->right));	  
  
  return thisNode;
}
