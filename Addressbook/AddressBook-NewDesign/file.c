#include <stdio.h>
#include "file.h"
#include "contact.h"

// Save contacts to file and exit
void saveAndexit(AddressBook *addressBook)
{
    // Open file in write mode
    FILE *fp = fopen("contacts.txt", "w");
    // Check if file opened successfully
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
 // Write contacts to file
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp); // file close
    printf("Contacts saved successfully ✔️✔️\n");
}
// Load contacts from file into address book
void loadContactsFromFile(AddressBook *addressBook)
{
     // Open file in read mode
    FILE *fp = fopen("contacts.txt", "r");
    // If file doesn't exist or can't be opened, exit function
    if(fp == NULL)
        return;  // File not found or error, do nothing
    // Read contacts from file until end (EOF = end)
    while(fscanf(fp, " %[^,],%[^,],%[^\n]\n",
        addressBook->contacts[addressBook->contactCount].name,
        addressBook->contacts[addressBook->contactCount].phone,
        addressBook->contacts[addressBook->contactCount].email) != EOF)
    {
        // Increment contact count for each successful read
        addressBook->contactCount++;
    }
    // Close file after reading
    fclose(fp);
}