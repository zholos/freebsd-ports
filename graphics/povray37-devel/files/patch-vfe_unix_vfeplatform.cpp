--- vfe/unix/vfeplatform.cpp
+++ vfe/unix/vfeplatform.cpp
@@ -50,6 +50,7 @@
 #ifdef HAVE_SYS_TIME_H
 # include <sys/time.h>
 #endif
+#include <sys/wait.h>
 
 // from directory "vfe"
 #include "vfe.h"
