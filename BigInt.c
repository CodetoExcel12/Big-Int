#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 310

typedef struct integer
{
    char sign;
    int *nums;
    int length; 
} integer;

void printinteger(integer *n)
{
    printf("%c", n->sign);
    for (int i = n->length - 1; i >= 0; i--)
    {
        printf("%d", n->nums[i]);
    }
}

integer convert_string(char str[])
{
    integer b;
    b.sign = str[0];
    int j = strlen(str) - 2;
    b.length = j;  
    b.nums = (int *)malloc(sizeof(int) * b.length);
    int i = 0;
    while (j > 0)
    {

        b.nums[i] = str[j] - '0';
        i++;
        j--;
    }
    return b;
}

integer *subtractintegers(integer *b1, integer *b2);
integer *subtract(integer *b1, integer *b2);
integer *multiplication(integer *b1, integer *b2);
  /* RETURNS 0 IF B1=B2
      RETURNS <0  IF B1<B2
      RETURNS >0 IF B1>B2  */
int compare(integer *b1, integer *b2)
{
    int i, retval;
    if (b1->length == b2->length)
    {
        i = (b1->length) - 1;
        while (i >= 0 && b1->nums[i] == b2->nums[i])
        {
            i--;
        }
        if (i < 0)
        {
            retval = 0;
        }
        else
        {
            retval = (b1->nums[i]) - (b2->nums[i]);
        }
    }
    else
    {
        retval = (b1->length) - (b2->length);
    }
    return retval;
}

integer *add(integer *b1, integer *b2)
{
    integer *sum = (integer *)malloc(sizeof(integer));
    if (b1->length > b2->length)
    {
        sum->nums = (int *)malloc(sizeof(int) * (b1->length + 1));
    }
    else
    {
        sum->nums = (int *)malloc(sizeof(int) * (b2->length + 1));
    }
    int i = 0, rem = 0, add;
    if (b1->sign == b2->sign)
    {
        while (i < b1->length && i < b2->length)
        {
            add = b1->nums[i] + b2->nums[i] + rem;
            rem = add / 10;
            add = add % 10;
            sum->nums[i] = add;
            i++;
        }
        while (i < b1->length)
        {
            add = b1->nums[i] + rem;
            rem = add / 10;
            add = add % 10;
            sum->nums[i] = add;
            i++;
        }
        while (i < b2->length)
        {
            add = b2->nums[i] + rem;
            rem = add / 10;
            add = add % 10;
            sum->nums[i] = add;
            i++;
        }
        while (rem != 0)
        {
            sum->nums[i] = (rem % 10);
            rem = rem / 10;
            i++;
        }
        sum->length = i;
        sum->sign = b1->sign;
    }
    else
    {
        if (b1->sign == '+' && b2->sign == '-')
        {
            b2->sign = '+';
            sum = subtractintegers(b1, b2);
            b2->sign = '-';
        }
        else
        {
            b1->sign = '+';
            sum = subtractintegers(b2, b1);
            b1->sign = '-';
        }
    }
    return sum;
}

integer *subtract(integer *b1, integer *b2)
{
    integer *diff = (integer *)malloc(sizeof(integer));
    diff->nums = (int *)malloc(sizeof(int) * (b1->length));
    int carry = 0;
    int sub, j = 0;
    while (j < b2->length)
    {
        sub = b1->nums[j] - b2->nums[j] - carry;
        if (sub < 0)
        {
            carry = 1;
            sub = sub + 10;
        }
        else
        {
            carry = 0;
        }
        diff->nums[j] = sub;
        j++;
    }
    while (j < b1->length)
    {
        sub = b1->nums[j] - carry;
        if (sub < 0)
        {
            carry = 1;
            sub = sub + 10;
        }
        else
        {
            carry = 0;
        }
        diff->nums[j] = sub;
        j++;
    }
    diff->length = j;
    return diff;
}

integer *subtractintegers(integer *b1, integer *b2)
{
    integer *diff = (integer *)malloc(sizeof(integer));
    if (b1->length > b2->length)
    {
        diff->nums = (int *)malloc(sizeof(int) * (b1->length));
    }
    else
    {
        diff->nums = (int *)malloc(sizeof(int) * (b2->length));
    }
    if (b1->sign != b2->sign)
    {
        if (b2->sign == '-')
        {
            b2->sign = '+';
            diff = add(b1, b2);
            b2->sign = '-';
            diff->sign = '+';
        }
        else
        {
            b1->sign = '+';
            diff = add(b1, b2);
            b2->sign = '-';
            diff->sign = '-';
        }
    }
    else   /* SAME SIGN CASE */
    {

        if (compare(b1, b2) > 0)
        {
            diff = subtract(b1, b2);
            diff->sign = b1->sign;
        }
        else
        {
            diff = subtract(b2, b1);
            if (b1->sign == '+')
            {
                diff->sign = '-';
            }
            else
            {
                diff->sign = '+';
            }
        }
    }
    return diff;
}

integer *multiplication(integer *b1, integer *b2)
{
    integer *mul = (integer *)malloc(sizeof(integer));
    mul->length = (b1->length + b2->length);
    mul->nums = (int *)malloc(sizeof(int) * (mul->length));
    int carry;
    int product;
    for (int k = 0; k < mul->length; k++)
    {
        mul->nums[k] = 0;
    }
    int i, j;
    for (i = 0; i < b1->length; i++)
    {
        carry = 0;
        for (j = 0; j < b2->length; j++)
        {
            product = (b1->nums[i] * b2->nums[j]) + carry;
            carry = product / 10;
            mul->nums[i + j] += product % 10;
            if (mul->nums[i + j] > 9)
            {
                mul->nums[i + j + 1] += 1;
                mul->nums[i + j] %= 10;
            }
        }
        while (carry != 0)
        {
            mul->nums[i + j] += (carry % 10);
            if (mul->nums[i + j] > 9)
            {
                mul->nums[i + j + 1] += 1;
                (mul->nums[i + j]) %= 10;
            }
            carry /= 10;
            j++;
        }
    }
    if (b1->sign == b2->sign)
    {
        mul->sign = '+';
    }
    else
    {
        mul->sign = '-';
    }
   
    /* removing zeroes by decreasing the length*/
     j = mul->length - 1;
    while (mul->nums[j] == 0)
    {
        j--;
        (mul->length)--;
    }
    /* special case of zero*num */
    if (mul->length == 0)
    {
        mul->sign = ' ';
        mul->length = 1;
    }
    return mul;
}

int main()
{
    integer b1, b2;
    char s1[MAXSIZE];
    char s2[MAXSIZE];
    printf("Enter the numbers in the given format:\n    Positive numbers starting with +\n    Negative numbers starting with -\n");
    printf("Enter the first number: ");
    fgets(s1, sizeof(s1), stdin);
    while (s1[0] != '+' && s1[0] != '-')
    {
        printf("Enter number in a valid format.\n");
        printf("Enter the first number: ");
        fgets(s1, sizeof(s1), stdin);
    }
    fflush(stdin);
    printf("Enter the second number: ");
    fgets(s2, sizeof(s2), stdin);
    while (s2[0] != '+' && s2[0] != '-')
    {
        printf("Enter number in a valid format.\n");
        printf("Enter the second number: ");
        fgets(s2, sizeof(s2), stdin);
    }
    fflush(stdin);
    b1 = convert_string(s1);
    b2 = convert_string(s2);
    printinteger(&b1);
    printf("\n");
    printinteger(&b2);
    integer *ans = add(&b1, &b2);
    printf("\n");
    printf("SUM OF 2 NUMBERS       : ");
    printinteger(ans);
    printf("\n");
    ans = subtractintegers(&b1, &b2);
    printf("\nDIFFERENCE OF 2 NUMBERS       : ");
    printinteger(ans);
    printf("\n");
    ans = multiplication(&b1, &b2);
    printf("PRODUCT OF 2 NUMBERS         : ");
    printinteger(ans);
    printf("\n");
    fflush(stdin);
    return 0;
}