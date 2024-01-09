#include<iostream>

#include<fstream>

#include <stdlib.h>
#include<time.h>
using namespace std;

// global

class Nodetree
 {
    public: string word;
    string meaning;
    string synoyms[3];
    int height;
    Nodetree * left;
    Nodetree * right;

    Nodetree() {
        word = "\0";
        meaning = "\0";
        synoyms[0] = "\0";
        synoyms[1] = "\0";
        synoyms[2] = "\0";
        left = NULL;
        right = NULL;
        height = 1;
    }
};



Nodetree * Nodedelete(Nodetree * node, string key);


class NodeHash
{
    public: char Firstletter;
    Nodetree * root = NULL;
    int Frequency;

    NodeHash()
    {
        Frequency = 0;
    }
};


int getheight(Nodetree * node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return node -> height;
    }

}

int max(int l, int r)
{
    if (l > r)
    {
        return l;
    }
    else
    {
        return r;
    }
}
int getbalance(Nodetree * node) {
    if (node == NULL) {
        return 0;
    } else {
        return getheight(node -> left) - getheight(node -> right);
    }

}
Nodetree * rotateleft(Nodetree * node) {
    Nodetree * y = node -> right;
    Nodetree * T2 = y -> left;

    y -> left = node;
    node -> right = T2;

    node -> height = 1 + max(getheight(node -> left), getheight(node -> right));
    y -> height = 1 + max(getheight(y -> left), getheight(y -> right));

    return y;
}
Nodetree * rotateright(Nodetree * node) {
    Nodetree * y = node -> left;
    Nodetree * T2 = y -> right;

    y -> left = node;
    node -> left = T2;

    node -> height = 1 + max(getheight(node -> left), getheight(node -> right));
    y -> height = 1 + max(getheight(y -> left), getheight(y -> right));
    return y;
}
Nodetree * newnode(string Word, string meaning, string Sy1, string Sy2, string Sy3) {

    Nodetree * temp = new Nodetree;
    temp -> word = Word;
    temp -> meaning = meaning;
    temp -> synoyms[0] = Sy1;
    temp -> synoyms[1] = Sy2;
    temp -> synoyms[2] = Sy3;
    return temp;
}

Nodetree * Nodeinsert(Nodetree * root, string Word, string Meaning, string Sy1, string Sy2, string Sy3) {
    if (root == NULL) {
        root = newnode(Word, Meaning, Sy1, Sy2, Sy3);
    } else if (Word < root -> word) {
        root -> left = Nodeinsert(root -> left, Word, Meaning, Sy1, Sy2, Sy3);
    } else if (Word > root -> word) {
        root -> right = Nodeinsert(root -> right, Word, Meaning, Sy1, Sy2, Sy3);
    } else {
        return root;
    }

    root -> height = 1 + max(getheight(root -> left), getheight(root -> right));

    int balance = getbalance(root);
    if (balance < -1 && Word > root -> word) {
        return rotateleft(root);
    } else if (balance > 1 && Word < root -> word) {
        return rotateright(root);
    } else if (balance < -1 && Word < root -> word) {
        root -> right = rotateright(root);
        return rotateleft(root);
    } else if (balance > 1 && Word > root -> word) {
        root -> left = rotateleft(root);
        return rotateright(root);
    } else {
        return root;
    }
}
Nodetree * Nodedelete(Nodetree * node, string key) {
    if (node == NULL) {
        return node;
    } else if (key > node -> word) {
        node -> right = Nodedelete(node -> right, key);
    } else if (key < node -> word) {
        node -> right = Nodedelete(node -> right, key);
    } else {

        if (node -> left == NULL) {
            Nodetree * temp = node -> right;
            delete node;
            return temp;
        } else if (node -> right == NULL) {
            Nodetree * temp = node -> left;
            delete node;
            return temp;
        } else {

            Nodetree * succParent = node;
            Nodetree * succ = node -> right;
            while (succ -> left != NULL) {
                succParent = succ;
                succ = succ -> left;
            }

            if (succParent != node)
                succParent -> left = succ -> right;
            else
                succParent -> right = succ -> right;

            node -> word = succ -> word;
            delete succ;
            return node;
        }
    }

    if (node == NULL) {
        return node;
    }

    node -> height = 1 + max(getheight(node -> left), getheight(node -> right));

    int balance = getbalance(node);
    if (balance < -1 && getbalance(node -> right) <= 0) {
        return rotateleft(node);
    } else if (balance > 1 && getbalance(node -> right) >= 0) {
        return rotateright(node);
    } else if (balance < -1 && getbalance(node -> right) > 0) {
        node -> right = rotateright(node);
        return rotateleft(node);
    } else if (balance > 1 && getbalance(node -> right) < 0) {
        node -> left = rotateleft(node);
        return rotateright(node);
    }
    return node;
}

void display_Node(Nodetree * root)
{
	string Word=root -> word;
    cout << "\n\n\t//==========================================\\\\\n";
    cout << "\n \t[*] Word: ";
    for(int i=0;i<Word.length();i++){
    	if(Word[i]=='@'){
    		cout<<" ";
		}
		else{
			cout<<Word[i];
		}
	}
	cout<<endl;
    cout << " \t[*] Meaning: "<< root -> meaning << endl;
    cout << "\n \t[*] Suggestion: ";
    cout << root -> synoyms[0] << "\t";
    cout << root -> synoyms[1] << "\t";
    cout << root -> synoyms[2] << endl;
    cout << "\n\t\\\\==========================================//";
}
void inorder(Nodetree * root)
{
    if (root == NULL)
        return;

    inorder(root -> left);
    display_Node(root);
    inorder(root -> right);

}

//global

void wordofthedaygl(Nodetree * root, int count, int freq,int flag) {
//    if (root == NULL){
//    	return;
//        display_Node(root);
//	}
//
//	else{
//
//    	wordofthedaygl(root -> left, ++count, freq,flag);
//    	wordofthedaygl(root -> right, ++count, freq,flag);
//		if (count == freq&&flag==0)
//    	{
//        	display_Node(root);
//        	return wordofthedaygl(root, ++count, freq,1);
//    	}
//
//	}
	Nodetree *temp;
	temp=root;
	while(1){

		if(count==freq){
			display_Node(root);
			break;
		}
		if(count%2==0){
			if(temp->left==NULL){
				display_Node(root);
				break;
			}
			else{
				count++;
				temp=temp->left;
			}
		}
		if(count%2!=0){
			if(temp->right==NULL){
				display_Node(root);
				break;
			}
			else{
				count++;
				temp=temp->right;
			}
		}










	}








}

class Dictionary {
    int size;
    NodeHash * arr;
    public:
        Dictionary() {
            size = 26;

            arr = new NodeHash[size];
            for (int i = 65; i < 92; i++) {
                insert(i);
            }

            readingdictionary((char * )"A.txt");
        }

    void readingdictionary(char * file) {
        ifstream R;
        string W;
        string M;
        string S1;
        string S2;
        string S3;
        R.open(file, ios::app);
        while (!R.eof()) {
            std::getline(R, W);
            std::getline(R, M);
            std::getline(R, S1);
            std::getline(R, S2);
            std::getline(R, S3);

            insertword(W, M, S1, S2, S3);
        }

        R.close();
    }

    int Hashfuction(char key) {
        int index = key % 65;
        return index;
    }
    void insert(char key) {
        int index = Hashfuction(key);
        arr[index].Firstletter = key;
    }
    void insertword(string Word, string Meaning, string Sy1, string Sy2, string Sy3)
    {
        int first = Word[0];
        if (first > 91) {
            first = first - 32;
            Word[0] = Word[0] - 32;
        }
        for (int i = 1; i < Word.length(); i++) {
            if (Word[i] < 91) {
                Word[i] = Word[i] + 32;
            }
        }

        int index = Hashfuction(first);
        arr[index].root = Nodeinsert(arr[index].root, Word, Meaning, Sy1, Sy2, Sy3);
        arr[index].Frequency++;

    }
    bool searchs(Nodetree * root, string key) {
        if (root == NULL)
            return false;

        else {
            searchs(root -> left, key);
            if (root -> synoyms[0] == key || root -> synoyms[1] == key || root -> synoyms[2] == key) {
                //print;
                display_Node(root);
                return true;
            }
            searchs(root -> right, key);

        }
    }


    void search(string key) {
        int first = key[0];
        if (first > 91) {
            first = first - 32;
            key[0] = key[0] - 32;
        }
        for (int i = 1; i < key.length(); i++) {
            if (key[i] < 91) {
                key[i] = key[i] + 32;
            }
        }
        int index = Hashfuction(first);
        Nodetree * temp = arr[index].root;
        if (temp == NULL) {
            for (int i = 0; i < 26; i++) {

                bool confirm = searchs(arr[i].root, key);
                if (confirm == true)
                    return;
                if (false == searchs(arr[25].root, key)) {
                    cout << "\n\t[-] No word" << endl;
                    return;
                }
            }
        }
        while (1)
        {

            if (temp -> word == key) {

               display_Node(temp);
                break;
            } else if (key < temp -> word) {
                if (temp -> left == NULL) {

                    for (int i = 0; i < 26; i++) {

                        bool confirm = searchs(arr[i].root, key);
                        if (confirm == true)
                            break;
                        if (false == searchs(arr[25].root, key)) {
                            cout << "\n\t[-] No word" << endl;
                            break;
                        }
                    }
                    break;
                } else {
                    temp = temp -> left;
                }
            } else if (key > temp -> word) {
                if (temp -> right == NULL) {
                    for (int i = 0; i < 26; i++) {

                        bool confirm = searchs(arr[i].root, key);
                        if (confirm == true)
                            break;
                        if (false == searchs(arr[25].root, key)) {
                            cout << "No word" << endl;
                            break;
                        }
                    }

                    break;
                } else {
                    temp = temp -> right;
                }
            } else {
                cout << "no word found: ";
                break;
            }
        }
        return;
    }
    int Viewfrequncy(string F) {
        int First = F[0];
        if (First > 91) {
            First = First - 32;
        }
        int index = Hashfuction(First);
        return arr[index].Frequency;
    }


    int totalFreq()
    {
        int total_count = 0;
        total_count += Viewfrequncy("A");
        total_count += Viewfrequncy("B");
        total_count += Viewfrequncy("C");
        total_count += Viewfrequncy("D");
        total_count += Viewfrequncy("E");
        total_count += Viewfrequncy("F");
        total_count += Viewfrequncy("G");
        total_count += Viewfrequncy("H");
        total_count += Viewfrequncy("I");
        total_count += Viewfrequncy("J");
        total_count += Viewfrequncy("K");
        total_count += Viewfrequncy("L");
        total_count += Viewfrequncy("M");
        total_count += Viewfrequncy("N");
        total_count += Viewfrequncy("O");
        total_count += Viewfrequncy("P");
        total_count += Viewfrequncy("Q");
        total_count += Viewfrequncy("R");
        total_count += Viewfrequncy("S");
        total_count += Viewfrequncy("T");
        total_count += Viewfrequncy("U");
        total_count += Viewfrequncy("V");
        total_count += Viewfrequncy("W");
        total_count += Viewfrequncy("X");
        total_count += Viewfrequncy("Y");
        total_count += Viewfrequncy("Z");
        return total_count;
    }
    void displayFreq()
    {
        int total_count = totalFreq();

        cout << "\t [-] TOTAL WORDS: " << total_count << endl;
        cout << "\t  [+] A: " << Viewfrequncy("A") << endl;
        cout << "\t  [+] B: " << Viewfrequncy("B") << endl;
        cout << "\t  [+] C: " << Viewfrequncy("C") << endl;
        cout << "\t  [+] D: " << Viewfrequncy("D") << endl;
        cout << "\t  [+] E: " << Viewfrequncy("E") << endl;
        cout << "\t  [+] F: " << Viewfrequncy("F") << endl;
        cout << "\t  [+] G: " << Viewfrequncy("G") << endl;
        cout << "\t  [+] H: " << Viewfrequncy("H") << endl;
        cout << "\t  [+] I: " << Viewfrequncy("I") << endl;
        cout << "\t  [+] J: " << Viewfrequncy("J") << endl;
        cout << "\t  [+] K: " << Viewfrequncy("K") << endl;
        cout << "\t  [+] L: " << Viewfrequncy("L") << endl;
        cout << "\t  [+] M: " << Viewfrequncy("M") << endl;
        cout << "\t  [+] N: " << Viewfrequncy("N") << endl;
        cout << "\t  [+] O: " << Viewfrequncy("O") << endl;
        cout << "\t  [+] P: " << Viewfrequncy("P") << endl;
        cout << "\t  [+] Q: " << Viewfrequncy("Q") << endl;
        cout << "\t  [+] R: " << Viewfrequncy("R") << endl;
        cout << "\t  [+] S: " << Viewfrequncy("S") << endl;
        cout << "\t  [+] T: " << Viewfrequncy("T") << endl;
        cout << "\t  [+] U: " << Viewfrequncy("U") << endl;
        cout << "\t  [+] V: " << Viewfrequncy("V") << endl;
        cout << "\t  [+] W: " << Viewfrequncy("W") << endl;
        cout << "\t  [+] X: " << Viewfrequncy("X") << endl;
        cout << "\t  [+] Y: " << Viewfrequncy("Y") << endl;
        cout << "\t  [+] Z: " << Viewfrequncy("Z") << endl;

    }

    void display() {
        for (int i = 0; i < 26; i++) {
            inorder(arr[i].root);
        }
    }
    Nodetree * deletenode(string key) {
        char first = key[0];
        int index = Hashfuction(first);
        arr[index].root = Nodedelete(arr[index].root, key);

    }

    void wordoftheday()
    {
    	srand(time(NULL));
        int index = 0 + (rand() % 25);
        while(arr[index].root==NULL){
        	if(arr[index].root==NULL){
        		int index = 0 + (rand() % 25);
			}
			cout<<index<<endl;
		}

        int trivfreq = 1 + (rand() % arr[index].Frequency);
        trivfreq=trivfreq/2;
        cout<<arr[index].Frequency<<endl;
        wordofthedaygl(arr[index].root, 0, trivfreq,0);
        return;

    }

};
int main() {
    Dictionary T;
    int ch;
    system("Color 06");

    do
    {

        main_L:
        system("CLS");
        cout << "\n\t }--------------------------------------------{";
        cout << "\n\t}------------- [ DICTIONARY ] -----------------{";
        cout << "\n\t }--------------------------------------------{";
        cout << "\n\t================================================";
        cout << "\n\n\t [1]: Search Meaning";
        cout << "\n\t [2]: Word Count ";
        cout << "\n\t [3]: Word of the day";
        cout << "\n\t [4]: Display Dictionary";
        cout << "\n\t [0]: Exit\t\t\t :";
        //cout << "\n\t================================================";
        cin >> ch;


        switch(ch)
        {
        case 1:
            {
            	E:
                string tempst;
                system("CLS");
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t}------------- [ DICTIONARY ] -----------------{";
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t================================================";
                cout << "\n\n\t [*] >>| Enter the word |<<";
                cout << "\n\t Word: ";
                fflush(stdin);
                getline(cin,tempst);
                system("CLS");
                T.search(tempst);
                getchar();
                //getchar();
                break;

            }

        case 2:
            {

                system("CLS");
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t}------------- [ DICTIONARY ] -----------------{";
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t================================================";
                cout << "\n\n\t [*] >>| WORD COUNT IN DICTIONARY |<<";
                T.displayFreq();
                getchar();
                getchar();



                break;
            }

        case 3:
            {
                system("CLS");
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t}------------- [ DICTIONARY ] -----------------{";
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t================================================";
                cout << "\n\n\t [*] >>| WORD OF THE DAY |<<";
                cout << "\n\t [-] Word: ";
                T.wordoftheday();
                getchar();
				getchar();
                break;


            }
        case 4:
            {
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t}------------- [ DICTIONARY ] -----------------{";
                cout << "\n\t }--------------------------------------------{";
                cout << "\n\t================================================";
                cout << "\n\n\t [*] >>| DICTIONARY |<<";
                T.display();
                getchar();
                getchar();
                break;
            }

        case 0:
            {
                exit(0);
                break;
            }

        default:
            {
                goto main_L;
            }
        }



    }while(ch!=0);

}
