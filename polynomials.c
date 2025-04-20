#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Node structure for the linked list
struct Node {
    int coeff;
    int power;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int power) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertNode(struct Node** poly, int coeff, int power) {
    struct Node* newNode = createNode(coeff, power);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to add two polynomials and return the result
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp1 = poly1;
    struct Node* temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->power > temp2->power) {
            insertNode(&result, temp1->coeff, temp1->power);
            temp1 = temp1->next;
        } else if (temp1->power < temp2->power) {
            insertNode(&result, temp2->coeff, temp2->power);
            temp2 = temp2->next;
        } else {
            int sumCoeff = temp1->coeff + temp2->coeff;
            if (sumCoeff != 0) {  // Avoid inserting zero coefficients
                insertNode(&result, sumCoeff, temp1->power);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    // Add the remaining terms of poly1
    while (temp1 != NULL) {
        insertNode(&result, temp1->coeff, temp1->power);
        temp1 = temp1->next;
    }

    // Add the remaining terms of poly2
    while (temp2 != NULL) {
        insertNode(&result, temp2->coeff, temp2->power);
        temp2 = temp2->next;
    }

    return result;
}

// Function to evaluate a polynomial for a given value of x
int evaluatePolynomial(struct Node* poly, int x) {
    int result = 0;
    while (poly != NULL) {
        result += poly->coeff * pow(x, poly->power);
        poly = poly->next;
    }
    return result;
}

// Function to print the polynomial
void printPolynomial(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->power);
        if (poly->next != NULL && poly->next->coeff > 0) {
            printf(" + ");
        }
        poly = poly->next;
    }
    printf("\n");
}

// Function to read a polynomial from the user
struct Node* readPolynomial() {
    struct Node* poly = NULL;
    int n, coeff, power;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and power for term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);
        insertNode(&poly, coeff, power);
    }

    return poly;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;
    int x;

    // Read the first polynomial from the user
    printf("Enter the first polynomial:\n");
    poly1 = readPolynomial();

    // Read the second polynomial from the user
    printf("Enter the second polynomial:\n");
    poly2 = readPolynomial();

    // Add the polynomials
    result = addPolynomials(poly1, poly2);

    // Print the result
    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);
    printf("Sum: ");
    printPolynomial(result);

    // Evaluate the sum for a given value of x
    printf("Enter the value of x to evaluate the polynomial: ");
    scanf("%d", &x);
    int sumValue = evaluatePolynomial(result, x);
    printf("The value of the polynomial at x = %d is: %d\n", x, sumValue);

    return 0;
}
