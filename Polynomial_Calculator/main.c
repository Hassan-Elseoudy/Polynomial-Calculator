#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

typedef struct
{
    Node *head,*tail;
} LinkedList;

void init(LinkedList*list)
{
    list -> head = NULL;
    list -> tail = NULL;
}

Node *newNode(int coe,int exp)
{
    Node *p = malloc(sizeof(Node));
    p -> coefficient=coe;
    p -> exponent=exp;
    p -> next = NULL;
    return p;
}

LinkedList *Sort (LinkedList*L)
{
    Node *t,*t1,*t2,*tt;
    if(L->head == NULL)
        printf("\nThe linked list is empty!");
    else
    {
        t1 = L -> head -> next;
        while(t1 != NULL)
        {
            t2 = t1 -> next;
            for(t = L->head; t != t1; t = t -> next)
            {
                if(t1->exponent  >  t->exponent)
                {
                    t1 -> next = t;
                    for(tt=L->head; tt->next != t1; tt=tt->next);
                    tt -> next = t2;
                    if(t == L->head)
                        L->head = t1;
                    else
                    {
                        for(tt=L->head; tt->next != t; tt=tt->next);

                        tt -> next = t1;
                    }
                    break;
                }
            }
            t1 = t2;
        }
    }
}

void addHead(LinkedList*list,int coe,int exp)
{
    Node *p = newNode(coe,exp);
    p->next=list->head;
    list->head=p;
    if (list->tail==NULL)
        list->tail=p;
}

void deleteHead(LinkedList*list)
{
    Node *first = list->head;
    if (first!=NULL)
    {
        list->head=first->next;
        free(first);
    }
    else
        list->tail=NULL;
}

void deleteTail(LinkedList *list)
{
    Node *prevTail=NULL;
    Node *temp=list->head;
    if (temp!=NULL)
    {
        while(temp->next!=NULL)
        {
            prevTail=temp;
            temp=temp->next;
        }
        free(temp);
        prevTail->next=NULL;
        list->tail=prevTail;
    }
}

void DeleteNode(LinkedList*L,Node*after)
{
    Node* current = L->head;
    Node* temp;

    while (current != NULL)
    {
        if (current->next==after)
        {
            temp = after;
            temp-> coefficient = after -> coefficient;
            temp-> exponent = after -> exponent;
            current -> next  = after -> next;
            after = current -> next;
            free(temp);
            break;
        }
        current = current -> next;
    }

}

void display_poly(LinkedList*x)
{
    Node *p = x->head;
    printf("Polynomial: ");
    while (p!=NULL)
    {
        switch(p->coefficient)
        {
        case 1:
            if (p->exponent==1)
                printf("x");
            else if (p->exponent)
                printf("x^%d",p->exponent);
            p=p->next;
            break;
        case 0:
            p=p->next;
            break;
        default:
            if (p->exponent==1)
                printf("%dx",p->coefficient);
            else if (p->exponent>1||p->exponent<0)
                printf("%dx^%d",p->coefficient,p->exponent);
            else
                printf("%d");
            p=p->next;
            break;
        }

        if (p!=NULL && p->coefficient > 0)
            printf("+");
    }
}

float getValue(LinkedList*l,float x)
{
    Node *p= l->head;
    float sum=0.0;
    while (p!=NULL)
    {
        sum+=p->coefficient*pow((x),p->exponent);
        p=p->next;
    }
    return sum;
}

void *poly_simp (LinkedList *X)
{
    Node *x = X-> head;
    if (x==NULL)
        printf("Invalid");
    Node * after = x->next;
    while (after!=NULL)
    {
        while (x->exponent == after->exponent)
        {
            x->coefficient += after -> coefficient;
            DeleteNode(X,after);
            after = x->next;
        }
        x = x -> next;
        after = x->next;
    }
}

LinkedList *poly_add(LinkedList*L,LinkedList*X)
{
    LinkedList *add = (LinkedList*)malloc(sizeof(LinkedList));
    init(&add);
    Node *l= L->head;
    Node *x= X->head;
    while (x!=NULL && l!=NULL)
    {
        if(x->exponent == l-> exponent)
        {
            addHead(&add,(x->coefficient + l->coefficient),(l -> exponent));
            l=l->next;
            x=x->next;
        }
        else if (x->exponent > l->exponent)
        {
            addHead(&add,x->coefficient,x->exponent);
            x=x->next;
        }
        else
        {
            addHead(&add,l->coefficient,l->exponent);
            l = l->next;
        }
    }
    while(x != NULL)
    {
        addHead(&add,x->coefficient,x->exponent);
        x=x->next;
    }
    while(l != NULL)
    {
        addHead(&add,l->coefficient,l->exponent);
        l=l->next;
    }
    Sort(&add);
    poly_simp(&add);
    return add;
}

LinkedList *poly_Mult(LinkedList*L,LinkedList*X)
{
    LinkedList *Mult = (LinkedList*)malloc(sizeof(LinkedList));
    init(&Mult);
    Node *l = L->head;
    Node *x = X->head;
    Node *temp = X->head;
    while(l!=NULL)
    {
        while(x!=NULL)
        {
            addHead(&Mult,((x->coefficient)*(l->coefficient)),(x->exponent + l->exponent));
            x = x->next;
        }
        x = temp;
        l = l->next;
    }
    Sort(&Mult);
    poly_simp(&Mult);
    return Mult;
}

int main()
{
    printf("Welcome to my program!");
    int i,n,coe,exp,ch;
    float value;
    LinkedList x;
    LinkedList y;
    LinkedList *z;
    init(&x);
    init(&y);
    init(&z);
    while (1)
    {
        printf("\n--------------------\nEnter Operation:\n1. Addition.\n2. Multiplication.\n3. Simplifying.\n--------------------\n");
        scanf(" %d",&ch);
        printf("\nEnter the coefficient and power for each term after selecting # of terms \n");
        switch (ch)
        {
        case 1 :
            printf("How many terms for polynomial (1) ?\n");
            scanf("%d", &n);
            while (n<0)
            {
                puts("Invalid");
                scanf("%d", &n);
            }
            init(&x);
            for (i=0; i<n; i++)
            {
                scanf("%d%d",&coe,&exp);
                addHead(&x,coe,exp);
            }
            Sort(&x);
            display_poly(&x);
            printf("\nHow many terms for polynomial (2) ?\n");
            scanf("%d", &n);
            while (n<0)
            {
                puts("Invalid");
                scanf("%d", &n);
            }
            init(&y);
            for (i=0; i<n; i++)
            {
                scanf("%d%d",&coe,&exp);
                addHead(&y,coe,exp);
            }
            Sort(&y);
            display_poly(&y);
            puts("");
            z = poly_add(&x,&y);
            Sort(&z);
            display_poly(&z);
            printf("\nEnter you required value?\n");
            scanf(" %f",&value);
            printf("Value is : %f ",getValue(&z,value));
            while ( x.head !=NULL )
            {
                deleteHead(&x);
            }
            while ( y.head !=NULL )
            {
                deleteHead(&y);
            }
            break;
        case 2:
            printf("How many terms for polynomial (1) ?\n");
            scanf("%d",&n);
            while (n<0)
            {
                puts("Invalid");
                scanf("%d", &n);
            }
            init(&x);
            for (i=0; i<n; i++)
            {
                scanf("%d%d",&coe,&exp);
                addHead(&x,coe,exp);
            }
            Sort(&x);
            display_poly(&x);
            printf("\nHow many terms for polynomial (2) ?\n");
            scanf("%d",&n);
            while (n<0)
            {
                puts("Invalid");
                scanf("%d", &n);
            }
            init(&y);
            for (i=0; i<n; i++)
            {
                scanf("%d%d",&coe,&exp);
                addHead(&y,coe,exp);
            }
            Sort(&x);
            display_poly(&y);
            puts("");
            z = poly_Mult(&x,&y);
            Sort(&z);
            display_poly(&z);
            puts("");
            printf("\nEnter you required value?\n");
            scanf(" %f",&value);
            printf("Value is : %f ",getValue(&z,value));
            while ( x.head !=NULL )
            {
                deleteHead(&x);
            }
            while ( y.head !=NULL )
            {
                deleteHead(&y);
            }
            break;
        case 3 :
            printf("How many terms for polynomial ?\n");
            scanf("%d", &n);
            while (n<0)
            {
                puts("Invalid");
                scanf("%d", &n);
            }
            init(&x);
            for (i=0; i<n; i++)
            {
                scanf("%d%d",&coe,&exp);
                addHead(&x,coe,exp);
            }
            Sort(&x);
            poly_simp(&x);
            display_poly(&x);
            while ( x.head !=NULL )
            {
                deleteHead(&x);
            }
            break;
        default:
            printf("Invalid command");
            break;
        }
    }
    return 0;
}

