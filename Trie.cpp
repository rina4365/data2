#include "Trie.h"

Trie::Trie()
{
	root = new TrieNode(NULL);
}


void Trie::clear(TrieNode* current)
{
	if (current->contin.empty())
	{
		delete current;
		return;
	}
	list<TrieNode*>::iterator it = current->contin.begin();
	list<TrieNode*>::iterator en = current->contin.end();
	while (it != en)
	{
		clear((*it));
		it++;
	}
	delete current;
}

void Trie::insert(string word, TrieNode* current)
{
	if (word == "")
	{
		current->isWord = true;
		return;
	}
	list<TrieNode*>::iterator it = current->contin.begin();
	list<TrieNode*>::iterator en = current->contin.end();
	//int i=0;
	while (it != en)//checks if the letter exists in the list of the current node
	{
		if (word[0] == (*it)->key)
		{
			return insert(word.substr(1, word.length()), (*it));
		}
		it++;
		//i++;
	}
	//not exist
	int length = word.length();
	for (int i = 0; i < length; i++)
	{
		TrieNode* temp = new TrieNode(word[i]);
		current->contin.push_back(temp);
		current = current->contin.back();
		//delete temp;
	}
	current->isWord = true;
}

bool Trie::del(string word)
{
	if (findWord(word))//check if the word exists
		return del(word, root, word.length(),root);
	return false;
}

bool Trie::del(string word, TrieNode* current, int length, TrieNode* father)
{
	if (length == 0)//Stop conditions
	{
		if (current->contin.empty())
		{
			(*current)=NULL;	
		}
		else
			current->isWord = false;
		return true;
	}
	list<TrieNode*>::iterator it = current->contin.begin();
	list<TrieNode*>::iterator en = current->contin.end();
	while (it != en)//checks if the letter exists in the list of the current node
	{
		if (word[0] == (*it)->key)
		{
			if (word.length() == 1)
				del(word, (*it), --length, current);
			else
				del(word.substr(1, word.length() - 1), (*it), --length, current);
			if ((*it)->key == NULL)
			{
				delete (*it);
				current->contin.erase(it);
				if (current->isWord != true && current->contin.empty())
					(*current) = NULL;
			}
			/*if (current->contin.size() == 1 && current->isWord != true)
			{
				delete current;
				father->contin.erase(it);
			}*/
			return true;
		}
		it++;
	}
	return true;
}

bool Trie::findWord(string word, TrieNode* current, int length)
{
	if (length == 0 && current->isWord==true)//Stop conditions
		return true;
	
	list<TrieNode*>::iterator it = current->contin.begin();
	list<TrieNode*>::iterator en = current->contin.end();
	while (it != en)//checks if the letter exists in the list of the current node
	{
		if ((*it)->key == word[0])
		{
			if (word.length() == 1)
				return findWord(word, (*it), --length);
			else
				return findWord(word.substr(1, word.length() - 1), (*it), --length);
		}
		it++;
	}
	return false;
}

TrieNode* Trie::findNode(string str)
{
	TrieNode* current = root;
	int i = 0;
	int length = str.length();
	while (i < length)
	{
		list<TrieNode*>::iterator it = current->contin.begin();
		list<TrieNode*>::iterator en = current->contin.end();
		while (it != en)
		{
			if ((*it)->key == str[i])
			{
				current = (*it);
				break;
			}
			it++;
		}
		i++;
	}
	return current;
}

bool Trie::printWords(string str2)
{
	//string str = ""; 
	TrieNode* node;
	if (search(str2))
	{
		//str += str2;

		node = findNode(str2);
		bool check = printWords(node, str2.substr(0, str2.size() - 1));
		return check;
	}
	//return printWords(node, str);
	return false;
}

/*bool Trie::printWords(TrieNode* node)
{
	list<TrieNode*>::iterator it = root->contin.begin();
	list<TrieNode*>::iterator en = root->contin.end();
	while (it != en)
	{
		if ((*it)->key == node->key)
		{
			string str = "";
			return printWords(node, str += node->key);
		}
	}
	return false;
}*/

bool Trie::printWords(TrieNode* node, string str)
{
	if (node->contin.empty())
	{
		cout<<str <<node->key<< endl;
		return true;
	}
	list<TrieNode*>::iterator it = node->contin.begin();
	list<TrieNode*>::iterator en = node->contin.end();
	
	str += node->key;
	int size = node->contin.size();
	while(it!=en)
	{
		//str += node->key;
		if (node->isWord)
			cout << str << endl;
		printWords((*it), str);
		it++;
	}
	return true;
}

bool Trie::search(string word, TrieNode* current, int length)
{
	if (length == 0)//Stop conditions
		return true;
	list<TrieNode*>::iterator it = current->contin.begin();
	list<TrieNode*>::iterator en = current->contin.end();
	while (it != en)//checks if the letter exists in the list of the current node
	{
		if ((*it)->key == word[0])
		{
			if (word.length() == 1)
				return search(word, (*it), --length);
			else
				return search(word.substr(1, word.length() - 1), (*it), --length);
		}
		it++;
	}
	return false;
}
