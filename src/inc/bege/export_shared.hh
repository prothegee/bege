
#ifndef BEGE_SHARED_EXPORT_H
#define BEGE_SHARED_EXPORT_H

#ifdef BEGE_SHARED_STATIC_DEFINE
#  define BEGE_SHARED_EXPORT
#  define BEGE_SHARED_NO_EXPORT
#else
#  ifndef BEGE_SHARED_EXPORT
#    ifdef bege_shared_EXPORTS
        /* We are building this library */
#      define BEGE_SHARED_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define BEGE_SHARED_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef BEGE_SHARED_NO_EXPORT
#    define BEGE_SHARED_NO_EXPORT 
#  endif
#endif

#ifndef BEGE_SHARED_DEPRECATED
#  define BEGE_SHARED_DEPRECATED __declspec(deprecated)
#endif

#ifndef BEGE_SHARED_DEPRECATED_EXPORT
#  define BEGE_SHARED_DEPRECATED_EXPORT BEGE_SHARED_EXPORT BEGE_SHARED_DEPRECATED
#endif

#ifndef BEGE_SHARED_DEPRECATED_NO_EXPORT
#  define BEGE_SHARED_DEPRECATED_NO_EXPORT BEGE_SHARED_NO_EXPORT BEGE_SHARED_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BEGE_SHARED_NO_DEPRECATED
#    define BEGE_SHARED_NO_DEPRECATED
#  endif
#endif

#endif /* BEGE_SHARED_EXPORT_H */
