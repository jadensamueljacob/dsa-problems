#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Interactions 
{
    int product_id;
    int interaction_count;
    struct Interactions *left;
    struct Interactions *right;
} Interactions;

typedef struct User 
{
    int id;
    char name[50];
    Interactions *history; // Tree for product interactions
    struct User *next;
} User;

typedef struct Product 
{
    int id;
    char name[50];
    struct Product *next;
} Product;

typedef struct Data 
{
    User *users[100];
    Product *products[100];
} Data;

// the Hash function
int hash(int id) 
{
    return id % 100;
}

// Initialising the data structure
void init(Data *store) 
{
    memset(store->users, 0, sizeof(store->users));
    memset(store->products, 0, sizeof(store->products));
}

// User management functions
void add_user(Data *store, int id, char *name) 
{
    User *new_user = (User *)malloc(sizeof(User));
    new_user->id = id;
    strcpy(new_user->name, name);
    new_user->history = NULL;
    new_user->next = NULL;

    int index = hash(id);
    new_user->next = store->users[index];
    store->users[index] = new_user;
}

void display_users(Data *store) 
{
    printf("Users:\n");
    for (int i = 0; i < 100; i++) 
    {
        User *temp = store->users[i];
        while (temp) 
        {
            printf("User ID: %d, Name: %s\n", temp->id, temp->name);
            temp = temp->next;
        }
    }
}

User *find(Data *store, int id) 
{
    int index = hash(id);
    User *temp = store->users[index];
    while (temp) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Product management functions
void add_product(Data *store, int id, char *name) 
{
    Product *new_product = (Product *)malloc(sizeof(Product));
    new_product->id = id;
    strcpy(new_product->name, name);
    new_product->next = NULL;

    int index = hash(id);
    new_product->next = store->products[index];
    store->products[index] = new_product;
}

void display_products(Data *store) 
{
    printf("Products:\n");
    for (int i = 0; i < 100; i++) 
    {
        Product *temp = store->products[i];
        while (temp) 
        {
            printf("Product ID: %d, Name: %s\n", temp->id, temp->name);
            temp = temp->next;
        }
    }
}

Product *get_product(Data *store, int id) 
{
    int index = hash(id);
    Product *temp = store->products[index];
    while (temp) 
    {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Product tree functions
Interactions *create_interaction(int product_id) 
{
    Interactions *node = (Interactions *)malloc(sizeof(Interactions));
    node->product_id = product_id;
    node->interaction_count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Interactions *add_history(Interactions *root, int product_id) 
{
    if (root == NULL) 
    {
        return create_interaction(product_id);
    }

    if (product_id < root->product_id) 
    {
        root->left = add_history(root->left, product_id);
    } 
    else if (product_id > root->product_id) 
    {
        root->right = add_history(root->right, product_id);
    } 
    else 
    {
        root->interaction_count++;
    }

    return root;
}

void max_interaction(Interactions *root, int *max_product, int *max_count) 
{
    if (root == NULL) 
    {
        return;
    }

    if (root->interaction_count > *max_count) 
    {
        *max_count = root->interaction_count;
        *max_product = root->product_id;
    }

    max_interaction(root->left, max_product, max_count);
    max_interaction(root->right, max_product, max_count);
}

// Interaction management
void add_interaction(Data *store, int user_id, int product_id) 
{
    User *user = find(store, user_id);
    if (!user) 
    {
        printf("Error: User ID %d not found.\n", user_id);
        return;
    }

    user->history = add_history(user->history, product_id);
}

void generate_recommendations(Data *store, int user_id) 
{
    User *user = find(store, user_id);
    if (!user) 
    {
        printf("Error: User ID %d not found.\n", user_id);
        return;
    }

    if (!user->history) 
    {
        printf("No interactions found for User ID %d.\n", user_id);
        return;
    }

    int max_product = -1, max_count = 0;
    max_interaction(user->history, &max_product, &max_count);

    if (max_product != -1) 
    {
        Product *product = get_product(store, max_product);
        if (product) 
        {
            printf("Recommended Product for User ID %d:\n", user_id);
            printf("Product ID: %d, Name: %s\n", product->id, product->name);
        }
    } 
    else 
    {
        printf("No recommendations available for User ID %d.\n", user_id);
    }
}

// Menus
void user_menu(Data *store) 
{
    int choice, id;
    char name[50];

    while (1) 
    {
        printf("\nUser Management:\n");
        printf("1. Add User\n");
        printf("2. Display Users\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter User ID: ");
                scanf("%d", &id);
                printf("Enter User Name: ");
                scanf("%s", name);
                add_user(store, id, name);
                break;
            case 2:
                display_users(store);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void product_menu(Data *store) 
{
    int choice, id;
    char name[50];

    while (1) 
    {
        printf("\nProduct Management:\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter Product ID: ");
                scanf("%d", &id);
                printf("Enter Product Name: ");
                scanf("%s", name);
                add_product(store, id, name);
                break;
            case 2:
                display_products(store);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void recommendation_menu(Data *store) 
{
    int choice, user_id, product_id;

    while (1) 
    {
        printf("\nRecommendation System:\n");
        printf("1. Add Interaction\n");
        printf("2. Generate Recommendations\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter User ID for Interaction: ");
                scanf("%d", &user_id);
                printf("Enter Product ID for Interaction: ");
                scanf("%d", &product_id);
                add_interaction(store, user_id, product_id);
                break;
            case 2:
                printf("Enter User ID for Recommendations: ");
                scanf("%d", &user_id);
                generate_recommendations(store, user_id);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Main function
int main() 
{
    Data store;
    init(&store);

    int choice;

    while (1) 
    {
        printf("\nMain Menu:\n");
        printf("1. User Management\n");
        printf("2. Product Management\n");
        printf("3. Recommendation System\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                user_menu(&store);
                break;
            case 2:
                product_menu(&store);
                break;
            case 3:
                recommendation_menu(&store);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}