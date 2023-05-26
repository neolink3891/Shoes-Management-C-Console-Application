#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100

char lines[MAX_LINES][MAX_LINE_LENGTH]; 
char line[MAX_LINE_LENGTH];
int line_count = 0;
char tmpline[MAX_LINE_LENGTH];
int readmode = 0;
FILE *fp;
char filename[20] = "data/data.txt";
int tmptots;
int len;
int small[5];
int medium[5];
int large[5];
char *sdata[30][4];
char *mdata[30][4];
char *ldata[30][4];
char *datarow[7];
int dri = 0;
int tmprow = 0;
int menu;
int submenu;
char r_anumber[4];
char r_fname[200];
char r_lname[200];
char r_fullname[300];
char r_date[10];

void printBanner();
void setupArrays();
void loadData();
void writeData();
void markAssetsAsLost();
void displayAvailableAssets();
void displayRentedAssets();
void displayLostAssets();
void findLeastAndMost();
void printGoodBye();
int findIn(char[], int);
int isAssetAvailable(char[], int);
int isAssetRented(char[], int);

int main() {
    printBanner();
    setupArrays();
    loadData();
    markAssetsAsLost();
    
    do {
        printf("\n********************************************************************************************************************************************************");
        printf("\nWhat do you want to do?\n");
        printf("1 - Rent a Shoe.\n");
        printf("2 - Return a Shoe.\n");
        printf("3 - View Reports.\n");
        printf("4 - Statictics.\n");
        printf("5 - Exit.\n");
        printf("\n");
        printf("[INPUT] Please, select an Option: ?>> ");
        scanf("%i", &menu);

        switch (menu) {
        case 1:
            printf("\n");
            printf("Selected Option: 1 - RENT A SHOE.\n");
            printf("Rental Details.\n");
            printf("[INPUT] Input Client Firstname and press ENTER: ?>> ");
            scanf("%s", r_fname);
            printf("[INPUT] Input Client Lastname and press ENTER: ?>> ");
            scanf("%s", r_lname);
            printf("[INPUT] Input Asset Number: ?>> ");
            scanf("%s", r_anumber);
            time_t d_date = time(NULL);
            struct tm tm = *localtime(&d_date);
            sprintf(r_date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            if(findIn(r_anumber, 1) == 1) {
                if(isAssetAvailable(r_anumber, 1) == 1) {
                    printf("[INFO] ASSET %s HAS BEEN SUCESSFULLY RENTED TO %s %s TODAY %s.\n\n", r_anumber, r_fname, r_lname, r_date);
                    writeData();
                } else {
                    printf("[WARNING] SORRY, ASSET %s IS NOT AVAILABLE FOR RENT. NO ACTION DONE.\n\n", r_anumber);
                }
            } else if(findIn(r_anumber, 2) == 1) {
                if(isAssetAvailable(r_anumber, 2) == 1) {
                    printf("[INFO] ASSET %s HAS BEEN SUCESSFULLY RENTED TO %s %s TODAY %s.\n\n", r_anumber, r_fname, r_lname, r_date);
                    writeData();
                } else {
                    printf("[WARNING] SORRY, ASSET %s IS NOT AVAILABLE FOR RENT. NO ACTION DONE.\n\n", r_anumber);
                }
            } else if(findIn(r_anumber, 3) == 1) {
                if(isAssetAvailable(r_anumber, 3) == 1) {
                    printf("[INFO] ASSET %s HAS BEEN SUCESSFULLY RENTED TO %s %s TODAY %s.\n\n", r_anumber, r_fname, r_lname, r_date);
                    writeData();
                } else {
                    printf("[WARNING] SORRY, ASSET %s IS NOT AVAILABLE FOR RENT. NO ACTION DONE.\n\n", r_anumber);
                }
            } else {
                printf("[WARNING] SORRY, ASSET %s COULD NOT BE FOUND. NO ACTION DONE.\n\n", r_anumber);
            }
            break;
        case 2:
            printf("\n");
            printf("[INPUT] Input Asset Number: ?>> ");
            scanf("%s", r_anumber);
            if(findIn(r_anumber, 1) == 1) {
                if(isAssetRented(r_anumber, 1) == 1) {
                    writeData();
                } else {
                    printf("[WARNING] SORRY, ASSET %s IS NOT AVAILABLE FOR RETURN. NO ACTION DONE.\n\n", r_anumber);
                }
            } else if(findIn(r_anumber, 2) == 1) {
                if(isAssetRented(r_anumber, 2) == 1) {
                    writeData();
                } else {
                    printf("[WARNING] SORRY, ASSET %s IS NOT AVAILABLE FOR RETURN. NO ACTION DONE.\n\n", r_anumber);
                }
            } else if(findIn(r_anumber, 3) == 1) {
                if(isAssetRented(r_anumber, 3) == 1) {
                    writeData();
                } else {
                    printf("[WARNING] SORRY, ASSET %s IS NOT AVAILABLE FOR RETURN. NO ACTION DONE.\n\n", r_anumber);
                }
            }  else {
                printf("[WARNING] SORRY, ASSET %s COULD NOT BE FOUND. NO ACTION DONE.\n\n", r_anumber);
            }
            break;
        case 3:
        printf("\n");
            printf("Type of Report\n");
            printf("1 - Available Assets per Category\n");
            printf("2 - Rented Assets per Category\n");
            printf("3 - Lost Assets per Category\n");
            printf("\n");
            printf("[INPUT] Please, Select a Report: ?>> ");
            scanf("%i", &submenu);

            switch(submenu) {
                case 1:
                    displayAvailableAssets();
                    loadData();
                    break;
                case 2:
                    displayRentedAssets();
                    loadData();
                    break;
                case 3:
                    displayLostAssets();
                    loadData();
                    break;
                default:
                    printf("[WARNING] SORRY, REPORT NOT FOUND, NO ACTION DONE.\n\n");
                    break;
            }
            
            break;
        case 4:
            findLeastAndMost();

            break;
        case 5:
            printGoodBye();
            break;
        default:
            printf("[WARNING] Invalid Option, please try again.\n");
            break;
        }
    } 
    while(menu != 5);

    return 0;
}

void displayAvailableAssets() {
    printf("\n...................[ DISPLAYING AVAILABLE ASSETS REPORT ]...................\n");
    printf("Availables in Category SMALL:\n");
    for(int r = 0; r < small[1]; r++) {
        if(strcmp("A", sdata[r][1]) == 0) {
            printf("* %s\n", sdata[r][0]);
        }
    }
    printf("Availables in Category MEDIUM:\n");
    for(int r = 0; r < medium[1]; r++) {
        if(strcmp("A", mdata[r][1]) == 0) {
            printf("* %s\n", mdata[r][0]);
        }
    }
    printf("Availables in Category LARGE:\n");
    for(int r = 0; r < large[1]; r++) {
        if(strcmp("A", ldata[r][1]) == 0) {
            printf("* %s\n", ldata[r][0]);
        }
    }
    tmptots = small[4] + medium[4] + large[4];
    printf("\nTOTAL AVAILABLE ASSETS: [%i] - SMALL: %i, MEDIUM: %i, LARGE: %i\n\n", tmptots, small[4], medium[4], large[4]);
    printf("\n............................................................................\n");
}

void displayRentedAssets() {
    printf("\n...................[ DISPLAYING RENTED ASSETS REPORT ]...................\n");
    printf("Rented in Category SMALL:\n");
    for(int r = 0; r < small[1]; r++) {
        if(strcmp("R", sdata[r][1]) == 0) {
            printf("* %s\n", sdata[r][0]);
        }
    }
    printf("Rented in Category MEDIUM:\n");
    for(int r = 0; r < medium[1]; r++) {
        if(strcmp("R", mdata[r][1]) == 0) {
            printf("* %s\n", mdata[r][0]);
        }
    }
    printf("Rented in Category LARGE:\n");
    for(int r = 0; r < large[1]; r++) {
        if(strcmp("R", ldata[r][1]) == 0) {
            printf("* %s\n", ldata[r][0]);
        }
    }
    tmptots = small[2] + medium[2] + large[2];
    printf("\nTOTAL RENTED ASSETS: [%i] - SMALL: %i, MEDIUM: %i, LARGE: %i\n\n", tmptots, small[2], medium[2], large[2]);
    printf("\n..........................................................................\n");
}

void displayLostAssets() {
    printf("\n...................[ DISPLAYING LOST ASSETS REPORT ]...................\n");
    printf("Lost in Category SMALL:\n");
    for(int r = 0; r < small[1]; r++) {
        if(strcmp("L", sdata[r][1]) == 0) {
            printf("* %s\n", sdata[r][0]);
        }
    }
    printf("Lost in Category MEDIUM:\n");
    for(int r = 0; r < medium[1]; r++) {
        if(strcmp("L", mdata[r][1]) == 0) {
            printf("* %s\n", mdata[r][0]);
        }
    }
    printf("Lost in Category LARGE:\n");
    for(int r = 0; r < large[1]; r++) {
        if(strcmp("L", ldata[r][1]) == 0) {
            printf("* %s\n", ldata[r][0]);
        }
    }
    tmptots = small[3] + medium[3] + large[3];
    printf("\nTOTAL LOST ASSETS: [%i] - SMALL: %i, MEDIUM: %i, LARGE: %i\n\n", tmptots, small[3], medium[3], large[3]);
    printf("\n........................................................................\n");
}

void findLeastAndMost() {
    tmptots = small[3] + medium[3] + large[3];
    printf("\n...................[ DISPLAYING STATISTICS REPORT ]...................\n");
    printf("\nMOST LIKELY CATEGORY TO BE LOST:\n");
    if(tmptots > 0) {
        if(small[3] >= medium[3]) {
            if(small[3] >= large[3]) {
                printf("* SMALL - [%i] Units Lost\n\n", small[3]);
            } else {
                printf("* LARGE - [%i] Units Lost\n\n", large[3]);
            }
        } else {
            if(medium[3] >= large[3]) {
                printf("* MEDIUM - [%i] Units Lost\n\n", medium[3]);
            } else {
                printf("* LARGE - [%i] Units Lost\n\n", large[3]);
            }
        }
    } else {
        printf("\n[INFO] NOT ENOUGH DATA TO CALCULATE\n\n");
    }
    printf("\nLEAST LIKELY CATEGORY TO BE LOST:\n");
    if(tmptots > 0) {
        if(small[3] <= medium[3]) {
            if(small[3] <= large[3]) {
                printf("* SMALL - [%i] Units Lost\n\n", small[3]);
            } else {
                printf("* LARGE - [%i] Units Lost\n\n", large[3]);
            }
        } else {
            if(medium[3] <= large[3]) {
                printf("* MEDIUM - [%i] Units Lost\n\n", medium[3]);
            } else {
                printf("* LARGE - [%i] Units Lost\n\n", large[3]);
            }
        }
    } else {
        printf("\n[INFO] NOT ENOUGH DATA TO CALCULATE\n\n");
    }
    printf("\nLOST ASSET LIST:\n");
    if(tmptots > 0) {
        for(int r = 0; r < small[1]; r++) {
            if(strcmp("L", sdata[r][1]) == 0) {
                printf("- ASSET [%s] RENTED TO [%s] ON [%s]\n", sdata[r][0], sdata[r][2], sdata[r][3]);
            }
        }
        for(int r = 0; r < medium[1]; r++) {
            if(strcmp("L", mdata[r][1]) == 0) {
                printf("- ASSET [%s] RENTED TO [%s] ON [%s]\n", mdata[r][0], mdata[r][2], mdata[r][3]);
            }
        }
        for(int r = 0; r < large[1]; r++) {
            if(strcmp("L", ldata[r][1]) == 0) {
                printf("- ASSET [%s] RENTED TO [%s] ON [%s]\n", ldata[r][0], ldata[r][2], ldata[r][3]);
            }
        }
    } else {
        printf("\n[INFO] NO ASSET HAS BEEN MARKED AS LOST, YET\n\n");
    }
    
    printf("\n\n");
}

void markAssetsAsLost() {
    time_t d_date = time(NULL);
    struct tm tm = *localtime(&d_date);
    sprintf(r_date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    for (int s = 0; s < small[1]; s++) {
        if(strcmp(r_date, sdata[s][3]) == 1) {
            if(strcmp("R", sdata[s][1]) == 0) {
                strcpy(sdata[s][1], "L");
                small[2] = small[2] - 1;
                small[3] = small[3] + 1;
            }
        }
    }
    for (int m = 0; m < medium[1]; m++) {
        if(strcmp(r_date, mdata[m][3]) == 1) {
            if(strcmp("R", mdata[m][1]) == 0) {
                strcpy(mdata[m][1], "L");
                medium[2] = medium[2] - 1;
                medium[3] = medium[3] + 1;
            }
        }
    }
    for (int l = 0; l < large[1]; l++) {
        if(strcmp(r_date, ldata[l][3]) == 1) {
            if(strcmp("R", ldata[l][1]) == 0) {
                strcpy(ldata[l][1], "L");
                large[2] = large[2] - 1;
                large[3] = large[3] + 1;
            }
        }
    }
    writeData();
    printf("[INFO] Data sync and up to date!\n");
}

int isAssetRented(char asset[], int source) {
    switch (source) {
        case 1:
            for (int r = 0; r < small[1]; r++) {
                if (strcmp(asset, sdata[r][0]) == 0) {
                    if(strcmp("L", sdata[r][1]) == 0) {
                        printf("[WARNING] Asset %s its LOST and can not be marked as Returned.\n", asset);

                        return 0;
                    } else if(strcmp("R", sdata[r][1]) == 0) {
                        small[2] = small[2] - 1;
                        small[4] = small[4] + 1;
                        strcpy(sdata[r][1], "A");
                        strcpy(sdata[r][2], "XXXXXXXXXXXXXXXXXXXXXXXXX");
                        strcpy(sdata[r][3], "XXXXXXXXXX");
                        printf("[INFO] Asset %s has been returned from Rent Status.\n", asset);

                        return 1;
                    } else {
                        return 0;
                    }
                } 
            }
            break;
        case 2:
            for (int r = 0; r < medium[1]; r++) {
                if (strcmp(asset, mdata[r][0]) == 0) {
                    if(strcmp("L", mdata[r][1]) == 0) {
                        printf("[WARNING] Asset %s its LOST and can not be marked as Returned.\n", asset);

                        return 0;
                    } else if(strcmp("R", mdata[r][1]) == 0) {
                        medium[2] = medium[2] - 1;
                        medium[4] = medium[4] + 1;
                        strcpy(mdata[r][1], "A");
                        strcpy(mdata[r][2], "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                        strcpy(mdata[r][3], "XXXXXXXXXX");
                        printf("[INFO] Asset %s has been returned from Rent Status.\n", asset);

                        return 1;
                    } else {
                        return 0;
                    }
                } 
            }
            break;
        case 3:
            for (int r = 0; r < large[1]; r++) {
                if (strcmp(asset, ldata[r][0]) == 0) {
                    if(strcmp("L", ldata[r][1]) == 0) {
                        printf("[WARNING] Asset %s its LOST and can not be marked as Returned.\n", asset);

                        return 0;
                    } else if(strcmp("R", ldata[r][1]) == 0) {
                        large[2] = large[2] - 1;
                        large[4] = large[4] + 1;
                        strcpy(ldata[r][1], "A");
                        strcpy(ldata[r][2], "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                        strcpy(ldata[r][3], "XXXXXXXXXX");
                        printf("[INFO] Asset %s has been returned from Rent Status.\n", asset);

                        return 1;
                    } else {
                        return 0;
                    }
                } 
            }
            break;
        default:
            break;
    }
    return 0;
}

int isAssetAvailable(char asset[], int source) {
    switch (source) {
        case 1:
            for (int r = 0; r < small[1]; r++) {
                if (strcmp(asset, sdata[r][0]) == 0) {
                    if(strcmp("A", sdata[r][1]) == 0) {
                        sprintf(r_fullname, "%s %s", r_fname, r_lname);
                        strcpy(sdata[r][1], "R");
                        strcpy(sdata[r][2], r_fullname);
                        strcpy(sdata[r][3], r_date); 
                        small[2] = small[2] + 1;
                        small[4] = small[4] - 1;
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            break;
        case 2:
            for (int r = 0; r < medium[1]; r++) {
                if (strcmp(asset, mdata[r][0]) == 0) {
                    if(strcmp("A", mdata[r][1]) == 0) {
                        sprintf(r_fullname, "%s %s", r_fname, r_lname);
                        strcpy(mdata[r][1], "R");
                        strcpy(mdata[r][2], r_fullname);
                        strcpy(mdata[r][3], r_date); 
                        medium[2] = medium[2] + 1;
                        medium[4] = medium[4] - 1;
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            break;
        case 3:
            for (int r = 0; r < large[1]; r++) {
                if (strcmp(asset, ldata[r][0]) == 0) {
                    if(strcmp("A", ldata[r][1]) == 0) {
                        sprintf(r_fullname, "%s %s", r_fname, r_lname);
                        strcpy(ldata[r][1], "R");
                        strcpy(ldata[r][2], r_fullname);
                        strcpy(ldata[r][3], r_date); 
                        large[2] = large[2] + 1;
                        large[4] = large[4] - 1;
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            break;
        default:
            break;
    }

    return 0;
}

int findIn(char asset[], int source) {
    switch (source) {
        case 1:
            for (int r = 0; r < small[1]; r++) {
                if (strcmp(asset, sdata[r][0]) == 0) {
                    return 1;
                }
            }
            break;
        case 2:
            for (int r = 0; r < medium[1]; r++) {
                if (strcmp(asset, mdata[r][0]) == 0) {
                    return 1;
                }
            }
            break;
        case 3:
            for (int r = 0; r < large[1]; r++) {
                if (strcmp(asset, ldata[r][0]) == 0) {
                    return 1;
                }
            }
            break;
        default:
            break;
    }

    return 0;
}

void writeData() {
    printf("[SYSTEM] SAVING DATA...\n");
    if(access(filename, F_OK) == 0) {
        fp = fopen(filename, "w");
        fprintf(fp, "DATA STORAGE FILE\n");
        fprintf(fp, "version:1.0.0\n");
        fprintf(fp, "//CATEGORY|PREFIX|CURRENT|TOTAL|RENTED|LOST|AVAILABLE\n");
        fprintf(fp, "//ASSET|STATUS|CLIENT|DATE\n");
        fprintf(fp, "**INFORMATION\n");
        fprintf(fp, "SMALL|1|%i|%i|%i|%i|%i\n", small[0], small[1], small[2], small[3], small[4]);
        fprintf(fp, "MEDIUM|2|%i|%i|%i|%i|%i\n", medium[0], medium[1], medium[2], medium[3], medium[4]);
        fprintf(fp, "LARGE|3|%i|%i|%i|%i|%i\n", large[0], large[1], large[2], large[3], large[4]);
        fprintf(fp, "**DATA-S\n");

        for (int r = 0; r < small[1]; r++) {
            fprintf(fp, "%s|%s|%s|%s|||\n", sdata[r][0], sdata[r][1], sdata[r][2], sdata[r][3]);
        }
        fprintf(fp, "**DATA-M\n");

        for (int r = 0; r < medium[1]; r++) {
            fprintf(fp, "%s|%s|%s|%s|||\n", mdata[r][0], mdata[r][1], mdata[r][2], mdata[r][3]);
        }
        fprintf(fp, "**DATA-L\n");

        for (int r = 0; r < large[1]; r++) {
            fprintf(fp, "%s|%s|%s|%s|||\n", ldata[r][0], ldata[r][1], ldata[r][2], ldata[r][3]);
        }
        fclose(fp);
        printf("[SYSTEM] DATA SAVED SUCESSFULLY!\n");
    } else {
        printf("[WARNING] A PROBLEM HAS OCURRED WHILE SAVING DATA LOCALLY.\n");
    }
}

void loadData() {
    printf("[SYSTEM] Checking Data File....\n");
    if (access(filename, F_OK) != 0) {
        printf("[SYSTEM] Data File not found. Initializing...\n");
        fp = fopen(filename, "w");
        fprintf(fp, "DATA STORAGE FILE\n");
        fprintf(fp, "version:1.0.0\n");
        fprintf(fp, "**INFORMATION\n");
        fprintf(fp, "SMALL|1|31|30|0|0|30\n");
        fprintf(fp, "MEDIUM|2|21|20|0|0|20\n");
        fprintf(fp, "LARGE|3|26|25|0|0|25\n");
        fprintf(fp, "**DATA-S\n");
        for(int r = 0; r < 30; r++) {
            fprintf(fp, "%i|A|XXXXXXXXXXXXXXXXXXXXXXXXX|XXXXXXXXXX|||\n", (r + 1001));
        }
        fprintf(fp, "**DATA-M\n");
        for(int r = 0; r < 20; r++) {
            fprintf(fp, "%i|A|XXXXXXXXXXXXXXXXXXXXXXXXX|XXXXXXXXXX|||\n", (r + 2001));
        }
        fprintf(fp, "**DATA-L\n");
        for(int r = 0; r < 25; r++) {
            fprintf(fp, "%i|A|XXXXXXXXXXXXXXXXXXXXXXXXX|XXXXXXXXXX|||\n", (r + 3001));
        }
        fclose(fp);
        printf("[SYSTEM] Data File has been initialized.\n");
    } else {
        printf("[SYSTEM] Data File found, loading data...\n");
    }
    printf("[SYSTEM] Done loading Data.\n");

    fp = fopen(filename, "r");

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line_count < MAX_LINES) {  
            len = strlen(line);
            strncpy(lines[line_count], line, len-1);
            line_count++;
        } else {
            fprintf(stderr, "Warning: Maximum number of lines exceeded\n");
            break;
        }
    }

    fclose(fp);

    for (int i = 0; i < line_count; i++) {
        if (strcmp(lines[i], "**INFORMATION") == 0) {
            readmode = 1;
        } else if (strcmp(lines[i], "**DATA-S") == 0) {
            readmode = 2;
            tmprow = 0;
        } else if (strcmp(lines[i], "**DATA-M") == 0) {
            readmode = 3;
            tmprow = 0;
        } else if (strcmp(lines[i], "**DATA-L") == 0) {
            readmode = 4;
            tmprow = 0;
        } else {
            dri = 0;
            char *infodat = strtok(lines[i], "|");
            while (infodat != NULL) {
                datarow[dri++] = infodat;
                infodat = strtok(NULL, "|");
            }
            
            switch(readmode) {
                case 1:
                    switch(atoi(datarow[1])) {
                        case 1:
                            small[0] = atoi(datarow[2]);
                            small[1] = atoi(datarow[3]);
                            small[2] = atoi(datarow[4]);
                            small[3] = atoi(datarow[5]);
                            small[4] = atoi(datarow[6]);

                            datarow[2] = "";
                            datarow[3] = "";
                            datarow[4] = "";
                            datarow[5] = "";
                            datarow[6] = "";
                            break;
                        case 2:
                            medium[0] = atoi(datarow[2]);
                            medium[1] = atoi(datarow[3]);
                            medium[2] = atoi(datarow[4]);
                            medium[3] = atoi(datarow[5]);
                            medium[4] = atoi(datarow[6]);

                            datarow[2] = "";
                            datarow[3] = "";
                            datarow[4] = "";
                            datarow[5] = "";
                            datarow[6] = "";
                            break;
                        case 3:
                            large[0] = atoi(datarow[2]);
                            large[1] = atoi(datarow[3]);
                            large[2] = atoi(datarow[4]);
                            large[3] = atoi(datarow[5]);
                            large[4] = atoi(datarow[6]);

                            datarow[2] = "";
                            datarow[3] = "";
                            datarow[4] = "";
                            datarow[5] = "";
                            datarow[6] = "";
                            break;
                        default:
                            break;
                    }
                    break;
                case 2:
                    sdata[tmprow][0] = datarow[0];
                    sdata[tmprow][0] = datarow[0];
                    sdata[tmprow][1] = datarow[1];
                    sdata[tmprow][2] = datarow[2];
                    sdata[tmprow][3] = datarow[3];
                    
                    datarow[0] = "";
                    datarow[1] = "";
                    datarow[2] = "";
                    datarow[3] = "";
                    tmprow++;
                    break;
                case 3:
                    mdata[tmprow][0] = datarow[0];
                    mdata[tmprow][1] = datarow[1];
                    mdata[tmprow][2] = datarow[2];
                    mdata[tmprow][3] = datarow[3];

                    datarow[0] = "";
                    datarow[1] = "";
                    datarow[2] = "";
                    datarow[3] = "";
                    
                    tmprow++;
                    break;
                case 4:
                    ldata[tmprow][0] = datarow[0];
                    ldata[tmprow][1] = datarow[1];
                    ldata[tmprow][2] = datarow[2];
                    ldata[tmprow][3] = datarow[3];

                    datarow[0] = "";
                    datarow[1] = "";
                    datarow[2] = "";
                    datarow[3] = "";
                    
                    tmprow++;
                    break;
                default:
                    break;
            }
        }
    }
}

void setupArrays() {
    for(int r = 0; r < 30; r++) {
        for(int c = 0; c < 4; c++) {
            sdata[r][c] = "";
            mdata[r][c] = "";
            ldata[r][c] = "";
        }
    }
    for(int r = 0; r < 5; r++) {
        small[r] = 0;
        medium[r] = 0;
        large[r] = 0;
    }
}

void printBanner() {
    printf("\n");
    printf("********************************************************************************************************************************************************\n");
    printf("\n");
    printf(" ________  ________  ___       __   ___               ________  ________  ________      ___    ___      ________  ________  ___       __   ___          \n");
    printf("|\\   __  \\|\\   __  \\|\\  \\     |\\  \\|\\  \\             |\\   __  \\|\\   __  \\|\\   __  \\    |\\  \\  /  /|    |\\   __  \\|\\   __  \\|\\  \\     |\\  \\|\\  \\         \n");
    printf("\\ \\  \\|\\ /\\ \\  \\|\\  \\ \\  \\    \\ \\  \\ \\  \\            \\ \\  \\|\\ /\\ \\  \\|\\  \\ \\  \\|\\ /_   \\ \\  \\/  / /    \\ \\  \\|\\ /\\ \\  \\|\\  \\ \\  \\    \\ \\  \\ \\  \\        \n");
    printf(" \\ \\   __  \\ \\  \\ \\  \\ \\  \\  __\\ \\  \\ \\  \\            \\ \\   __  \\ \\   __  \\ \\   __  \\   \\ \\    / /      \\ \\   __  \\ \\  \\ \\  \\ \\  \\  __\\ \\  \\ \\  \\       \n");
    printf("  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\|\\__\\_\\  \\ \\  \\____        \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\|\\  \\   \\/  /  /        \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\|\\__\\_\\  \\ \\  \\____  \n");
    printf("   \\ \\_______\\ \\_______\\ \\____________\\ \\_______\\       \\ \\_______\\ \\__\\ \\__\\ \\_______\\__/  / /           \\ \\_______\\ \\_______\\ \\____________\\ \\_______\\\n");
    printf("    \\|_______|\\|_______|\\|____________|\\|_______|        \\|_______|\\|__|\\|__|\\|_______|\\___/ /             \\|_______|\\|_______|\\|____________|\\|_______|\n");
    printf("                                                                                      \\|___|/                                                          \n");
    printf("\n");
    printf("********************************************************************************************************************************************************\n");
    printf("                                                    SHOES RENTAL MANAGEMENT SYSTEM - v1.0\n");
    printf("********************************************************************************************************************************************************\n");
    printf("\n");
}

void printGoodBye() {
    printf("********************************************************************************************************************************************************\n");
    printf("\n");
    printf("                             _       _       _____                 _   ____                  _       _                                \n");
    printf("                          /\\| |/\\ /\\| |/\\   / ____|               | | |  _ \\              /\\| |/\\ /\\| |/\\                             \n");
    printf("            ______ ______ \\ ` ' / \\ ` ' /  | |  __  ___   ___   __| | | |_) |_   _  ___   \\ ` ' / \\ ` ' / ______ ______ ______ ______ \n");
    printf("           |______|______|_     _|_     _| | | |_ |/ _ \\ / _ \\ / _` | |  _ <| | | |/ _ \\ |_     _|_     _|______|______|______|______|\n");
    printf("                          / , . \\ / , . \\  | |__| | (_) | (_) | (_| | | |_) | |_| |  __/  / , . \\ / , . \\                             \n");
    printf("                          \\/|_|\\/ \\/|_|\\/   \\_____|\\___/ \\___/ \\__,_| |____/ \\__, |\\___|  \\/|_|\\/ \\/|_|\\/                             \n");
    printf("                                                                              __/ |                                                   \n");
    printf("                                                                             |___/                                                    \n");
    printf("\n");
}