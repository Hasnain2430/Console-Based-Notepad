#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Node
{
    char data;
    Node *before;
    Node *after;
    Node *below;
    Node *above;

    Node()
    {
        data = ' ';
        before = NULL;
        after = NULL;
        below = NULL;
        above = NULL;
    }

    Node(char c)
    {
        data = c;
        before = NULL;
        after = NULL;
        below = NULL;
        above = NULL;
    }
};

class Notepad
{
private:
    Node *cursor;
    Node *head;

public:
    Notepad()
    {
        cursor = NULL;
        head = NULL;
    }

    void insert(char c)
    {
        Node *newNode = new Node(c);
        Node *temp = head;

        if (!cursor) // If cursor is not set, create a new line ( Document is Empty )
        {
            Node *newline = new Node('\n');
            cursor = newline;
            head = newline;
        }
        if (c == '\n') // New Line ( when enter is hit )
        {
            if (head->below == NULL) // when enter is hit for the first time, head is connected to the new line
            {
                head->below = newNode;
                newNode->above = head;
            }
            else
            {
                while (temp->below != NULL) // connecting the first character of each line
                {
                    temp = temp->below;
                }
                temp->below = newNode;
                newNode->above = temp;
            }
        }

        // Link the new node into the doubly linked list

        newNode->before = cursor;
        newNode->after = cursor->after;
        if (cursor->after)
        {
            cursor->after->before = newNode;
        }

        cursor->after = newNode;

        cursor = newNode; // Move the cursor to the new node
    }

    void del()
    {
        if (!cursor)
        {
            return; // Cannot delete a newline or if cursor is not set
        }

        Node *toDelete = cursor;

        cursor = cursor->before;

        if (cursor)
        {
            cursor->after = toDelete->after;
        }

        if (toDelete == head)
        {
            head = toDelete->after;
        }

        delete toDelete;
    }

    void left()
    {
        if (cursor && cursor->before)
        {
            cursor = cursor->before;
        }
    }

    void right()
    {
        if (cursor && cursor->after)
        {
            cursor = cursor->after;
        }
    }

    void up()
    {
        if (cursor) // words if cursor is not equal to null
        {
            while (cursor->before != NULL && cursor->above == NULL)
            {
                left(); // Move cursor to left until it reaches first character of line
            }
            if (cursor == head) // Ager head hai to iss sai uper ni jaa skte to it takes us to the end of the line
            {
                while (cursor->after != NULL && cursor->after->above == NULL)
                {
                    right(); // Taking us the to end of the line
                }
            }
            else // If it is not head ( we are not on the first line )
            {
                cursor = cursor->above; // Moves the cursor to the line above
                while (cursor->after != NULL && cursor->after->above == NULL)
                {
                    right(); // Takes us to the end of the new line
                }
            }
        }
    }

    void down()
    {
        if (cursor) // words if cursor is not equal to null
        {
            while (cursor->before != NULL && cursor->below == NULL)
            {
                left(); // Move cursor to left until it reaches first character of line
            }
        }

        cursor = cursor->below; // Moves the cursor to the line below

        while (cursor->after != NULL && cursor->after->above == NULL)
        {
            right(); // Takes us to the end of the new line
        }
    }

    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data;
            if (temp == cursor)
            {
                cout << '^';
            }

            if (temp->data == '\n')
            {
                cout << endl;
            }

            temp = temp->after;
        }
    }

    Node *getFirstNode()
    {
        return head;
    }

    ~Notepad()
    {
        while (head)
        {
            Node *temp = head;
            head = head->below;
            delete temp;
        }
    }
};

void loadTextFromFile(Notepad &notepad)
{
    ifstream inputFile("save.txt"); // reading from .txt file
    if (inputFile.is_open())
    {
        char character;

        while (inputFile.get(character)) // gets a character from the file
        {
            notepad.insert(character); // inserts it into the linked list by calling the insert function
        }
        inputFile.close();
    }
}

void saveToFile(Notepad &notepad)
{
    ofstream outFile("save.txt"); // writing to file
    if (outFile.is_open())
    {
        Node *temp = notepad.getFirstNode(); // get head
        while (temp)                         // runs till end of nodes in linked list
        {
            outFile << temp->data; // writes in file
            temp = temp->after;    // moves to next node
        }
        outFile.close();
    }
}

vector<string> loadDictionary() // Saving dictionary in vector
{
    vector<string> dictionary;
    ifstream dictionaryFile("dictionary.txt"); // reading dictionary file

    if (dictionaryFile.is_open()) // opening it
    {
        string word;
        while (getline(dictionaryFile, word)) // picks up each line from dictionary
        {
            dictionary.push_back(word); // gets stored in vector
        }
        dictionaryFile.close();
    }
    return dictionary; // returns vector ( has the whole dictionary stored in it )
}

void Letter_sub(Notepad &notepad, vector<string> dictionary)
{
    Node *temp = notepad.getFirstNode();
    string word;
    while (temp) // words until last node in Linked list ( last character basically )
    {
        if (isalpha(temp->data)) // Alphabet hai ya nai
        {
            word += temp->data; // joining character by character to make word
        }
        else if (!word.empty())
        {
            // Check if the word is in the dictionary
            bool found = false;
            for (int i = 0; i < dictionary.size(); i++) // iterate through dictionary to find the word
            {
                if (word == dictionary[i])
                {
                    found = true;
                    break; // Mill gaya to true and then the loop gets broken ( no need to )
                }
            }
            if (!found)
            {
                // Word is not in the dictionary, suggest corrections
                bool suggestions = false;
                for (int j = 0; j < dictionary.size(); j++) // iterate through each word in the dictionary
                {
                    string dictWord = dictionary[j];
                    if (dictWord.size() == word.size()) // Ager size same hai then only we try to correct it
                    {
                        int diffCount = 0;
                        for (int i = 0; i < word.size(); i++) // checking k kitne letters k fark hai
                        {
                            if (word[i] != dictWord[i])
                            {
                                diffCount++;
                            }
                            if (diffCount > 1)
                            {
                                break; // only works if there is exact one letter difference ( eik sai zada pr kaam ni krey gha bcs Question say so )
                            }
                        }
                        if (diffCount == 1)
                        {
                            if (suggestions)
                            {
                                cout << ", ";
                            }
                            else
                            {
                                cout << word << " => ";
                            }
                            cout << dictWord; // dict word prints here
                            suggestions = true;
                        }
                    }
                }
            }
            word.clear(); // the word gets cleared and same process on new word can now be repeated
        }
        temp = temp->after;
    }
}

void Lettet_Omission(Notepad &notepad, vector<string> dictionary)
{
    Node *temp = notepad.getFirstNode();
    string word;
    while (temp) // words until last node in Linked list ( last character basically )
    {
        if (isalpha(temp->data)) // Alphabet hai ya nai
        {
            word += temp->data; // joining character by character to make word
        }
        else if (!word.empty())
        {
            // Check if the word is in the dictionary
            bool found = false;
            for (int i = 0; i < dictionary.size(); i++) // iterate through dictionary to find the word
            {
                if (word == dictionary[i])
                {
                    found = true;
                    break; // Mill gaya to true and then the loop gets broken ( no need to )
                }
            }
            if (!found)
            {
                // Word is not in the dictionary, suggest corrections
                bool suggestions = false;

                // Suggest corrections by omitting one letter at a time
                for (int i = 0; i < word.size(); i++)
                {
                    string omittedWord = word.substr(0, i) + word.substr(i + 1);

                    for (int j = 0; j < dictionary.size(); j++)
                    {
                        string dictWord = dictionary[j];
                        if (dictWord == omittedWord)
                        {
                            if (suggestions)
                            {
                                cout << ", ";
                            }
                            else
                            {
                                cout << word << " => ";
                            }

                            cout << dictWord;
                            suggestions = true;
                        }
                    }
                }
            }
            word.clear();
        }
        temp = temp->after;
    }
}

int main()
{
    Notepad notepad;
    char key;

    vector<string> dictionary = loadDictionary();

    system("cls");
    cout << setw(80) << "~~~~~~~~~~ Console-Based Notepad ~~~~~~~~~~" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(68) << "Press Any key to start! " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    while (true)
    {
        notepad.display();
        key = _getch();

        if (key == 27)
        {
            notepad.~Notepad();
            break; // If ESC key is pressed, exit the program
        }
        else if (key == 8)
        {
            notepad.del(); // If backspace is pressed
        }
        else if (key == 13)
        {
            notepad.insert('\n'); // If Enter is pressed
        }
        else if (key == 12)
        {
            loadTextFromFile(notepad); // If Ctrl + L is pressed (load from file)
        }
        else if (key == 19)
        {
            saveToFile(notepad); // // If Ctrl + S is pressed (Save to File)
        }
        else if ((key >= 32 && key <= 126) || key == ' ')
        {
            notepad.insert(key); // Character input
            if (key == ' ')
            {
                cout << endl;
                cout << setw(90);
                Letter_sub(notepad, dictionary);
                cout << endl;
                cout << setw(90);
                Lettet_Omission(notepad, dictionary);
                key = _getch();
            }
        }

        else if (key == 0 || key == -32)
        {
            key = _getch();
            if (key == 75) // Left arrow
            {
                notepad.left();
            }
            else if (key == 77) // Right arrow
            {
                notepad.right();
            }
            else if (key == 72) // Up Arrow
            {
                notepad.up();
            }
            else if (key == 80) // Down Arrow
            {
                notepad.down();
            }
        }

        system("cls");
    }

    return 0;
}
