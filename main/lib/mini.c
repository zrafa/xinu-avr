/* 
 * <program>   := <statement>
 * <statement> := "if" <paren_expr> <statement>
 *             := "if" <paren_expr> <statement> "else" <statement> 
 *             := "while" <paren_expr> <statement> 
 *             := "do" <statement> "while" <paren_expr> ";" 
 *             := "print" <paren_expr> ";"
 *             := "{" { <statement> } "}" 
 *             := <expr> ";" 
 *             := ";"
 * 
 * <paren_expr> := "(" <expr> ")"
 * <expr>       := <test> 
 *              := <id> "=" <expr> 
 * <test>       := <sum> 
 *              := <sum> "<" <sum>
 * <sum>        := <term> 
 *              := <sum> "+" <term> 
 *              := <sum> "-"  <term> 
 * <term>       := <id>
 *              := <int> 
 *              := <paren_expr> 
 * <id>         := <a_finite_sequence_of_acceptable_symbols>
 * <num>        := <an_unsigned_decimal_integer> 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void syntax_error(char *msg)
{
  fprintf(stderr, "syntax error - %s\n", msg);
  exit(1);
}

/*----------------------------------------------------------------------------*/
/* Tokenizer */

enum
{
  DO_SYM,
  ELSE_SYM,
  IF_SYM,
  WHILE_SYM,
  PRINT_SYM,
  READ_SYM,
  LBRA_SYM,
  RBRA_SYM,
  LPAR_SYM,
  RPAR_SYM,
  PLUS_SYM,
  MINUS_SYM,
  LESS_SYM,
  SEMI_SYM,
  EQUAL_SYM,
  NUM_SYM,
  ID_SYM,
  EOI_SYM
};

char *words[] = {"do", "else", "if", "while", "print", "read", NULL};

int ch = ' ';
void next_ch() { ch = getchar(); }

int num_val;
//char id_name[100];
char id_name[2];

int sym;
void next_sym()
{
again:
  switch (ch)
  {
  case ' ':
  case '\n':
    next_ch();
    goto again;
  case EOF:
  case 'F':
    sym = EOI_SYM;
    break;
  case '{':
    next_ch();
    sym = LBRA_SYM;
    break;
  case '}':
    next_ch();
    sym = RBRA_SYM;
    break;
  case '(':
    next_ch();
    sym = LPAR_SYM;
    break;
  case ')':
    next_ch();
    sym = RPAR_SYM;
    break;
  case '+':
    next_ch();
    sym = PLUS_SYM;
    break;
  case '-':
    next_ch();
    sym = MINUS_SYM;
    break;
  case '<':
    next_ch();
    sym = LESS_SYM;
    break;
  case ';':
    next_ch();
    sym = SEMI_SYM;
    break;
  case '=':
    next_ch();
    sym = EQUAL_SYM;
    break;
  default:
//	printf("s:%d\n",sym);
    if (ch >= '0' && ch <= '9')
    {
      num_val = 0;
      while (ch >= '0' && ch <= '9')
      {
        num_val = num_val * 10 + (ch - '0');
        next_ch();
      }
      sym = NUM_SYM;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
      int i = 0;
      while ((ch >= 'a' && ch <= 'z') || ch == '_' || (ch >= '0' && ch <= '9'))
      {
        id_name[i++] = ch;
        next_ch();
      }
      id_name[i] = '\0';
	printf("s3:%s\n",id_name);
      sym = 0;
      while (words[sym] != NULL && strcmp(words[sym], id_name) != 0) {
        sym++;
	}
      if (words[sym] == NULL)
        sym = ID_SYM;
	printf("s3s:%d\n",sym);
    }
    else
      syntax_error("unknown symbol");
  }
}
/*
void print_tokens()
{
again:
  next_sym();
  switch (sym)
  {
  case DO_SYM:
    printf("DO_SYM \"%s\"\n", id_name);
    goto again;
  case ELSE_SYM:
    printf("ELSE_SYM \"%s\"\n", id_name);
    goto again;
  case IF_SYM:
    printf("IF_SYM \"%s\"\n", id_name);
    goto again;
  case WHILE_SYM:
    printf("WHILE_SYM \"%s\"\n", id_name);
    goto again;
  case PRINT_SYM:
    printf("PRINT_SYM \"%s\"\n", id_name);
    goto again;
  case LBRA_SYM:
    printf("LBRA_SYM\n");
    goto again;
  case RBRA_SYM:
    printf("RBRA_SYM\n");
    goto again;
  case LPAR_SYM:
    printf("LPAR_SYM\n");
    goto again;
  case RPAR_SYM:
    printf("RPAR_SYM\n");
    goto again;
  case PLUS_SYM:
    printf("PLUS_SYM\n");
    goto again;
  case MINUS_SYM:
    printf("MINUS_SYM\n");
    goto again;
  case LESS_SYM:
    printf("LESS_SYM\n");
    goto again;
  case SEMI_SYM:
    printf("SEMI_SYM\n");
    goto again;
  case EQUAL_SYM:
    printf("EQUAL_SYM\n");
    goto again;
  case NUM_SYM:
    printf("NUM_SYM \"%d\"\n", num_val);
    goto again;
  case ID_SYM:
    printf("ID_SYM \"%s\"\n", id_name);
    goto again;
  case EOI_SYM:
    printf("EOI_SYM\n");
    break;
  }
}
*/

/*----------------------------------------------------------------------------*/
/* Parser */

enum
{
  VAR,
  CST,
  ADD,
  SUB,
  LT,
  SET,
  IF,
  IFELSE,
  WHILE,
  DO,
  PRINT,
  EMPTY,
  SEQ,
  EXPR,
  PROG,
  READ
};

typedef struct node
{
  int kind;
  struct node *o1, *o2, *o3;

  union {
    int val;
    //char id[100];
    char id[2];
  };

} node;

struct node nodes[100];
int n_node = 0;

void consume(int expected)
{
  if (sym == expected)
    next_sym();
  else {
	printf("se:%d\n", expected);
    syntax_error("unknown expected");
  }
}

node *new_node(int k)
{
	printf("\nn\n");
  // node *x = malloc(sizeof(node));
  node *x = &nodes[n_node];
  n_node++;

  x->kind = k;
  return x;
}

node *id()
{
  node *x = new_node(VAR);
  strcpy(x->id, id_name);
  next_sym();
  return x;
}

node *num()
{
  node *x = new_node(CST);
  x->val = num_val;
  next_sym();
  return x;
}

node *paren_expr();

node *term()
{
  if (sym == ID_SYM)
    return id();
  else if (sym == NUM_SYM)
    return num();
  else {
	printf("aca30\n");
    return paren_expr();
}
}

node *sum()
{
	printf("aca31\n");
  node *x = term();
  while (sym == PLUS_SYM || sym == MINUS_SYM)
  {
    node *t = x;
    x = new_node(sym == PLUS_SYM ? ADD : SUB);
    next_sym();
    x->o1 = t;
	printf("aca32\n");
    x->o2 = term();
  }
  return x;
}

node *test()
{
	printf("aca33\n");
  node *x = sum();
  if (sym == LESS_SYM)
  {
    node *t = x;
    x = new_node(LT);
    next_sym();
    x->o1 = t;
	printf("aca34\n");
    x->o2 = sum();
  }
  return x;
}

node *expr()
{
  if (sym != ID_SYM)
    return test();

  node *x = test();
  if (x->kind == VAR && sym == EQUAL_SYM)
  {
    node *t = x;
    x = new_node(SET);
    next_sym();
    x->o1 = t;
    x->o2 = expr();
  }
  return x;
}

node *paren_expr()
{
printf("aca6\n");
  consume(LPAR_SYM);
  node *x = expr();
printf("aca7\n");
  consume(RPAR_SYM);

  return x;
}

node *paren_read()
{
	printf("aca51\n");
  consume(LPAR_SYM);
  node *x = id();
  node *y = new_node(SET);
	y->o1 = x;
	y->o2 = new_node(CST);
  y->o2->val = num_val;
	printf("aca2\n");
  consume(RPAR_SYM);

  return y;
}

node *statement()
{
printf("stat:%d\n", sym);
  node *x;
  if (sym == IF_SYM)
  {
    next_sym();
    x = new_node(IF);
	printf("aca20\n");
    x->o1 = paren_expr();
    x->o2 = statement();
    if (sym == ELSE_SYM)
    {
      x->kind = IFELSE;
      next_sym();
      x->o3 = statement();
    }
  }
  else if (sym == WHILE_SYM)
  {
    x = new_node(WHILE);
    next_sym();
	printf("aca21\n");
    x->o1 = paren_expr();
    x->o2 = statement();
  }
  else if (sym == DO_SYM)
  {
    x = new_node(DO);
    next_sym();
    x->o1 = statement();
printf("aca9\n");
    consume(WHILE_SYM);
	printf("aca21\n");
    x->o2 = paren_expr();
printf("aca10\n");
    consume(SEMI_SYM);
  }
  else if (sym == PRINT_SYM)
  {
    x = new_node(PRINT);
    next_sym();
	printf("aca24\n");
    x->o1 = paren_expr();
printf("aca11\n");
    consume(SEMI_SYM);
  }
  else if (sym == READ_SYM)
  {
	printf("aca3\n");
	fflush(0);
    x = new_node(READ);
    next_sym();
    x->o1 = paren_read();
printf("aca12\n");
    consume(SEMI_SYM);
  }
  else if (sym == LBRA_SYM)
  {
    x = new_node(EMPTY);
    next_sym();
    while (sym != RBRA_SYM)
    {
      node *t = x;
      x = new_node(SEQ);
      x->o1 = t;
      x->o2 = statement();
    }
    next_sym();
  }
  else if (sym == SEMI_SYM)
  {
    x = new_node(EMPTY);
    next_sym();
  }
  else
  {
    x = new_node(EXPR);
    x->o1 = expr();
printf("aca13\n");
    consume(SEMI_SYM);
  }

  return x;
}

node *program()
{
  node *x = new_node(PROG);
  x->o1 = statement();
printf("aca14\n");
  consume(EOI_SYM);
  return x;
}

/*
void print_ast(node *x)
{
  switch (x->kind)
  {
  case VAR:
    printf("VAR \"%s\" ", x->id);
    break;
  case CST:
    printf("CST \"%d\" ", x->val);
    break;
  case ADD:
    print_ast(x->o1);
    printf("ADD ");
    print_ast(x->o2);
    break;
  case SUB:
    print_ast(x->o1);
    printf("SUB ");
    print_ast(x->o2);
    break;
  case LT:
    print_ast(x->o1);
    printf("LT ");
    print_ast(x->o2);
    break;
  case SET:
    printf("SET ");
    print_ast(x->o1);
    print_ast(x->o2);
    break;
  case IF:
    printf("IF ");
    print_ast(x->o1);
    print_ast(x->o2);
    break;
  case IFELSE:
    printf("IF ");
    print_ast(x->o1);
    print_ast(x->o2);
    printf("ELSE ");
    print_ast(x->o3);
    break;
  case EXPR:
    printf("EXPR ");
    print_ast(x->o1);
    break;
  case SEQ:
    printf("SEQ ");
    print_ast(x->o1);
    print_ast(x->o2);
    break;
  case PRINT:
    printf("PRINT ");
    print_ast(x->o1);
    break;
  case WHILE:
    printf("WHILE ");
    print_ast(x->o1);
    print_ast(x->o2);
    break;
  case DO:
    printf("DO ");
    print_ast(x->o1);
    printf("WHILE ");
    print_ast(x->o2);
    break;
  case PROG:
    printf("PROG ");
    print_ast(x->o1);
    break;
  case EMPTY:
    printf("EMPTY ");
    break;
  default:
    syntax_error("unknown node");
    break;
  }
}
*/

node *parse()
{
  next_sym();
  node *x = program();
	printf("aca54\n");
  return x;
}

/*----------------------------------------------------------------------------*/
/* Interpreter */

typedef struct list
{
  char *id;
  int value;
  struct list *next;
} list;

list *env;

struct list list_arr[100];
int n_list = 0;

list *get_id(char *id)
{
  for (list *lst = env; lst; lst = lst->next)
    if (strcmp(lst->id, id) == 0)
      return lst;

  return (list *)NULL;
}

void lookup_error(char *id)
{
  fprintf(stderr, "error looking up %s\n", id);
  exit(1);
}

int lookup_value(char *id)
{
  list *pid = get_id(id);
  if (pid)
    return pid->value;

  lookup_error(id);
  return -1;
}

void add_id(char *id, int value)
{
printf("lista3:%s\n",id);
  list *pid = get_id(id);
  if (pid)
  {
printf("lista2:%d\n",value);
    pid->value = value;
    return;
  }

  // list *lst = malloc(sizeof(list));
  list *lst = &list_arr[n_list];
  n_list++;

printf("lista:%d\n",value);
  lst->id = id;
  lst->value = value;
  lst->next = env;
  env = lst;
}

void eval_error()
{
  fprintf(stderr, "semantics error");
  exit(1);
}

int eval_expr(node *x)
{

  switch (x->kind)
  {
  case VAR:
    return lookup_value(x->id);
  case CST:
    return x->val;
  case ADD:
    return eval_expr(x->o1) + eval_expr(x->o2);
  case SUB:
    return eval_expr(x->o1) - eval_expr(x->o2);
  case LT:
    return eval_expr(x->o1) < eval_expr(x->o2);
  case SET:
  {
    node *var = x->o1;
    int val = eval_expr(x->o2);
    add_id(var->id, val);
    return val;
  }
  default:
    eval_error();
    return -1;
  }
}

void eval_statement(node *x)
{
	printf("eval:rafa\n");
    node *var;
    char s[16];
    int val;
  switch (x->kind)
  {
  case PRINT:
    printf("%d\n", eval_expr(x->o1));
    break;
  case READ:
	printf("rafa\n");
    var = x->o1;
	read(0, s, 15);
	s[15]=0;
    val = atoi(s);
    add_id(var->id, val);
    break;
  case IF:
    if (eval_expr(x->o1))
      eval_statement(x->o2);
    break;
  case IFELSE:
    if (eval_expr(x->o1))
      eval_statement(x->o2);
    else
      eval_statement(x->o3);
    break;
  case WHILE:
    while (eval_expr(x->o1))
      eval_statement(x->o2);
    break;
  case DO:
    do
      eval_statement(x->o1);
    while (eval_expr(x->o2));
    break;
  case SEQ:
    eval_statement(x->o1);
    eval_statement(x->o2);
    break;
  case EXPR:
    eval_expr(x->o1);
    break;
  case EMPTY:
    break;
  default:
    eval_error();
  }
}

void eval_program(node *x)
{
  switch (x->kind)
  {
  case PROG:
    eval_statement(x->o1);
    break;
  default:
    eval_error();
  }
}

/*----------------------------------------------------------------------------*/
/* Compiler */

enum
{
  IFETCH,
  ISTORE,
  IPUSH,
  IPOP,
  IADD,
  ISUB,
  ILT,
  IJZ,
  IJNZ,
  IJMP,
  IPRINT,
  IHALT
};

typedef char code;
code *here;

void g(code c) { *here++ = c; }

code *hole() { return here++; }

void fix(code *src, code *dst) { *src = dst - src; }

//char names[100][100], (*namespt)[100] = names;
char names[1][2], (*namespt)[2] = names;

/*
int globals[1000];
void initialize_globals()
{
  for (int i = 0; i < 100; i++)
    globals[i] = -1;
}
*/

int get_index(char *name)
{
  int i;
  for (char(*npt)[2] = names; npt < namespt; npt++)
  {
    i = npt - names;
    if (strcmp(name, names[i]) == 0)
      return i;
  }
  i = namespt++ - names;
  strcpy(names[i], name);
  return i;
}

char sa[16];
void c(node *x)
{
  code *p1, *p2;
  switch (x->kind)
  {
  case VAR:
    g(IFETCH);
    g(get_index(x->id));
    break;
  case CST:
    g(IPUSH);
    g(x->val);
    break;
  case ADD:
    c(x->o1);
    c(x->o2);
    g(IADD);
    break;
  case SUB:
    c(x->o1);
    c(x->o2);
    g(ISUB);
    break;
  case LT:
    c(x->o1);
    c(x->o2);
    g(ILT);
    break;
  case SET:
    c(x->o2);
    g(ISTORE);
    g(get_index(x->o1->id));
    break;
  case READ:
	printf("leemos\n");
	read(0, sa, 10);
	sa[15]=0;
	printf("lee:%d\n",atoi(sa));
//	x->o1->id = atoi(s);
	x->o1->o2->val = atoi(sa);
	printf("lee2:%d\n",x->o1->o2->kind);
        c(x->o1->o2);
	printf("lee3:%d\n",atoi(sa));
        g(ISTORE);
        g(get_index(x->o1->o1->id));
    //c(x->o1);
    //	add_id(x->o1->id, atoi(sa));
    break;
  case IF:
    c(x->o1);
    g(IJZ);
    p1 = hole();
    c(x->o2);
    fix(p1, here);
    break;
  case IFELSE:
    c(x->o1);
    g(IJZ);
    p1 = hole();
    c(x->o2);
    g(IJMP);
    p2 = hole();
    fix(p1, here);
    c(x->o3);
    fix(p2, here);
    break;
  case WHILE:
    p1 = here;
    c(x->o1);
    g(IJZ);
    p2 = hole();
    c(x->o2);
    g(IJMP);
    fix(hole(), p1);
    fix(p2, here);
    break;
  case DO:
    p1 = here;
    c(x->o1);
    c(x->o2);
    g(IJNZ);
    fix(hole(), p1);
    break;
  case PRINT:
    c(x->o1);
    g(IPRINT);
    break;
  case EMPTY:
    break;
  case SEQ:
    c(x->o1);
    c(x->o2);
    break;
  case EXPR:
    c(x->o1);
    g(IPOP);
    break;
  case PROG:
    c(x->o1);
    g(IHALT);
    break;
  }
}

void run(code *object)
{
  //int stack[1000], *sp = stack;
  int stack[200], *sp = stack;
  int globals[100];
//  code object[100], *here = object;
  code *pc = object;
again:
  switch (*pc++)
  {
  case IFETCH:
    *sp++ = globals[*pc++];
    goto again;
  case ISTORE:
    globals[*pc++] = sp[-1];
    goto again;
  case IPUSH:
    *sp++ = *pc++;
    goto again;
  case IPOP:
    --sp;
    goto again;
  case IADD:
    sp[-2] = sp[-2] + sp[-1];
    --sp;
    goto again;
  case ISUB:
    sp[-2] = sp[-2] - sp[-1];
    --sp;
    goto again;
  case ILT:
    sp[-2] = sp[-2] < sp[-1];
    --sp;
    goto again;
  case IJZ:
    if (*--sp == 0)
      pc += *pc;
    else
      pc++;
    goto again;
  case IJMP:
    pc += *pc;
    goto again;
  case IJNZ:
    if (*--sp != 0)
      pc += *pc;
    else
      pc++;
    goto again;
  case IPRINT:
    printf("%d\n", *--sp);
    goto again;
  }
}

/*----------------------------------------------------------------------------*/

int main()
{
  node *prog = parse();

  code object[100];
  here = object;

//  printf("\n--- The abstract syntax code: \n");
//  print_ast(prog);

 // printf("\n--- The interpreter: \n");
//  eval_program(prog);

  //printf("\n--- The virtual machine interpreting the bytecodes: \n");
  c(prog);
  run(object);

  return 0;
}
