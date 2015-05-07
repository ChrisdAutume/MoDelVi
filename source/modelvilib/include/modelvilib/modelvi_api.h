#pragma once

#ifdef _MSC_VER
#   define MODELVI_API_EXPORT_DECLARATION __declspec(dllexport)
#   define MODELVI_API_IMPORT_DECLARATION __declspec(dllimport)
#elif __GNUC__
#	define MODELVI_API_EXPORT_DECLARATION __attribute__ ((visibility ("default")))
#	define MODELVI_API_IMPORT_DECLARATION __attribute__ ((visibility ("default")))
#else
#   define MODELVI_API_EXPORT_DECLARATION
#   define MODELVI_API_IMPORT_DECLARATION
#endif 

#ifndef MODELVI_STATIC
#ifdef MODELVI_EXPORTS
#   define MODELVI_API MODELVI_API_EXPORT_DECLARATION
#else
#   define MODELVI_API MODELVI_API_IMPORT_DECLARATION
#endif
#else
#   define MODELVI_API
#endif

#ifdef N_DEBUG
#   define IF_DEBUG(statement)
#   define IF_NDEBUG(statement) statement
#else
#   define IF_DEBUG(statement) statement
#   define IF_NDEBUG(statement)
#endif // N_DEBUG

// http://stackoverflow.com/questions/18387640/how-to-deal-with-noexcept-in-visual-studio
#ifndef NOEXCEPT
#   ifdef _MSC_VER
#       define NOEXCEPT
#   else
#       define NOEXCEPT noexcept
#   endif
#endif