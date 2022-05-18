#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "gender.h"
#include "dorm.h"
#include "student.h"

/**
 * @brief define your structure, enums, globally accessible variables, and function prototypes here.
 * The actual function implementation should be defined in the corresponding source file.
 *
 */

struct dorm_t create_dorm(char *_name, unsigned short _capacity, char *_gender);
struct student_t create_student(char *_id, char *_name, char *_year, char *_gender);
#endif
