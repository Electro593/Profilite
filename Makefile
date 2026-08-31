.PHONY: all
all: profiler docs

profiler: profiler.c profiler.h
	$(CC) $(CFLAGS) -O3 -lm -shared $^ -o $@

.PHONY: docs
docs:
	doxygen

.PHONY: clean
clean:
	$(RM) profiler
