// 12S21015 - Sitogab Antonio Octavianus Girsang
// 12S21049 - Jesika Audina Purba

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/dorm.h"
#include "libs/student.h"
#include "libs/repository.h"

int main(int _argc, char **_argv)
{
    
    struct dorm_t *dorms = malloc(100 * sizeof(struct dorm_t));
    struct student_t *students = malloc(100 * sizeof(struct student_t));

    
    char input[100];
    char id[12];
    char student_name[40];
    char year[5];

    
    char dorm_name[40];
    unsigned short capacity;

    
    char *data;
    int idx_s, idx_d;
    int std = 0, dr = 0;

    
    FILE *fd;
    fd = fopen("storage/dorm-repository.txt", "r");

    while (fgets(input, 100, fd) != NULL)
    {
        data = strtok(input, "|");
        strcpy(dorms[dr].name, data);
        data = strtok(NULL, "|");
        capacity = atoi(data);
        dorms[dr].capacity = capacity;
        dorms[dr].residents_num = 0;
        data = strtok(NULL, "|");
        if (strcmp(data, "male") == 0)
        {
            dorms[dr].gender = GENDER_MALE;
        }
        else if (strcmp(data, "female") == 0)
        {
            dorms[dr].gender = GENDER_FEMALE;
        }
        dr++;
        
    }
    fclose(fd);

    
    FILE *fs;
    fs = fopen("storage/student-repository.txt", "r");
    if (fs == NULL)
    {
        NULL;
    }
    while (fgets(input, 100, fs) != NULL)
    {
        data = strtok(input, "|");
        strcpy(students[std].id, data);
        data = strtok(NULL, "|");
        strcpy(students[std].name, data);
        data = strtok(NULL, "|");
        strcpy(students[std].year, data);
        data = strtok(NULL, "|");
        if (strcmp(data, "male") == 0)
        {
            students[std].gender = GENDER_MALE;
        }
        else if (strcmp(data, "female") == 0)
        {
            students[std].gender = GENDER_FEMALE;
        }
        std++;
    }
    fclose(fs);

    
    do
    {
        fflush(stdin);
        input[0] = '\0';
        int c = 0;
        while (1)
        {
            char x = getchar();
            if (x == '\r')
            {
                continue;
            }
            if (x == '\n')
            {
                break;
            }
            input[c] = x;
            input[++c] = '\0';
        }
        data = strtok(input, "#");
        if (strcmp(data, "---") == 0)
        {
            break;
        }
        else if (strcmp(data, "student-print-all") == 0)
        {
            print_student(students, std);
        }
        else if (strcmp(data, "student-print-all-detail") == 0)
        {
            print_student_detail(students, std);
        }
        else if (strcmp(data, "student-add") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(id, data);
            data = strtok(NULL, "#");
            strcpy(student_name, data);
            data = strtok(NULL, "#");
            strcpy(year, data);
            data = strtok(NULL, "#");
            students[std] = create_student(id, student_name, year, data);
            std++;
        }
        else if (strcmp(data, "dorm-print-all") == 0)
        {
            print_dorm(dorms, dr);
        }
        else if (strcmp(data, "dorm-print-all-detail") == 0)
        {
            print_dorm_detail(dorms, dr);
        }
        else if (strcmp(input, "dorm-add") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(dorm_name, data);
            data = strtok(NULL, "#");
            capacity = atoi(data);
            data = strtok(NULL, "#");
            dorms[dr] = create_dorm(dorm_name, capacity, data);
            dr++;
        }
        else if (strcmp(data, "assign-student") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(id, data);
            data = strtok(NULL, "#");
            strcpy(dorm_name, data);
            idx_s = 0;
            idx_d = 0;
            for (int i = 0; i < std; i++)
            {
                if (strcmp(students[i].id, id) == 0)
                {
                    idx_s = i;
                    break;
                }
            }
            for (int i = 0; i < std; i++)
            {
                if (strcmp(dorms[i].name, dorm_name) == 0)
                {
                    idx_d = i;
                    break;
                }
            }
            assign_student(&students[idx_s], &dorms[idx_d], id, dorm_name);
        }
        else if (strcmp(data, "move-student") == 0)
        {
            data = strtok(NULL, "#");
            strcpy(id, data);
            data = strtok(NULL, "#");
            strcpy(dorm_name, data);
            idx_s = 0;
            idx_d = 0;
            for (int i = 0; i < std; i++)
            {
                if (strcmp(students[i].id, id) == 0)
                {
                    idx_s = i;
                    break;
                }
            }
            for (int i = 0; i < dr; i++)
            {
                if (strcmp(dorms[i].name, dorm_name) == 0)
                {
                    idx_d = i;
                    break;
                }
            }
            if (students[idx_s].dorm == NULL)
            {
                assign_student(&students[idx_s], &dorms[idx_d], id, dorm_name);
            }
            else
            {
                for (int i = 0; i < dr; i++)
                {
                    if (strcmp(students[idx_s].dorm->name, dorms[i].name) == 0)
                    {
                        move_student(&students[idx_s], &dorms[idx_d], &dorms[i], id, dorm_name);
                        break;
                    }
                }
            }
        }
    } while (1);
    free(students);
    free(dorms);
    return 0;
}
