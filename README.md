# Address Book Management System in C

## Project Overview

The Address Book Management System is a menu-driven application developed using C programming. It allows users to manage contact information efficiently by performing operations such as creating, searching, editing, deleting, and displaying contacts.

The application uses structures and file handling concepts to store and retrieve contact information, ensuring that contact details are available even after the program is closed.

## Features

- Create new contacts.
- Search contacts using name, phone number, or email ID.
- Edit existing contact details.
- Delete contacts.
- Display all saved contacts.
- Validate contact names, phone numbers, and email addresses.
- Check duplicate phone numbers and email IDs.
- Sort contacts alphabetically by name.
- Save contact information into a file.
- Load previously saved contacts when the application starts.

## Technologies Used

- Programming Language: C
- Compiler: GCC
- Concepts: Structures, Arrays, Functions, Pointers, String Handling, File Handling
- File Operations: `fopen()`, `fscanf()`, `fprintf()`, `fclose()`
- String Functions: `strcmp()`, `strcpy()`, `strlen()`

## Project Structure

```text
AddressBook-NewDesign/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── contacts.txt
├── README.md
└── .gitignore
```

## How to Compile

Make sure GCC is installed on your system.

Open the terminal in the project directory and execute:

```bash
gcc main.c contact.c file.c populate.c -o addressbook
```

## How to Execute

On Linux:

```bash
./addressbook
```

On Windows (using MinGW):

```bash
addressbook.exe
```

## Application Menu

1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Save and Exit

## File Handling

The application uses `contacts.txt` to store contact information.

- Existing contacts are loaded when the application starts.
- New or modified contact information is maintained in the address book.
- Contact information is saved into the file when the user selects Save and Exit.

## Learning Outcomes

Through this project, I gained practical experience in:

- Developing modular C programs.
- Working with structures and arrays.
- Implementing CRUD operations.
- Understanding pointers and functions.
- Performing string manipulation and validation.
- Implementing file handling for persistent data storage.
- Organizing a project using multiple source and header files.

## Author

Manupriya J

## Project Category

C Programming | Data Structures | File Handling
