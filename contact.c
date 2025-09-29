#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "contact.h"

/* Function Definition*/

/* Loading Contacts to the program from File */ 
void init_initialization(AddressBook *addressbook)
{
    FILE *fp = fopen("addressbook.csv","r");
    if(fp == NULL){ // Checking if  file is present or not
        printf(RED"Error: Unable to access Addressbook or Addressboook not found!\n"RESET);
        return;
    }
    fscanf(fp,"#%d\n",&addressbook->contact_count); // reading the no. of contacts/contact count

    fscanf(fp, "%*[^\n]\n");    // This line reads and discards the header row

    for(int i = 0; i < addressbook->contact_count; i++){ // loading the contacts to the structures
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",
            addressbook->contact_details[i].Name,
            addressbook->contact_details[i].Mobile_number,
            addressbook->contact_details[i].Mail_ID);
    }
    fclose(fp); // close the file
}

/* Creating Contacts */
int create_contact(AddressBook *addressbook) 
{
    char name[32], phone[15], email[35]; // Temporary Variables to store details before/for validating
    char choice;

    do {
        int i = addressbook->contact_count;

        // Validate Name
        do {
            printf(CYAN"\nEnter Name: "RESET);
            scanf(" %[^\n]", name);
        } while (!validate_name(name));

        // Validate Phone
        do {
            printf(CYAN"Enter Phone Number: "RESET);
            scanf(" %[^\n]", phone);
        } while (!validate_phone(addressbook, phone));

        // Validate Email
        do {
            printf(CYAN"Enter Mail ID: "RESET);
            scanf(" %[^\n]", email);
        } while (!validate_email(addressbook, email));

        // Copying from temporary variable to structure
        strcpy(addressbook->contact_details[i].Name, name);
        strcpy(addressbook->contact_details[i].Mobile_number, phone);
        strcpy(addressbook->contact_details[i].Mail_ID, email);

        addressbook->contact_count++;
        printf(GREEN"\nContact Added Successfully!\n"RESET);

        printf(MAGENTA"Do you want to add more contacts? (y/n): "RESET);
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
    
    sort_contacts(addressbook); // Sorting Contacts after storing the details

    return 0;
}

/* Listing All Contacts */
void list_contacts(AddressBook *addressbook) 
{
    if (addressbook->contact_count == 0) { // If no contacts are available or found
        printf("\nNo contacts available\n");
        return;
    }

    // printing the contact list
    print_contact_table();
    for (int i = 0; i < addressbook->contact_count; i++) {
        print_contact(&addressbook->contact_details[i], i + 1, i);
    }
    printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);
}

/* Search Contacts */
int search_contacts(AddressBook *addressbook) {
    if (addressbook->contact_count == 0) { // Checking if contacts present or  not
        printf("\nNo contacts available\n");
        return 0;
    }
    int ch;
    while(1){
        printf(BLUE"Search Contact menu : \n1. Name \n2. Mobile number\n3. Mail ID\n4. Exit\nEnter the option : "RESET);
        scanf("%d", &ch);
        switch (ch) {
            case 1: 
                search_name(addressbook, false); // mode -> false because no need to ask user to enter the choice for editing or deleting
                break;
            case 2: 
                search_phone(addressbook, false); 
                break;
            case 3: 
                search_email(addressbook, false); // mode -> false because no need to ask user to enter the choice for editing or deleting
                break;
            case 4: 
                return 0; // exit from the edit contact menu.
            default: 
                printf(RED"Invalid Choice\n"RESET);
        }
    }
}

/* Edit Contacts*/
int edit_contact(AddressBook *addressbook) {
    if (addressbook->contact_count == 0) {
        printf(YELLOW"\nNo contacts available\n"RESET);
        return 0;
    }

    edit:
    char main_choice;
    do {
        printf(BLUE"\nSearch Contact to Edit : \n1. Name \n2. Mobile number\n3. Mail ID\n4. Exit"RESET CYAN"\nEnter the option : "RESET);
        int opt;
        scanf("%d", &opt);

        int idx = -1;
        switch (opt) {
            case 1:
                idx = search_name(addressbook, true);
                break;
            case 2:
                idx = search_phone(addressbook, true);
                break;
            case 3:
                idx = search_email(addressbook, true);
                break;
            case 4:
                return 0;
            default:
                printf(RED"Invalid option.\n"RESET);
                continue;
        }

        if (idx == -1) {
            continue;
        }

        // Display the selected contact details before editing
        printf(CYAN"\nSelected Contact:\n"RESET);
        print_contact_table();
        print_contact(&addressbook->contact_details[idx], 1, idx);
        printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);

        // Add confirmation for editing
        char confirm_edit;
        printf(MAGENTA"Are you sure you want to edit this contact? (y/n): "RESET);
        scanf(" %c", &confirm_edit);

        if (confirm_edit == 'n' || confirm_edit == 'N') {
            printf(YELLOW"Editing cancelled. Returning to edit menu.\n"RESET);
            goto edit; // Go back to the main edit menu loop
        }

        char sub_choice;
        do {
            int option;
            printf(BLUE"\nEdit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "RESET);
            scanf("%d", &option);

            char edit_n[32], edit_p[15], edit_e[35];

            switch (option) {
            case 1:
                do {
                    printf(CYAN"Enter the new name: "RESET);
                    scanf(" %[^\n]", edit_n);
                } while (!validate_name(edit_n));
                strcpy(addressbook->contact_details[idx].Name, edit_n);
                printf(GREEN"Name Changed Successfully!\n"RESET);
                break;
            case 2:
                do {
                    printf(CYAN"Enter the new Phone Number: "RESET);
                    scanf("%s", edit_p);
                } while (!validate_phone(addressbook, edit_p));
                strcpy(addressbook->contact_details[idx].Mobile_number, edit_p);
                printf(GREEN"Phone Number Changed Successfully!\n"RESET);
                break;
            case 3:
                do {
                    printf(CYAN"Enter the new E-Mail ID: "RESET);
                    scanf("%s", edit_e);
                } while (!validate_email(addressbook, edit_e));
                strcpy(addressbook->contact_details[idx].Mail_ID, edit_e);
                printf(GREEN"Email Changed Successfully!\n"RESET);
                break;
            case 4:
                sub_choice = 'n';
                continue;
            default:
                printf(RED"Invalid Choice\n"RESET);
            }

            printf(MAGENTA"Do you want to edit more fields of this contact? (y/n): "RESET);
            scanf(" %c", &sub_choice);

        } while (sub_choice == 'y' || sub_choice == 'Y');

        sort_contacts(addressbook);

        printf(MAGENTA"Do you want to edit other contacts? (y/n): "RESET);
        scanf(" %c", &main_choice);

    } while (main_choice == 'y' || main_choice == 'Y');

    return 0;
}

/* Delete Contacts */
int delete_contact(AddressBook *addressbook) 
{
    if (addressbook->contact_count == 0) {
        printf("\nNo contacts available\n");
        return 0;
    }

    char choice;
    do {
        // Step 1: Pick which contact to delete
        printf(BLUE"\nDelete Contact menu:\n1. Name\n2. Mobile number\n3. Mail ID\n4. Exit\nEnter option: "RESET);
        int opt;
        scanf("%d", &opt);

        int idx = -1;
        switch (opt) {
            case 1: 
                idx = search_name(addressbook, true); // mode -> true because need to ask user to enter the choice for editing
                break;
            case 2: 
                idx = search_phone(addressbook, true); 
                break;
            case 3: 
                idx = search_email(addressbook, true); // idx gets the index value of the contact to edit
                break;
            case 4: 
                return 0;
            default: 
                printf(RED"Invalid option.\n"RESET); 
                continue;
        }

        if (idx == -1) 
            continue;
        
        // Display the selected contact details before editing
        printf(CYAN"\nSelected Contact:\n"RESET);
        printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);
        print_contact(&addressbook->contact_details[idx], 1, idx);
        printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);

        // Step 2: Delete the selected contact
        char confirm; // Confirmation for deleting
        printf(MAGENTA"Are you sure you want to delete this contact? (y/n): "RESET);
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') {
            for (int j = idx; j < addressbook->contact_count - 1; j++) {
                addressbook->contact_details[j] = addressbook->contact_details[j + 1]; // Shifting the contacts to left/top
            }
            addressbook->contact_count--; // Decreasing the contact count
            printf(GREEN"Contact deleted successfully.\n"RESET);
        } else {
            printf(YELLOW"Deletion cancelled.\n"RESET);
        }

        if (addressbook->contact_count == 0) { // If all contacts are deleted
            printf(CYAN"\nNo more contacts available to delete.\n"RESET);
            break;
        }

        // Step 3: After finishing with this contact
        printf(MAGENTA"Do you want to delete more contacts? (y/n): "RESET);
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

/* Saving Contacts to the File */
int save_contacts(AddressBook *addressbook) 
{
    FILE *fp = fopen("addressbook.csv", "w+"); // Opening the file
    fprintf(fp,"#%d\n",addressbook->contact_count); // Saving the contact count

    fprintf(fp, "\"Name\",\"Phone Number\",\"Email\"\n"); // header for contact details (because of csv)

    for (int i = 0; i < addressbook->contact_count; i++) // Saving the contact details
    {
        fprintf(fp,"%s,%s,%s\n",
            addressbook->contact_details[i].Name,
            addressbook->contact_details[i].Mobile_number,
            addressbook->contact_details[i].Mail_ID);
    }
    fclose(fp);
    return 0;
}

/* -- Search Functions -- */

/* Search by name */
int search_name(AddressBook *addressbook, bool select_mode) {
    char search_name[32];
    printf(CYAN"\nEnter Name to search: "RESET);
    scanf(" %[^\n]", search_name);

    int indices[100], count = 0;

    for (int i = 0; i < addressbook->contact_count; i++) {
        // Check if search_name is a substring of contact.Name (case-insensitive)
        if (strcasestr(addressbook->contact_details[i].Name, search_name)) {
            indices[count++] = i;
        }
    }

    if (count == 0) { // If no contacts match/found
        printf(YELLOW"No contact found with name containing: %s\n"RESET, search_name);
        return -1;
    }

    // If found print the matching contacts
    print_contact_table();
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        print_contact(&addressbook->contact_details[idx], i + 1, idx);
    }
    printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);

    // This section is for edit/delete contacts
    if (!select_mode) { // false == 0 -> !0 = 1; so exits
        return -1; // display only
    }

    int choice;
    printf(CYAN"Enter your choice (1-%d): "RESET, count);
    scanf("%d", &choice);
    if (choice < 1 || choice > count) { // Checking for invalid choice
        printf(RED"Invalid choice.\n"RESET);
        return -1;
    }
    return indices[choice - 1]; // returns index value to idx in edit/delete contacts function
}

/* Search by Phone Number */
int search_phone(AddressBook *addressbook, bool select_mode) {
    char search_phone[15];
    printf(CYAN"\nEnter Phone Number to search: "RESET);
    scanf("%s", search_phone);

    int indices[100], count = 0;

    for (int i = 0; i < addressbook->contact_count; i++) {
        // Check if search_phone is a substring of contact.Mobile_number (case-insensitive)
        if (strstr(addressbook->contact_details[i].Mobile_number, search_phone)) {
            indices[count++] = i;
        }
    }

    if (count == 0) { // If no contacts match/found
        printf(YELLOW"No contact found with phone number containing: %s\n"RESET, search_phone);
        return -1;
    }

    // If found print the matching contacts
    print_contact_table();
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        print_contact(&addressbook->contact_details[idx], i + 1, idx);
    }
    printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);

    // This section is for edit/delete contacts
    if (!select_mode) { // false == 0 -> !0 = 1; so exits
        return -1; // display only
    }

    int choice;
    printf(CYAN"Enter your choice (1-%d): "RESET, count);
    scanf("%d", &choice);
    if (choice < 1 || choice > count) { // Checking for invalid choice
        printf(RED"Invalid choice.\n"RESET);
        return -1;
    }
    return indices[choice - 1]; // returns index value to idx in edit/delete contacts function
}

/* Search by Email ID */
int search_email(AddressBook *addressbook, bool select_mode) {
    char search_email[35];
    printf(CYAN"\nEnter Email ID to search: "RESET);
    scanf(" %[^\n]", search_email);

    int indices[100], count = 0;

    for (int i = 0; i < addressbook->contact_count; i++) {
        // case-insensitive substring search in email
        if (strcasestr(addressbook->contact_details[i].Mail_ID, search_email)) {
            indices[count++] = i;
        }
    }

    if (count == 0) {
        printf(YELLOW"No contact found with email containing: %s\n"RESET, search_email);
        return -1;
    }

    print_contact_table();
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        print_contact(&addressbook->contact_details[idx], i + 1, idx);
    }
    printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);

    // This section is for edit/delete contacts
    if (!select_mode) { // false == 0 -> !0 = 1; so exits
        return -1; // display only
    }

    int choice;
    printf(CYAN"Enter your choice (1-%d): "RESET, count);
    scanf("%d", &choice);
    if (choice < 1 || choice > count) { // Checking for invalid choice
        printf(RED"Invalid choice.\n"RESET);
        return -1;
    }
    return indices[choice - 1]; // returns index value to idx in edit/delete contacts function
}

/* Validation Functions */

/* Name Validation and Auto-Correction */
bool validate_name(char *name) {
    // Only alphabets and spaces allowed
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha((unsigned char)name[i]) && !isspace((unsigned char)name[i])) {
            printf(RED"Invalid Name: Name should only contain alphabets and spaces (no numbers or special characters).\n"RESET);
            return false;
        }
    }

    // Convert to Title Case
    int capitalize = 1;
    for (int i = 0; name[i] != '\0'; i++) {
        if (isspace((unsigned char)name[i])) {
            capitalize = 1;
        } else if (capitalize && isalpha((unsigned char)name[i])) {
            name[i] = toupper((unsigned char)name[i]);
            capitalize = 0;
        } else {
            name[i] = tolower((unsigned char)name[i]);
        }
    }

    return true;
}

/* Phone Number Validation and Auto-Correction */
bool validate_phone(AddressBook *addressbook, char *phone) {
    
    // Remove spaces
    int j = 0;
    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isspace((unsigned char)phone[i])) {
            phone[j++] = phone[i];
        }
    }
    phone[j] = '\0';

    // 10 Digit check
    int len = strlen(phone);
    if (len != 10) {
        printf(RED"Invalid Phone: Phone number must be exactly 10 digits.\n"RESET);
        return false;
    }

    // Digit only check
    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)phone[i])) { 
            printf(RED"Invalid Phone: Phone number must contain only digits.\n"RESET);
            return false;
        }
    }

    // Valid first digit check
    if (phone[0] < '6' || phone[0] > '9') {
        printf(RED"Invalid Phone: Phone number must start with 6, 7, 8, or 9.\n"RESET);
        return false;
    }

    // Check duplicates
    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(addressbook->contact_details[i].Mobile_number, phone) == 0) {
            printf(YELLOW"Warning: This phone number already exists.\n"RESET);
            return false;
        }
    }

    return true;
}

/* Email ID Validation and Auto-Correction */
bool validate_email(AddressBook *addressbook, char *email) {
    // Remove spaces and convert to lowercase
    int j = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (!isspace((unsigned char)email[i])) {
            email[j++] = tolower((unsigned char)email[i]);
        }
    }
    email[j] = '\0';
    
    // Check if email begins with a digit or invalid character
    if (j > 0 && (!isalpha((unsigned char)email[0]) && !isdigit((unsigned char)email[0]))) {
        printf(RED"Invalid Email: Email should not begin with special character.\n"RESET);
        return false;
    }
    
    // Check for @ and .com and presence of domain
    char *at = strchr(email, '@');
    int len = strlen(email);

    if (!at || at == email) { // check for @ and if it's at the beginning
        printf(RED"Invalid Email: Email must contain '@' and have characters before it.\n"RESET);
        return false;
    }

    if (len < 5 || strcmp(email + len - 4, ".com") != 0) { // check for .com
        printf(RED"Invalid Email: Email must end with '.com'.\n"RESET);
        return false;
    }

    if (at[1] == '.' || at > email + len - 5) { // check for domain
        printf(RED"Invalid Email: Must have a valid domain name between '@' and '.com'.\n"RESET);
        return false;
    }

    // Check for invalid characters in the local part (before @)
    for (char *c = email; c < at; c++) {
        if (!isalnum((unsigned char)*c) && *c != '.' && *c != '_' && *c != '-') {
            printf(RED"Invalid Email: Local part contains invalid characters.\n"RESET);
            return false;
        }
    }

    // Check for invalid characters in the domain part (after @)
    for (char *c = at + 1; c < email + len; c++) {
        if (!isalnum((unsigned char)*c) && *c != '.' && *c != '-') {
            printf(RED"Invalid Email: Domain part contains invalid characters.\n"RESET);
            return false;
        }
    }
    
    // Check for consecutive dots or multiple ".com"
    if (strstr(email, "..")) {
        printf(RED"Invalid Email: Email cannot contain consecutive dots.\n"RESET);
        return false;
    }

    // Check for ".com" should appear only at the end
    char *dotcom = strstr(email, ".com");
    if (dotcom && dotcom != email + len - 4) {
        printf(RED"Invalid Email: Email must not contain multiple '.com'.\n"RESET);
        return false;
    }

    // Check duplicates
    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0) {
            printf(YELLOW"Warning: This email already exists.\n"RESET);
            return false;
        }
    }

    return true;
}

/* Contact Sort */
void sort_contacts(AddressBook *addressbook) {
    for (int i = 0; i < addressbook->contact_count - 1; i++) {
        for (int j = i + 1; j < addressbook->contact_count; j++) {
            if (strcasecmp(addressbook->contact_details[i].Name,
                           addressbook->contact_details[j].Name) > 0) {
                Contacts temp = addressbook->contact_details[i];
                addressbook->contact_details[i] = addressbook->contact_details[j];
                addressbook->contact_details[j] = temp;
            }
        }
    }
}

/* -- Contacts Printing in Table Format -- */
/* table header */
void print_contact_table() {
    printf(BLUE"\n------------------------------------------------------------------------------------------------\n"RESET);
    printf(BLUE BOLD"| %-6s | %-6s | %-20s | %-13s | %-35s |\n"RESET,
           "S.No.", "C. No.", "Name", "Mobile Number", "E-Mail ID");
    printf(BLUE"------------------------------------------------------------------------------------------------\n"RESET);
}

/* printing contacts */
void print_contact(Contacts *c, int serial, int index) {
    printf(BLUE"| "RESET "%-6d" BLUE" | "RESET "%-6d" BLUE" | "RESET "%-20s" BLUE" | " RESET "%-13s" BLUE" | " RESET "%-35s" BLUE" |\n"RESET,
           serial, index + 1, c->Name, c->Mobile_number, c->Mail_ID);
}