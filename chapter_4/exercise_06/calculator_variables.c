#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLINE 500
#define MAXOP 100
#define NUMBER '0'
#define VARGET 'A'
#define VARSET '_'

int getop(char line[], char s[]);
void push(double);
double pop(void);
void print();
void duplicate();
void swap();
void clear();
int is_empty(void);

int getsline(char line[], int lim);

void varset(double n);
double varget(char var);
char var;

int main(void)
{
  int type;
  double op2, last_val;
  char s[MAXOP], line[MAXLINE];

  while (getsline(line[MAXLINE], MAXOP))
  {
    while ((type = getop(line, s)) != EOF)
    {
      switch (type)
      {
      case NUMBER:
        push(atof(s));
        break;

      case VARGET:
        varget(var);
        break;

      case VARSET:
        varset(pop());
        break;

      case '$':
        push(last_val);
        break;

      case '+':
        push(pop() + pop());
        break;

      case '-':
        op2 = pop();
        push(pop() - op2);
        break;

      case '*':
        push(pop() * pop());
        break;

      case '/':
        if ((op2 = pop()) != 0)
        {
          push(pop() / op2);
        }
        else
          printf("error: zero divisor\n");
        break;

      case '%':
        if ((op2 = pop()) != 0)
        {
          push((int)pop() % (int)op2);
        }
        else
          printf("error: zero divisor\n");
        break;

      case '^':
        op2 = pop();
        push(pow(op2, pop()));
        break;

      case '~':
        push(sin(pop()));
        break;

      case 'e':
        push(exp(pop()));
        break;

      case '\n':
        if (!is_empty())
        {
          last_val = pop();
          printf("\t%.8g\n", last_val);
        }
        break;

      case 'p':
        print();
        break;

      case 'd':
        duplicate();
        break;

      case 's':
        swap();
        break;

      case 'c':
        clear();
        break;

      default:
        printf("error: unknown command %s\n", s);
        break;
      }
    }
  }
  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
  if (sp < MAXVAL)
  {
    val[sp++] = f;
  }
  else
  {
    printf("error: stack overflow, can't push %g\n", f);
  }
}

double pop(void)
{
  if (sp > 0)
  {
    return val[--sp];
  }
  else
  {
    printf("error: stack empty\n");
    return 0.0;
  }
}

void print()
{
  if (sp > 0)
  {
    printf("Top element in stack: %.8g\n", val[sp - 1]);
  }
  else
  {
    printf("error: stack empty\n");
  }
}

void duplicate()
{
  if (sp > 0)
  {
    push(val[sp - 1]);
  }
  else
  {
    printf("error: stack empty\n");
  }
}

void swap()
{
  if (sp > 1)
  {
    double op1 = pop();
    double op2 = pop();

    push(op1);
    push(op2);
  }
  else
  {
    printf("error: not enough elements to swap\n");
  }
}

void clear()
{
  if (sp)
  {
    sp = 0;
  }
  else
    printf("error: stack already empty");
}

int is_empty(void)
{
  if (sp > 0)
  {
    return 0;
  }

  return 1;
}

#define MAXVAR 26

double varstack[MAXVAR];
int var_sp;

void varset(double n)
{
  if (var_sp < MAXVAR && n != 0)
  {
    varstack[var_sp++] = n;
    printf("variable %c = %.3f\n", 'A' + var_sp - 1, n);
  }
  else if (var_sp >= MAXVAR)
  {
    printf("error: variable stack overflow\n");
  }
  else
  {
    printf("error: cannot set variable to 0\n");
  }
}

double varget(char var)
{
  if (varstack[var - 'A'])
  {
    push(varstack[var - 'A']);
  }
  else
  {
    printf("error: variable %c not set\n", var);
  }
}

#include <ctype.h>

int getop(char line[], char s[])
{
  int i, c, j;

  while ((s[0] = c = line[j++]) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (isalpha(c) && c <= 'Z')
  {
    var = c;
    return VARGET;
  }

  if (c == '$')
  {
    return c;
  }

  if (!isdigit(c) && c != '.' && c != '-')
  {
    return c;
  }

  i = 0;

  if (c == '-')
  {
    int next = getch();

    if (isdigit(next))
    {
      s[++i] = c = next;
    }
    else if (next != '.')
    {
      if (next != EOF)
      {
        ungetch(next);
      }

      return c;
    }
  }

  if (isdigit(c))
  {
    while (isdigit(s[++i] = c = getch()))
      ;
  }

  if (c == '.')
  {
    while (isdigit(s[++i] = c = getch()))
      ;
  }

  s[i] = '\0';

  if (c != EOF)
  {
    ungetch(c);
  }

  return NUMBER;
}

int getsline(char line[], int lim)
{
  int i = 0, c;

  while (i < lim - 1 && (c = getchar()) != '\n')
  {
    line[i] = c;
    ++i;
  }

  if (c == '\n')
  {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}
