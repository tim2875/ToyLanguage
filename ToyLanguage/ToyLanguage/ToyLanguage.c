
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


#include "ToyLanguage.h"

int main() {
	file_name = malloc(sizeof(char));
	
	int check = 0;
	int result;



	while (1) {

		printf("=====================================\n");
		printf("1. File Load\n");
		printf("2. Interactive Mode\n");
		printf("3. Exit\n");
		printf("=====================================\n");
		printf("메뉴를 선택하세요 >> ");
		scanf_s("%d", &menu_num);
		getchar();
		
		switch (menu_num) {
		case 1:
			file_load();
			break;
		case 2:
			result = interactive_mode();
			if (result != -200000) {
				printf("결과 : %d\n", result);
			}
			break;

		case 3:
			printf("프로그램을 종료합니다.\n");
			free(root);
			return 0;
			break;
		default:
			printf("잘못 입력했습니다.\n");
		}
	}
	return 0;
}

void file_load() {
	FILE* file = NULL;
	input_index = 0; 
	Tree* root = NULL;
	char* str = malloc(sizeof(char));
	int check = 0;

	for (int i = 0; i < 100; i++) {
		input_line[i] = malloc(sizeof(char));
	}

	while (1) {
		printf("파일명을 입력하세요 >> ");
		scanf_s("%s", file_name, 40);
		getchar();

		file = fopen(file_name, "rt");

		if (file == NULL) {
			printf("없는 파일입니다. 다시 입력하세요.\n");
			continue;
		}
		else {
			break;
		}
	}
	if (file != NULL) {
		while (!feof(file)) {                                   //1개가 추가로 더 저장됨
			fgets(input_line[input_index], 100, file);

			input_index++;
		}
		fclose(file);
		printf("파일 내용과 결과는\n---------------------------------\n");
		

		for (int a = 0; a < input_index; a++) {
			root = NULL;
			top = -1;
			operator_count = 0, expression_count = 0;

			strcpy(str, input_line[a]);
			str = strtok(str, "\n");
			check = check_line(str);

			
			
			if (check == 0) {
				continue;
			}
			else if(check == 1){
				root = make_tree(root, input_line[a], 0, 0);	//트리 생성
				operator_count = 0, expression_count = 0;

				print_tree(root);
				for (int i = 0; i < operator_count; i++) {		//남은 ) 출력
					printf(")");
				}
				postorder(root);
				if (stack[0] != NULL) {
					final_result = atoi(stack[0]);
				}
				printf("\n 결과 : %d\n", final_result);
			}
		}
		printf("---------------------------------\n입니다.\n\n");
	}
	

}


int interactive_mode() {
	Tree* root = NULL;
	top = -1;
	interactive_line = malloc(sizeof(char));
	temp = malloc(sizeof(char));
	temp_str = malloc(sizeof(char));
	int check = 0;

	printf("문장을 입력하세요.\n");
	printf("---------------------------------\n");
	scanf("%[^\n]", interactive_line);
	getchar();

	check = check_line(interactive_line);
	if (check == 1) {
		root = make_tree(root, interactive_line, 0, 0);
		postorder(root);
		if (stack[0] != NULL) {
			final_result = atoi(stack[0]);
		}
	}
	else {
		final_result = -200000;
	}
	return final_result;
}

void print_tree(Tree* root) {
	if (root == NULL) {
		return;
	}

	char* buffer = malloc(sizeof(char));
	int temp = 0;


	if (root->data != NULL) {
		if (strncmp(root->data, "-", 1) == 0 || root->data[0] <= '9' && root->data[0] > '0') {
			if (operator_count > expression_count) {
				printf(" %s", root->data);
				expression_count++;
			}
			else if (operator_count == expression_count) {
				printf(" %s)", root->data);
				expression_count--;
				operator_count--;
			}
		}
		else if (strcmp(root->data, "IF") == 0 || strcmp(root->data, "MINUS") == 0) {
	
			if (operator_count > expression_count) {
				expression_count++;
			}
				printf(" (%s", root->data);
				operator_count++;
		}
	}
	print_tree(root->left);
	print_tree(root->right);
}



Tree* GetNode() {
	Tree* tmp;
	tmp = malloc(sizeof(Tree));
	tmp->data = NULL;
	tmp->right = NULL;
	tmp->left = NULL;
	return tmp;
}

int check_line(char* str) {				//0일 경우 오류, 1일 경우 오류 x
	int len;
	int check = 1;

	integer_count = 0;
	left_count = 0;
	right_count = 0;
	operator_count = 0;
	operand_count = 0;
	expression_count = 0;
	minus_count = 0;

	if (str != NULL) {
		len = strlen(str);
		for (int a = 0; a < len; a++) {
			if (str[a] != 0 && str[a] == ' ') {
				continue;
			}
			else if (str[a] == '(') {
				left_count++;
			}
			else if (a == 0 && str[a] != '(') {
				printf(str);
				printf("\n\"(\"가 누락되었습니다.\n");
				check = 0;
				break;
			}
			else if (str[a] == ')') {
				if (left_count <= right_count) {
					printf(str);
					printf("\n\")\"을 잘못 사용하셨습니다.\n");
					check = 0;
					break;
				}
				else if (expression_count == operator_count && operand_count < operator_count) {
					right_count++;
					if (left_count == right_count && operand_count != operator_count) {
						printf(str);
						printf("\n\")\"의 위치가 잘못되었습니다.\n");
						check = 0;
						break;
					}
				}
				else if (operator_count == expression_count  && operand_count == operator_count && left_count > right_count) {
					right_count++;
					continue;
				}
			}
			else if (str[a] == '0') {
				if (integer_count == 1) {
					if (str[a + 1] != 0 && str[a + 1] == ' ') {
						integer_count = 0;
					}
				}
				else if (integer_count == 0 && str[a + 1] != 0) {
					if (str[a + 1] == ' ') {
						expression_count++;
					}
					else if (str[a + 1] >= '0' && str[a + 1] <= '9') {
						printf(str);
						printf("\nerror : 잘못된 숫자 표기법입니다\n");
						check = 0;
						break;
					}
				}
				else if (str[a + 1] != 0 && str[a + 1] == '.') {
					if (str[a + 2] != 0 && str[a + 2] >= '0' && str[a + 2] <= '9') {
						printf(str);
						printf("\nerror : 실수입니다\n");
						check = 0;
						break;
					}
					else {
						printf(str);
						printf("\nerror : 잘못된 표기법입니다.\n");
						check = 0;
						break;
					}
				}
			}
			else if (str[a] <= '9' && str[a] > '0') {
				if (left_count == 0) {
					if (left_count == 0) {
						printf(str);
						printf("\n\"(\"가 존재하지 않습니다.");
						check = 0;
						break;
					}
				}
				else if (operator_count > expression_count) {
					if (str[a + 1] != 0 && str[a + 1] == ' ') {
						if (minus_count != 0)
							minus_count = 0;
						expression_count++;
						integer_count = 0;
					}
					else if (str[a + 1] <= '9' && str[a + 1] > '0') {
						continue;
					}
					else if (str[a + 1] != 0 && str[a + 1] == ')') {
						printf(str);
						printf("\n\")\"의 위치가 잘못되었습니다.\n");
						check = 0;
						break;
					}
				}
				else if (operator_count == expression_count) {
					if (operand_count == operator_count) {
						printf(str);
						printf("\n\"MINUS 혹은 IF가 존재하지 않습니다.\"\n");
						check = 0;
						break;
					}
					else if (operand_count != operator_count) {
						if (str[a + 1] != 0 && (str[a + 1] == ' ' || str[a + 1] == ')')) {
							operand_count++;
						}
						else if (str[a + 1] != 0 && str[a + 1] <= '9' && str[a + 1] >= '0') {
							continue;
						}
					}
				}
			}
			else if (str[a] == 'M') {
				if (operator_count == left_count) {
					printf(str);
					printf("\n\"(\"가 누락되었습니다.\n");
					check = 0;
					break;
				}
				else {
					if (str[++a] != 0 && str[a] == 'I') {
						if (str[++a] != 0 && str[a] == 'N') {
							if (str[++a] != 0 && str[a] == 'U') {
								if (str[++a] != 0 && str[a] == 'S') {
									if (str[++a] != 0 && str[a] == ' ') {
										if (expression_count == operator_count && expression_count != 0) {
											operand_count++;
										}
										else if (expression_count < operator_count) {
											expression_count++;
										}
										operator_count++;
									}
									else {
										printf(str);
										printf("\nundefined\n");
										check = 0;
										break;
									}
								}
								else {
									printf(str);
									printf("\nundefined\n");
									check = 0;
									break;
								}
							}
							else {
								printf(str);
								printf("\nundefined\n");
								check = 0;
								break;
							}
						}
						else {
							printf(str);
							printf("\nundefined\n");
							check = 0;
							break;
						}
					}
					else {
						printf(str);
						printf("\nundefined\n");
						check = 0;
						break;
					}
				}
			}
			else if (str[a] == 'I') {
				if (operator_count == left_count) {
					printf(str);
					printf("\n\"(\"가 누락되었습니다.\n");
					check = 0;
					break;
				}
				else {
					if (str[++a] == 'F') {
						if (str[a + 1] != 0 && str[a + 1] == ' ') {
							if (expression_count == operator_count && expression_count != 0) {
								operand_count++;
							}
							else if (expression_count < operator_count) {
								expression_count++;
							}
							operator_count++;
						}
						else {
							printf(str);
							printf("\nundefined\n");
							check = 0;
							break;
						}
					}
					else {
						printf(str);
						printf("\nundefined\n");
						check = 0;
						break;
					}
				}
			}
			else if (str[a] == '-') {
				if (str[a + 1] != 0) {
					if (minus_count == 0 && str[a+1] != '-') {
						minus_count++;
					}
					else if (minus_count == 0 && str[a+1] == '-') {
						printf(str);
						printf("\n\"-\"가 여러번 사용되었습니다.\n");
						check = 0;
						break;
					}
					else if (minus_count != 0 && (str[a + 1] >= 'A' && str[a + 1] <= 'Z')) {
						printf(str);
						printf("\n잘못된 위치에 알파벳이 위치합니다.\n");
						check = 0;
						break;
					}
					else if (minus_count != 0 && str[a + 1] == '0') {
						printf(str);
						printf("\n\"0\"의 위치가 잘못되었습니다.\n");
						check = 0;
						break;
					}
					else if (minus_count != 0 && str[a + 1] == ')') {
						printf(str);
						printf("\n\")\"의 위치가 잘못되었습니다.\n");
						check = 0;
						break;
					}
					else if (minus_count != 0 && str[a + 1] == '(') {
						printf(str);
						printf("\n\"(\"의 위치가 잘못되었습니다.\n");
						check = 0;
						break;
					}
					else if (minus_count != 0 && (str[a + 1] <= '9' && str[a + 1] > '0')) {
						continue;
					}

				}
			}
			else if ((str[a] >= 'A' && str[a] <= 'Z') && str[a] != 'I' && str[a] != 'M') {
				printf(str);
				printf("\nundefined\n");
				check = 0;
				break;
			}
			else {
				printf(str);
				printf("\nundefined\n");
				check = 0;
				break;
			}
		}
	}
	return check;
}


Tree* make_tree(Tree* root, char* str, int d, int lor){

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
				make_tree(root->left, temp_str, depth+1, 1);
			}
		}
		else if (root != NULL && left_or_right[depth] == 2) {
			if (strncmp(temp, "-", 1) == 0) {
				root->right = GetNode();
				root->right->data = temp;
				left_or_right[depth] = 3;
			}
			else if (root != NULL &&temp[0] <= '9' && temp[0] > '0') {
				root->right = GetNode();
				root->right->data = temp;
				left_or_right[depth] = 3;
			}
			else if (root!= NULL && strcmp(temp, "MINUS") == 0 || strcmp(temp, "IF") == 0) {
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
