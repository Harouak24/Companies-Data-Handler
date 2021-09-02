#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
typedef struct {
  char name[40], industry[25], country[20];
  double revenue, profit;
  int n_employees;
} company_info;
void menu(void);
int load_data_to_arr(company_info *companies);
int convert_str_to_int(char *element);
int data_company_X(company_info *companies, char company_X[40], int N);
char* convert_int_to_str(int element);
void sort_by_n_employees(company_info *companies, int N);
int update_data_of_company(company_info *companies, int new_N, int index, char company_X[40]);
int search_for_country_X(company_info *companies, int N, char country_X[40]);
void filter_companies_by_country(company_info *companies, int N, int index, char country_X[40]);
int main(void) {
  int N, choice, load_first = 0, index, new_N, update;
  char company_X[40], country_X[40], temp;
  company_info companies[50];
  do {
    menu();
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch(choice){
       case 1: N = load_data_to_arr(companies);
      load_first++;
      printf("\n\nData was successfully loaded to an array!\n\n");
      break;
      case 2: if(load_first == 0) {
        printf("\nLoad data to array first!\n");
        break;
      }
      else {
        printf("\nInput the name of the company you wish to get data about: ");
        scanf("%c", &temp);
        gets(company_X);
        index = data_company_X(companies, company_X, N);
        if(index == -101)
          printf("\n\nCompany not found!\n\n");
        else{
          printf("\n\nCompany Name: %s\n", companies[index].name);
          printf("Company Industry: %s\n", companies[index].industry);
          printf("Company Revenue: $%s\n\n", convert_int_to_str(companies[index].revenue));
          printf("Company Profit: $%s\n\n", convert_int_to_str(companies[index].profit));
          printf("Company Number of Employees: %s\n\n", convert_int_to_str(companies[index].n_employees));
          printf("Company Country: %s\n", companies[index].country);
        }
      }
      break;
      case 3: if(load_first == 0) {
        printf("\nAdd company records first!\n");
        break;
      }
      else{
        sort_by_n_employees(companies, N);
        printf("\nThe file was sorted successfully!\n\nPlease go to 'data_by_employees.txt' to check.\n\n");
      }
      break;
      case 4: if(load_first == 0) {
        printf("\nAdd company records first!\n");
        break;
      }
      else {
        printf("\nInput the name of the company you would like to update: ");
        scanf("%s", company_X);
        index = data_company_X(companies, company_X, N);
        if(index == -101)
          printf("\n\nCompany not found!\n\n");
        else {
          printf("\nEnter the new number of employees in %s: ", company_X);
          scanf("%d", &new_N);
          update = update_data_of_company(companies, new_N, index, company_X);
          if(update == 1)
            printf("\nThe number of employees working for %s has been successfully updated.\n\n", company_X);
          else
           printf("\nThis company cannot have more than %'d employees.\n\n", update);
        }
      }
      break;
      case 5: if(load_first == 0) {
        printf("\nAdd company records first!\n");
        break;
      }
      else {
        printf("\nInput the name of the country you wish to view all its companies: ");
        scanf("%c", &temp);
        gets(country_X);
        index = search_for_country_X(companies, N, country_X);
        if(index == -101)
          printf("\nCountry Not Found!\n");
        else {
            filter_companies_by_country(companies, N, index, country_X);
            printf("\nA new file that holds data belonging to %s was generated.\n", country_X);
        }
      }
      break;
      case 6: printf("\n\nLater Alligator!\n\n");
      break;
      default: printf("\n\nError! Please try again.\n");
    }
  } while(choice != 6);
  return 0;
}
void menu(void){
  printf("\n\n");
  printf("---------------------------------------------\n");
  printf("|                   MENU                    |\n");
  printf("---------------------------------------------\n");
  printf("1. Load Data to an Array\n");
  printf("---------------------------------------------\n");
  printf("2. Get data about a company\n");
  printf("---------------------------------------------\n");
  printf("3. Sort companies by number of employees\n");
  printf("---------------------------------------------\n");
  printf("4. Update data of a company\n");
  printf("---------------------------------------------\n");
  printf("5. Filter Companies by country\n");
  printf("---------------------------------------------\n");
  printf("6. Quit\n");
  printf("---------------------------------------------\n");
}
int load_data_to_arr(company_info companies[50]) {
  int i = 0, j, z;
  char temp[20];
  FILE* infp = fopen("data.txt","r");
  if(infp == NULL){
    printf("\nFile could not be opened!\n");
    exit(1);
    // exit(1) terminates the program and shows that an error happened
  }
  while(!feof(infp)) {
    fgets(companies[i].name, 40, infp);
    fgets(companies[i].industry, 25, infp);
    fgets(temp, 20, infp);
    for(j = 0; j < strlen(temp); j++)
      temp[j] = temp[j + 1];
    companies[i].revenue = convert_str_to_int(temp);
    fgets(temp, 20, infp);
    for(j = 0; j < strlen(temp); j++)
      temp[j] = temp[j + 1];
    companies[i].profit = convert_str_to_int(temp);
    fgets(temp, 20, infp);
    companies[i].n_employees = convert_str_to_int(temp);
    fgets(companies[i].country, 20, infp);
    fgets(temp, 20, infp);
    i++;
  }
  return i;
  fclose(infp);
}
int convert_str_to_int(char *temp) {
  int i, j;
  for(i = 0; i < strlen(temp); i++) {
    if(temp[i] == ',') {
      for(j = i; j < strlen(temp); j++)
        temp[j] = temp[j + 1];
    }
  }
  return atoi(temp);
  //We used atoi() to convert the string into an integer
}
char* convert_int_to_str(int element) {
  int commas, i, swaps;
  char *result, temp;
  sprintf(result, "%d", element);
  commas = ceil(strlen(result) / 3.0) - 1;
  for(i = 0; i < commas; i++)
    strncat(result, ",", 1);
  while(commas != 0) {
    swaps = commas * 4 - 1;
    for(i = 1; i <= swaps; i++) {
      temp = result[strlen(result) - i];
      result[strlen(result) - i] = result[strlen(result) - i - 1];
      result[strlen(result) - i - 1] = temp;
    }
    commas--;
  }
  return result;
}
int data_company_X(company_info companies[50], char company_X[40], int N) {
  int i;
  for(i = 0; i < N; i++) {
    if(strncmp(companies[i].name, company_X, strlen(company_X)) == 0)
      return i;
  }
  return -101;
}
void sort_by_n_employees(company_info companies[50], int N) {
  setlocale(LC_NUMERIC, "");
  int i, j;
  FILE* outfp = fopen("data_by_employees.txt", "w");
  company_info temp;
  for (i = 1; i < N; i++) {
    temp = companies[i];
    j = i-1;
    while((temp.n_employees > companies[j].n_employees) && (j >= 0)) {
         companies[j+1] = companies[j];
         j--;
      }
      companies[j+1] = temp;
  }
  for(i = 0; i < N; i++) {
    fprintf(outfp, "%s", companies[i].name);
    fprintf(outfp, "%s", companies[i].industry);
    fprintf(outfp, "$%'.0f\n", companies[i].profit);
    fprintf(outfp, "$%'.0f\n", companies[i].revenue);
    fprintf(outfp, "%'d\n", companies[i].n_employees);
    fprintf(outfp, "%s", companies[i].country);
    fprintf(outfp, "------------------\n");
  }
  fclose(outfp);
}
int update_data_of_company(company_info *companies, int new_N, int index, char company_X[40]) {
  setlocale(LC_NUMERIC, "");
  FILE* infp = fopen("data.txt","r+");
  int i, temp, count = 0, max, compare;
  char line[60], new_N_str[20];
  while(fgets(line, 60, infp) != NULL) {
    if(strncmp(line, company_X, strlen(company_X)) == 0) {
      fgets(line, 60, infp);
      fgets(line, 60, infp);
      fgets(line, 60, infp);
      fgets(line, 60, infp);
      strcpy(new_N_str, line);
      compare = convert_str_to_int(new_N_str);
      temp = compare;
      while (temp != 0) {
        temp /= 10;
        count++;
      }
      max = pow(10, count) - 1;
      if(new_N > max) {
        fclose(infp);
        return max;
      }
      else {
        companies[index].n_employees = new_N;
        fseek(infp, -strlen(line), 1);
        for(i = 0; i < strlen(line) - 1; i++) {
          fputc(' ', infp);
        }
        fseek(infp, 1-strlen(line), 1);
        fprintf(infp, "%'d", new_N);
      }
      fclose(infp);
      return 1;
    }
  }
  fclose(infp);
  return -101;
}
int search_for_country_X(company_info companies[50], int N, char country_X[40]) {
  int i;
  for(i = 0; i < N; i++){
    if(strncmp(companies[i].country, country_X, strlen(country_X)) == 0)
      return i;
  }
  return -101;
}
void filter_companies_by_country(company_info *companies, int N, int index, char country_X[40]) {
  setlocale(LC_NUMERIC, "");
  char fname[50];
  int i;
  FILE* outfp;
  strcpy(fname, country_X);
  for(i = 0; i < strlen(fname); i++) {
    if(fname[i] == ' ')
      fname[i] = '_';
  }
  strcat(fname, "_data.txt");
  outfp = fopen(fname, "w");
  for(i = 0; i < N; i++) {
    if(strncmp(companies[i].country, country_X, strlen(country_X)) == 0) {
      fprintf(outfp, "%s", companies[i].name);
      fprintf(outfp, "%s", companies[i].industry);
      fprintf(outfp, "$%'.0f\n", companies[i].profit);
      fprintf(outfp, "$%'.0f\n", companies[i].revenue);
      fprintf(outfp, "%'d\n", companies[i].n_employees);
      fprintf(outfp, "%s", companies[i].country);
      fprintf(outfp, "------------------\n");
    }
  }
  fclose(outfp);
}
