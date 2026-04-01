int ds_contains(Dynstr *s, const char *needle) {
    return ds_find(s, needle) >= 0;
}

int ds_starts_with(Dynstr *s, const char *prefix) {
    size_t plen = strlen(prefix);
    return plen <= s->len && strncmp(s->data, prefix, plen) == 0;
}

int ds_ends_with(Dynstr *s, const char *suffix) {
    size_t slen = strlen(suffix);
    return slen <= s->len && strcmp(s->data + s->len - slen, suffix) == 0;
}

int ds_replace(Dynstr *s, const char *from, const char *to) {
    size_t flen = strlen(from);
    size_t tlen = strlen(to);
    int count = 0;
    size_t pos = 0;
    Dynstr *tmp = ds_new("");
    while (1) {
        char *found = strstr(s->data + pos, from);
        if (!found) break;
        size_t before = (size_t)(found - (s->data + pos));
        size_t old_len = tmp->len;
        ds_grow(tmp, tmp->len + before + tlen + 1);
        memcpy(tmp->data + tmp->len, s->data + pos, before);
        tmp->len += before;
        tmp->data[tmp->len] = '\0';
        ds_append(tmp, to);
        pos = (size_t)(found - s->data) + flen;
        count++;
        (void)old_len;
    }
    ds_append(tmp, s->data + pos);
    free(s->data);
    s->data = tmp->data;
    s->len  = tmp->len;
    s->cap  = tmp->cap;
    tmp->data = NULL;
    ds_free(tmp);
    return count;
}

Dynstr **ds_split(Dynstr *s, const char *delim, int *count) {
    *count = 0;
    size_t dlen = strlen(delim);
    int n = 1;
    const char *p = s->data;
    while ((p = strstr(p, delim))) { n++; p += dlen; }
    Dynstr **parts = malloc((size_t)(n + 1) * sizeof(Dynstr *));
    if (!parts) return NULL;
    const char *start = s->data;
    int i = 0;
    while (i < n - 1) {
        const char *found = strstr(start, delim);
        size_t seg = (size_t)(found - start);
        char *tmp = malloc(seg + 1);
        memcpy(tmp, start, seg);
        tmp[seg] = '\0';
        parts[i] = ds_new(tmp);
        free(tmp);
        start = found + dlen;
        i++;
    }
    parts[i] = ds_new(start);
    parts[i + 1] = NULL;
    *count = n;
    return parts;
}

void ds_split_free(Dynstr **parts, int count) {
    for (int i = 0; i < count; i++) ds_free(parts[i]);
    free(parts);
}

Dynstr *ds_join(const char *parts[], int count, const char *sep) {
    Dynstr *out = ds_new(NULL);
    for (int i = 0; i < count; i++) {
        if (i > 0 && sep) ds_append(out, sep);
        ds_append(out, parts[i]);
    }
    return out;
}

Dynstr *ds_interpolate(const char *tmpl, const char *keys[], const char *values[]) {
    Dynstr *out = ds_new(NULL);
    const char *p = tmpl;
    while (*p) {
        if (*p == '{') {
            const char *end = strchr(p + 1, '}');
            if (!end) { ds_append_char(out, *p++); continue; }
            size_t klen = (size_t)(end - p - 1);
            int matched = 0;
            for (int i = 0; keys[i]; i++) {
                if (strlen(keys[i]) == klen && strncmp(keys[i], p + 1, klen) == 0) {
                    ds_append(out, values[i]);
                    matched = 1;
                    break;
                }
            }
            if (!matched)
                for (const char *q = p; q <= end; q++) ds_append_char(out, *q);
            p = end + 1;
        } else {
            ds_append_char(out, *p++);
        }
    }
    return out;
}
