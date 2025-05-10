
#ifndef BEGE_STATIC_EXPORT_H
#define BEGE_STATIC_EXPORT_H

#ifdef BEGE_STATIC_STATIC_DEFINE
#  define BEGE_STATIC_EXPORT
#  define BEGE_STATIC_NO_EXPORT
#else
#  ifndef BEGE_STATIC_EXPORT
#    ifdef bege_static_EXPORTS
        /* We are building this library */
#      define BEGE_STATIC_EXPORT 
#    else
        /* We are using this library */
#      define BEGE_STATIC_EXPORT 
#    endif
#  endif

#  ifndef BEGE_STATIC_NO_EXPORT
#    define BEGE_STATIC_NO_EXPORT 
#  endif
#endif

#ifndef BEGE_STATIC_DEPRECATED
#  define BEGE_STATIC_DEPRECATED __declspec(deprecated)
#endif

#ifndef BEGE_STATIC_DEPRECATED_EXPORT
#  define BEGE_STATIC_DEPRECATED_EXPORT BEGE_STATIC_EXPORT BEGE_STATIC_DEPRECATED
#endif

#ifndef BEGE_STATIC_DEPRECATED_NO_EXPORT
#  define BEGE_STATIC_DEPRECATED_NO_EXPORT BEGE_STATIC_NO_EXPORT BEGE_STATIC_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BEGE_STATIC_NO_DEPRECATED
#    define BEGE_STATIC_NO_DEPRECATED
#  endif
#endif

#endif /* BEGE_STATIC_EXPORT_H */
