--- source/core/material/texture.cpp
+++ source/core/material/texture.cpp
@@ -59,6 +59,8 @@
 #include "core/material/warp.h"
 #include "core/support/imageutil.h"
 
+#include "backend/frame.h"
+
 #if defined(TRY_OPTIMIZED_NOISE)
     #include OPTIMIZED_NOISE_H
 #endif
