--- source/core/math/randomsequence.h
+++ source/core/math/randomsequence.h
@@ -44,8 +44,6 @@
 namespace pov
 {
 
-using namespace pov_base;
-
 vector<int> RandomInts(int minval, int maxval, size_t count);
 vector<double> RandomDoubles(int minval, int maxval, size_t count);
 
