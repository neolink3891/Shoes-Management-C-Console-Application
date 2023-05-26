# SHOES MANAGEMENT SYSTEM - CONSOLE BASED C APPLICATION

This is a Console Based Application writen in C for an University final project Assigment.

## Purpose

This application keeps track of Shoes being rented in a bowling bussiness in a daily basis. Shoes are categorized in SMALL, MEDIUM, and LARGE size, each pair of shoes are identified by an Asset Tag Number as follow: 1XXX for Small size, 2XXX for Medium size, and 3XXX for Large size. Once a pair of shoes is rented, it will be marked as LOST if its not returned the same day, and it should present information about how many pair of shoes are Available, Rented, and Lost, this information needs to be presented by category and show the Asset Number associated. It also needs to show which category its the one that have most and least amount of Lost Shoes.

The application presents a home menu with the following options:
1 - Rent Shoes.
2 - Return Shoes.
3 - View Reports.
   3.1 - Available Assets per Category.
   3.2 - Rented Assets per Category.
   3.3 - Lost Assets per Category.
4 - Statistics.
5 - Exit.

## Data Persistance 

This application uses a text file to storage information, the format is:

```bash
DATA STORAGE FILE
version:1.0.0
//CATEGORY|PREFIX|CURRENT|TOTAL|RENTED|LOST|AVAILABLE
//ASSET|STATUS|CLIENT|DATE
**INFORMATION
SMALL|1|31|30|0|0|30
MEDIUM|2|21|20|0|1|19
LARGE|3|26|25|1|0|24
**DATA-S
1001|A|XXXXXXXXXXXXXXXXXXXXXXXXX|XXXXXXXXXX|||
**DATA-M
2001|A|XXXXXXXXXXXXXXXXXXXXXXXXX|XXXXXXXXXX|||
**DATA-L
3001|A|XXXXXXXXXXXXXXXXXXXXXXXXX|XXXXXXXXXX|||
```

### **INFORMATION Section
Holds counters that simplied calculations, this counters are updated anytime data changes.

### **DATA-S/M/L Sections
Each row in this sections represents an Asset, separated by | symbos, this lines are converted to Array objects within the program.

## SWITCHING AN ASSET TO LOST STATE

Everytime that the application starts it runs a verification when data from the file is loaded, if the date of the rental is different to the current date it changes the status from R to L and updates the counters.

## AUTOGENERATION OF DATA.TXT FILE

Everytime that the application starts it verifies that the file data.txt exists in data folder, if not, it will create an empty one.