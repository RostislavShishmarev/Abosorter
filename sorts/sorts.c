#include <string.h>
#include <stdlib.h>

void swap(void* first, void* second, void* buf, size_t size) {
	memcpy(buf, first, size);
	memcpy(first, second, size);
	memcpy(second, buf, size);
}

void gnome_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg) {
	if (nmemb < 2) {
		return;
	}
	
	size_t i = 0;
	size_t last_i = nmemb - 1;

	void* buf = malloc(size);
	if (buf == NULL) {
		return;
	}

	while (i != last_i) {
		void *first = base + (size * i);
		void *second = base + (size * (i + 1));
		int res = compar(first, second, arg);

		if (res > 0) {
			swap(first, second, buf, size);
			if (i != 0) {
				i -= 1;
			} else {
				i += 1;
			}
		} else {
			i += 1;
		}
	}

	free(buf);
}

void dselect_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg) {
	if (nmemb < 2) {
		return;
	}
	
	size_t first_i = 0;
	size_t last_i = nmemb - 1;
	size_t min_i = first_i;
	size_t max_i = last_i;

	size_t j = 0;

	void* buf = malloc(size);
	if (buf == NULL) {
		return;
	}

	while (first_i < last_i) {
		void *first_el = base + (first_i * size);
		void *last_el = base + (last_i * size);
		void *min_el = base + (min_i * size);
		void *max_el = base + (max_i * size);

		int res = 0;
	
		for (j = first_i; j <= last_i; ++j) {
			void *j_el = base + (j * size);
			res = compar(j_el, min_el, arg);
			if (res <= 0) {
				min_i = j;
				min_el = j_el;
			}

			res = compar(max_el, j_el, arg);
			if (res <= 0) {
				max_i = j;
				max_el = j_el;
			}
		}
		
		if (first_el == max_el) {
			max_el = min_el;
		}
		swap(first_el, min_el, buf, size);
		swap(last_el, max_el, buf, size);

		first_i += 1;
		last_i -= 1;
		min_i = first_i;
		max_i = last_i;
	}

	free(buf);
}

