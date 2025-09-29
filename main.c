/*
Name: Reyonce Aswin T
Student ID: 25021_181
Description: This project is a console-based address book application designed for Linux terminal environments. 
             It allows users to efficiently manage contact information through a command-line interface

             Users can seamlessly add, edit, delete, and view contact entries. 
             To ensure data integrity, the application performs validation checks on all contact inputs, including names, phone numbers, and email addresses.
             The application supports robust searching by name, phone number, and email address, allowing for quick retrieval of specific contacts.
             All contacts are saved to a file, ensuring data is retained between sessions. 
             The program also features a clean exit function to properly save all changes.
             Contacts can be imported from and exported to CSV files, providing a convenient way to back up or migrate data.
*/
#include <stdio.h>
#include "contact.h"
/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    int option;
    AddressBook addressbook;
    addressbook.contact_count = 0;

    init_initialization(&addressbook); // Function call for loading all contacts from flle to program

    while (1)
    {
        printf(BLUE"\nAddress book menu\n"RESET); /* Give a prompt message for a user */
        printf(BLUE"1. Add contact\n2. Search contact\n3. Edit contact\n4. Delete contact\n5. Display contact\n6. Save contact\n7. Exit\n"RESET);
        printf(CYAN"Enter the option : "RESET);
        scanf("%d", &option);

        switch (option) /* Based on choosed option */
        {
        case 1: // Create or Add Contacts
            create_contact(&addressbook);
            break;
            
        case 2: // Search Contacts
            search_contacts(&addressbook);
            break;

        case 3: // Edit Contacts
            //printf("Edit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */

            edit_contact(&addressbook);
            break;

        case 4: // Delete Contacts
            //printf("Delete Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */

            delete_contact(&addressbook);
            break;

        case 5: // List or Display all Contacts
            printf(CYAN"\nList Contacts:"RESET);
            list_contacts(&addressbook);
            break;

        case 6: // Save Contacts
            printf(GREEN"Saving contacts\n"RESET);
            save_contacts(&addressbook);
            printf(GREEN"Contacts saved successfully\n"RESET);
            break;

        case 7: // Exit with saving
            printf(GREEN"\nINFO : Save and Exit...\n\n"RESET);
            save_contacts(&addressbook);
            return 0;

        default: // If wrong input option
            printf(RED"Invalid option \n"RESET);
            break;
        }
    }
    return 0;
}