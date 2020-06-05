#pragma once

struct tree {
	char* data;
	struct tree* left;
	struct tree* right;
};
typedef struct tree Tree;

Tree* root;

static int operator_count;
static int expression_count;
static int integer_count;
static int left_count;
static int right_count;
static int minus_count;
static int operand_count;


char* file_name;
int menu_num;
static int final_result;

char* temp;
char* temp_str;

char* input_line[100];		
char* stack[100];			//stack

static int input_index;
static int top;				

char* interactive_line;
int left_or_right[50];		//둘다 비어있을 때 = 1 왼쪽은 있고 오른쪽은 없을 때= 2 둘다있을 때 = 3  



int interactive_mode();
void file_load();
Tree* GetNode();
Tree* make_tree(Tree* root, char* str, int d, int lor);
void print_tree(Tree* root);
void postorder(Tree* root);
void Push(char* str);
char* Pop();
int check_line(char* str);