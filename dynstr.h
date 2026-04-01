int     ds_contains(Dynstr *s, const char *needle);
int     ds_starts_with(Dynstr *s, const char *prefix);
int     ds_ends_with(Dynstr *s, const char *suffix);
int     ds_replace(Dynstr *s, const char *from, const char *to);
Dynstr **ds_split(Dynstr *s, const char *delim, int *count);
void    ds_split_free(Dynstr **parts, int count);
Dynstr *ds_join(const char *parts[], int count, const char *sep);
Dynstr *ds_interpolate(const char *tmpl, const char *keys[], const char *values[]);
