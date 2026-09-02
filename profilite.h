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
 * \def PROFILITE
 *
 * \ingroup configuration
 *
 * \brief Enable the profiler.
 *
 * \details Overrides \ref PROFILITE_HEADER and \ref PROFILITE_IMPLEMENTATION.
 * If unset, all profiler macros and functions will be compiled out.
 *
 * This is both a **header** and **implementation** configuration. It is
 * recommended to define this in your build system so that it can be enabled
 * or disabled in only one location.
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

#if PROFILITE || defined(PROFILITE_DOXYGEN)

/**
 * \def PROFILITE_STORAGE
 *
 * \ingroup configuration
 *
 * \brief Configures the storage specifier on function prototypes and
 * definitions.
 *
 * \details Use this if you want to make Profilite functions static or inline.
 *
 * This is both a **header** and **implementation** configuration.
 *
 * Defaults to nothing.
 */
#ifndef PROFILITE_STORAGE
#define PROFILITE_STORAGE
#endif

/**
 * \def PROFILITE_TRADITIONAL
 *
 * \ingroup configuration
 *
 * \brief Switches definitions to use traditional K&R C syntax.
 *
 * \details Use this if you're, for some strange reason, compiling K&R C but
 * have `__STDC__` or `__STDC_VERSION__` defined.
 *
 * This is both a **header** and **implementation** configuration and should be
 * the same across all inclusions of this file.
 *
 * Defaults to 0 if __STDC__ or __STDC_VERSION__ are defined, 1 otherwise.
 */
#ifndef PROFILITE_TRADITIONAL
#if defined(__STDC__) || defined(__STDC_VERSION__) || defined(PROFILITE_DOXYGEN)
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

/**
 * \def PROFILITE_CONST
 *
 * \ingroup compiler_polyfills
 *
 * \brief Alias for `const`.
 *
 * \details May be redefined to disable const. Polyfilled on K&R C as empty.
 *
 * This is both a **header** and **implementation** configuration.
 */
#ifndef PROFILITE_CONST
#if PROFILITE_TRADITIONAL
#define PROFILITE_CONST
#else
#define PROFILITE_CONST const
#endif
#endif



/******************************************************************************\
|                                    HEADER                                    |
\******************************************************************************/



/**
 * \def PROFILITE_HEADER
 *
 * \ingroup configuration
 *
 * \brief Include the profiler's declarations.
 *
 * \details If set, declarations will be included. This macro is redefined to 0
 * after inclusion to act as a header guard.
 *
 * This is a **header** configuration, but in most cases, you will not need to
 * set it manually.
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

#if PROFILITE_HEADER || defined(PROFILITE_DOXYGEN)
#ifndef PROFILITE_DOXYGEN
#undef PROFILITE_HEADER
#define PROFILITE_HEADER 0
#endif

struct profilite_profile
{
    PROFILITE_CONST long ProfiliteProfileId;
};

struct profilite_scope
{
    struct profilite_profile *ProfiliteScopeProfile;
};

PROFILITE_STORAGE struct profilite_scope Profilite_BeginScope(struct profilite_profile *Profile);

PROFILITE_STORAGE int Profilite_EndScope(struct profilite_scope *Scope);

#endif /** PROFILITE_HEADER */



/******************************************************************************\
|                                IMPLEMENTATION                                |
\******************************************************************************/



/**
 * \def PROFILITE_IMPLEMENTATION
 *
 * \ingroup configuration
 *
 * \brief Include the profiler's definitions.
 *
 * \details If set, definitions will be included. This macro is redefined to 0
 * after inclusion to act as a header guard.
 *
 * This is an **implementation** configuration and should be set once per
 * project.
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

#if PROFILITE_IMPLEMENTATION || defined(PROFILITE_DOXYGEN)
#ifndef PROFILITE_DOXYGEN
#undef PROFILITE_IMPLEMENTATION
#define PROFILITE_IMPLEMENTATION 0
#endif

PROFILITE_STORAGE struct profilite_scope
#if PROFILITE_TRADITIONAL
Profilite_BeginScope(Profile)
struct profilite_profile *Profile;
#else
Profilite_BeginScope(struct profilite_profile *Profile)
#endif
{
    struct profilite_scope Scope;
    Scope.ProfiliteScopeProfile = Profile;
    return Scope;
}

PROFILITE_STORAGE int
#if PROFILITE_TRADITIONAL
Profilite_EndScope(Scope)
struct profilite_scope *Scope;
#else
Profilite_EndScope(struct profilite_scope *Scope)
#endif
{
    Scope = Scope;
    return 0;
}

#endif /** PROFILITE_IMPLEMENTATION */

#else /** !PROFILITE */

#define Profilite_BeginScope(Profile)
#define Profilite_EndScope(Scope)

#endif /** PROFILITE */

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
 */

/**
 * \defgroup compiler_polyfills Compiler Polyfill Macros
 *
 * \brief Macros for compiler- or version- specific operations.
 *
 * \details These are defined for MSVC, Clang, and GCC. Support for other
 * compilers must be configured by defining these polyfills prior to including
 * this file.
 */

/**
 * \defgroup lifecycle_functions Lifecycle Functions
 *
 * \brief Primary functions for initializing, creating, and reporting profiles.
 *
 * \details Depending on your use of \ref PROFILITE_AUTO_REPORT and
 * \ref scope_helpers, you may not use most or even any of these functions.
 */
