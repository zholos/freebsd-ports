--- unix/povconfig/syspovconfig_bsd.h
+++ unix/povconfig/syspovconfig_bsd.h
@@ -39,21 +39,23 @@
 #ifndef POVRAY_UNIX_SYSPOVCONFIG_BSD_H
 #define POVRAY_UNIX_SYSPOVCONFIG_BSD_H
 
-#include <unistd.h>
+#include <limits.h>
 
-#if defined(_POSIX_V6_LPBIG_OFFBIG) || defined(_POSIX_V6_LP64_OFF64) || defined(_POSIX_V6_ILP32_OFFBIG)
+#ifdef OFF_MAX
+#if OFF_MAX >= 0x7fffffffffffffffLL
     // `off_t` is at least 64 bits.
     // This variant of BSD provides large file support via the `lseek` function,
     // with file offsets having type `off_t`.
     #define POV_LSEEK(handle,offset,whence) lseek(handle,offset,whence)
     #define POV_OFF_T off_t
-#elif defined(_POSIX_V6_ILP32_OFF32)
+#else
     // `off_t` is at least 32 bits.
     // This variant of BSD does _not_ provide large file support via the `lseek` function.
     // Comment-out the following line to proceed anyway.
     #error "Image size will be limited to approx. 100 Megapixels. Proceed at your own risk."
     #define POV_LSEEK(handle,offset,whence) lseek(handle,offset,whence)
     #define POV_OFF_T off_t
+#endif
 #else
     // Unable to detect `off_t` size at compile-time.
     // This variant of BSD _may or may not_ provide large file support via the `lseek` function.
@@ -65,14 +67,11 @@
 
 /// @file
 /// @todo The POV_LONG stuff is just copied from the Posix settings; someone needs to verify universal BSD compatibility.
-#if defined(_POSIX_V6_LPBIG_OFFBIG) || defined(_POSIX_V6_LP64_OFF64)
+#if LONG_MAX >= 0x7fffffffffffffffLL
     // long is at least 64 bits.
     #define POV_LONG long
-#elif defined(_POSIX_V6_ILP32_OFFBIG) || defined(_POSIX_V6_ILP32_OFF32)
-    // long is 32 bits.
-    #define POV_LONG long long
 #else
-    // Unable to detect long size at compile-time, assuming less than 64 bits.
+    // long is 32 bits.
     #define POV_LONG long long
 #endif
 
