#include "repository.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dorm_t create_dorm(char *_name, unsigned short _capacity, char *_gender)
{
    FILE *fd;
    fd = fopen("storage/dorm-repository.txt", "r");
    if (fd == NULL)
    {
        printf("File not found\n");
    }
    fprintf(fd, "%s|%d|%s\n", _name, _capacity, _gender);

    struct dorm_t d;
    strcpy(d.name, _name);
    d.capacity = _capacity;
    if (strcmp(_gender, "male") == 0)
    {
        d.gender = GENDER_MALE;
    }
    else if (strcmp(_gender, "male") == 0)
    {
        d.gender = GENDER_FEMALE;
    }
    d.residents_num = 0;
    return d;
}

struct student_t create_student(char *_id, char *_name, char *_year, char *_gender)
{
    FILE *fs;
    fs = fopen("storage/student-repository.txt", "r");
    if (fs == NULL)
    {
        printf("File not found\n");
    }
    fprintf(fs, "%s|%s|%s|%s\n", _id, _name, _year, _gender);
    fclose(fs);
    
    struct student_t s;
    strcpy(s.id, _id);
    strcpy(s.name, _name);
    strcpy(s.year, _year);
    if (strcmp(_gender, "male") == 0)
    {
        s.gender = GENDER_MALE;
    }
    else if (strcmp(_gender, "male") == 0)
    {
        s.gender = GENDER_FEMALE;
    }

    s.dorm = malloc(sizeof(struct dorm_t));
    s.dorm = NULL;
    return s;
}