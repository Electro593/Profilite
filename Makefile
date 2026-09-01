DOC_INDEX = docs/html/index.html

# CC = clang
CC ?= gcc

CFLAGS += -std=c89 -O3 -Werror -pedantic-errors

ifneq ($(findstring clang,$(shell $(CC) --version 2>&1)),)
	CFLAGS += -Weverything
else
	CFLAGS += -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -Wundef -Wabi
	CFLAGS += -Walloc-zero -Walloca -Wanalyzer-symbol-too-complex -Wanalyzer-too-complex -Wc++-compat
	CFLAGS += -Waggregate-return -Wauto-profile -Warith-conversion -Wbad-function-cast -Wcast-align=strict
	CFLAGS += -Wcast-qual -Wdate-time -Wdisabled-optimization -Wdouble-promotion -Wduplicated-branches
	CFLAGS += -Wduplicated-cond -Wflex-array-member-not-at-end -Wfloat-equal -Wformat-signedness -Wpacked
	CFLAGS += -Winit-self -Winline -Winvalid-pch -Winvalid-utf8 -Wkeyword-macro -Wlogical-op -Wmultichar
	CFLAGS += -Wmissing-declarations -Wmissing-include-dirs -Wmissing-prototypes -Wnested-externs -Wpadded
	CFLAGS += -Wmissing-variable-declarations -Wnull-dereference -Wopenacc-parallelism -Wredundant-decls
	CFLAGS += -Wsuggest-attribute=cold -Wsuggest-attribute=const -Wsuggest-attribute=format -Wtrampolines
	CFLAGS += -Wsuggest-attribute=malloc -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure
	CFLAGS += -Wsuggest-attribute=returns_nonnull -Wsuggest-final-methods -Wsuggest-final-types
	CFLAGS += -Wstack-protector -Wstrict-prototypes -Wswitch-default -Wswitch-enum -Wtrivial-auto-var-init
	CFLAGS += -fstrict-flex-arrays=3 -Wstrict-flex-arrays -Wunsuffixed-float-constants -Wunused-macros
	CFLAGS += -Wuseless-cast -Wvector-operation-performance -Wwrite-strings -Wzero-as-null-pointer-constant
	CFLAGS += -Wsystem-headers

# 	CFLAGS_FIND_WARNS = -Q --help=warning

# 	These are antiquated and incompatible with c23
# 	CFLAGS += -Wtraditional -Wtraditional-conversion

# 	These are false-positives reported for Modula-2
# 	CFLAGS += Wpedantic-cast -Wpedantic-param-names -Wstyle -Wuninit-variable-checking

# 	I couldn't figure out where this one comes from at all
# 	CFLAGS += -Wverbose-unbounded
endif

# CFLAGS += -m32

.PHONY: all
all: docs test

.PHONY: test
test: build/test

.PHONY: docs
docs: $(DOC_INDEX)

build/test: Makefile test.c profilite.h
	mkdir -p build
	$(CC) $(CFLAGS) -E test.c -o $@.i
	$(CC) $(CFLAGS) test.c -o $@
	@if [ "$(CFLAGS_FIND_WARNS)" != "" ]; then \
		$(CC) $(CFLAGS) $(CFLAGS_FIND_WARNS) test.c | grep '\[disabled\]'; \
	fi

$(DOC_INDEX): Doxyfile profilite.h
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf docs/ build/
