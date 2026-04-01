#include <stdio.h>
#include "dynstr.h"

int main(void) {
    // test ds_new and ds_append
    Dynstr *str = ds_new("Hello");
    ds_append(str, ", World");
    ds_append_char(str, '!');
    printf("append:      %s\n", str->data);

    // test ds_find
    printf("find 'World': %d\n", ds_find(str, "World"));
    printf("find 'cat':   %d\n", ds_find(str, "cat"));

    // test ds_contains, ds_starts_with, ds_ends_with
    printf("contains 'World':    %d\n", ds_contains(str, "World"));
    printf("starts_with 'Hello': %d\n", ds_starts_with(str, "Hello"));
    printf("ends_with '!':       %d\n", ds_ends_with(str, "!"));

    // test ds_replace
    ds_replace(str, "World", "Neil");
    printf("replace:     %s\n", str->data);
    ds_free(str);

    // test ds_split
    Dynstr *text = ds_new("one,two,three,four");
    int num;
    Dynstr **list = ds_split(text, ",", &num);
    printf("split:       ");
    for (int i = 0; i < num; i++)
        printf("[%s] ", list[i]->data);
    printf("\n");
    ds_split_free(list, num);
    ds_free(text);

    // test ds_join
    const char *words[] = {"one", "two", "three"};
    Dynstr *result = ds_join(words, 3, " | ");
    printf("join:        %s\n", result->data);
    ds_free(result);

    // test ds_interpolate
    const char *keys[]   = {"name", "lang", NULL};
    const char *values[] = {"Neil", "C",    NULL};
    Dynstr *msg = ds_interpolate("Hello {name}, you are coding in {lang}!", keys, values);
    printf("interpolate: %s\n", msg->data);
    ds_free(msg);

    return 0;
}
