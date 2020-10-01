#ifndef MINECRAFT_BASE_H
#define MINECRAFT_BASE_H

#include <memory>
#include <filesystem>

using namespace std::string_literals;
namespace fs = std::filesystem;

/*
 *	Defining Macros
 */

/* Configuration Macros */
#if defined(NDEBUG)
	#define MC_RELEASE
#else
	#define MC_DEBUG
#endif

/* Platform Macros */
#if defined(_WIN32)
	#define MC_WINDOWS_OS
#elif defined(__linux__)
	#define MC_LINUX_OS
	#if defined(__ANDROID__)
		#define MC_ANDROID_OS
		#define MC_UNSUPPORTED_OS
	#endif
#elif defined(__APPLE__)
	#define MC_MAC_OS
	#define MC_UNSUPPORTED_OS
#else
	#define MC_UNKNOWN_OS
	#define MC_UNSUPPORTED_OS
#endif

/* Debug-break */
#if !defined(MC_UNSUPPORTED_OS) && defined(MC_DEBUG)

	#if defined(MC_WINDOWS_OS)
		#define MC_DEBUGBREAK() __debugbreak()
	#elif defined(MC_LINUX_OS)
		#include <csignal>
		#define MC_DEBUGBREAK() raise(SIGTRAP)
	#endif

#else
	#define MC_DEBUGBREAK()
#endif

/* Asserting and error */
#if defined(MC_DEBUG)
	#define MC_ASSERT(x, ...) if(!static_cast<bool>(x)) { MC_LOG_ERROR(__VA_ARGS__); MC_DEBUGBREAK(); }
	#define MC_ASSERT_WARN(x, ...)  if(!static_cast<bool>(x)) { MC_LOG_ERROR(__VA_ARGS__); }
	#define MC_ASSERT_ERROR(x, ...) if(!static_cast<bool>(x)) { MC_LOG_ERROR(__VA_ARGS__); }
	#define MC_ERROR(...) MC_LOG_ERROR(__VA_ARGS__); MC_DEBUGBREAK()
#else
	#define MC_ASSERT(x, ...)
	#define MC_ERROR(...)
#endif

/*
 * Defining Types
 */

using byte = char;
using ubyte = unsigned char;

template<typename T, size_t w, size_t h, size_t z>
using Array3D = std::array<std::array<std::array<T, w>,h>,z>;

/* Reference */
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ...Args>
constexpr Ref<T> CreateRef(Args ...args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

/* Atomic Reference */
template<typename T>
using AtomicRef = std::atomic_ref<T>;

/* Weak Reference */
template<typename T>
using WeakRef = std::weak_ptr<T>;

#endif //MINECRAFT_BASE_H
