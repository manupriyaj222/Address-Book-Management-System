#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount=0;
    loadContactsFromFile(addressBook); // Load contacts from file

}
// Sort contacts in ascending order by name
void sortContacts(AddressBook *addressBook)
{
    for(int i = 0; i < addressBook->contactCount - 1; i++)   // Outer loop for each contact
    {
        for(int j = i + 1; j < addressBook->contactCount; j++)  // Inner loop to compare with remaining contacts
        {
            if(strcmp(addressBook->contacts[i].name,
                      addressBook->contacts[j].name) > 0)   // Check if current contact name is greater than next one
            {
                // Swap contacts if they are in wrong order
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}
// Display all contacts in the address book
void listContacts(AddressBook *addressBook) 
{
    if(addressBook->contactCount ==0)
    {
        printf("----------------------------------------------------------\n");
        printf("No contacts Available 📵 \n");   // Display message when no contacts are available
        printf("----------------------------------------------------------\n");
        return ;
    }
    sortContacts(addressBook); // Sort contacts before listing
    int count=1;
   printf("----------------------------------------------------------\n");
   printf("                     Contact List               \n");
   printf("----------------------------------------------------------\n");
   printf("sl.no      Name           Phone               Email-Id\n");
   printf("----------------------------------------------------------\n");

   for(int i=0 ;i< addressBook->contactCount; i++)
   {
    // Print contact details
    printf("\n%d        %5s           %5s         %5s" ,count++,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
   
   }
   printf("\n");
   printf("----------------------------------------------------------\n");
   
}
// Save contacts to file and exit the program
void saveAndExit(AddressBook *addressBook) 
{
    saveAndexit(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
// Validate if a name contains only letters, spaces, and dots
int validate_name(char *name)
{
    int i=0;
   while(name[i]!='\0')
    {
        // Check if character is invalid
        if(!((name[i]>='A' && name[i]<='Z')  ||
        (name[i]>='a' && name[i]<='z') || 
        name[i]==' ' || name[i]=='.'))
        {
        return 0;  // Return 0 if invalid character found
        }
        i++; // Move to next character
    }
    return 1; // Return 1 if name is valid
}
// Validate if a phone number contains exactly 10 digits
int validate_phone(char*phone)
{
    int i=0; // Initialize index
    int len =10; // Expected length of phone number
    while(phone[i]!='\0')
    {
         // Check if character is not a digit or length is less than expected
        if(!(phone[i]>='0'&& phone[i]<='9')||
           strlen(phone)<len)
           {
            return 0; // Return 0 if phone number is invalid
           }
           i++;
    }
    return 1; // Return 1 if phone number is valid
}
// Check if a phone number already exists in the address book
int duplicate_phone(AddressBook*addressBook,char*phone)
{
for(int i=0;i<addressBook->contactCount;i++)
{
    // Check if phone number matches
    if((strcmp(addressBook->contacts[i].phone,phone) == 0))
    {
        printf("\nInvalid number is existing!🚫\n");  // Print error message if duplicate found
        return 1; // not unique
    }
}
return 0; // unique
}
// Validate an email address
int validate_email(char*email) 
{   int i=0,dot=0,at=0;
    int len=strlen(email); // Get email length
    int at_pos=-1,dot_pos=-1; // Positions of '@' and '.'
    while(email[i]!='\0')  // Loop through each character
    {
        // Check if character is invalid
        if(!((email[i]>='a'&&email[i]<='z')||
              (email[i]>='0'&&email[i]<='9')||
               email[i]=='@'|| email[i]=='.' ||
                email[i]=='-' || email[i]=='_'))
                {
                printf("Invalid email ‼️");
                return 0; // invalid
               }
               if(email[i]=='@') // Track '@' symbol
               {
                at++;
                at_pos = i;  // Store '@' position
               }
               if(email[i]=='.')   // Track '.' symbol
               {
                dot++;
                dot_pos=i;  // Store '.' position
               }
               i++; // Move to next character
    }
    // check for string before '@' , between '@' and '.' , and after '.'
        return (at==1 && dot >= 1 && at_pos > 0 && dot_pos > at_pos + 1 && dot_pos < len -1);
}
// Check if a email id already exists in the address book
int duplicate_email(AddressBook*addressBook,char*email)
{
for(int i=0;i<addressBook->contactCount;i++)
{
    if((strcmp(addressBook->contacts[i].email,email) == 0))
    {
        printf("\nInvalid email is existing!🚫\n");
        return 1; // not unique
    }
}
return 0; // unique
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char name[20];
    int valid;

    while(1) //get valid name
    {
        printf("Enter the name : ");
        scanf(" %[^\n]",name);
        valid = validate_name(name);
        if(valid == 1)// valid
            break;
    }

    char phone[11];
    while(1)
    {
        printf("Enter the phone number : ");
        scanf(" %[^\n]",phone);
        if(validate_phone(phone)&& !duplicate_phone(addressBook,phone))//valid
            break;
    }

    char email[30];
    while(1)
    {
        printf("Enter the Email id : ");
        scanf(" %[^\n]",email);
        if(validate_email(email) && !duplicate_email(addressBook,email)) //valid
        break;
    }
    //add contact to adressbook
    Contact *c= &addressBook->contacts[addressBook->contactCount];
     strcpy(addressBook->contacts[addressBook->contactCount].name,name); // Copy name
     strcpy(addressBook->contacts[addressBook->contactCount].phone,phone); // Copy number
     strcpy(addressBook->contacts[addressBook->contactCount].email,email); // Copy mail
  addressBook->contactCount++; //increment contact count
}
// Convert a string to lowercase
void tolowercase(char *str)
{
    for(int i=0 ; str[i] ; i++)   // Loop through each character
    {
        // Convert to lowercase
        str[i]=tolower(str[i]);
    }
}
// Search contacts by name in the address book
void search_by_name(AddressBook *addressBook)
{
    char name[20];
    printf("Enter name to search :");
    scanf(" %[^\n]",name);
    
    
    tolowercase(name);  // Convert to lowercase for comparison

    int found=0,count=1,i;
         printf("sl.no    Name        Phone              Email-Id\n");
         printf("----------------------------------------------------------\n");
    for(i=0;i<addressBook->contactCount;i++)
    {  
        char contactName[50]; // Store contact name
        strcpy(contactName,addressBook->contacts[i].name);
        tolowercase(contactName); // Convert to lowercase for comparison

        if(strcmp(contactName,name)==0)
        {
        printf("\n%d        %5s           %5s         %5s\n" ,count++,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        found = 1;
        }
    }
    printf("----------------------------------------------------------\n");
    if(found == 0)
    {
        // Display message if not found
        printf("❌❌---Contact not found---❌❌\n");
    }
}
// Search contacts by phone number in the address book
void search_by_phone(AddressBook *addressBook)
{
    char phone[20];
    printf("Enter phone to search :");
    scanf(" %[^\n]",phone);
    int found=0,count=1;

         printf("sl.no      Name          Phone               Email-Id\n");
         printf("----------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {  
        if(strcmp(addressBook->contacts[i].phone,phone)==0)
        {
        printf("\n%d        %5s           %5s         %5s\n" ,count++,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        found = 1;
        }
    }  
    printf("----------------------------------------------------------\n");
    if(found == 0)
    {
        printf("❌❌---Contact not found---❌❌\n");
    }
}
// Search contacts by email in the address book
void search_by_email(AddressBook *addressBook)
{
    char email[20];
    printf("Enter email to search :");
    scanf(" %[^\n]",email);
    int found=0,count=1;

         printf("sl.no      Name          Phone               Email-Id\n");
         printf("----------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {  
        if(strcmp(addressBook->contacts[i].email,email)==0)
        {
        printf("\n%d        %5s           %5s         %5s\n" ,count++,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        found = 1;
        }
    }  
    printf("----------------------------------------------------------\n");
    if(found == 0)
    {
        printf("❌❌---Contact not found---❌❌\n"); //display if not found
    }
}

void searchContact(AddressBook *addressBook) 
{
    int by;
   while(1)
   {
      printf("\nSearch by:\n");
      printf("1. Name\n");
      printf("2. Phone\n");
      printf("3. Email\n");
      printf("4. Back to main menu\n");
      printf("Enter your choice:");
      scanf("%d",&by);

      switch(by)
      {
         case 1:
         search_by_name(addressBook);
         break;

         case 2:
         search_by_phone(addressBook);
         break;

         case 3:
         search_by_email(addressBook);
         break;

         case 4:
         printf("Returning To Main Menu....\n");
         return ;
      default:
         printf("invalid choice ");
      }
  } 
}
// Edit a contact by name in the address book
void edit_by_name(AddressBook *addressBook) {
    char name[20];
    printf("Select name to be edited: ");
    scanf(" %[^\n]", name);
    tolowercase(name); // Convert to lowercase for comparison

    int found = 0, count = 1, index[10], matchCount = 0;
    
    // Find matches and store indices
    for (int i = 0; i < addressBook->contactCount; i++) {
        char contactName[50];
        strcpy(contactName, addressBook->contacts[i].name);
        tolowercase(contactName);
        if (strcmp(contactName, name) == 0) {
            index[matchCount++] = i; // store index of match
            found = 1;
        }
    }

    if (!found) {
        printf("Contact not found\n");
        return;
    }

    // Show matches if more than one
    if (matchCount > 1) {
        printf("Multiple matches found:\n");
        printf("sl.no Name Phone Email-Id\n");
        printf("----------------------------------------------------------\n");
        for (int i = 0; i < matchCount; i++) {
            int idx = index[i];
            printf("%d %s %s %s\n", i + 1, addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
        }
        printf("----------------------------------------------------------\n");

        int choice;
        printf("Enter sl no of the contact to edit: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > matchCount) {
            printf("Invalid choice\n");
            return;
        }
        int editIndex = index[choice - 1];

        // Edit the selected contact
        char new_name[20];
        printf("Enter new name: ");
        scanf(" %[^\n]", new_name);
        if (validate_name(new_name)) {
            strcpy(addressBook->contacts[editIndex].name, new_name);
            printf("Contact updated successfully!\n");
        } else {
            printf("Invalid name\n");
        }
    } else {
        // Only one match, edit directly
        int editIndex = index[0];
        char new_name[20];
        printf("Edit name for: %s? Enter new name: ", addressBook->contacts[editIndex].name);
        scanf(" %[^\n]", new_name);
        if (validate_name(new_name)) {
            strcpy(addressBook->contacts[editIndex].name, new_name);
            printf("Contact updated successfully ✔️\n");
        } else {
            printf("Invalid name\n");
        }
    }
}
   // Edit a contact by phone number in the address book
 void edit_by_phone(AddressBook *addressBook)
 {
    char phone[20];
     printf("Enter phone to search :");
     scanf(" %19[^\n]",phone); // Limit input to 19 chars
     int found=0,count=1;

       printf("sl.no      Name          Phone               Email-Id\n");
        printf("----------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {  
         if(strcmp(addressBook->contacts[i].phone,phone)==0) // Match phone number
       {
         printf("\n%d        %5s           %5s         %5s\n" ,count++,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
         
          char new_phone[20]; // New phone number
           printf("\nEnter new_phone : ");
           scanf(" %19[^\n]",new_phone);
            // Validate and update phone
          if(validate_phone(new_phone) && !duplicate_phone(addressBook,new_phone)) 
             {
          strcpy(addressBook->contacts[i].phone,new_phone);
                   printf("\n---Contact updated succesfully✔️✔️-\n");
                   found=1;
            }
       }
         
    }
    printf("----------------------------------------------------------\n");
        if(found ==0 )  // Display message if not found
        {
        printf("Contact not found  ❌\n");
        printf("invalid try again ‼️\n");
         }
            
 }
 // Edit a contact by email in the address book
  void edit_by_email(AddressBook *addressBook)
 {
    char email[20]; // Email to search (increased size for typical email length)
     printf("Enter email to search :");
     scanf(" %19[^\n]",email); // Limit input, adjusted size
     int found=0,count=1;

        printf("sl.no      Name          Phone               Email-Id\n");
        printf("----------------------------------------------------------\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {  
         if(strcmp(addressBook->contacts[i].email,email)==0) //emial match
       {
         // Print matching contact
         printf("\n%d        %5s           %5s         %5s\n" ,count++,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
         
          char new_email[20];
           printf("\nEnter new_email : ");
           scanf(" %19[^\n]",new_email);
            // Validate and update email
          if(validate_email(new_email) && !duplicate_email(addressBook,email)) 
             {
          strcpy(addressBook->contacts[i].email,new_email);
                   printf("\n---Contact updated succesfully✔️✔️\n");
                   found=1; // Mark as found
            }
       }
    }
    printf("----------------------------------------------------------\n");
     if(found==0)
         {
        printf("Contact not found  ❌\n");
        printf("invalid try again ‼️\n");
         }
 }
void editContact(AddressBook *addressBook)
{
	int field;
    if(addressBook->contactCount==0)
    {
        printf("No contacts available\n");
        return ;
    }
    while(1)
    {
      printf("\nSelect which field has to be edited:\n");
      printf("1. Name\n");
      printf("2. Phone\n");
      printf("3. Email\n");
      printf("4. Back to main menu\n");
      printf("Enter your choice:");
      scanf("%d",&field);

      switch(field)
      {
         case 1:
         edit_by_name(addressBook);
         break;

         case 2:
         edit_by_phone(addressBook);
          break;

         case 3:
          edit_by_email(addressBook);
          break;

         case 4:
         printf("Returning To Main Menu....\n");
         return ;
      default:
         printf("invalid choice ");
      }
    }   
}
void delete_by_name(AddressBook *addressBook) {
    char name[50];
    printf("Enter the name of contact to delete: ");
    scanf(" %[^\n]", name);
    tolowercase(name);

    int found = 0, count = 1, index[10], matchCount = 0;

    // Find matches and store indices
    for (int i = 0; i < addressBook->contactCount; i++) {
        char contactName[50];
        strcpy(contactName, addressBook->contacts[i].name);
        tolowercase(contactName);
        if (strcmp(contactName, name) == 0) {
            index[matchCount++] = i; // store index of match
            found = 1;
        }
    }

    if (!found) {
        printf("Contact not found ❌\n");
        return;
    }

    // Show matches if more than one
    if (matchCount > 1) {
        printf("Multiple matches found:\n");
       printf("sl.no      Name          Phone               Email-Id\n");
        printf("----------------------------------------------------------\n");
        for (int i = 0; i < matchCount; i++) {
            int idx = index[i];
            printf("%d %s %s %s\n", i + 1, addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
        }
        printf("----------------------------------------------------------\n");

        int choice;
        printf("Enter sl no of the contact to delete: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > matchCount) {
            printf("Invalid choice\n");
            return;
        }
        int delIndex = index[choice - 1];

        // Shift contacts down
        memmove(&addressBook->contacts[delIndex], &addressBook->contacts[delIndex + 1],
                (addressBook->contactCount - delIndex - 1) * sizeof(Contact));
        addressBook->contactCount--;
        printf("Contact deleted successfully ✔️\n");
    } else {
        // Only one match, delete directly
        int delIndex = index[0];
        memmove(&addressBook->contacts[delIndex], &addressBook->contacts[delIndex + 1],
                (addressBook->contactCount - delIndex - 1) * sizeof(Contact));
        addressBook->contactCount--;
        printf("Contact deleted successfully ✔️\n");
    }
}
// Delete a contact by phone number from the address book
void delete_by_phone(AddressBook *addressBook)
{
char phone[50]; // Phone number to delete (adjusted size)
    printf("Enter the phone of contact to delete:");
    scanf(" %[^\n]",phone);

int index = -1;// Index of contact to delete
for(int i =0 ;i<addressBook->contactCount;i++)  // Find contact by phone
{
    if(strcmp(addressBook->contacts[i].phone,phone)==0)
    {
        index =i;// Store index
        break;
    }
}   
if(index == -1)  // Handle not found
{
    printf("Contact not found ❌\n");
    return ;
}
// Shift contacts to fill gap
for(int i = index ; i<addressBook->contactCount-1;i++)
{
    addressBook->contacts[i]=addressBook->contacts[i+1];
}
addressBook->contactCount--;  //Decrement count
printf("\nContact deleted successfully✔️✔️\n");
}
// Delete a contact by email from the address book
void delete_by_email(AddressBook *addressBook)
{
char email[50]; // Email to delete (adjusted size)
    printf("Enter the email of contact to delete:");
    scanf(" %[^\n]",email); //limit input

int index = -1; // Index of contact to delete
for(int i =0 ;i<addressBook->contactCount;i++) //find contact by email
{
    if(strcmp(addressBook->contacts[i].email,email)==0)
    {
        index =i; //store index
        break;
    }
}   
if(index == -1)  // Handle not found
{
    printf(" Invalid Contact not found ❌\n"); // Removed "Invalid"
    return ;
}
// Shift contacts to fill gap
for(int i = index ; i<addressBook->contactCount-1;i++)
{
    addressBook->contacts[i]=addressBook->contacts[i+1];
}
addressBook->contactCount--; //decrement count
printf("\nContact deleted successfully✔️✔️\n");
}
// Delete a contact from the address book
void deleteContact(AddressBook *addressBook)
{
    int choo; // Choice for deletion method
    if(addressBook->contactCount==0)
    {
        printf("No contacts available\n");
        return ;
    }
    while(1)
    {
      printf("\nSelect which field has to be deleted:\n");
      printf("1. Name\n");
      printf("2. Phone\n");
      printf("3. Email\n");
      printf("4. Back to main menu\n");
      printf("Enter your choice:");
      scanf("%d",&choo);
      switch(choo)
      {
         case 1:
         delete_by_name(addressBook);
         break;

         case 2:
         delete_by_phone(addressBook);
          break;

         case 3:
          delete_by_email(addressBook);
          break;

         case 4:
         printf("Returning To Main Menu....\n");
         return ;
      default:
         printf("invalid choice ");
      }
    }   
}
