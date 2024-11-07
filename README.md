# Console-Based Notepad

A simple console-based Notepad application in C++ that allows users to create, edit, save, and load text files with spell-checking functionality. This project demonstrates linked list operations and spell-checking techniques with custom cursor control in a console environment.

## Features

- **Text Editing**: Insert, delete, and navigate text using custom cursor controls.
- **Saving & Loading**: Automatically load from and save to `save.txt`.
- **Cursor Control**: Navigate text using arrow keys; the console displays the custom cursor in real-time.
- **Spell Checker**: Check spelling with suggestions for misspelled words. Suggestions include letter substitution, omission, insertion, and reversal for words not found in `dictionary.txt`.

## Usage

1. **Start Editing**: Press any key to start the Notepad.
2. **Insert Text**: Type directly to add text.
3. **Delete Text**: Use "Backspace" to delete characters.
4. **Save**: Press `Ctrl + S` to save the content to `save.txt`.
5. **Load**: Press `Ctrl + L` to load content from `save.txt`.
6. **Exit**: Press `Esc` to exit.

## File Structure

- **main.cpp**: Main application file containing the Notepad functionality and spell-check logic.
- **save.txt**: The default file to save and load Notepad content.
- **dictionary.txt**: Dictionary file with correct words used for spell-checking.

## How It Works

- **2D Doubly Linked List**: Each character in the notepad is stored in a node, linked both horizontally and vertically, allowing multi-line text editing.
- **Spell Checking**: Dictionary words are loaded into a vector. For each word not found in the dictionary, the spell-checker suggests alternatives using:
  - Letter Substitution
  - Letter Omission
  - Letter Insertion
  - Letter Reversal

## Example

For a sample text file `save.txt`:
```
I like coding.
```

If you type `codding`, the application might suggest:
```
codding => coding
```


## Contributing

Feel free to contribute to this project by creating pull requests, reporting issues, or suggesting new features.
