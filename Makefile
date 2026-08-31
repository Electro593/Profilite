DOC_INDEX = docs/html/index.html

CFLAGS += -std=c23 -O3

.PHONY: all
all: test docs

test: test.c profilite.h
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: docs
docs: $(DOC_INDEX)

$(DOC_INDEX): Doxyfile profilite.h
	doxygen Doxyfile

.PHONY: clean
clean:
	$(RM) -rf docs/
	$(RM) test
