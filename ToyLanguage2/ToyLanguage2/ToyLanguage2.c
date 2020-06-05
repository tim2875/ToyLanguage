
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <Windows.h>

#include "ToyLanguage2.h"

int main() {
	defun_file_name = malloc(sizeof(char));
	input_file_name = malloc(sizeof(char));
	
	int result = 0;
	int menu_num;

	while (1) {
		//Sleep(100);
		printf("=====================================\n");
		printf("1. Define DEFUN\n");
		printf("2. Print DEFUN\n");
		printf("3. Interpreter\n");
		printf("4. Exit\n");
		printf("=====================================\n");
		printf("메뉴를 선택하세요 >> ");
		Sleep(100);

		scanf_s("%d", &menu_num);
		getchar();


		if (menu_num == 1) {
			define_defun();
		}
		else if (menu_num == 2) {
			Sleep(100);
			print_defun();
		}

		else if (menu_num == 3) {
			result = interpreter();
		}
		else if (menu_num == 4) {
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		else {
			printf("잘못 입력했습니다.\n");
		}	
	}
}

void define_defun() {
	FILE* file = NULL;
	char* new_defun = malloc(sizeof(char));
	char* temp_defun[100];
	int count = 0;
	char* tmp = malloc(sizeof(char));
	char* tmp1 = malloc(sizeof(char));
	char* tmp2 = malloc(sizeof(char));

	for (int i = 0; i < 100; i++) {
		temp_defun[i] = malloc(sizeof(char));
	}

	
	printf("DEFUN >> ");
	scanf("%[^\n]", new_defun);
	getchar();


	strcpy(tmp, new_defun);
	tmp1 = strtok(tmp, " ")	;

	file = fopen("defun.txt", "rt");
	if (file == NULL) {
		printf("파일이 존재하지 않습니다.");
		return;
	}
	else {
		while (!feof(file)) {
			fgets(temp_defun[count], 100, file);
			count++;
		}
		fclose(file);
			
		for (int i = 0; i < count - 1; i++) {
			strcpy(tmp2, temp_defun[i]);
			tmp2 = strtok(tmp2, " ");
			printf("tmp2 = %s\n", tmp2);
			printf("tmp1 = %s\n", tmp1);

			if (strcmp(tmp2, tmp1) == 0) {
				printf("이미 존재합니다.\n");
				return;
			}
		}
		strcpy(tmp, new_defun);
		tmp2 = strtok(tmp, " ");
		tmp2 = strtok(NULL, " ");
		if (tmp2 == NULL || strcmp(tmp2, "(") != 0) {
			printf("에러입니다.\n");
			return;
		}
	}

	file = fopen("defun.txt", "at");
	if (file == NULL) {
		printf("입력된 파일이 없습니다.\n");
		return;
	}
	else if (file != NULL) {
		fprintf(file, "%s", new_defun);
		fprintf(file, "\n");
	}

	fclose(file);
}


void print_defun() {
	FILE* file = NULL;
	defun_count = 0;
	int len;
	char* expression = malloc(sizeof(char));
	char* name = malloc(sizeof(char));
	char* tmp = malloc(sizeof(char));
	char* tmp2 = malloc(sizeof(char));
	char* tmp3 = malloc(sizeof(char));
	char* tmp4 = malloc(sizeof(char));
	
	for (int i = 0; i < 100; i++) {
		defun_line[i] = malloc(sizeof(char));			//defun이 저장되는 곳
		memset(defun_line[i], 0, 5);
		defun_name[i] = malloc(sizeof(char));			//
		expression_line[i] = malloc(sizeof(char));		//
		defun_var[i] = malloc(sizeof(char));
	}

	 
	file = fopen("defun.txt", "r");
	if (file == NULL) {
		printf("없는 파일입니다.\n");
		return;
	}
	else if(file != NULL){
		while (!feof(file)) {
			fflush(file);
			
			fgets(defun_line[defun_count], 150, file);
			fflush(stdout);
			Sleep(150);
			defun_count++;
			
		
		}


		for (int i = 0; i < defun_count - 1; i++) {
			printf("%s\n", defun_line[i]);
		}

	}
	fflush(file);
	fclose(file);

}


int interpreter() {
	FILE* file = NULL;
	int count = 0;
	char* filename = malloc(sizeof(char));
	char* tmp = malloc(sizeof(char));
	char* tmp2 = malloc(sizeof(char));
	char* tmp3 = malloc(sizeof(char));
	char* tmp4 = malloc(sizeof(char));
	char* tmp5 = malloc(sizeof(char));

	for (int i = 0; i < 100; i++) {
		input_line[i] = malloc(sizeof(char));
	}

	printf("실행 파일명을 입력하세요 >> ");
	scanf("%[^\n]", filename);
	getchar();

	file = fopen(filename, "rt");
	if (file == NULL) {
		printf("파일이 없습니다.\n");
		return -1;
	}
	else {	//파일이 존재할 때
		while (!feof(file)) {
			fgets(input_line[count], 100, file);
			fflush(stdout);
			Sleep(100);
			count++;
		}
		for (int i = 0; i < defun_count-1; i++) {
			strcpy(tmp, defun_line[i]);
			
			strcpy(defun_name[i], strtok(tmp, " "));
			
			strcpy(tmp2 ,strtok(NULL, "("));
			strcpy(defun_var[i], tmp2);

			strcpy(tmp3, defun_line[i]);
			strcpy(tmp3, strtok(tmp3, ")"));

			strcpy(tmp4, defun_line[i]);
			strtok(tmp4, ")");
			tmp5 =strtok(NULL, "\n");
			strcpy(expression_line[i], tmp5);
			printf("%s\n", expression_line[i]);

			fflush(stdout);

		}
		
	}
	fflush(file);
	fclose(file);
	return 1;
}

Tree* GetNode() {
	Tree* tmp;
	tmp = malloc(sizeof(Tree));
	tmp->data = NULL;
	tmp->right = NULL;
	tmp->left = NULL;
	return tmp;
}


Tree* make_tree(Tree* root, char* str, int d, int lor) {

	int depth = d;
	char* sub_str = malloc(sizeof(char));
	left_or_right[depth] = 0;
	left_or_right[depth] = lor;
	strcpy(sub_str, str);

	if (root == NULL && left_or_right[depth] == 0) {
		temp = strtok(sub_str, "() \n");
		root = GetNode();
		root->data = temp;
		left_or_right[depth] = 1;
	}

	while (1) {
		if (left_or_right[depth] == 3) {
			break;
		}

		temp_str = strtok(NULL, "\n");
		temp = strtok(temp_str, "()\n ");

		if (temp == NULL) {
			break;
		}
		else if (root != NULL && left_or_right[depth] == 1) {
			if (root != NULL && strncmp(temp, "-", 1) == 0) {
				root->left = GetNode();
				root->left->data = temp;
				left_or_right[depth] = 2;
			}
			else if (root != NULL && temp[0] <= '9' && temp[0] >= '0') {
				root->left = GetNode();
				root->left->data = temp;
				left_or_right[depth] = 2;
			}
			else if (root != NULL && strcmp(temp, "MINUS") == 0 || strcmp(temp, "IF") == 0) {
				root->left = GetNode();
				root->left->data = temp;
				left_or_right[depth] = 2;
				make_tree(root->left, temp_str, depth + 1, 1);
			}
		}
		else if (root != NULL && left_or_right[depth] == 2) {
			if (strncmp(temp, "-", 1) == 0) {
				root->right = GetNode();
				root->right->data = temp;
				left_or_right[depth] = 3;
			}
			else if (root != NULL && temp[0] <= '9' && temp[0] > '0') {
				root->right = GetNode();
				root->right->data = temp;
				left_or_right[depth] = 3;
			}
			else if (root != NULL && strcmp(temp, "MINUS") == 0 || strcmp(temp, "IF") == 0) {
				root->right = GetNode();
				root->right->data = temp;
				left_or_right[depth] = 3;
				make_tree(root->right, temp_str, depth + 1, 1);
			}
		}
	}
	return root;
}

void Push(char* str) {
	if (str != NULL) {
		top++;
		stack[top] = str;
	}
}

char* Pop() {
	char* str = malloc(sizeof(char));
	if (top >= 0) {
		str = stack[top];
		stack[top] = 0;
		top--;
	}
	else {
		printf("Pop할 것이 없습니다.\n");
	}

	return str;
}


void postorder(Tree* root) {
	if (root == NULL) {
		return;
	}
	char* tmp_str1 = malloc(sizeof(char));
	char* tmp_str2 = malloc(sizeof(char));
	char* buffer = malloc(sizeof(char));
	int temp = 0;

	postorder(root->left);
	postorder(root->right);

	if (root->data != NULL) {
		if (strncmp(root->data, "-", 1) == 0 || root->data[0] <= '9' && root->data[0] > '0') {
			Push(root->data);
		}
		else if (strcmp(root->data, "IF") == 0 || strcmp(root->data, "MINUS") == 0) {
			if (top >= 1) {
				tmp_str2 = Pop();	//2번째 값
				tmp_str1 = Pop();	//1번째 값
			}
			if (strcmp(root->data, "IF") == 0) {
				if (atoi(tmp_str1) > 0) {
					Push(tmp_str2);
				}
				else if (atoi(tmp_str1) <= 0) {
					buffer = "0";
					Push(buffer);
				}
			}
			else if (strcmp(root->data, "MINUS") == 0) {
				temp = atoi(tmp_str1) - atoi(tmp_str2);
				sprintf(buffer, "%d", temp);
				Push(buffer);
			}

		}
	}

}
