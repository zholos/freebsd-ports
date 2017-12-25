--- vfe/unix/syspovconfig.h
+++ vfe/unix/syspovconfig.h
@@ -162,7 +162,8 @@
     #include <sys/param.h>
     #if defined(BSD)
         // BSD-style Unix detected.
-        #error BSD-style Unix detected, but not explicitly supported yet; proceed at your own risk.
+        #include <sys/wait.h> // for WEXITSTATUS
+        #define lseek64(handle,offset,whence) lseek(handle,offset,whence)
     #else
         // Not officially supported yet; comment-out the following line to try with default POSIX settings.
         #error Unix detected, but flavor not identified; proceed at your own risk.
