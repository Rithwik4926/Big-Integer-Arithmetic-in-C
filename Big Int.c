#include <stdio.h>
#include <string.h>

#define SIZE 311                                                                     // for sign and '\0'

typedef struct bigInt{
    char number[SIZE];
} bigInt;

int findGreater(bigInt x, bigInt y);
void Input(bigInt *num);
void Add(bigInt x, bigInt y, bigInt *result);
void Subtract(bigInt x, bigInt y, bigInt *result);
void Multiply(bigInt x, bigInt y, bigInt *result);

int findGreater(bigInt x, bigInt y){
    int xlen = strlen(x.number);
    int ylen = strlen(y.number);

    if (xlen > ylen){
        return 0;                                                                    // x is bigger
    }
    else if (xlen < ylen){
        return 1;                                                                    // y is bigger
    }
    
    for (int i = 1; i < xlen; i++){                                                  // If lengths are equal, compare digit by digit
        if (x.number[i] > y.number[i]){
            return 0;                                                                // x is bigger
        }
        else if (x.number[i] < y.number[i]){
            return 1;                                                                // y is bigger
        }
    }
    return 0;                                                                        // Both are equal, returning x
}

void Input(bigInt *num){
    scanf("%310s", num->number);
    int len = strlen(num->number);

    if (num->number[0]!= '-' && num->number[0]!= '+'){
        for (int i=len-1; i>=0; i--){
            num->number[i+1] = num->number[i];
        }
        num->number[0] = '+';
        num->number[len+1] = '\0';
    }
}

void Add(bigInt x, bigInt y, bigInt *result){
    for(int i = 0; i < SIZE; i++){
        result->number[i] = '0';                                                     //Initialize the result
    }
    result->number[SIZE-1] = '\0';

    if(x.number[0] == y.number[0]){                                                  // Check if signs are the same    
        result->number[0] = x.number[0];                                             // Both numbers have the same sign, perform addition so set the result sign
    }else{
        if (y.number[0] == '+'){                                                     // Signs are different, treat it as subtraction
            y.number[0] = '-';                                                       // Change y's sign
        }else{
            y.number[0] = '+';                                                       // Change y's sign
        }
        Subtract(x, y, result);
        return;
    }
    int carry = 0;                                                                   // Perform addition
    int xlen = strlen(x.number), ylen = strlen(y.number);
    int i = xlen-1, j = ylen-1, k = SIZE-2;

    while(i>0 || j>0 || carry>0){
        int a = 0, b = 0;
        
        if(i > 0){
            a = x.number[i--] - '0';
        }else{
            a = 0;                                                                   // No more digits in x
        }

        if(j > 0){
            b = y.number[j--] - '0';
        }else{
            b = 0;                                                                   // No more digits in y
        }

        int sum = a + b + carry;

        if(sum >= 10){
            carry = sum / 10;                                                        // Update carry if sum is 10 or more
        }else{
            carry = 0;                                                               // No carry
        }
        result->number[k--] = (sum % 10) + '0';                                      // Store the last digit of sum
    }

    int start = k+1;                                                                 // Remove leading zeros from the result
    while(result->number[start] == '0' && start < SIZE-2){
        start++;
    }

    int id = 1;                                                                      // Leave space for the sign
    for(int m = start; m < SIZE-1; m++){
        result->number[id++] = result->number[m];
    }
    result->number[id] = '\0';
}

void Subtract(bigInt x, bigInt y, bigInt *result){
    for(int i = 0; i < SIZE; i++){                                                   // Initialize the result array
        result->number[i] = '0';
    }
    result->number[SIZE-1] = '\0';

    if(x.number[0] != y.number[0]){                                                  // If the numbers have different signs, perform addition
        if(y.number[0] == '+'){
            y.number[0] = '-';                                                       // Change the sign of y
        }else{
            y.number[0] = '+';                                                       // Change the sign of y
        }
        Add(x, y, result);
        return;
    }else{                                                                           // Both numbers have the same sign; flip the sign of y
        if(y.number[0] == '+'){
            y.number[0] = '-';
        }else{
            y.number[0] = '+';
        }
    }

    int great = findGreater(x, y);                                                   // Find the greater number
    if(great == 0){                                                                  // i.e., x >= y
        if(x.number[0] == '+'){
            result->number[0] = '+';
        }else{
            result->number[0] = '-';
        }
    }else{                                                                           //i.e., y > x
        if(x.number[0] == '+'){
            result->number[0] = '-';
        }else{
            result->number[0] = '+';
        }
    }

    int borrow = 0, diff = 0;                                                        // Perform subtraction digit by digit
    int xlen = strlen(x.number), ylen = strlen(y.number);
    int i = xlen-1, j = ylen-1, k = SIZE-2;

    while(i>0 || j>0){
        int a=0, b=0;

        if(i>0){
            a = x.number[i] - '0';
            i--;
        }

        if(j>0){
            b = y.number[j] - '0';
            j--;
        }

        if(great == 0){                                                              // x >= y
            diff = a-b-borrow;
        }else{                                                                       // y > x
            diff = b-a-borrow;
        }

        if(diff < 0){
            diff += 10;
            borrow = 1;
        }else{
            borrow = 0;
        }

        result->number[k] = diff + '0';
        k--;
    }

    int start = k+1;                                                                 // Remove leading zeros from the result
    while(result->number[start] == '0' && start < SIZE-2){
        start++;
    }

    int id = 1;                                                                      // Leave space for the sign
    for(int m = start; m < SIZE-1; m++){
        result->number[id] = result->number[m];
        id++;
    }
    result->number[id] = '\0';

    if(strcmp(result->number,"+0")==0 || strcmp(result->number,"-0")==0){
        result->number[0] = '0';
        result->number[1] = '\0';
    }
}

void Multiply(bigInt x, bigInt y, bigInt *result){
    for(int i = 0; i < SIZE; i++){                                                   // Initialize the result array
        result->number[i] = '0';
    }
    result->number[SIZE-1] = '\0';

    if(x.number[0] == y.number[0]){                                                  // Determine the sign of the result
        result->number[0] = '+';
    }else{
        result->number[0] = '-';
    }

    int xlen = strlen(x.number);
    int ylen = strlen(y.number);

    if(xlen+ylen > SIZE-2){                                                          // Check if the result will fit in the array
        printf("The result of Multiplication is Overflowing\n");
        return;
    }

    int temp[SIZE] = {0};                                                            // Temporary array for storing intermediate results

    for(int i = xlen-1; i>0; i--){                                                   // Perform multiplication
        int carry = 0;
        int xD = x.number[i] - '0';

        for(int j = ylen-1, k = (SIZE-2)-((xlen-1)-i); j>0 ; j--, k--){
            int yD = y.number[j] - '0';
            int product = (xD*yD) + temp[k] + carry;

            temp[k] = product%10;
            carry = product/10;
        }

        int k = (SIZE-2)-((xlen-1)- i + ylen-1);                                     // Store the carry in the next cell
        while(carry>0 && k >= 1){
            int sum = temp[k] + carry;
            temp[k] = sum%10;
            carry = sum/10;
            k--;
        }
    }

     int start = 0;                                                                  // Remove leading zeros from the result
    while(start < SIZE-1 && temp[start] == 0){
        start++;
    }

    int id = 1;                                                                      // Leave space for the sign
    for(int i = start; i < SIZE-1; i++){
        result->number[id] = temp[i] + '0';
        id++;
    }
    result->number[id] = '\0';

    if(strcmp(result->number,"+")==0 || strcmp(result->number,"-")==0){
        result->number[0] = '0';
        result->number[1] = '\0';
    }
}

int main(){
    bigInt num1, num2, result;
    int choice;

    do{
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Choose an operation:\n");
        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Exit\n");
        printf("Enter operation number: ");
        scanf("%d",&choice);

        switch(choice){
        case 1:
            printf("Enter Your 1st Number:");
            Input(&num1);
            printf("Enter Your 2nd Number:");
            Input(&num2);
            
            Add(num1, num2, &result);
            printf("Result: %s\n", result.number);
            break;

        case 2:
            printf("Enter Your 1st Number:");
            Input(&num1);
            printf("Enter Your 2nd Number:");
            Input(&num2);

            Subtract(num1, num2, &result);
            printf("Result: %s\n", result.number);
            break;

        case 3:
            printf("Enter Your 1st Number:");
            Input(&num1);
            printf("Enter Your 2nd Number:");
            Input(&num2);

            Multiply(num1, num2, &result);
            printf("Result: %s\n", result.number);
            break;

        case 4:
            printf("Exit\n");
            break;

        default:
            printf("Invalid choice!!\n");
        }
    }while(choice != 4);

    return 0;
}