/**
 * \file
 *
 * \version 1.0.0
 *
 * \author Aria Seiler (ariaseiler02@gmail.com)
 *
 * \date August 31, 2026
 */

/**
 * \defgroup configuration Configuration Macros
 *
 * \brief Macros for configuring profiler functionality.
 *
 * \details These can be defined prior to importing this header to configure
 * its functionality. If undefined, default values can be seen as the defined
 * values below. If defined and empty, they are interpreted as 1.
 *
 * All configuration macros must be defined prior to including profilite.h.
 *
 * \{
 */

/**
 * \def PROFILITE
 *
 * \brief Enable the profiler.
 *
 * \details Overrides \ref PROFILITE_HEADER and \ref PROFILITE_IMPLEMENTATION.
 * If unset, all profiler macros and functions will be compiled out.
 *
 * This is a **header** configuration and must be specified any time
 * profilite.h is included. It is recommended to define this in your build
 * system so that it can be enabled/disabled in only one location.
 *
 * Defaults to 0.
 */
#ifndef PROFILITE
#define PROFILITE 0
#else
#if (0 - PROFILITE - 1) == 1 && (PROFILITE - 0) != -2 /* Check empty */
#undef PROFILITE
#define PROFILITE 1
#endif
#endif

/**
 * \def PROFILITE_AUTO_REPORT
 *
 * \brief Enable automatic Profilite_Init() and Profilite_Report() on process
 * start and exit.
 *
 * \details If set, Profilite_Init() will be inserted into the `.init_array`/
 * `.CRT$XCU` sections to automatically execute on process start. Similarly,
 * Profilite_Report() will be inserted into `.fini_array`/`.CRT$XPU` to execute
 * on process termination.
 *
 * This is an **implementation** configuration and should be set in the same
 * file as \ref PROFILITE_IMPLEMENTATION.
 *
 * Defaults to 0.
 *
 * \warning If you use a custom entrypoint, the functions will still be placed
 * into the above sections but will not be executed automatically.
 */
#ifndef PROFILITE_AUTO_REPORT
#define PROFILITE_AUTO_REPORT 0
#else
#if (0 - PROFILITE_AUTO_REPORT - 1) == 1 && (PROFILITE_AUTO_REPORT - 0) != -2 /* Check empty */
#undef PROFILITE_AUTO_REPORT
#define PROFILITE_AUTO_REPORT 1
#endif
#endif

/**
 * \def PROFILITE_HEADER
 *
 * \brief Include the profiler's declarations.
 *
 * \details If set, declarations will be included. This macro is redefined to 0
 * after inclusion to act as a header guard.
 *
 * In most cases, you will not need to set this configuration manually.
 *
 * Defaults to 1.
 */
#ifndef PROFILITE_HEADER
#define PROFILITE_HEADER 1
#else
#if (0 - PROFILITE_HEADER - 1) == 1 && (PROFILITE_HEADER - 0) != -2 /* Check empty */
#undef PROFILITE_HEADER
#define PROFILITE_HEADER 1
#endif
#endif

/**
 * \def PROFILITE_IMPLEMENTATION
 *
 * \brief Include the profiler's definitions.
 *
 * \details If set, definitions will be included. This macro is redefined to 0
 * after inclusion to act as a header guard. You should expect to set this once
 * in your main file.
 *
 * Defaults to 0.
 */
#ifndef PROFILITE_IMPLEMENTATION
#define PROFILITE_IMPLEMENTATION 0
#else
#if (0 - PROFILITE_IMPLEMENTATION - 1) == 1 && (PROFILITE_IMPLEMENTATION - 0) != -2 /* Check empty */
#undef PROFILITE_IMPLEMENTATION
#define PROFILITE_IMPLEMENTATION 1
#endif
#endif

/**
 * \def PROFILITE_STORAGE
 *
 * \brief Configures the storage specifier on all function definitions.
 *
 * \details Use this if you want to make Profilite functions static or inline.
 *
 * Defaults to nothing.
 */
#ifndef PROFILITE_STORAGE
#define PROFILITE_STORAGE
#endif

/**
 * \def PROFILITE_TRADITIONAL
 *
 * \brief Switches definitions to use traditional K&R C syntax.
 *
 * \details Use this if you're, for some strange reason, compiling K&R C.
 *
 * Defaults to 0 if __STDC__ or __STDC_VERSION__ are defined, 1 otherwise.
 */
#ifndef PROFILITE_TRADITIONAL
#if defined(__STDC__) || defined(__STDC_VERSION__) || defined(_PROFILITE_DOXYGEN)
#define PROFILITE_TRADITIONAL 0
#else
#define PROFILITE_TRADITIONAL 1
#endif
#else
#if (0 - PROFILITE_TRADITIONAL - 1) == 1 && (PROFILITE_TRADITIONAL - 0) != -2 /* Check empty */
#undef PROFILITE_TRADITIONAL
#define PROFILITE_TRADITIONAL 1
#endif
#endif

/** \} */

#if PROFILITE || defined(_PROFILITE_DOXYGEN)

#if PROFILITE_HEADER || defined(_PROFILITE_DOXYGEN)
#ifndef _PROFILITE_DOXYGEN
#undef PROFILITE_HEADER
#define PROFILITE_HEADER 0
#endif

/**
 * \defgroup compiler_polyfills Compiler Polyfill Macros
 *
 * \brief Macros for compiler-specific operations.
 *
 * \details These are defined for MSVC, Clang, and GCC. Support for other
 * compilers must be configured by defining these polyfills prior to including
 * this file.
 *
 * \{
 */

/**
 * \def PROFILITE_CLEANUP(Function)
 *
 * \brief Register a function to execute when the following declaration leaves
 * scope.
 *
 * \details Must be a C declaration attribute. Defined for Clang and GCC. Must
 * be defined in order to use \ref scope_helpers.
 */
#ifndef PROFILITE_CLEANUP
#if defined(__GNUC__) || defined(__clang__)
#define PROFILITE_CLEANUP(Function) __attribute__((cleanup(Function)))
#else
#if defined(_MSC_VER)
/* clang-format off */
    #warning PROFILITE_CLEANUP: MSVC is unable to support Profile_*() helpers. Define PROFILITE_CLEANUP prior to inclusion to remove this message and enable them, or use Profilite_WrapScope() instead
/* clang-format on */
#else
/* clang-format off */
    #warning PROFILITE_CLEANUP: Your compiler is unsupported; disabling Profile_*() helpers. Define PROFILITE_CLEANUP prior to inclusion to remove this message and enable them, or use Profilite_WrapScope() instead
/* clang-format on */
#endif
#endif
#endif

/**
 * \def PROFILITE_CONST
 *
 * \brief Alias for `const`.
 *
 * \details May be redefined to disable const. Polyfilled on K&R C as empty.
 */
#ifndef PROFILITE_CONST
#if PROFILITE_TRADITIONAL
#define PROFILITE_CONST
#else
#define PROFILITE_CONST const
#endif
#endif

/**
 * \def PROFILITE_SECTION(Name, ...)
 *
 * \brief Insert the following declaration into the given section.
 *
 * \details Must be a C declaration attribute. Defined for MSVC, Clang, and
 * GCC. Must be defined in order to use \ref PROFILITE_AUTO_REPORT or
 * Profilite_DeclareProfile().
 *
 * \param[in] Name The name of the section to insert into.
 *
 * \param[in] Attributes MSVC-only: The attributes to apply to the created section.
 * Must include `read`, optionally `write`, as a comma-delimited string.
 */
#ifndef PROFILITE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define PROFILITE_SECTION(Name, Attributes) __attribute__((section(Name)))
#else
#if defined(_MSC_VER)
#define _PROFILITE_SECTION(Name, Attributes) _Pragma("section(" Name ", " Attributes ")") __declspec(allocate(Name))
#else
/* clang-format off */
    #error PROFILITE_SECTION: Your compiler is unsupported. Define PROFILITE_SECTION prior to inclusion to remove this error
/* clang-format on */
#endif
#endif
#endif

/**
 * \def PROFILITE_UINTMAX
 *
 * \brief Alias for `unsigned long long int`.
 *
 * \details May be redefined to specify a different base type. Polyfilled on
 * K&R C as `long int` and on unsupported C89 compilers as `unsigned long int`.
 */
#ifndef PROFILITE_UINTMAX
#if defined(__STDC_VERSION__) && __STDC_VERSION__ > 199409L
#define PROFILITE_UINTMAX unsigned long long int
#else
#if defined(__GNUC__) || defined(__clang__)
__extension__ typedef unsigned long long int profilite_uint64;
#define PROFILITE_UINTMAX profilite_uint64
#else
#if defined(_MSC_VER)
#define PROFILITE_UINTMAX unsigned __int64
#else
#if PROFILITE_TRADITIONAL
#define PROFILITE_UINTMAX long int
#else
/* clang-format off */
    #warning PROFILITE_UINTMAX: Your compiler is unsupported; defaulting to `unsigned long int`, which may be 32-bit. Define PROFILITE_UINTMAX prior to inclusion to remove this warning
/* clang-format on */
#define PROFILITE_UINTMAX unsigned long int
#endif
#endif
#endif
#endif
#endif

/** \} */

struct profilite_profile
{
    PROFILITE_CONST char *FileName;
    PROFILITE_CONST char *FunctionName;
    PROFILITE_CONST unsigned int Line;
    PROFILITE_CONST unsigned int Id;

    PROFILITE_CONST char *Name;
    PROFILITE_UINTMAX DataSize;

    PROFILITE_UINTMAX Elapsed;
    PROFILITE_UINTMAX RootElapsed;
    PROFILITE_UINTMAX HitCount;
};

struct profilite_scope
{
    struct profilite_profile *Profile;
    struct profilite_profile *Parent;
    PROFILITE_UINTMAX Start;
    PROFILITE_UINTMAX PrevElapsed;
};

struct profilite
{
    struct profilite_profile *Profiles;
    PROFILITE_UINTMAX Start;
    int Initialized;
    int Padding0;
};

/**
 * \defgroup lifecycle_functions Lifecycle Functions
 *
 * \brief Primary functions for initializing, creating, and reporting profiles.
 *
 * \details Depending on your use of \ref PROFILITE_AUTO_REPORT and
 * \ref scope_helpers, you may not use most or even any of these functions.
 *
 * \{
 */

/**
 * \brief Initialize the profiler.
 *
 * \details All code executed after this call returns, until Profilite_Report(),
 * will be included under the `<Root>` scope in the report.
 *
 * If called again, all previous profile data will be discarded and collection
 * will be restarted from that point onward.
 */
PROFILITE_STORAGE void Profilite_Init(void);

/**
 * \def Profilite_DeclareProfile(Id, Name, DataSize)
 *
 * \brief Declare a new profile with the given id.
 *
 * \details The declared profile is a static variable `ProfiliteProfile<Id>`,
 * stored within the `.profiler` section.
 *
 * \param[in] Id A scope-unique identifier for the given profile. Providing a
 * duplicate id will result in variable name conflicts.
 *
 * \param[in] Name A human-readable name for the profile. If null, the profile
 * will default to a unique generated name.
 *
 * \param[in] DataSize The amount of data this profile expects to process, in
 * bytes. This is used to report throughput. Pass zero to omit.
 */
#ifdef PROFILITE_SECTION
#define Profilite_DeclareProfile(Id, Name, DataSize)                                                                   \
    PROFILITE_SECTION(".profiler", "read, write")                                                                      \
    static struct profiler_profile ProfiliteProfile##Id = {                                                            \
        __FILE__, __FUNCTION__, __LINE__, Id, Name, DataSize, 0, 0, 0,                                                 \
    };
#endif

PROFILITE_STORAGE struct profilite_scope Profilite_BeginScope(struct profilite_profile *Profile);

PROFILITE_STORAGE void Profilite_EndScope(struct profilite_scope *Scope);

/**
 * \brief Print a report of the profiled scopes to stdout.
 *
 * \details When called, a profile of all scopes hit since the last
 * Profilite_Init() will be printed to stdout. Scopes not hit will not be
 * reported.
 *
 * This function may be called repeatedly, each time reporting the full profile
 * since the last init. To reset the profiler, call Profilite_Init().
 *
 * \bug The report's runtime is currently not excluded from subsequent reports.
 */
PROFILITE_STORAGE void Profilite_Report(void);

/** \} */

/**
 * \defgroup scope_helpers Profile Scope Helpers
 *
 * \brief Utilities of profiling until the end of a scope block.
 *
 * \{
 */

/**
 * \brief Profile the current scope.
 *
 * \details Place at the beginning of a scope block to profile its contents.
 * If placed toward the middle, only the contents after this function will be
 * included in the reported scope.
 *
 * May be repeated multiple times within a scope. Each following call will
 * report from itself to the end of scope.
 *
 * \warning This uses `__COUNTER__` to ensure no scope variable conflicts with
 * another. This may break poorly-designed libraries if they require contiguous
 * __COUNTER__ sequences.
 *
 * \warning This expands to multiple statements and cannot be placed within a
 * single-statement scope (single-statement `if`, `else`, `while`, or `for`).
 *
 * \param Name The name to register the scope under. While not required to be
 * unique, the report offers no mechanism to distinguish between two
 * identically-named scopes.
 *
 * \param DataSize The amount of bytes processed in this scope. If nonzero,
 * data size and bandwidth columns will be included in the report.
 */
#define Profilite_Scope(Name, DataSize)                                                                                \
    __attribute__((section(".profiler.scopes"))) static struct profile_scope ProfiliteScope##__COUNTER__ = {           \
        .Parent = };                                                                                                   \
    __attribute__((cleanup(Profile_End))) struct profile_scope ProfiliteScopeRef =                                     \
        Profile_Begin(_Profilite_NextBlockIndex(), Name, DataSize)

/**
 * \brief Profile the current scope.
 *
 * \details Alias of Profilite_ProfileScope(Name, 0).
 */
#define Profile_Scope(Name) Profile_Bandwidth(Name, 0)

/**
 * \brief Profile the current scope's data bandwidth.
 *
 * \details Alias of Profilite_ProfileScope("<function>:<line>", DataSize).
 */
#define Profile_Bandwidth(DataSize) Profilite_ProfileScope(_PROFILITE_SCOPE_CONCAT(__FUNCTION__, __LINE__), DataSize)

/**
 * @brief Profile the current function.
 *
 * \details Alias of Profilite_ProfileScope("<function>:<line>", 0).
 */
#define Profile_Func() Profile_Bandwidth(0)

/** \} */

/**
 * \brief Change the data size of the current scope.
 *
 * \details This can be used to profile data throughput when the total data
 * size isn't known ahead of time. Instead of declaring data size at scope
 * declaration, the stored size can be amended prior to the scope's end.
 *
 * \param DataSize The data size to amend the scope to, in bytes.
 */
void Profile_AmendDataSize(PROFILITE_UINTMAX DataSize);

#endif /** PROFILITE_HEADER */

#if PROFILITE_IMPLEMENTATION || defined(_PROFILITE_DOXYGEN)
#ifndef _PROFILITE_DOXYGEN
#undef PROFILITE_IMPLEMENTATION
#define PROFILITE_IMPLEMENTATION 0
#endif

#if (PROFILITE_AUTO_REPORT || defined(_PROFILITE_DOXYGEN)) && defined(PROFILITE_SECTION)
#ifdef _WIN32
PROFILITE_SECTION(".CRT$XCU", "read") static void (*PROFILITE_CONST ProfiliteInitCtor)(void) = Profilite_Init;
PROFILITE_SECTION(".CRT$XPU", "read") static void (*PROFILITE_CONST ProfiliteInitDstor)(void) = Profilite_Report;
#else /* TODO: __ELF__ */
PROFILITE_SECTION(".init_array", "read") static void (*PROFILITE_CONST ProfiliteInitCtor)(void) = Profilite_Init;
PROFILITE_SECTION(".fini_array", "read") static void (*PROFILITE_CONST ProfiliteInitDstor)(void) = Profilite_Report;
#endif
#endif

PROFILITE_STORAGE void
#if PROFILITE_TRADITIONAL
Profilite_Init()
#else
Profilite_Init(void)
#endif
{
}

PROFILITE_STORAGE struct profilite_scope
#if PROFILITE_TRADITIONAL
Profilite_BeginScope(Profile)
struct profilite_profile *Profile;
#else
Profilite_BeginScope(struct profilite_profile *Profile)
#endif
{
    struct profilite_scope Scope;
    Scope.Parent = Profile;
    return Scope;
}

PROFILITE_STORAGE void
#if PROFILITE_TRADITIONAL
    Profilite_EndScope(Scope) struct profilite_scope *Scope;
#else
Profilite_EndScope(struct profilite_scope *Scope)
#endif
{
    (void)Scope;
}

PROFILITE_STORAGE void
#if PROFILITE_TRADITIONAL
Profilite_Report()
#else
Profilite_Report(void)
#endif
{
}

#endif /** PROFILITE_IMPLEMENTATION */

#else /** !PROFILITE */

#define Profile_Bandwidth()
#define Profile_Scope()
#define Profile_Func()
#define Profile_AmendDataSize()

#define Profilite_Init()
#define Profilite_Report()

#endif /** PROFILITE */

#undef PROFILITE_CHECK_EMPTY
