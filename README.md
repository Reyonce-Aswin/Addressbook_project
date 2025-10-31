[README.md](https://github.com/user-attachments/files/23111273/README.md)
# Address Book in C

A **console-based address book application** written in C, designed for Linux terminal environments.  
It allows users to efficiently **manage, search, edit, and store contact information** directly from the command line.

---

## Project Overview

This address book system provides a simple interface to:
- Add, edit, delete, and view contacts
- Validate name, phone number, and email inputs
- Search contacts by name, phone number, or email
- Store and retrieve contacts from a CSV file
- Maintain data integrity between program runs

All contact data is stored in a **`addressbook.csv`** file, automatically loaded at startup and saved upon exit.

---

## Features

✅ **Create Contacts** – Add new contacts with validation checks  
✅ **List Contacts** – Display all contacts in a formatted table  
✅ **Search Contacts** – Find contacts by name, number, or email  
✅ **Edit Contacts** – Modify existing contact details  
✅ **Delete Contacts** – Remove contacts safely with confirmation  
✅ **Data Persistence** – Automatically load and save data from/to CSV  
✅ **Input Validation** – Ensures proper name, phone, and email formats  
✅ **Color-Coded CLI** – Uses ANSI color codes for a better terminal experience  

---

## Project Structure

```
├── main.c         # Entry point of the program (menu-driven interface)
├── contact.c      # Contains all logic and function definitions
├── contact.h      # Header file with structure definitions and function prototypes
└── addressbook.csv # Generated automatically when you save contacts
```

---

## How to Compile and Run

### Prerequisites
- GCC compiler
- Linux or any Unix-based terminal supporting ANSI colors

### Build
```bash
gcc main.c contact.c -o addressbook
```

### Run
```bash
./addressbook
```

---

## File Format

Contacts are stored in a **CSV** file with the following format:

```
#<contact_count>
"Name","Phone Number","Email"
John Doe,9876543210,john@example.com
Jane Smith,9123456789,jane@sample.com
```

---

## Data Structures Used

### `Contacts`
```c
typedef struct Contact_data {
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;
```

### `AddressBook`
```c
typedef struct AddressBook_Data {
    Contacts contact_details[100];
    int contact_count;
} AddressBook;
```

---

## Color Codes (for terminal display)

| Color | Description |
|--------|--------------|
| 🔴 **RED** | Error / Invalid input |
| 🟢 **GREEN** | Success message |
| 🟡 **YELLOW** | Warning or caution |
| 🔵 **BLUE** | Headings / UI elements |
| 🟣 **MAGENTA** | Prompts and user options |
| 🔷 **CYAN** | Input requests |

---

## Example Usage

```
Address book menu
1. Add contact
2. Search contact
3. Edit contact
4. Delete contact
5. Display contact
6. Save contact
7. Exit
Enter the option: 1

Enter Name: John Doe
Enter Phone Number: 9876543210
Enter Mail ID: john@example.com
Contact Added Successfully!
```

---

## Author

**Reyonce Aswin T**  
*Student ID: 25021_181*  
Embedded Systems Student, Emertxe Information Technologies, Bangalore

---


## Future Enhancements

- Add JSON/SQLite database support  
- Import/export to vCard format  
- GUI version using GTK or Qt  
- Integration with cloud storage  

---
