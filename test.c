#include <stdio.h>
#include "dynlist.h"

typedef struct
{
    char* name;
    int age;
} Student;

static void 
run_struct_test() 
{
    printf("===================== RUNNING STRUCT TESTS =============================");
    Student s1 = 
    {
        .name = "bob doe",
        .age = 69
    };
    Student s2 = 
    {
        .name = "john doe",
        .age = 96
    };

    dlist students = DLIST_CREATE(Student, 3);

    DLIST_PUSH(&students, Student, s1);
    DLIST_PUSH(&students, Student, s2);

    for (size_t i = 0; i < students.count; i++) 
    {
        Student* data = DLIST_GET(&students, i);
        printf("Data: %d\n", data->age);
        printf("Data: %s\n", data->name);
    }

    free_dlist(&students);
}

static void
run_int_test()
{
    printf("===================== RUNNING INT TESTS ================================");
    dlist ints = DLIST_CREATE(int, 10);
    for (size_t i = 0; i < 10; i++) 
    {
        DLIST_PUSH(&ints, int, i);
    }

    for (size_t i = 0; i < 10; i++) 
    {
        int* val = DLIST_GET(&ints, i);
        printf("%d\n", *val);
    }
    free_dlist(&ints);
}

static void 
run_pointer_test()
{
    printf("===================== RUNNING POINTER TESTS ================================");
    dlist ptrs = DLIST_CREATE(void*, 10);
    int x = 1;

    for (size_t i = 0; i < 10; i++)
    {
        DLIST_PUSH_PTR(&ptrs, void*, &x);
    }

    for (size_t i = 0; i < 10; i++)
    {
        int* data = DLIST_GET(&ptrs, i);
        printf("%d\n", *data);
    }
}

int 
main() 
{
    run_struct_test();
    run_int_test();
    run_pointer_test();
    return 0;
}