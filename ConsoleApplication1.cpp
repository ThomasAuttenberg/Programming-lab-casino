// STRUCTS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <math.h>
typedef struct DATE DATE;
typedef struct USER USER;
#define any_place -1;



struct DATE {
	int YY, MM, DD, h, min, sec;
};

struct USER {

	char surname[100];
	float balance;
	DATE date;
};

int MAX_ID = 10000;
USER person[10000];
int id_counter = 0;
int id_using_list[10000];

int is_id_free(int id) {

	if (id_using_list[id] == 0) return 1;
	else return 0;

}


int insert_in_list(USER new_user, int user_id) {
	if (user_id == -1) {
		for (int i = 0; i < MAX_ID; i++) {
			if (id_using_list[i] == 0) {
				user_id = i;
				break;
			}
		}
	}
	if (user_id != -1)
		if (id_using_list[user_id] == 0) person[user_id] = new_user;
		else return -1;

	return user_id;
}

void delete_from_list(user_id) {
	id_using_list[user_id] = 0;
}

void add_to_balance(int id, float amount) {
	person[id].balance += amount;
}
void reduce_balance(int id, float amount) {
	person[id].balance -= amount;
}
void set_balance(int id, float amount) {
	person[id].balance = amount;
}
void update_date(int id, DATE new_date) {
	person[id].date = new_date;
}

int download() {
	FILE* fp;
	if ((fp = fopen("base", "r")) == NULL) return 0;
	int id;
	int id_max;
	fscanf(fp, "%d", &id_max);
	for (int i = 1; i <= id_max; i++) {
		fscanf(fp, "\nid=[%d]\n", &id);
		id_using_list[id] = 1;
		fscanf(fp, "%s%f\n[%d.%d.%d] %d:%d:%d", &person[id].surname, &person[id].balance, &person[id].date.DD, &person[id].date.MM, &person[id].date.YY, &person[id].date.h, &person[id].date.min, &person[id].date.sec);
	}
	fclose(fp);
	return 1;
}
int upload() {
	FILE* fp;
	if ((fp = fopen("base", "w")) == NULL) return 0;
	int counter = 0;
	for (int i = 0; i < MAX_ID; i++) {
		if (id_using_list[i] == 0) continue;
		counter++;
	}
	fprintf(fp, "%d", counter);
	for (int id = 0; id < MAX_ID; id++) {
		if (id_using_list[id] == 0) continue;
		fprintf(fp, "\nid=[%d]\n%s\n%.2f\n[%d.%d.%d] %d:%d:%d", id, person[id].surname, person[id].balance, person[id].date.DD, person[id].date.MM, person[id].date.YY, person[id].date.h, person[id].date.min, person[id].date.sec);
	}
	fclose(fp);
	return 1;
}

int edit(int id, struct tm* timing) {
	int buffer;
	float rebalance;
	while (1) {
		buffer = 0;
		system("cls");
		printf(" [Меню] \n\n 1) Изменение баланса \n 2) Обновить дату последней активности\n 3) Удалить пользователя\n 4) Назад\n\n");
		scanf("%d", &buffer);
		switch (buffer) {
		case 1:
			system("cls");
			buffer = 0;
			printf(" Пользователь id %d | Баланс = %.2f\n\n 1) Добавить средства\n 2) Снять средства\n 3) Установить баланс\n\n", id, person[id].balance);
			scanf("%d", &buffer);
			switch (buffer) {
			case 1:
				printf(" Введите сумму: ");
				scanf("%f", &rebalance);
				person[id].balance += rebalance;
				break;
			case 2:
				printf(" Введите сумму: ");
				scanf("%f", &rebalance);
				person[id].balance -= rebalance;
				break;
			case 3:
				printf(" Введите сумму: ");
				scanf("%f", &rebalance);
				person[id].balance = rebalance;
				break;
			}
			person[id].date.YY = timing->tm_year + 1900;
			person[id].date.MM = timing->tm_mon + 1;
			person[id].date.DD = timing->tm_mday;
			person[id].date.h = timing->tm_hour;
			person[id].date.min = timing->tm_min;
			person[id].date.sec = timing->tm_sec;
			printf("\n\n [Операция проведена!]");
			_getch();
			break;
		case 2:
			printf(" Введите время в формате DD.MM.YY H:MIN:SEC\n");
			scanf("%d.%d.%d %d:%d:%d", &person[id].date.DD, &person[id].date.MM, &person[id].date.YY, &person[id].date.h, &person[id].date.min, &person[id].date.sec);
			printf("\n\n [Время последней активности изменено]");
			_getch();
			break;
		case 3:
			delete_from_list(id);
			printf("\n [Операция проведена!]");
			_getch();
			return 3;
			break;
		case 4:
			return 0;
			break;
		}
	}
}

int get_length(char* s) {
	int count = 0;
	while (1) {
		if (s[count] == '\0' || s[count] == '\n') break;
		else {
			count++;
		}
	}
	return count;
}
int alphabet_sort(char* s1, char* s2) { //возвращает 1, если s1 по алфавиту должен стоять раньше, иначе 0
	if (s1[0] - '0' == s2[0] - '0') {
		if (get_length(s1) <= 1 && get_length(s2) <= 1)
			return 0;
		else
			if (get_length(s1) <= 1) return 0;
			else
				if (get_length(s2) <= 1) return 1;
				else
					return alphabet_sort((s1 + 1), (s2 + 1));
	}
	else {
		if (s1[0] - '0' < s2[0] - '0') {
			return 0;
		}
		else {
			return 1;
		}
	}
}
int alphabet_find(char* s1, char* s2) { //возвращает 1, если s1 по алфавиту должен стоять раньше, иначе 0
	int count = 0;
	if (s1[0] - '0' == s2[0] - '0') {
		if (get_length(s1) <= 1 && get_length(s2) <= 1)
			return 1;
		else
			if (get_length(s1) <= 1) return 1;
			else
				if (get_length(s2) <= 1) return 1;
				else
					return alphabet_find((s1 + 1), (s2 + 1));
	}
	else {
		return 0;
	}
}
USER buf_person[10000];
USER* get_sorted_users(int type, int* size) { //1 - Баланс (уб) 2 - Баланс (воз) 3 - По алфавиту
	int count = 0;
	USER buffer;
	unsigned long int T_time[2];
	for (int i = 0; i < MAX_ID; i++) {
		if (id_using_list[i]) {
			buf_person[count] = person[i];
			count++;
		}
	}
	if (type == 1) {
		for (int i = 0; i < count - 1; i++) {
			for (int j = i + 1; j < count; j++) {
				if (buf_person[i].balance < buf_person[j].balance) {
					buffer = buf_person[i];
					buf_person[i] = buf_person[j];
					buf_person[j] = buffer;
				}
			}
		}
	}
	if (type == 2) {
		for (int i = 0; i < count - 1; i++) {
			for (int j = i + 1; j < count; j++) {
				if (buf_person[i].balance > buf_person[j].balance) {
					buffer = buf_person[i];
					buf_person[i] = buf_person[j];
					buf_person[j] = buffer;
				}
			}
		}
	}
	if (type == 3) {
		for (int i = 0; i < count - 1; i++) {
			for (int j = i + 1; j < count; j++) {
				if (alphabet_sort(buf_person[i].surname, buf_person[j].surname)) {
					buffer = buf_person[i];
					buf_person[i] = buf_person[j];
					buf_person[j] = buffer;
				}
			}
		}
	}
	if (type == 4) {
		for (int i = 0; i < count - 1; i++) {
			T_time[0] = (unsigned long int)(buf_person[i].date.YY - 1900) * 31536000;
			T_time[0] += (unsigned long int)(buf_person[i].date.MM - 1) * 2648400;
			T_time[0] += (unsigned long int)(buf_person[i].date.DD) * 86400;
			T_time[0] += (unsigned long int)(buf_person[i].date.h) * 3600;
			T_time[0] += (unsigned long int)(buf_person[i].date.min) * 60;
			T_time[0] += (unsigned long int)(buf_person[i].date.sec);
			for (int j = i + 1; j < count; j++) {
				T_time[1] = (unsigned long int)(buf_person[j].date.YY - 1900) * 31536000;
				T_time[1] += (unsigned long int)(buf_person[j].date.MM - 1) * 2648400;
				T_time[1] += (unsigned long int)buf_person[j].date.DD * 86400;
				T_time[1] += (unsigned long int)buf_person[j].date.h * 3600;
				T_time[1] += (unsigned long int)buf_person[j].date.min * 60;
				T_time[1] += (unsigned long int)buf_person[j].date.sec;
				if (T_time[0] < T_time[1]) {
					buffer = buf_person[i];
					buf_person[i] = buf_person[j];
					buf_person[j] = buffer;
				}
			}
		}
	}
	printf("Сортировка произведена");
	*size = count;
	return (buf_person);
}
USER* search_in_list(int type, int* size) {
	int count = 0;
	int buffer;
	unsigned long int min_r = 100000000;
	int id_founded;
	USER pers1;
	char buffer_s[100];
	unsigned long int T_time[2];
	switch (type) {

	case 5:
		printf("Введите баланс: ");
		scanf("%d", &buffer);
		printf("\n\n");
		for (int i = 0; i < MAX_ID; i++) {
			if (id_using_list[i]) {
				if (abs(person[i].balance == buffer)) {
					id_founded = i;
					break;
				}
				if (abs(person[i].balance - buffer) < min_r) {
					id_founded = i;
					min_r = person[i].balance;
				}
			}
		}

		count = 1;
		buf_person[0] = person[id_founded];
		break;
	case 6:
		printf("Введите id: ");
		scanf("%d", &buffer);
		printf("\n\n");
		if (id_using_list[buffer]) {
			buf_person[0] = person[buffer];
			count = 1;
		}
		break;
	case 7:
		printf("Введите фамилию или ее часть: ");
		scanf("%s", &buffer_s);
		count = 0;
		for (int i = 0; i < MAX_ID; i++) {
			if (id_using_list[i]) {
				if (alphabet_find(buffer_s, person[i].surname) != 0) {
					buf_person[count] = person[i];
					count++;
				}
			}
		}
		break;
	case 8:

		count = 1;
		printf(" \nВведите время в формате DD.MM.YY H:MIN:SEC\n");
		scanf("%d.%d.%d %d:%d:%d", &pers1.date.DD, &pers1.date.MM, &pers1.date.YY, &pers1.date.h, &pers1.date.min, &pers1.date.sec);
		T_time[0] = (unsigned long int)(pers1.date.YY - 1900) * 31536000;
		T_time[0] += (unsigned long int)(pers1.date.MM - 1) * 2648400;
		T_time[0] += (unsigned long int)pers1.date.DD * 86400;
		T_time[0] += (unsigned long int)pers1.date.h * 3600;
		T_time[0] += (unsigned long int)pers1.date.min * 60;
		T_time[0] += (unsigned long int)pers1.date.sec;
		for (int i = 0; i < MAX_ID; i++) {
			T_time[1] = (unsigned long int)(person[i].date.YY - 1900) * 31536000;
			T_time[1] += (unsigned long int)(person[i].date.MM - 1) * 2648400;
			T_time[1] += (unsigned long int)person[i].date.DD * 86400;
			T_time[1] += (unsigned long int)person[i].date.h * 3600;
			T_time[1] += (unsigned long int)person[i].date.min * 60;
			T_time[1] += (unsigned long int)person[i].date.sec;
			if (T_time[0] == T_time[1]) {
				buf_person[0] = person[i];
				break;
			}
			if (abs(T_time[0] - T_time[1]) < min_r) {
				min_r = abs(T_time[0] - T_time[1]);
				buf_person[0] = person[i];
			}
		}
		break;
	}




	*size = count;
	return (buf_person);
}
int main()
{
	system("CHCP 1251");
	system("cls");
	setlocale(LC_ALL, "Russian");
	const time_t timer = time(NULL);
	struct tm* timing = localtime(&timer);
	FILE* fp;
	USER* user_ptr;
	USER new_user;
	for (int i = 0; i < MAX_ID; i++) {
		id_using_list[i] = 0;
	}
	int buffer;
	int choose;
	int id_using_list_[10000];
	int id_;
	int size;
	int flag = 0;
	while (1) {
		system("cls");
		printf(" [ Меню ]:\n 1) Загрузка БД\n 2) Выгрузка БД\n 3) Просмотр данных\n 4) Создание нового пользователя\n 5) Управление данными\n");
		scanf_s("%d", &choose);
		switch (choose) {
		case 1:
			buffer = download();
			if (!buffer) printf("\n\n[Warning] Ошибка при чтении файла! Создайте файл 'base' ");
			printf("Успешно завершено!", id_using_list[2]);
			_getch();
			break;
		case 2:
			if ((fp = fopen("base", "w")) == NULL)
			{
				buffer = 0;
				fclose(fp);
			}
			else
				buffer = 1;
			if (!buffer) printf("\n\n[Warning] Ошибка при записи файла! Создайте файл 'base' ");
			else {
				upload();
				printf("Успешно завершено!");
			}
			_getch();
			break;
		case 3:

			system("cls");
			printf(" Без сортировки: 0\n\n\nСортировка:\n 1) По балансу (убывание)\n 2) По балансу (возрастание)\n 3) По алфавиту\n 4) По дате посл. активности\n\n\n Найти:\n 5) По балансу\n 6) По id\n 7) По фамилии\n");
			scanf("%d", &buffer);
			switch (buffer) {
			case 0:
				for (int i = 0; i < MAX_ID; i++) {
					if (id_using_list[i] == 1) {
						printf("\n[id = %d] | Surname = %s | Balance = %.2f | Last Activity: [%d.%d.%d] %d:%d:%d", i, person[i].surname, person[i].balance, person[i].date.DD, person[i].date.MM, person[i].date.YY, person[i].date.h, person[i].date.min, person[i].date.sec);
					}
				}
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				user_ptr = get_sorted_users(buffer, &size);
				for (int i = 0; i < size; i++) {
					printf("\n[id = %d] | Surname = %s | Balance = %.2f | Last Activity: [%d.%d.%d] %d:%d:%d", i, user_ptr[i].surname, user_ptr[i].balance, user_ptr[i].date.DD, person[i].date.MM, user_ptr[i].date.YY, user_ptr[i].date.h, user_ptr[i].date.min, user_ptr[i].date.sec);
				}
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				user_ptr = search_in_list(buffer, &size);
				for (int i = 0; i < size; i++) {
					printf("\n[id = %d] | Surname = %s | Balance = %.2f | Last Activity: [%d.%d.%d] %d:%d:%d", i, user_ptr[i].surname, user_ptr[i].balance, user_ptr[i].date.DD, person[i].date.MM, user_ptr[i].date.YY, user_ptr[i].date.h, user_ptr[i].date.min, user_ptr[i].date.sec);
				}
				break;
			}
			_getch();
			break;
		case 4:
			system("cls");
			printf("Введите фамилию пользователя: ");
			scanf("%s", &new_user.surname);
			printf("\nВведите текущий баланс пользователя: ");
			scanf("%f", &new_user.balance);
			new_user.date.YY = timing->tm_year + 1900;
			new_user.date.MM = timing->tm_mon;
			new_user.date.DD = timing->tm_mday;
			new_user.date.h = timing->tm_hour;
			new_user.date.min = timing->tm_min;
			new_user.date.sec = timing->tm_sec;
			buffer = insert_in_list(new_user, -1);
			id_using_list[buffer] = 1;
			printf("\n\nПользователь создан (id = %d)", buffer);
			_getch();
			break;
		case 5:

			while (1) {
				system("cls");
				printf("Введите id пользователя или -1 для выхода: ");
				scanf("%d", &buffer);
				if (buffer == -1) break;
				if (!is_id_free(buffer)) {
					int id_ = edit(buffer, timing);
					if (id_ == 3) break;
				}
				else {
					system("cls");
					printf("\n\n Пользователя с заданным id не существует.");
					_getch();
				}
			}
			break;
		}
	}


}