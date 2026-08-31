DOC_INDEX = docs/html/index.html

CFLAGS += -std=c89 -O3 -Wall -Werror -pedantic

.PHONY: all
all: test docs

test: Makefile test.c profilite.h
	$(CC) $(CFLAGS) test.c -o $@

.PHONY: docs
docs: $(DOC_INDEX)

$(DOC_INDEX): Makefile Doxyfile profilite.h
	doxygen Doxyfile

.PHONY: clean
clean:
	$(RM) -rf docs/
	$(RM) test
