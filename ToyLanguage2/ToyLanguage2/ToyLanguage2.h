#pragma once

struct tree {
	char* data;
	struct tree* left;
	struct tree* right;
};
typedef struct tree Tree;
Tree* root;


char* temp;
char* temp_str;

static int operator_count;
static int expression_count;
static int defun_count;

char* defun_file_name;
char* input_file_name;


static int final_result;
static int top;

char* input_line[100];
char* defun_line[100];
char* expression_line[100];
char* defun_name[100];
char* defun_var[100];

char* stack[100];			//stack
int left_or_right[50];		//둘다 비어있을 때 = 1 왼쪽은 있고 오른쪽은 없을 때= 2 둘다있을 때 = 3  


void print_defun();
void define_defun();
int interpreter();

void postorder(Tree* root);
char* Pop();
void Push(char* str);
