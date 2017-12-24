--- unix/povconfig/syspovconfig_bsd.h
+++ unix/povconfig/syspovconfig_bsd.h
@@ -39,16 +39,18 @@
 #ifndef POVRAY_UNIX_SYSPOVCONFIG_BSD_H
 #define POVRAY_UNIX_SYSPOVCONFIG_BSD_H
 
-#include <unistd.h>
+#include <limits.h>
 
-#if defined(_POSIX_V6_LPBIG_OFFBIG) || defined(_POSIX_V6_LP64_OFF64) || defined(_POSIX_V6_ILP32_OFFBIG)
+#ifdef OFF_MAX
+#if OFF_MAX >= 0x7fffffffffffffffLL
     // off_t is at least 64 bits
     #define lseek64(handle,offset,whence) lseek(handle,offset,whence)
-#elif defined(_POSIX_V6_ILP32_OFF32)
+#else
     // off_t is 32 bits
     // Comment-out the following line to proceed anyway.
     #error "Image size will be limited to approx. 100 Megapixels. Proceed at your own risk."
     #define lseek64(handle,offset,whence) lseek(handle,offset,whence)
+#endif
 #else
     // Unable to detect off_t size at compile-time; comment-out the following line to proceed anyway.
     #error "Image size may be limited to approx. 100 Megapixels. Proceed at your own risk."
@@ -57,14 +59,11 @@
 
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
 
